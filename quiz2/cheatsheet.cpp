#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <algorithm> // for swap
#include <map>
#include <numeric>   // (optional: for accumulate, not used yet)
#include <functional> // (optional: for bind, not used yet)
#include <iterator>   // for iterators
#include <algorithm>  // REQUIRED for count_if, transform
#include <iomanip> // for std::setw, optional for pretty output
#include <array>     // for std::array
#include <stdexcept> // for std::runtime_error

using namespace std;

void iterator_example() {
    cout << "=== Iterator Example ===" << endl;
    list<string> courses = {"CPSC331", "CPSC355", "CPSC365"};
    string val = "UPDATED";

    auto it1 = courses.begin(); // mutable iterator
    auto it2 = courses.rbegin(); // reverse iterator (not used in assignment, just declared)
    auto it3 = courses.cbegin(); // const iterator (not used in assignment, just declared)

    cout << "Original courses list:" << endl;
    for (const auto& c : courses) cout << c << " ";
    cout << endl;

    while (it1 != courses.end()) {
        *it1 = val;
        ++it1;
    }

    cout << "After assigning 'UPDATED' using iterator:" << endl;
    for (const auto& c : courses) cout << c << " ";
    cout << endl;
}

void assignment_and_swap_example() {
    cout << "\n=== Assignment and Swap Example ===" << endl;

    array<int, 5> a1 = {0, 1, 2, 3, 4};
    array<int, 5> a2 = {0}; // all elements initialized to 0
    a2 = a1;

    cout << "Array a2 after assignment from a1: ";
    for (int n : a2) cout << n << " ";
    cout << endl;

    list<string> names;
    vector<const char*> old = {"a", "b", "c"};
    names.assign(old.cbegin(), old.cend());

    cout << "List names after assign from vector<const char*>: ";
    for (const auto& name : names) cout << name << " ";
    cout << endl;

    vector<int> v1 = {0, 1, 2};
    vector<int> v2 = {3, 4, 5, 6};

    cout << "Before swap:\n v1: ";
    for (int n : v1) cout << n << " ";
    cout << "\n v2: ";
    for (int n : v2) cout << n << " ";
    cout << endl;

    v1.swap(v2); // or swap(v1, v2)

    cout << "After swap:\n v1: ";
    for (int n : v1) cout << n << " ";
    cout << "\n v2: ";
    for (int n : v2) cout << n << " ";
    cout << endl;
}

void insertion_deletion_example() {
    cout << "\n=== Insertion Example ===" << endl;

    vector<string> v = {"a", "b", "c"};
    v.insert(v.begin() + 2, "0"); // {"a", "b", "0", "c"}
    v.insert(v.end(), 3, "x");    // {"a", "b", "0", "c", "x", "x", "x"}

    cout << "Vector after insertions: ";
    for (const auto& s : v) cout << s << " ";
    cout << endl;
}

void erase_example() {
    cout << "\n=== Erase Example (remove odd numbers from list) ===" << endl;

    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it % 2) {
            it = lst.erase(it); // erase returns the next valid iterator
        } else {
            ++it;
        }
    }

    cout << "List after erasing odd numbers: ";
    for (int n : lst) cout << n << " ";
    cout << endl;
}

void associative_container_example() {
    cout << "\n=== Associative Container Example (map<string, size_t>) ===" << endl;

    vector<string> vec = {"5", "5", "6", "0", "1", "2", "0", "2", "3", "4"};
    map<string, size_t> wc;

    cout << "Inserting words from vector into map and counting occurrences..." << endl;
    for (auto& s : vec) {
        ++wc[s]; // default-inserts 0 and increments if key doesn't exist
    }

    // Add new entry using insert (insert doesn't overwrite existing keys)
    wc.insert({"10", 3});

    // Print the map contents using a range-based loop
    cout << "Contents of word count map:\n";
    for (const auto& w : wc) {
        cout << "  " << w.first << " --> " << w.second << endl;
    }

    // Find and print specific key
    string key = "10";
    auto it = wc.find(key);
    if (it != wc.end()) {
        cout << "Found key \"" << key << "\" with count: " << it->second << endl;
    } else {
        cout << "Key \"" << key << "\" not found." << endl;
    }
}

