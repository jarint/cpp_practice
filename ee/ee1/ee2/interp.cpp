/**
 * @file interp.cpp
 * @brief Cubic B-spline interpolatin on a 2D grid
 * 
 * Code for an empirical exercise that investigates the effect
 * of different compiler optimization levels on run-time performance.
 */

// minimal includes to keep profile output clean
#include <iostream>

using size_t = unsigned long;

// We'll use an N x N grid for interpolation
const size_t N = 64;

// a padding value to ensure we stay within bounds
const size_t PAD = 3;

// 2D to 1D index conversion
inline size_t ind(size_t row, size_t col) {
    return row * N + col;
}

// 1D cubic interpolation in a cell using an interpolating cubic B-spline,
// coefficients are in an array p.
double interp (double p[4], double t) {
    return p[1] + 0.5 * t*(p[2] - p[0] + t*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + t*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

// interpolate at a point (x,y) within the [0,N-1]^2 grid
double  interp2D( const double grid[], double x, double y) {
    // determine base cell index    
    int I = x;
    int J = y;

    // offsets within base cell
    double tx = x - I;
    double ty = y - J;

    // fill up a 4x4 grid around the base cell
    double p[4][4];
    for(int i = 0; i <= 3; i++) 
        for(int j = 0; j <= 3; j++) 
            p[i][j] = grid[ind(J+j-1, I+i-1)];
            
    // separable interpolation.
    double result[4];
    for(size_t i = 0; i <=3; i++) 
        result[i] = interp(p[i], ty);
    return interp(result, tx);
}


int main() {
    // fill NxN grid with ones. Interpolating anywhere inside the grid
    // should yield 1. 
    double grid[N*N];
    for( size_t i = 0; i < N*N; i++ )
        grid[i] = 1.0;

    // perform a number of interpolations
    // on a higher resolution grid
    // NUM is the number of partititions in one dimension,
    // so in 2D, the total number of points will be NUM^2.
    size_t NUM = 1e4;
    //size_t NUM = 4;
    double step = (N-1-2.0*PAD) / NUM;
    double ctr = 0.0;
    for(double x = PAD; x < N-1-PAD; x+= step ) {
        for(double y = PAD; y < N-1-PAD; y+= step ) {
            ctr += interp2D(grid, x, y);
        }
    }
    // each interpolated value is 1, so result should be NUM^2 (modulo precision)
    std::cout << ctr << std::endl;
}