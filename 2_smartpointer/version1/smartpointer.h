#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

template <typename T>  // 将智能指针定义成模板类
class SmartPointer {
public:
    // 默认构造函数
    SmartPointer():mPointer(NULL) {
        std::cout << "In sp_default_construct_func, create unknown smart pointer." << std::endl;
    } 
    // 接收不同指针类型的构造函数
    SmartPointer( T *p ):mPointer(p) {
        std::cout << "In sp_parameter_construct_func, create smartpointer pointed to " << static_cast< const void* >(p) << std::endl; 
        std::cout << std::endl << "mPointer's address is " << &mPointer << ", and the object's address by this.mPointer pointed is " 
                  << static_cast< const void* >(mPointer) << std::endl;
        //std::cout << "->----------------this is a note: can't ouput mPointer direactly--->" << mPointer << std::endl << std::endl; 
    
    } 
    // 析构函数
    ~SmartPointer() {
        std::cout << "In sp_deconstruct_func, release smartpointer pointed to " << static_cast< const void* >(mPointer) << std::endl;
        // 实现内存资源自动销毁机制
        if(mPointer) {
            delete mPointer;
        } 
    } 

private:
    T* mPointer;  // 指向智能指针实际对应的内存资源，根据参数自动推导规则，定义内部资源指针类型 
    
}; 
#endif  // __SMARTPOINTER_H__