void algorithm_examples() {
    cout << "\n=== Algorithms: count_if and transform ===" << endl;

    vector<int> vec = {0,1,2,3,4,5,6,7,8,9};

    // count_if: count how many elements are odd
    int count = count_if(vec.cbegin(), vec.cend(), [](int i){ return i % 2 != 0; });
    cout << "Number of odd elements in vec: " << count << endl;

    // transform: set all odd elements to 0, leave even as-is
    cout << "Original vector: ";
    for (int i : vec) cout << i << " ";
    cout << endl;

    transform(vec.cbegin(), vec.cend(), vec.begin(),
              [](int i) { return i % 2 ? 0 : i; });

    cout << "After transform (odds replaced with 0): ";
    for (int i : vec) cout << i << " ";
    cout << endl;
}

// Class vs Struct Example
class Date {
    // these are private by default
    int d, m, y;
    static Date default_date; // static member

public:
    // Constructors
    // We can define multiple constructors as long as they differ in their argument types.
    Date(int dd, int mm, int yy) : d{dd}, m{mm}, y{yy} {}
    Date(int dd, int mm) : d{dd}, m{mm}, y{2025} {}
    Date(int dd) : d{dd}, m{3}, y{2025} {}
    Date() : d{1}, m{1}, y{2000} {}
    Date(const char* s) : d{1}, m{1}, y{1999} {
        cout << "Constructed from string (dummy implementation): " << s << endl;
    }

    void add_year(int n) { y += n; }
    void print() const { cout << "Date: " << d << "/" << m << "/" << y << endl; }

    static void set_default(int dd, int mm, int yy) {
        default_date = Date{dd, mm, yy};
    }

    static void print_default() {
        cout << "Default Date: ";
        default_date.print();
    }
};

Date Date::default_date {1, 1, 2000}; // Definition outside class

// Equivalent struct version
struct Date1 {
private:
    int d, m, y;
public:
    Date1(int dd, int mm, int yy) : d{dd}, m{mm}, y{yy} {}
    void add_year(int n) { y += n; }
    void print() const { cout << "Date1: " << d << "/" << m << "/" << y << endl; }
};

// Class with explicit constructor - always runs?
class X {
    private:
        int m; // one private member
    public:
        explicit X(int i = 0) : m{i} {
            cout << "X constructed with value: " << m << endl;
        }
};

void class_examples() {
    cout << "\n=== Class and Struct Examples ===" << endl;

    // Class vs Struct instantiation
    Date d1(25, 2, 2025);
    Date d2 {25, 2, 2025};
    d1.print();
    d2.print();

    Date d3(15);        d3.print();
    Date d4;            d4.print();
    Date d5("March 27, 2025");

    Date::print_default();
    Date::set_default(7, 4, 1776);
    Date::print_default();

    Date1 s1 {1, 1, 2022};
    s1.add_year(1);
    s1.print();

    cout << "\n=== Explicit Constructor Example ===" << endl;

    X x1(365);  // OK
    //X x2 = 365; // ❌ Error if uncommented: implicit conversion is disallowed "remember implicit conversions"
    X x3{};     // OK (default arg)
    X x4{365}; // Also good
}

void initialization_examples() {
    cout << "\n=== Object Initialization Examples ===" << endl;

    // Vector initialization examples
    vector<int> vec1 {365};   // vector with one element: 365
    vector<int> vec2(365);    // vector with 365 elements, each initialized to 0

    cout << "vec1 (initializer list): ";
    for (int x : vec1) cout << x << " ";
    cout << "\nvec2 (size-based constructor): size = " << vec2.size() << ", first element = " << vec2[0] << endl;

    // Structs: memberwise vs constructor-based initialization
    struct S1 {
        int a, b;
    };

    struct S2 {
        int a, b;
        S2(int aa = 0, int bb = 0) : a{aa}, b{bb} {}
    };

    // S1 x(1, 2); // ❌ Would cause error: no constructor
    S1 y {1, 2};    // ✅ OK: aggregate memberwise init
    cout << "S1 y initialized with memberwise init: a = " << y.a << ", b = " << y.b << endl;

    S2 s1(1, 2);    // ✅ OK: uses constructor
    S2 s2 {1, 2};   // ✅ OK: uses constructor (brace syntax)

    S2 s3{}; // default args in constructor.  can't use S2 s3();

    cout << "S2 s1: a = " << s1.a << ", b = " << s1.b << endl;
    cout << "S2 s2: a = " << s2.a << ", b = " << s2.b << endl;
    cout << "S2 s3: a = " << s3.a << ", b = " << s3.b << endl;
}

