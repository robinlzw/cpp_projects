#include <iostream>
#include "smartpointer.h"

/*继承于引用计数基类的SomeClass类*/ 
class SomeClass: public RefBase {
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

void testcase3(void) {
    SomeClass* pSomeClass = new SomeClass(1);  //1
    SmartPointer<SomeClass>  spOuter = pSomeClass;
    std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer1." << std::endl;
    std::cout << std::endl;
     
    {   // inner语句块
        SmartPointer<SomeClass> spInner = spOuter;
        std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") inner." << std::endl;       
    }
    // 跳出inner语句块，spInner指针被销毁，但SomeClass没有被销毁，引用计数-1 
    std::cout << std::endl;
    
    std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer2." << std::endl;
    // delete pSomeClass; 不需要也不能执行delete操作！
    std::cout << std::endl;
    std::cout << "new another SomeClass class for spOuter. " << std::endl;
    SmartPointer<SomeClass>  spOuter2 = new SomeClass(2);  //2 
    spOuter = spOuter2;  // 1处new出来的SomeClass将会被自动释放 
     
}

int main(void) {
    std::cout << std::endl << std::endl << std::endl;    
    testcase3();    
    /**
    * 当退出testcase3()函数时,spOuter和spOuter2将被销毁,
    * spOuter和spOuter2共同指向的SomeClass_2只被销毁1次。 
    */
    std::cout << std::endl << std::endl << std::endl;
    return 0;
}

