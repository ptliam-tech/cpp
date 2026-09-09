# Constructors and Destructors    

## Key points  

### Constructors  
- Same name as class, no return type  
- Called automatically when object is created  
- Can be overloaded  
- Type: Default, Parameterized, Copy  
- Initialization list vs assignment in constructor body  
- Cannot be virtual  

### Destructors  
- Name: ~ClassName()  
- No parameters, no return type  
- Only one destructor per class  
- Called when object goes out of scope  
- Should be virtual in base clase if inheritance is used  
- Used for cleanup (deallocate memory, close files, etc.)  

## Important notes  

### Initialization List: Why more Efficient?  

#### Performance Comparison  

**Without Initialization List (Assignment in Body)**  
```cpp  
class Student {
    string name;
    int age;
public:
    Student(string n, int a) {
        name = n;
        age = a;
    }
};
```  

**What happens behind the scenes**  
```  
Step 1: Default constructor called AUTOMATICALLY 
        name = string();    // Empty string create  
        age = int();        // Default int  
Step 2: Assignment in constructor body  
        name = n;           // Destroy old. assign new  
        age = a;
Step 3: Cleanup (for complex types)  

Total operation for 'name': 3 steps
```  

**With Initialization List**  
```cpp  
class Student {
    string name;
    int age;
public:
    Student(string n, int a) : name(n), age(a) {
        // Member ALREADY initialized
    }   
};
```  
**What happens behind the scenes**  
```  
Step 1: Direct construction with value  
    name = string(n);    // Construct directly  
    age = a;             // Direct initialization  

Total operation for 'name': 1 step 
```  
**Impact:** For complex types (string, vector, objects), initialization list is significantly faster!  

### Object Creation Timeline  

#### Understanding "Khi nào thì các biến tồn tại?"  

**Class = mô tả kiểu dữ liệu (No memory allocated)**  
```cpp  
class Student {
    string name;    // Just a declaration, no memory yet!  
    int age;        // Just a declaration, no memory yet!
}

// Tại thời điểm này chưa có đối tượng tồn tại  
```  

**Object Creation Process**  
```  
Step 1: Memory Allocation  
    Memory for obj <- Space allocated
Step 2: Initialization List Excutes  
    Memory for obj 
    - name: value  <- Initialized directly  
    - age: value   <- Initialized directly 
Step 3: Constructor Body Executes  
    (Additional logic if any)  
Step 4: Object Ready  
    Variables now exist and are usable  
```  

### Key Interview Points  

**Q: Why is initialization list more efficient?**  
> It directly constructs members with given values in one step, whereas assignment first default-constructs members, then assigns new values (two steps). This matters especially for complex types like strings, vectors and objects.  

**Q: When do member variables come into existence?**  
> Member variables come into existence when an object is created. Memory is allocated, then the initialization list runs to initialize members, then the constructor body executes. Before object creation, the class is just a blueprint.  

**Q: When MUST you use initialization list?**  
> - Const member variables (Cannot be assigned after creation)  
```cpp  
class Person {
    const int age;
public:
    Person(int a) : age(a) {

    }
};

class Person {
    const int age;

public:
    Person(int a) {
        age = a; // Error 
    }
};
```  
> - Reference member variables (must be initialized)  
```cpp  
int &b; // Error -> tham chiếu khi khởi tạo cần bind ngay tới 1 dối tượng nào đó

int a;
int &b = a; // TRUE

class Person {
    std::string& name;
    int age;
public:
    Person(std::string& n, int a) : name(n), age(a) {

    }
};
```  
> - Member objects without default constructors  
```cpp  
class Engine {
    int power;
public:
    Engine(int p) {

    }
};

class Car {
    Engine engine;
public:
    Car(int power) : engine(power) {

    }
};
```  
> - Calling base class constructors (inheritance)  
```cpp  
class Animal {
    std::string name;
public:
    Animal(string n) {
        std::out << "Animal constructor!\n";
    }
}; 

class Dog : public Animal {
public:
    Dog(std::string n) : Animal(n) {

    }
}  
```  
### Explicit Keywork: Preventing Implicit Conversions  

#### The problem: Implicit Type Conversion  

**Without `explicit` keywork**  
```cpp  
class Distance {
    int meters;
public:
    Distance(int m) : meters(m) {

    }
};

Distance d = 100; // This WORK but unintended -> int implicitly converted (ngầm định chuyển đổi) to Distance  
```  

**What C++ compiler does automatically**  
```  
Step 1: Sees you want Distance object  
Step 2: Sees you provided int (100)  
Step 3: Finds constructor Distance(int)  
Step 4: Automatically calls Distance(100)  
Step 5: Distance d = 100; becomes Distance d = Distance(100);  
```  

This is called **Implicit type conversion** - compiler does it automatically without asking you!  

#### Why this can be dangerous  

**Real-work example**  
```cpp  
class BankAccount {
    double balance;
public:
    BankAccount(double bal) : balance(bal) {}
};

void withDraw(BankAccount acc) {
    // Process withdrawal from account  
}

withDraw(5000); // DANGER! What does this mean?
```  

**The problem**  
- Did you mean account ID `5000`?  
- Or create new account with balance 5000?  
- Code compiles but does WRONG thing!  
- C++ sliently creates temporary `BankAccount(5000)` - **BUG!**  

#### The solution: `explicit` Keywork  

```cpp  
class Distance {
    int meters;
public:
    explicit Distance(int m) : meters(m) {

    }
};

Distance d(100); // OK
Distance d = Distance(100) // OK - Explicit conversion 
Distance d = 100; // ERROR! Implicit conversion blocked
```  

- Explicit does:  
    - Tell compiler: Don't automatically convert for me!  
    - Forces programmer: Be explicit about what you want!  
    - Prevents bugs: No accidental conversions  

#### When to use `explicit`  
- Make constructors `explicit` by default. Only remove it if you have a good reason.  

#### Exceptions (Rare cases)  
Some standard library types intentionally allow implicit conversion:  
```cpp  
std::string s = "hello"; // char* -> string

std::complex<double> c = 3.14; // double -> complex (makes sense!)
```  

#### Interview Answer  

**Q: What is the `explicit` keyword and when should you use it?**  

**A:** The `explicit` keyword prevents single-parameter constructors from being used for implicit type conversions.  

- **Without `explicit`:** `Distance d = 100;` works (compiler silently converts int → Distance)  
- **With `explicit`:** `Distance d = 100;` gives compile error, must use `Distance d(100);`  

**Why use it?** Prevents accidental bugs from unintended type conversions. Makes code intentions clear and compiler catches mistakes at compile-time.  

**Best practice:** Make ALL single-parameter constructors `explicit` unless you specifically want implicit conversion. It's the safe default in modern C++.  

**Think of `explicit` as a safety belt** - always wear it! 🔒  