class Club {

    // class members
    string name;
    vector<string> members;
    Date founded;

public:
    Club(const string& n, Date fd)
        : name{n}, members{}, founded{fd} { // member-eise initializer list
        cout << "Club constructor executed with member initializer list." << endl;
    }

    // Constructor with members
    Club(const string& n, const vector<string>& m, Date fd)
        : name{n}, members{m}, founded{fd} {
        cout << "Club constructor (with members) executed.\n";
    }

    // added for printing
    void print() const {
        cout << "Club: " << name << "\nFounded: ";
        founded.print();
        cout << "Members count: " << members.size() << endl;
    }
};

void member_initializer_list_example() {
    cout << "\n=== Member Initializer List Example ===" << endl;
    Date d {15, 3, 2025}; // reuse Date class from earlier
    Club c("Chess Club", d);
    vector<string> member_names = {"Alice", "Bob", "Charlie"};
    Club c2("Chess Club 2", member_names , d);
    c.print();
    c2.print();
};


class Matrix {
    std::array<int, 2> dim;
    double* elem;

public:
    Matrix(int d1, int d2)
        : dim{d1, d2}, elem{new double[d1 * d2]} {
        cout << "Constructor: Matrix(" << d1 << ", " << d2 << ")\n";
        for (size_t i = 0; i < size(); ++i) elem[i] = i;
    }

    size_t size() const { return dim[0] * dim[1]; }

    // Copy constructor
    Matrix(const Matrix& m)
        : dim{m.dim}, elem{new double[m.size()]} {
        cout << "Copy Constructor\n";
        copy(m.elem, m.elem + m.size(), elem);
    }

    // Copy assignment
    Matrix& operator=(const Matrix& m) {
        cout << "Copy Assignment\n";
        if (dim[0] != m.dim[0] || dim[1] != m.dim[1]) {
            throw runtime_error("Size mismatch in Matrix =");
        }
        copy(m.elem, m.elem + m.size(), elem);
        return *this;
    }

    // Move constructor
    Matrix(Matrix&& m)
        : dim{m.dim}, elem{m.elem} {
        cout << "Move Constructor\n";
        m.dim = {0, 0};
        m.elem = nullptr;
    }

    // Move assignment
    Matrix& operator=(Matrix&& m) {
        cout << "Move Assignment\n";
        swap(dim, m.dim);
        swap(elem, m.elem);
        return *this;
    }

    ~Matrix() {
        cout << "Destructor (" << dim[0] << "x" << dim[1] << ")\n";
        delete[] elem;
    }

    void print() const {
        cout << "Matrix [" << dim[0] << "x" << dim[1] << "]: ";
        for (size_t i = 0; i < size(); ++i) {
            cout << elem[i] << " ";
        }
        cout << endl;
    }
};

void matrix_examples() {
    cout << "\n=== Matrix Copy and Move Examples ===\n";

    Matrix m1(2, 3);
    m1.print();

    cout << "\n-- Copy Construct m2 from m1 --\n";
    Matrix m2 = m1;
    m2.print();

    cout << "\n-- Copy Assign m3 = m1 --\n";
    Matrix m3(2, 3);
    m3 = m1;
    m3.print();

    cout << "\n-- Move Construct m4 from temporary Matrix --\n";
    Matrix m4 = Matrix(2, 3);
    m4.print();

    cout << "\n-- Move Assign m5 = temporary Matrix --\n";
    Matrix m5(2, 3);
    m5 = Matrix(2, 3);
    m5.print();
}

class SmallInt {
    int val;

public:
    SmallInt(int i = 0) : val{i} {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad value");
        cout << "Constructed SmallInt(" << val << ")\n";
    }

    // Conversion operator to int
    operator int() const {
        cout << "Conversion operator called (to int)\n";
        return val;
    }

