#include <iostream>
#include "smartpointer.h"
class SomeClass {
public:
    SomeClass(int n):ID(n) {
        std::cout << "SomeClass" << ID << " default constructor !" << std::endl;
    }
    ~SomeClass() {
        std::cout << "SomeClass" << ID << " deconstructor !" << std::endl;
    }

private:
    int ID;
};

void testcase2(void) {
    // 先创建一个智能指针，再给已创建好的智能指针赋值 
    SmartPointer<SomeClass> spclass1 = new SomeClass(1);  // 带参构造函数
    std::cout << std::endl;

    // 自我赋值
    spclass1 = spclass1;  // 自我赋值失败,没有任何反应 
    std::cout << std::endl;
 
    // 创建另外一个智能指针，与先前的智能指针指向同一块内存资源 
    SmartPointer<SomeClass> spclassother = spclass1;  // 拷贝构造 
    std::cout << std::endl;
 
    // 先创建智能指针，再用另一个智能指针给已创建好的智能指针赋值 
    SmartPointer<SomeClass> spclass2 = new SomeClass(2);   // 带参构造函数
    std::cout << std::endl;
    spclass2 = spclass1;
    std::cout << std::endl;
  
}

int main(void) {
    std::cout << std::endl << std::endl << std::endl;
    testcase2();    
    std::cout << std::endl << std::endl << std::endl;
    return 0;
}

