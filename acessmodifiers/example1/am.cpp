#include<iostream>
#include"box.h" // here we are exposing means visibile to compiler

using namespace std;

class BoxPrinter{
public:
    void printlength(Box& box){
        cout << "Length of the box: " << box.len << endl; // this is accessible because this class is friend class
    }
};

void printlength(Box& box){
    cout << "Length of the box: " << box.len << endl; // this is accessible because this function is friend function
}

int main(){
    cout << "hello access modifier..\n";
    Box box;
    BoxPrinter boxPrinter;
    box.getlength(); // this is accessible
    //box.len = 6; //not access and error
    box.setlength(6); // this is accessible
    cout << "Length of the box: " << box.getlength() << endl;
    printlength(box); // this is accessible because this function is friend function
    boxPrinter.printlength(box); // this is accessible because this class is friend class

    return 0;
}