    // Pre-increment
    SmallInt& operator++() {
        cout << "Pre-increment ++SmallInt\n";
        ++val;
        return *this;
    }

    // Post-increment
    SmallInt operator++(int) {
        cout << "Post-increment SmallInt++\n";
        SmallInt temp = *this;
        val++;
        return temp;
    }

    void print() const {
        cout << "SmallInt value: " << val << endl;
    }
};

class Printer {
    char delim {'\t'};
    ostream& os {cout};

public:
    Printer() = default;
    Printer(ostream& out, char sep) : delim{sep}, os{out} {}

    void operator()(const string& s) const {
        os << s << delim;
    }
};

void select_operators_example() {
    cout << "\n=== Operator Overloading Examples ===" << endl;

    SmallInt si {4};
    si.print();

    cout << "--> Expression: si = si + 3;" << endl;
    si = si + 3;  // Calls operator int() for both operands

    si.print();

    cout << "--> ++si;" << endl;
    ++si;
    si.print();

    cout << "--> si++;" << endl;
    si++;
    si.print();

    cout << "\n-- Function Object: Printer --" << endl;
    vector<string> vec = {"one", "two", "three"};
    for_each(vec.cbegin(), vec.cend(), Printer{cout, ' '});
    cout << endl;

    cout << "\n-- Lambda Function (same as Printer) --" << endl;
    for_each(vec.cbegin(), vec.cend(), [](const string& s) {
        cout << s << " ";
    });
    cout << endl;
}


class Vector2; // forward declaration

class Matrix2 {
    float* m;
    int rows, cols;

public:
    Matrix2(int r, int c)
        : rows{r}, cols{c}, m{new float[r * c]} {
        cout << "Matrix2 constructor [" << r << "x" << c << "]\n";
        for (int i = 0; i < r * c; ++i)
            m[i] = i + 1; // dummy values
    }

    ~Matrix2() {
        delete[] m;
        cout << "Matrix2 destroyed\n";
    }

    void print() const {
        cout << "Matrix2:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << m[i * cols + j] << " ";
            cout << endl;
        }
    }

    friend Vector2 operator*(const Matrix2&, const Vector2&);
};

class Vector2 {
    float* v;
    int size;

public:
    Vector2(int s)
        : size{s}, v{new float[s]} {
        cout << "Vector2 constructor [size = " << s << "]\n";
        for (int i = 0; i < s; ++i)
            v[i] = i + 1; // dummy values
    }

    ~Vector2() {
        delete[] v;
        cout << "Vector2 destroyed\n";
    }

    void print() const {
        cout << "Vector2:\n";
        for (int i = 0; i < size; ++i)
            cout << v[i] << " ";
        cout << endl;
    }

    friend Vector2 operator*(const Matrix2&, const Vector2&);
};

Vector2 operator*(const Matrix2& mat, const Vector2& vec) {
    cout << "Friend operator*: Matrix2 * Vector2\n";

    if (mat.cols != vec.size) {
        throw runtime_error("Size mismatch in Matrix2 * Vector2");
    }

    Vector2 result(mat.rows);
    for (int i = 0; i < mat.rows; ++i) {
        result.v[i] = 0;
        for (int j = 0; j < mat.cols; ++j) {
            result.v[i] += mat.m[i * mat.cols + j] * vec.v[j];
        }
    }
    return result;
}

void friend_function_example() {
    cout << "\n=== Friend Function Example ===\n";

    Matrix2 m(2, 3);
    Vector2 v(3);

    m.print();
    v.print();

    Vector2 result = m * v;
    cout << "Result of Matrix2 * Vector2:\n";
    result.print();
}

struct A {
    A(int i) { cout << "A constructed with " << i << endl; }
    ~A()     { cout << "A destroyed\n"; }
};

struct B {
    B(int i) { cout << "B constructed with " << i << endl; }
    ~B()     { cout << "B destroyed\n"; }
};

struct Derived1 : A {
    B b;
    Derived1(int i) : A{i}, b{i + 1} {
        cout << "Derived1 constructed with " << i << endl;
    }
    // nested calls on both struct destroyers
    ~Derived1() {
        cout << "Derived1 destroyed\n";
    }
};

void inheritance_construction_example() {
    cout << "\n=== Inheritance Construction/Destruction Order ===\n";
    Derived1 d(10);
}

