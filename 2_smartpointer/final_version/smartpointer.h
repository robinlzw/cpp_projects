#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

template <typename T>  // 将智能指针定义成模板类
class SmartPointer {
public:
    // 默认构造函数
    SmartPointer():mPointer(NULL) {
        std::cout << "In sp_default_construct_function...create null smart pointer." << std::endl;
    } 
    // 接收不同对象类型的构造函数(带参构造函数)
    SmartPointer( T *p ):mPointer(p) {
        std::cout << "In sp_have_paramter_construct_function...Create smartpointer pointed to " << static_cast< const void* >(p) << std::endl; 
        // 智能指针指向类T，引用计数 +1 
        if(mPointer) {
            mPointer->incRefCount();
        } 
    } 
    // 析构函数
    ~SmartPointer() {
        std::cout << "Release smartpointer pointed to " << static_cast< const void* >(mPointer) << std::endl;
        // 实现内存资源自动销毁机制
        if( mPointer && mPointer->decRefCount() == 0 ) {
            delete mPointer;  //先调用T类型的对象的析构函数，再释放内存(也就是free(mPointer)) 
        } 
    } 

    // 拷贝构造函数
    SmartPointer( const SmartPointer& other ):mPointer( other.mPointer ) {
        std::cout<< "In sp_copy_construct_function...Copy smartpointer pointed to " << static_cast< const void* >(other.mPointer) << std::endl;
        // 引用计数 +1
        if(mPointer) {
            mPointer->incRefCount();
        } 
    } 
    
    // 赋值操作符
    SmartPointer& operator= ( const SmartPointer& other ) {
        std::cout<< "In sp_asign_construct_function..." << std::endl;
        T* temp(other.mPointer);  //调用拷贝构造函数创建一个新的T类型的指针temp 
        // 新指向对象，引用计数 +1 
        if(temp) {
            temp->incRefCount();
        }
        // 原指向对象，引用计数 -1，如果-1后引用计数为0则销毁原资源对象
        if( mPointer && mPointer->decRefCount() == 0 ) {
            delete mPointer;
        }
        // 智能指针指向新资源对象
        mPointer = temp;  //这句是普通指针之间的赋值 
        return *this;   
    } 
    
    // 重载*和->运算符
    T& operator* () const {
        return *mPointer;  //返回对象的引用 
    } 
    T* operator-> () const {
        return mPointer;  //返回指针
    } 
    
    // 判空与比较
    bool operator == ( const SmartPointer& o ) const {  
        return mPointer == o.mPointer;
    }
    bool operator != ( const SmartPointer& o ) const {  
        return mPointer != o.mPointer;
    }
    bool operator == ( const T* o ) const { 
        return mPointer == o;
    }
    bool operator != ( const T* o ) const { 
        return mPointer != o;
    }
     
private:
    T* mPointer;  // 指向智能指针实际对应的内存资源，根据参数自动推导规则，定义内部资源指针类型 
    
}; 

#endif  // __SMARTPOINTER_H__

