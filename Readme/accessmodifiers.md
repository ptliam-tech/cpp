# C++ Access Modifiers & Access Control
## Quyền mặc định  
- Struct: public by default  
- Class: private by default  

## Access vs Visibility  

- **Visibility**: Preprocessing + early compilation -> Can compilier see the name ?  
- **Access**: Compilation -> Can you see this member ?  

## Friend Mechanism

- **Important**: Freind không phải từ khóa chỉ định quyền truy cập  
- Friend là 1 cơ chế cấp phát quyền truy cập riêng biệt  

```cpp  
class Box {
private:
    int secret = 42;

    friend void printSecret(const Box& b);
    friend class BoxPrinter;
};

void printsecret(const Box& b) {
    cout << "Secret: " << b.secret << endl; // được truy cập
}

class BoxPrinter {
public:
    void printBox(Box& b) {
        cout << "Secret: " << b.secret << endl;
    } 
}
```  

## When to use friend  
- Operator overloading (`operator<<`, `operator+`)  
```cpp
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n) , age(a) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Name: " << p.name
       << ", Age: " << p.age;

    return os;
}

int main() {
    Person p("Lam", 25);

    std::cout << p << std::endl;

    return 0;
}
```  
- 2 class có mối quan hệ chặt chẽ như iterator và container: container cung cấp data và điểm bắt đầu, kết thúc. Iterator cung cấp cách duyệt và truy cập phần tử để lấy data.  
- Hàm factory cần truy cập private constructors  
```cpp
class Car {
private:
    int speed;

    Car(int s) {
        this-> speed = s;
    }

    //friend Car* createCar(int speed);
    friend Car createCar(int speed);
public:
    void print() const {
        std::cout << "Speed: " << speed << '\n';
    }
}; 
Car createCar(int speed) {
    if(speed < 0) {
        throw std::invalid_argument("Speed cannot be negative");
    }
    return Car(speed);
}

int main() {
    try {
        Car car1 = createCar(-10);
        car1.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Car1 can't create! " << e.what() << std::endl;
    }
    try {
        Car car2 = createCar(100);
        car2.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Car2 can't create! " << e.what() << std::endl;
    }
    
    return 0;
}
```  
## Inheritance & Access Control  

### Inheritance specifiers  

```cpp
clase Base{
public: int pub;
protected: int prot;
private: int priv;
};

class D1 : public Base {
    // pub -> public
    // prot -> protected
    // priv -> not accessible
};

class D2 : protected Base {
    // pub -> protected
    // prot -> protected
    // priv -> not accessible
};

class D3 : private Base {
    // pub -> private  
    // prot -> private
    // priv -> not accessible
};
```  
# Re-exposing Members

```cpp  
class Derived : private Base {
public:
    using Base::pub; // Make Base::pub public again in Derived
}  
```  

## Protected Access Rule
- Class con có thể truy cập vào protected members chỉ khi nó thuộc đối tượng của class con đó chứ không phải thông qua đối tượng của class cha

```cpp
class Base {
protected:
    int x = 0;
} 

class Derived : public Base {
    void ok(Derived& d) {
        d.x = 1; // ok: d is Derived
    }

    void bad(Base& b) {
        b.x = 2; // Error: b is base
    }

    void bad(Base* b) {
        b->x = 2; // Error
    }
}
```  

### Tại sao cần protected access rule của c++
- Tránh trường hợp có 2 class con kế thừa cùng 1 class base có thể truy cập và sửa đổi member protected của nhau thông qua class cha  
```cpp
class Base {
protected: 
    void dangerousOperation() {}
};

class SafeDerived : public Base {

};

class EvilDeribed : public Base {
public:
    void hackOtherDerived(Base &b) {
        b.dangerousOperation();
        // ❌ Not allowed:
        // b.dangerousOperation();

        // C++ prevents EvilDerived from accessing
        // protected members through an arbitrary Base object.
    }
};

int main () {
    SafeDerived safe;
    EvilDerived evil;

    evil.hackOtherDerived(safe);  // ❌ dangerousOperation() cannot be called
                                  // through Base& inside EvilDerived

}
```  
### Real-work example

```cpp  
class BankAccount {
protected:
    double balance = 1000.0;
    void setBalance(double b) { balance = b; }
};

class CheckingAccount : public BankAccount {
public:
    void deposit(double amount) {
        balance += amount;  // ✅ OK: accessing own balance
    }
    
    void transferFrom(CheckingAccount& other, double amount) {
        other.balance -= amount;  // ✅ OK: other is CheckingAccount
        this->balance += amount;
    }
    
    void dangerousHack(BankAccount& anyAccount) {
        // anyAccount.balance = 0;  // ❌ ERROR: can't access through Base&
        // Good! We shouldn't be able to mess with arbitrary accounts
    }
};

class SavingsAccount : public BankAccount {
    // Has different rules for withdrawals
};
```  
### Protected vs Private: Decision Guide