struct Base2 {
    int b;
    Base2(int val = 0) : b{val} {
        cout << "Base2 constructed\n";
    }
    Base2(const Base2& other) : b{other.b} {
        cout << "Base2 copied\n";
    }
};

struct Derived2 : Base2 {
    int d;
    Derived2(int val = 0) : Base2{val}, d{val + 100} {
        cout << "Derived2 constructed\n";
    }
    Derived2(const Derived2& other) : Base2{other}, d{other.d} {
        cout << "Derived2 copied\n";
    }
};

void slicing_example() {
    cout << "\n=== Slicing Example ===\n";
    Derived2 d(42);
    Base2 b = d; // slicing: only Base2 part is copied
    cout << "b.b = " << b.b << endl;
}

struct B2 {
    int x;
    B2(int i) : x{i} {
        cout << "B2 constructed with " << i << endl;
    }
    B2(const B2& other) : x{other.x} {
        cout << "B2 copied\n";
    }
};

struct BB2 : B2 {
    B2 b;

    // i+ 1 = 6
    BB2(int i) : B2{i}, b{i + 1} {
        cout << "BB2 constructed\n";
    }

    BB2(const BB2& other) : B2{other}, b{other.b} {
        cout << "BB2 copied\n";
    }
};

void copy_construction_in_hierarchy_example() {
    cout << "\n=== Copy Construction in Derived Hierarchy ===\n";
    BB2 a(5);
    BB2 b = a;
    cout << "b.x = " << b.x << ", b.b.x = " << b.b.x << endl;
}


class Employee {
protected:
    string first_name, family_name;
    int department;

public:
    Employee(const string& name, int dept)
        : first_name{name}, family_name{"(last)"}, department{dept} {
        cout << "Employee constructed\n";
    }

    virtual void print() const {
        cout << "Employee: " << family_name << "\tDept: " << department << endl;
    }

    virtual ~Employee() {
        cout << "Employee destroyed\n";
    }
};

class Manager : public Employee {
    list<Employee*> group;
    int level;

public:
    Manager(const string& name, int dept, int lvl)
        : Employee(name, dept), level{lvl} {
        cout << "Manager constructed\n";
    }

    void print() const override {
        Employee::print(); // call base print
        cout << "\tManager Level: " << level << endl;
    }

    ~Manager() {
        cout << "Manager destroyed\n";
    }
};

void virtual_function_example() {
    cout << "\n=== Virtual Function Example ===\n";

    Employee* e1 = new Employee("Alice", 101);
    Employee* e2 = new Manager("Bob", 102, 2);

    e1->print(); // calls Employee::print
    e2->print(); // calls Manager::print

    delete e1; // correctly calls Employee destructor
    delete e2; // correctly calls Manager then Employee destructor due to virtual
}

class Shape {
public:
    virtual void rotate(int degrees) = 0;
    virtual void draw() const = 0;
    virtual bool is_closed() const = 0;
    virtual ~Shape() {
        cout << "Shape destroyed\n";
    }
};

// asbtact class 
class Circle : public Shape {
    int angle = 0;
public:
    void rotate(int degrees) override {
        angle = (angle + degrees) % 360;
        cout << "Circle rotated to " << angle << " degrees\n";
    }

    void draw() const override {
        cout << "Drawing a Circle\n";
    }

    bool is_closed() const override {
        return true;
    }

    ~Circle() {
        cout << "Circle destroyed\n";
    }
};

void abstract_class_example() {
    cout << "\n=== Abstract Class Example ===\n";

    Shape* s = new Circle();
    s->draw();
    s->rotate(90);
    cout << "Is closed: " << boolalpha << s->is_closed() << endl;
    delete s;
}




int main() {
    iterator_example();
    assignment_and_swap_example();
    insertion_deletion_example();
    erase_example();
    associative_container_example();
    algorithm_examples();
    class_examples();
    initialization_examples();       
    member_initializer_list_example();
    matrix_examples();
    select_operators_example();
    friend_function_example();
    inheritance_construction_example();
    slicing_example();
    copy_construction_in_hierarchy_example();
    virtual_function_example();      // <--- Add this
    abstract_class_example();        // <--- Add this

    return 0;
}
