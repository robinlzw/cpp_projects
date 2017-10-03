#include <iostream>
#include "smartpointer.h"
class SomeClass {
public:
    SomeClass() {
        std::cout << "SomeClass default constructor !" << std::endl;
    }
    ~SomeClass() {
        std::cout << "SomeClass deconstructor !" << std::endl;
    }
};

void testcase1() {
    // 创建一个不知所指的智能指针
    SmartPointer<char> spunkonwn;
    // 创建空(NULL)智能指针
    SmartPointer<char> spnull = NULL;
    
    std::cout << std::endl << std::endl;
    // 创建指向具体类的智能指针
    SmartPointer<SomeClass> spclass = new SomeClass;
    
    std::cout << std::endl << std::endl;
    // 创建字符串的智能指针
    SmartPointer<const char> spstr = "Hello world!";  //如果不加const，会有警告：不建议使用从字符串常量到‘char*’的转换
    //SmartPointer<const char> spstr;
    //const char* spstr2 = "Hello lzw!"; 
    //spstr = spstr2;  
}

int main(void) {
    std::cout << "--------------------------------------------------------" << std::endl << std::endl; 
    testcase1();    
    std::cout << "---------->----a track line for bug----<-----------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl << std::endl;
   
    return 0;
}

