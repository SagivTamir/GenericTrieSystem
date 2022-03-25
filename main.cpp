#include <iostream>
#include <cmath>
#include <utility>
#include <random>
#include "System.h"

const int LENGTH_OF_ISRAELI_PHONE_NUMBER = 10;

class MyDataPhoneNumber {
    std::string phone_number;
    int length;
public:
    std::vector<int> my_ABC = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    explicit MyDataPhoneNumber(std::string phone_number, int length = LENGTH_OF_ISRAELI_PHONE_NUMBER) : phone_number(
            std::move(phone_number)), length(length) {}

    int operator[](int index) const {
        return phone_number[index];
    }

    int getLength() const {
        return length;
    }

    char convertToElementType(int index) const {
        return my_ABC[index];
    }
};

class MyDataString {
    std::string x;
    int length;
public:
    std::vector<int> my_ABC = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                               'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    explicit MyDataString(std::string x, int length) : x(std::move(x)), length(length) {}

    int operator[](int index) const {
        return x[index];
    }

    int getLength() const {
        return length;
    }

    char convertToElementType(int index) const {
        return my_ABC[index];
    }
};


int main() {
    // first example - strings system
    std::cout << "first example - abc string" << std::endl;
    System<MyDataString> my_system_1 = System<MyDataString>(26);
    MyDataString new_element1 = MyDataString("add", 3);
    MyDataString new_element2 = MyDataString("ac", 2);
    MyDataString new_element3 = MyDataString("adda", 4);
    MyDataString new_element4 = MyDataString("bcai", 4);
    MyDataString new_element5 = MyDataString("bcaf", 4);
    my_system_1.insert(new_element1);
    my_system_1.insert(new_element2);
    my_system_1.insert(new_element3);
    my_system_1.insert(new_element4);
    my_system_1.insert(new_element5);
    my_system_1.printSystem();
    std::cout << "'add' has " << my_system_1.numOfPrefixes(new_element1) << " prefixes" << std::endl;
    my_system_1.remove(new_element1);
    my_system_1.printSystem();
    std::cout << "'add' has " << my_system_1.numOfPrefixes(new_element1) << " prefix" << std::endl;

    // second example - phone numbers
    std::cout << "second example - phone numbers" << std::endl;
    System<MyDataPhoneNumber> my_system_2 = System<MyDataPhoneNumber>(LENGTH_OF_ISRAELI_PHONE_NUMBER);
    MyDataPhoneNumber phone_num_1 = MyDataPhoneNumber("0549142603");
    MyDataPhoneNumber phone_num_2 = MyDataPhoneNumber("0525985253");
    MyDataPhoneNumber phone_num_3 = MyDataPhoneNumber("0533225985");
    MyDataPhoneNumber phone_num_4 = MyDataPhoneNumber("0544214176");
    MyDataPhoneNumber phone_num_5 = MyDataPhoneNumber("5555555555");
    MyDataPhoneNumber phone_num_6 = MyDataPhoneNumber("6666666666");
    my_system_2.insert(phone_num_1);
    my_system_2.insert(phone_num_2);
    my_system_2.insert(phone_num_3);
    my_system_2.insert(phone_num_4);
    my_system_2.insert(phone_num_5);
    my_system_2.printSystem();
    my_system_2.remove(phone_num_1);
    my_system_2.remove(phone_num_6);
    my_system_2.printSystem();
    my_system_2.insert(phone_num_6);
    my_system_2.printSystem();
    MyDataPhoneNumber check_prefixes = MyDataPhoneNumber("05", 2);
    std::cout << "'05' has " << my_system_2.numOfPrefixes(check_prefixes) << " prefixes" << std::endl;
    my_system_2.remove(phone_num_3);
    my_system_2.printSystem();
    std::cout << "'05' has " << my_system_2.numOfPrefixes(check_prefixes) << " prefixes" << std::endl;

    return 0;
}










