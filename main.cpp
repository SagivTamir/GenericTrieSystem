#include <iostream>
#include <cmath>
#include <utility>
#include "System.h"

const int LENGTH_OF_ISRAELI_PHONE_NUMBER = 10;

class MyDataPhoneNumber{
    std::string phone_number;
    int length;
    int ABC_size = 10;
public:
    std::vector<int> my_ABC = {'0','1','2','3','4','5','6','7','8','9'};
    explicit MyDataPhoneNumber(std::string phone_number, int length = LENGTH_OF_ISRAELI_PHONE_NUMBER) : phone_number(std::move(phone_number)), length(length) {}

    int operator[](int index) const{
        return phone_number[index];
    }
    int getLength() const{
        return LENGTH_OF_ISRAELI_PHONE_NUMBER;
    }
    char convertToElementType(int index) const{
        return my_ABC[index];
    }
};

class MyDataString{
    std::string x;
    int length;
    int ABC_size = 26;
public:
    std::vector<int> my_ABC = {'a','b','c','d','e','f','g','h','i','j','k',
                               'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    explicit MyDataString(std::string x,int length) : x(std::move(x)), length(length) {}

    int operator[](int index) const{
        return x[index];
    }
    int getLength() const{
        return length;
    }
    char convertToElementType(int index) const{
        return my_ABC[index];
    }
};


int main() {
    // first example - strings system
    System<MyDataString> my_system_1 = System<MyDataString>(26);
    MyDataString new_element1 = MyDataString("add",3);
    MyDataString new_element2 = MyDataString("ac",2);
    MyDataString new_element3 = MyDataString("adda",4);
    MyDataString new_element4 = MyDataString("cbaeecbaeecbaeecbaee",20);
    my_system_1.insert(new_element1);
    my_system_1.insert(new_element2);
    my_system_1.insert(new_element3);
    my_system_1.insert(new_element4);
    my_system_1.printSystem();
    // second example - phone numbers
    System<MyDataPhoneNumber> my_system_2 = System<MyDataPhoneNumber>(LENGTH_OF_ISRAELI_PHONE_NUMBER);
    MyDataPhoneNumber phone_num_1 = MyDataPhoneNumber("0549142603");
    MyDataPhoneNumber phone_num_2 = MyDataPhoneNumber("0525985253");
    MyDataPhoneNumber phone_num_3 = MyDataPhoneNumber("0533225985");
    MyDataPhoneNumber phone_num_4 = MyDataPhoneNumber("0544214176");
    MyDataPhoneNumber phone_num_5 = MyDataPhoneNumber("5555555555");
    my_system_2.insert(phone_num_1);
    my_system_2.insert(phone_num_2);
    my_system_2.insert(phone_num_3);
    my_system_2.insert(phone_num_4);
    my_system_2.insert(phone_num_5);
    my_system_2.printSystem();
    return 0;
}
