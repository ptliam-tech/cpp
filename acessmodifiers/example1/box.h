class Box{
private: 
    int len;
    friend void printlength(Box& box); // this is friend function and it can access the private members of the class
    friend class BoxPrinter; // this is friend class and it can access the private members of the class

public:
    int getlength() const {
        //len = 10; //we cannot do this as we siad this function is const will not manipulate the values in the class
        return len;
    };

    void setlength(int l){
        len = l;
    };
};