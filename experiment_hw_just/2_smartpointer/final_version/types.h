#ifndef __TYPES_H__
#define __TYPES_H__


/*引用计数基类*/
class RefBase {
public:
    RefBase(): mCount(0) {}
    void incRefCount() {
        mCount++;
    }
    int decRefCount() {
        return --mCount;
    }
    
    // 调试接口，返回对象当前引用计数
    int getRefCount() {
        return mCount;
    } 
    // 将析构函数做出虚函数，由子类定义如何析构 
    virtual ~RefBase() {}

private:
    int mCount;
    
}; 

/*继承于引用计数基类的SomeClass类*/ 
class SomeClass: public RefBase {
public:
    SomeClass(int n):ID(n) {
        std::cout << "SomeClass" << ID << " call someclass_have_paramter_construct_function" << std::endl;
    }
    ~SomeClass() {
        std::cout << "SomeClass" << ID << " deconstructor !" << std::endl;
    }
    void func() {
        std::cout << "SomeClass func()" << std::endl;
    } 

private:
    int ID;
};

/*继承于引用计数基类的OtherClass类*/ 
class OtherClass: public RefBase {
public:
    OtherClass(int n):ID(n) {
        std::cout << "OtherClass" << ID << " call otherclass_have_paramter_construct_function" << std::endl;
    }
    ~OtherClass() {
        std::cout << "OtherClass" << ID << " deconstructor !" << std::endl;
    }
    void foo() {
        std::cout << "OtherClass foo()" << std::endl;
    } 

private:
    int ID;
};

#endif  // __TYPES_H__

