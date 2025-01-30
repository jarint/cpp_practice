#include <iostream>
#include <climits>
#include <limits>
#include <cfloat>
#include <cstdint>


// Booleans
bool b1 = 5; // ok, b1 becomes true
bool b2 {5}; // error: {}-initializer prevents narrowing
bool b3 {5!=0}; // this is ok, b3 becomes true
bool x = b1 + b2; // b1 + b2 is 2, so x becomes true
bool y = b1 || b2; // b1 || b2 is true, so y becomes true


// Characters
// Write the digits 0--9 to cout.
void digits() {
    for(int i=0; i < 10; i++) {
        cout << static_cast<char>('0'+i);
    }
}

// Beware of signedness
unsigned char uc {255}; // corresponds to 0xFF
signed char sc {uc}; // What will happen here? Sure we want to do this?
cout << (int)sc << endl;