| Use Case | Choose |
|----------|--------|
| Want derived classes to customize behavior | `protected` |
| Pure implementation detail, no inheritance needed | `private` |
| Template Method pattern (customizable steps) | `protected` virtual |
| External API should never touch | `private` |
| Data that defines class invariants | `private` with protected getters/setters |  

### Sai lầm khi sử dụng protected  

#### Lỗi 1: Protected Data = Tight Coupling

```cpp  
class BadBase {
protected:
    std::vector<int> data; // Derived classes directly manipulate
};

class GoodBase {
private:
    std::vector<int> data;
protected:
    void addItem(int item) { data.push_back(item); } 
    int getItem(size_t idx) const { return data.[idx]; }
};
```  

#### Lỗi 2: Protected Destructor Usage  

```cpp  
class Interface {
public:
    virtual void doWork() = 0;
protected:
    ~Interface() = default; // ✅ Prevents delete through Interface*
};

class Impl : public Interface {
public:
    void doWork() override {}
    ~Impl() { /*clean up*/ } // Can still delete Impl*
}

int main() {
    Interface* ptr = new Impl();
    ptr->doWork();
    // delete ptr; // ❌ ERROR: destructor is protected

    Impl* impl = new Impl();
    delete impl; // OK
}
```  

#### Ví dụ sử dụng Protected Destructor  

```cpp
class IConnection {
public:
    virtual void send(const std::string& data) = 0;
    virtual bool isConnected() const = 0;
protected:
    virtual ~IConnection() = default;
    friend class ConnectionManager;
};

class TcpConnection : public IConnection {
public:
    TcpConnection() {
        std::cout << "TCP connection created!\n";
    }

    ~TcpConnection() override {
        std::cout << "TCP connection destroyed!\n";
    }

    void send(const std::string& data) override {
        std::cout << "Send: " << data << std::endl;
    }

    bool isConnected() const override {
        return true;
    }
};

class ConnectionManager {
public:
    IConnection* createConnection() {
        return new TcpConnection();
    }

    void destroyConnection(IConnection* connection) {
        delete connection; // Được vì là hàm bạn
    }
};

int main() {

    ConnectionManager manager;

    IConnection* connection = manager.createConnection();

    connection.send("Hello");

    //delete connection; // Error

    manager.destroyConnection(connection);

    return 0;
}
```  
## Common Interview Questions

### Q1: What's the default access for `struct` vs `class`?

**Answer**: 
- `struct` → `public` (members and inheritance)
- `class` → `private` (members and inheritance)

### Q2: Can a derived class access base class private members?

**Answer**: No. Private members are not accessible in derived classes. Use `protected` if you want derived class access.

### Q3: Is `friend` an access specifier?

**Answer**: No. Access specifiers are `public`, `protected`, and `private`. `friend` is a separate mechanism that grants specific external functions/classes access to private and protected members.

### Q4: What's the difference between access and visibility?

**Answer**:
- **Visibility**: Whether the compiler can see a name during name lookup (controlled by `#include`, forward declarations)
- **Access**: Whether you're allowed to use a visible member (controlled by `public`/`protected`/`private`)

### Q5: When is access control checked?

**Answer**: At **compile-time** during semantic analysis, after name lookup succeeds.

### Q6: What does `const` after a member function mean?

**Answer**: It makes the function a **const member function**, which:
1. Promises not to modify member variables
2. Can be called on const objects
3. Is enforced at compile-time

```cpp
int getLength() const;  // const member function
```

### Q7: Can members of the same class access each other's private data?

**Answer**: Yes! Access control is **per-class, not per-object**. All instances of a class can access private members of other instances of the same class.

```cpp
class Box {
private:
    int len;
public:
    bool isBigger(const Box& other) const {
        return len > other.len;  // ✅ OK: accessing another Box's private member
    }
};
```

### Q8: Why can't I access a base's protected member through a Base reference in a derived class?

**Answer**: This is C++'s **protection against cross-hierarchy violations**. If `DerivedA` could access protected members through a `Base&`, it could manipulate `DerivedB`'s protected state through a base reference, violating encapsulation between sibling classes.

**See**: `example2/a.cpp` and `example3/realworld.cpp` for demonstrations

### Q9: What happens to protected members with private inheritance?

**Answer**: Protected members become **private** in the derived class. Further derived classes (grandchildren) cannot access them.

**See**: `example4/inheritancetype.cpp` for full demonstration

