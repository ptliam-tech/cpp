#include <iostream>
#include <string>

using namespace std;

class Animal {
protected:
    string name;
public:
    explicit Animal(string n) : name(n) {
        cout << "Animal constructor!" << endl;
    }

    void eat() {
        cout << name << " is eating " << endl;
    }
};

class Dog : public Animal {
private:
    string breed;
public:
    Dog(string n, string b) : Animal(n), breed(b) {
        cout << "Dog constructor: " << breed << endl;
    }

    void bark() {
        cout << name << " (" << breed << ") says: Woof!" << endl;
    }
};

int main() {
    Dog myDog("Buddy", "Golden Retriever");
    myDog.eat();  // Inherited from Animal
    myDog.bark(); // Dog's own method

    return 0;
}