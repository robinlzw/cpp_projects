#include <iostream>
#include "smartpointer.h"
#include "types.h"
using namespace std;

// 输出隔出多个空行 
void place_multi_line() {
    cout<<endl<<endl;
}

// 解引用测试 
void testcase4_1(void) {
    cout << "=============================testcase4_1=============================" << endl;
    SmartPointer<SomeClass>  spsomeclass = new SomeClass(1);
    (*spsomeclass).func();
    spsomeclass->func();
    cout << "======================================================================" << endl;
    place_multi_line();
}

// 判空与比较测试 
void testcase4_2(void) {
    place_multi_line();
    place_multi_line();
    cout << "=================================testcase4_2=================================" << endl;
    
    SomeClass* psomeclass = new SomeClass(2);  /*调用someclass_have_paramter_construct_function*/
    SmartPointer<SomeClass>  spsomeclass2 = psomeclass;  /*调用sp_have_paramter_construct_function*/
place_multi_line();

    SmartPointer<OtherClass>  spotherclass1 = new OtherClass(1);  /*调用sp_have_paramter_construct_function*/
    SmartPointer<OtherClass>  spotherclass2 = spotherclass1;  /*调用sp_copy_construct_function*/
    SmartPointer<OtherClass>  spotherclass3;  /*调用sp_default_construct_function*/ 
    spotherclass3 = spotherclass1;  /*调用sp_asign_construct_function*/ 
place_multi_line();

    if( spsomeclass2 == NULL ) {
        cout << "spsomeclass2 is NULL pointer" << endl;
    }
    if( spotherclass1 != NULL ) {
        cout << "spotherclass1 is not NULL pointer" << endl;
    }
    if( spsomeclass2 == psomeclass ) {
        cout << "spsomeclass2 and psomeclass are same pointer" << endl;
    }   
    if( spsomeclass2 != psomeclass ) {
        cout << "spsomeclass2 and psomeclass are not same pointer" << endl;
    }
        
//  if( spsomeclass != spotherclass ) {  // ERROR!
//      cout << "spsomeclass and spotherclass are not same pointer" << endl;
//  }   
//  if( spsomeclass == spotherclass ) {  // ERROR!
//      cout << "spsomeclass and spotherclass are same pointer" << endl;
//  }   
    
    if( spotherclass1 == spotherclass2 ) {  
        cout << "spotherclass1 and spotherclass2 are same pointer" << endl;
    }   
    
    if( spotherclass1 != spotherclass2 ) {  
        cout << "spotherclass1 and spotherclass2 are not same pointer" << endl;
    }   
    cout << "============================================================================" << endl;
    place_multi_line();
}


int main(void) {
    place_multi_line(); 
    testcase4_1();
    place_multi_line(); 
    testcase4_2();  
    place_multi_line();
    cout << "-----------------------------------------------------------------------------" << endl;
    return 0;
}