```cpp
class D3 : private Base {
    // Base's protected becomes private here
};

class D3Child : public D3 {
    // Cannot access Base's members - they're private in D3
};
```

### Q10: When should I use protected instead of private?

**Answer**: Use `protected` when:
- You're designing for inheritance and want derived classes to customize behavior
- Implementing Template Method pattern
- The member is part of the "interface for subclasses"

Use `private` when:
- It's an implementation detail
- You want to maintain full control over invariants
- No derived class should depend on it

**Best Practice**: Prefer `private` by default; use `protected` only when inheritance customization is intended.

---

## Best Practices

### 1. Encapsulation First
```cpp
class Account {
private:
    double balance;  // Hide implementation
public:
    void deposit(double amount);   // Public interface
    double getBalance() const;     // Const for read-only
};
```

### 2. Minimal Public Interface
- Keep data members `private`
- Expose only what clients need
- Use `protected` sparingly

### 3. Const Correctness
```cpp
class Box {
private:
    int len;
public:
    int getLength() const { return len; }     // ✅ const (read-only)
    void setLength(int l) { len = l; }        // Non-const (modifies)
};
```

### 4. Prefer Composition Over Inheritance
```cpp
// ❌ Avoid: Inheritance for code reuse
class Stack : private std::vector<int> { };

// ✅ Better: Composition
class Stack {
private:
    std::vector<int> data;  // Has-a relationship
};
```

### 5. Use `friend` Sparingly
Only when:
- Operator overloading requires it
- Tightly coupled design is justified
- Factory pattern needs private constructor access

---

## System Design Implications

### 1. Interface Stability
- Public API changes break client code
- Private changes don't affect clients
- Protected changes affect derived classes

### 2. Pimpl (Pointer to Implementation)
Hide implementation details to reduce compilation dependencies:

```cpp
// widget.h
class Widget {
public:
    Widget();
    ~Widget();
    void doSomething();
private:
    class Impl;  // Forward declaration
    Impl* pImpl; // Pointer to implementation
};
```

### 3. Abstract Interfaces
```cpp
class IShape {
public:
    virtual double area() const = 0;
    virtual ~IShape() = default;
protected:
    ~IShape() {}  // Protected destructor prevents deletion via interface
};
```

---

## Quick Reference Card

```cpp
// Access Specifiers
public:     // Accessible everywhere
protected:  // Class + friends + derived classes
private:    // Class + friends only

// Defaults
class → private
struct → public

// Friend (not an access specifier)
friend void func();
friend class Other;

// Const member function
int get() const;  // Won't modify members

// Inheritance
class D : public Base {};     // Most common
class D : protected Base {};  // Rare
class D : private Base {};    // Implementation inheritance
```

---

## Related Topics to Explore Next

1. **RAII** (Resource Acquisition Is Initialization)
2. **Const correctness** (const, constexpr, mutable)
3. **Virtual functions & Polymorphism**
4. **Smart pointers** (unique_ptr, shared_ptr)
5. **Move semantics** (rvalue references)
6. **Template metaprogramming**
7. **Design patterns** (Singleton, Factory, Observer)

---

## Summary: Example Directory Structure

```
acessmodifiers/
├── README.md                      # This file
├── example1/                      # Basic access & visibility
│   ├── box.h                     # Class with private/public
│   ├── am.cpp                    # Usage demonstrating access control
│   └── am.out                    # Compiled binary
├── example2/                      # Protected "through what?" rule
│   └── a.cpp                     # All 5 test cases for protected access
├── example3/                      # Real-world: Bank accounts
│   └── realworld.cpp             # CheckingAccount & SavingsAccount
└── example4/                      # Inheritance types
    └── inheritancetype.cpp       # Public/Protected/Private inheritance
```

**Learning Path**:
1. Start with `example1` → Understand basic access control & visibility
2. Move to `example2` → Master the tricky protected rules
3. Study `example3` → See why the rules matter in real systems
4. Finish with `example4` → Understand how inheritance changes access

---

**Interview Prep Tip**: Always distinguish between:
- **What** (access specifiers, friend, protected rules)
- **When** (compile-time phases: visibility → access)
- **Why** (encapsulation, const-correctness, security, interface design)

**Compile & Run All Examples**:
```bash
# Example 1
cd example1 && g++ -o am.out am.cpp && ./am.out

# Example 2 (will show compilation errors - that's expected!)
cd example2 && g++ -o a.out a.cpp

# Example 3
cd example3 && g++ -o realworld.out realworld.cpp && ./realworld.out

# Example 4
cd example4 && g++ -o inheritancetype.out inheritancetype.cpp && ./inheritancetype.out
```


