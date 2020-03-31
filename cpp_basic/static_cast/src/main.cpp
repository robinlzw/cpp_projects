#include <vector>
#include <iostream>
 
struct B {
    int m = 0;
    void hello() const {
        std::cout << "Hello world, this is B!\n";
    }
};
struct D : B {
    void hello() const {
        std::cout << "Hello world, this is D!\n";
    }
};
 
enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };
 
int main()
{
    // 1: 初始化转换
    int n = static_cast<int>(3.14); 
    std::cout << "n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "v.size() = " << v.size() << '\n';
 
    // 2: 静态向下转型
    D d;
    B& br = d; // 通过隐式转换向上转型
    br.hello();
    D& another_d = static_cast<D&>(br); // 向下转型
    another_d.hello();
 
    // 3: 左值到右值
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v);
    std::cout << "after move, v.size() = " << v.size() << '\n';
 
    // 4: 弃值表达式
    static_cast<void>(v2.size());
 
    // 5. 隐式转换的逆
    void* nv = &n;
    int* ni = static_cast<int*>(nv);
    std::cout << "*ni = " << *ni << '\n';
 
    // 6. 数组到指针后随向上转型
    D a[10];
    B* dp = static_cast<B*>(a);
 
    // 7. 有作用域枚举到 int 或 float
    E e = E::ONE;
    int one = static_cast<int>(e);
    std::cout << one << '\n';
 
    // 8. int 到枚举，枚举到另一枚举
    E e2 = static_cast<E>(one);
    EU eu = static_cast<EU>(e2);
 
    // 9. 指向成员指针向上转型
    int D::*pm = &D::m;
    std::cout << br.*static_cast<int B::*>(pm) << '\n';
 
    // 10. void* 到任何类型
    void* voidp = &e;
    std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
}
