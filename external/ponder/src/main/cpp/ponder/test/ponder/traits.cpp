/****************************************************************************
 **
 ** This file is part of the Ponder library, formerly CAMP.
 **
 ** The MIT License (MIT)
 **
 ** Copyright (C) 2009-2010 TECHNOGERMA Systems France and/or its subsidiary(-ies).
 ** Contact: Technogerma Systems France Information (contact@technogerma.fr)
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy
 ** of this software and associated documentation files (the "Software"), to deal
 ** in the Software without restriction, including without limitation the rights
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 ** copies of the Software, and to permit persons to whom the Software is
 ** furnished to do so, subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in
 ** all copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 ** THE SOFTWARE.
 **
 ****************************************************************************/

#include <ponder/detail/functiontraits.hpp>
#include <ponder/detail/objecttraits.hpp>
#include <ponder/detail/util.hpp>
#include <ponder/arraymapper.hpp>
#include <ponder/function.hpp>
#include <ponder/classbuilder.hpp>
#include "test.hpp"
#include <array>
#include <string.h> // strcmp()

#ifdef TEST_BOOST
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/result_type.hpp>
#endif

namespace TraitsTest
{
    static void func() {}

    static int funcArgReturn(float) {return 0;}
    
    struct Class
    {
        float method(float x) const { return x*3; }
        static int staticFunc() { return 77; }
    };
    
    struct Methods
    {
        void foo() {}
        ponder::String arr[10];
        int arri[7];
        std::array<int, 6> arrv;
    
        int v;
        const int& getV() const {return v;}
    };

    struct Callable {
        void operator () (void) {}
    };
    
    struct NonCallable {
        int x;
    };

    int intArray[10];
    
    template <class T>
    class TemplateClass
    {
    public:
        T x;
    };
    
    enum Enum { RED, GREEN, BLUE };
    enum class EnumCls { TALL, SHORT };

    struct FuncReturn
    {
        int m_i;
        Callable m_c;
        
        int i() const {return 0;}
        float f() {return 2.4f;}
        
        int* ip() {return &m_i;}
        
        std::shared_ptr<Callable> sp() {return std::make_shared<Callable>(m_c);}
        
        std::vector<int> ai() {return std::vector<int>{1,2,3};}
        
        std::vector<std::shared_ptr<Callable>> as()
        {
            return std::vector<std::shared_ptr<Callable>>();
        }
    };
}

using namespace TraitsTest;

//-----------------------------------------------------------------------------
//                         Tests for ponder traits
//-----------------------------------------------------------------------------

// Sanity check: make sure compiler supports features we need.
TEST_CASE("C++11 features and syntax")
{
    SECTION("function test")
    {
        func(); funcArgReturn(0.f); // to stop unused warning
        
        static_assert(std::is_function<decltype(func)>::value, "std::is_function failed");
        static_assert(std::is_function<void(void)>::value, "std::is_function failed");
        static_assert(std::is_function<
                        std::remove_pointer<decltype(&Class::staticFunc)>::type>::value,
                      "std::is_function failed");
        static_assert(std::is_function< std::function<void()>() >::value,
                      "std::is_function failed");
        
        static_assert( ! std::is_function<Callable>::value, "std::is_function failed");
        static_assert( ! std::is_function<NonCallable>::value, "std::is_function failed");
        static_assert( ! std::is_function<decltype(&Class::method)>::value,
                      "std::is_function failed");
        static_assert( ! std::is_function<void(Methods::*)()>::value, "std::is_function failed");
        static_assert( ! std::is_function<
                            std::remove_pointer<decltype(&Methods::foo)>::type>::value,
                      "std::is_function failed");
    }
    
    SECTION("function result")
    {
        static_assert(std::is_void< std::result_of<decltype(func)& ()>::type >::value,
                      "std::result_of failed");
        static_assert(std::is_void< std::result_of<decltype(&func) ()>::type >::value,
                      "std::result_of failed");
        typedef void (*foo_t)();
        static_assert(std::is_void< std::result_of<foo_t ()>::type >::value,
                      "std::result_of failed");
        static_assert(std::is_pointer<foo_t>::value, "std::is_pointer failed");

        typedef int (*bar_t)(float);
        static_assert(std::is_same< std::result_of<decltype(funcArgReturn)& (float)>::type,
                                    int >::value, "std::result_of failed");
        static_assert(std::is_same< std::result_of<decltype(&funcArgReturn) (float)>::type,
                                    int >::value, "std::result_of failed");
        static_assert(std::is_same< std::result_of<bar_t (float)>::type, int >::value,
                      "std::result_of failed");
    }

    SECTION("arrays")
    {
        static_assert( ! std::is_array<int>::value, "std::is_array failed");
        static_assert(   std::is_array<int[10]>::value, "std::is_array failed");
        static_assert( ! std::is_array<int*>::value, "std::is_array failed");
        static_assert( ! std::is_array<int*>::value, "std::is_array failed");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Ponder supports different function types")
{
    SECTION("what is not a function")
    {
        using ponder::detail::FunctionTraits;
        
        static_assert( ! FunctionTraits<int>::isFunction,   "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<float>::isFunction, "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<int*>::isFunction,  "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<char*>::isFunction, "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<int**>::isFunction, "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<ponder::String>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert( ! FunctionTraits<NonCallable>::isFunction,
                      "FunctionTraits<>::isFunction failed");
    }
    
    SECTION("what is not a function types")
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;
        
        static_assert(FunctionTraits<int>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<float>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<int*>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<char*>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<int**>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<ponder::String>::kind == FunctionKind::None,
                      "FunctionTraits<>::kind failed");
        static_assert(FunctionTraits<NonCallable>::kind == FunctionKind::None,
                      "FunctionTraits<>::isFunction failed");
    }
    
    SECTION("type function")
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;
        
        static_assert(ponder::detail::FunctionTraits<void(void)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<void(void)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
        
        static_assert(ponder::detail::FunctionTraits<void(int)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<void(int)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
        
        static_assert(ponder::detail::FunctionTraits<int(void)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<int(void)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
        
        static_assert(ponder::detail::FunctionTraits<int(char*)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<int(char*)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
        
        // non-class void(void)
        static_assert(FunctionTraits<decltype(func)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<decltype(func)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
        
        // non-class R(...)
        static_assert(FunctionTraits<decltype(funcArgReturn)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<decltype(funcArgReturn)>::kind == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");

        // class static R(void)
        static_assert(FunctionTraits<decltype(&Class::staticFunc)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<decltype(&Class::staticFunc)>::kind
                                                                     == FunctionKind::Function,
                      "FunctionTraits<>::kind failed");
    }


    SECTION("type member function")  // T(C::*)()
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;

        static_assert(std::is_member_function_pointer<void (TraitsTest::Methods::*)()>::value, "MFP");
        static_assert(FunctionTraits<void(Methods::*)()>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<void(Methods::*)()>::kind == FunctionKind::MemberFunction,
                      "FunctionTraits<>::kind failed");
        
        void (Methods::*meth_t)() = &Methods::foo;
        static_assert(FunctionTraits<decltype(meth_t)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<decltype(meth_t)>::kind == FunctionKind::MemberFunction,
                      "FunctionTraits<>::kind failed");
    }

    SECTION("type member object")   // T(C::*)
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;
        
        struct Members {
            int m;
            float a[5];
        };

        static_assert( ! FunctionTraits<int Members::*>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<int Members::*>::kind == FunctionKind::MemberObject,
                      "FunctionTraits<>::kind failed");
        
        static_assert( ! FunctionTraits<float (Members::*)[]>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<float (Members::*)[]>::kind == FunctionKind::MemberObject,
                      "FunctionTraits<>::kind failed");
        
        static_assert( ! FunctionTraits<decltype(&Members::a)>::isFunction,
                      "FunctionTraits<>::isFunction failed");
        static_assert(FunctionTraits<decltype(&Members::a)>::kind == FunctionKind::MemberObject,
                      "FunctionTraits<>::kind failed");
    }
    
    SECTION("type function wrapper")  // std::function<>
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;
        
        static_assert(FunctionTraits<std::function<void()>>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
            FunctionTraits<std::function<void()>>::kind == FunctionKind::FunctionWrapper,
            "FunctionTraits<>::kind failed");
        
        static_assert(FunctionTraits<std::function<int(float,int)>>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
            FunctionTraits<std::function<int(float,int)>>::kind == FunctionKind::FunctionWrapper,
            "FunctionTraits<>::kind failed");
        
        static_assert(FunctionTraits<std::function<char*(char[])>>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
            FunctionTraits<std::function<char*(char[])>>::kind == FunctionKind::FunctionWrapper,
            "FunctionTraits<>::kind failed");
    }

    SECTION("type lambda")  // [] () {}
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;
        
        auto l1 = [] () {};
        auto l2 = [] (int&) { return "hello"; };
        auto l3 = [] (float, float[]) -> float { return 3.1415927f; };
        
        static_assert(FunctionTraits<decltype(l1)>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
                      FunctionTraits<decltype(l1)>::kind == FunctionKind::Lambda,
                      "FunctionTraits<>::kind failed");
        
        static_assert(FunctionTraits<decltype(l2)>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
                      FunctionTraits<decltype(l2)>::kind == FunctionKind::Lambda,
                      "FunctionTraits<>::kind failed");
        
        static_assert(FunctionTraits<decltype(l3)>::isFunction,
                      "FunctionTraits<>::kind failed");
        static_assert(
                      FunctionTraits<decltype(l3)>::kind == FunctionKind::Lambda,
                      "FunctionTraits<>::kind failed");
    }

    SECTION("functions can return values")
    {
        using ponder::detail::FunctionTraits;
        using ponder::FunctionKind;

        typedef decltype(&FuncReturn::i) fn;
        static_assert(FunctionTraits<fn>::isFunction, "");
        static_assert(FunctionTraits<fn>::kind == FunctionKind::MemberFunction, "");

        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::i)>::ReturnType,
                                                  const int>::value, "");
        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::f)>::ReturnType,
                                                  float>::value, "");
        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::ip)>::ReturnType,
                                                  int*>::value, "");
        
        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::sp)>::ReturnType,
                                                  std::shared_ptr<Callable>>::value, "");

        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::ai)>::ReturnType,
                                              std::vector<int>>::value, "");
        static_assert(std::is_same<FunctionTraits<decltype(&FuncReturn::as)>::ReturnType,
                                              std::vector<std::shared_ptr<Callable>>>::value, "");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Ponder has object traits")
{
    SECTION("types can be tested for being writable")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
        // is writable
        static_assert(ObjectTraits<int*>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
        static_assert(ObjectTraits<char**>::isWritable,
                      "ObjectTraits<>::isWriteable failed");

        // is not writable
        static_assert( ! ObjectTraits<const int>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
        static_assert( ! ObjectTraits<int>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
        static_assert( ! ObjectTraits<const int*>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
        static_assert( ! ObjectTraits<const char * const *>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
        static_assert( ! ObjectTraits<void(...)>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert( ! ObjectTraits<decltype(intArray)>::isWritable,
                      "ObjectTraits<>::isWriteable failed");
    }

    SECTION("types can be references")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;

        // is ref
        static_assert(ObjectTraits<int*>::isRef, "ObjectTraits<>::isRef failed");
        static_assert(ObjectTraits<char**>::isRef, "ObjectTraits<>::isRef failed");
        static_assert(ObjectTraits<decltype(intArray)>::isRef,
                      "ObjectTraits<>::isRef failed");

        static_assert(ponder::detail::ObjectTraits<int&>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert(ponder::detail::ObjectTraits<int&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::isRef failed");
        static_assert(ponder::detail::ObjectTraits<int*&>::isRef,
                      "ObjectTraits<>::isRef failed");

        // is not ref
        static_assert( ! ObjectTraits<int>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert( ! ObjectTraits<float>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert( ! ObjectTraits<void(...)>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert( ! ponder::detail::ObjectTraits<Callable>::isRef,
                      "ObjectTraits<>::isRef failed");
        static_assert(ponder::detail::ObjectTraits<Callable>::kind != ObjectKind::Reference,
                      "ObjectTraits<>::isRef failed");
        static_assert( ! ponder::detail::ObjectTraits<NonCallable>::isRef,
                      "ObjectTraits<>::isRef failed");
    }

    SECTION("types can be converted to reference types")
    {
        using ponder::detail::ObjectTraits;

        static_assert(
            std::is_same<int&, ObjectTraits<int>::RefReturnType>::value,
            "ObjectTraits<>::RefReturnType failed");
        static_assert(
            std::is_same<float&, ObjectTraits<const float>::RefReturnType>::value,
            "ObjectTraits<>::RefReturnType failed");
    
        // ref return
        static_assert(
            std::is_same<int*, ObjectTraits<int*>::RefReturnType>::value,
            "ObjectTraits<>::RefReturnType failed");
        static_assert(
            std::is_same<const int*,
                         ObjectTraits<const int*>::RefReturnType>::value,
            "ObjectTraits<>::RefReturnType failed");
    }

    SECTION("types can be pointers")
    {
        using ponder::detail::ObjectTraits;

        // pointer type
        static_assert(std::is_same<int*, ObjectTraits<int*>::PointerType>::value,
                      "ObjectTraits<>::PointerType failed");
        static_assert(
            std::is_same<const int*, ObjectTraits<const int*>::PointerType>::value,
            "ObjectTraits<>::PointerType failed");
    }

    SECTION("is a smart pointer")
    {
        using ponder::detail::IsSmartPointer;
        
        static_assert(IsSmartPointer<int, int>::value == false,
                      "IsSmartPointer<> failed");

        static_assert(IsSmartPointer<int*, int>::value == false,
                      "IsSmartPointer<> failed");

        static_assert(IsSmartPointer<const int*, int>::value == false,
                      "IsSmartPointer<> failed");

        static_assert(IsSmartPointer<TraitsTest::TemplateClass<int>, int>::value == false,
                      "IsSmartPointer<> failed");

        static_assert(IsSmartPointer<std::unique_ptr<int>, int>::value == true,
                      "IsSmartPointer<> failed");

        static_assert(IsSmartPointer<std::shared_ptr<int>, int>::value == true,
                      "IsSmartPointer<> failed");
    }

    SECTION("types have a raw data type")
    {
        using ponder::detail::ObjectTraits;

        static_assert(std::is_same<int, ObjectTraits<int>::DataType>::value,
                      "ObjectTraits<>::DataType failed");
        static_assert(std::is_same<int, ObjectTraits<int*>::DataType>::value,
                      "ObjectTraits<>::DataType failed");
        static_assert(std::is_same<int, ObjectTraits<const int>::DataType>::value,
                      "ObjectTraits<>::DataType failed");
        static_assert(std::is_same<int, ObjectTraits<const int*>::DataType>::value,
                      "ObjectTraits<>::DataType failed");
        static_assert(std::is_same<int, ObjectTraits<int **>::DataType>::value,
                      "ObjectTraits<>::DataType failed");
        static_assert(
            std::is_same<int, ObjectTraits<decltype(intArray)>::DataType>::value,
            "ObjectTraits<>::DataType failed");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Object traits are classfied")
{
    SECTION("type object")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
        static_assert(ObjectTraits<int>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
        static_assert(ObjectTraits<float>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
        static_assert(ObjectTraits<Methods>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
//        static_assert(ObjectTraits<const int>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
//        static_assert(ObjectTraits<const float>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
//        static_assert(ObjectTraits<const Methods>::kind == ObjectKind::Object, "ObjectTraits<>::kind");
        
        static_assert(ObjectTraits<int*>::kind != ObjectKind::Object, "ObjectTraits<>::kind");
    }

    SECTION("type pointer")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
        static_assert(ObjectTraits<int*>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<float*>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<Methods*>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");

        static_assert(ObjectTraits<int**>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<float**>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<Methods**>::kind == ObjectKind::Pointer,
                      "ObjectTraits<>::kind");
    }
    
    SECTION("type reference")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
        static_assert(ObjectTraits<int&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<float&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<Methods&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
        
        static_assert(ObjectTraits<const int&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<const float&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<const Methods&>::kind == ObjectKind::Reference,
                      "ObjectTraits<>::kind");
    }
    
    SECTION("type smart pointer")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
//        static_assert(ObjectTraits<std::unique_ptr<Methods>>::kind == ObjectKind::SmartPointer,
//                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<std::shared_ptr<Methods>>::kind == ObjectKind::SmartPointer,
                      "ObjectTraits<>::kind");
    }

    SECTION("type builtin array")
    {
        using ponder::detail::ObjectTraits;
        using ponder::ObjectKind;
        
        static_assert(ObjectTraits<int[1]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<int[1000]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<float[1]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<Methods[10]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<int[10][10]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
        static_assert(ObjectTraits<int[10][20][30]>::kind == ObjectKind::BuiltinArray,
                      "ObjectTraits<>::kind");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Type testing")
{
    SECTION("find raw type of any type")
    {
        using ponder::detail::RawType;

        static_assert(std::is_same<int, RawType<int>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<int, RawType<int*>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<int, RawType<int**>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<int, RawType<int***>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<int, RawType<int&>::Type>::value, "RawType<> fail");

        static_assert(std::is_same<char, RawType<char>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<float, RawType<float*>::Type>::value, "RawType<> fail");
        
        static_assert(std::is_same<std::string, RawType<std::string>::Type>::value,
                      "RawType<> fail");
        static_assert(std::is_same<std::string, RawType<std::string&>::Type>::value,
                      "RawType<> fail");
        static_assert(std::is_same<std::string, RawType<const std::string&>::Type>::value,
                      "RawType<> fail");
        static_assert(std::is_same<std::string, RawType<std::string*>::Type>::value,
                      "RawType<> fail");
        static_assert(std::is_same<std::string, RawType<const std::string*>::Type>::value,
                      "RawType<> fail");

        static_assert(std::is_same<Callable, RawType<Callable>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<Callable, RawType<Callable*>::Type>::value, "RawType<> fail");
        static_assert(std::is_same<Callable, RawType<Callable&>::Type>::value, "RawType<> fail");
    }

    SECTION("which are user types")
    {
        using ponder::detail::IsUserType;
        
        static_assert( ! IsUserType<int>::value, "IsUserType<> fail");
        static_assert( ! IsUserType<char*>::value, "IsUserType<> fail");
        static_assert( ! IsUserType<std::string>::value, "IsUserType<> fail");
        static_assert( ! IsUserType<ponder::Value>::value, "IsUserType<> fail");
        static_assert( ! IsUserType<Enum>::value, "IsUserType<> fail");
        static_assert( ! IsUserType<EnumCls>::value, "IsUserType<> fail");
        
        static_assert(IsUserType<Callable>::value, "IsUserType<> fail");
        static_assert(IsUserType<NonCallable>::value, "IsUserType<> fail");
    }

    SECTION("which are user types")
    {
        using ponder::detail::IsUserObjRef;
        
        static_assert( ! IsUserObjRef<int>::value, "IsUserObjRef<> fail");
        static_assert( ! IsUserObjRef<Callable>::value, "IsUserObjRef<> fail");
        static_assert( ! IsUserObjRef<NonCallable>::value, "IsUserObjRef<> fail");

        static_assert(IsUserObjRef<NonCallable*>::value, "IsUserObjRef<> fail");
        static_assert(IsUserObjRef<NonCallable&>::value, "IsUserObjRef<> fail");
        static_assert(IsUserObjRef<const NonCallable&>::value, "IsUserObjRef<> fail");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Types supporting array interface are supported")
{
    SECTION("not arrays")
    {
        static_assert( ! ponder_ext::ArrayMapper<int>::isArray, "ponder_ext::ArrayMapper failed");
        static_assert( ! ponder_ext::ArrayMapper<char*>::isArray, "ponder_ext::ArrayMapper failed");
    }

    SECTION("C arrays")
    {
        static_assert(ponder_ext::ArrayMapper<int[10]>::isArray, "ponder_ext::ArrayMapper failed");
        static_assert(std::is_same<int, ponder_ext::ArrayMapper<int[10]>::ElementType>::value,
                      "ponder_ext::ArrayMapper failed");
    }

    SECTION("std::array")
    {
        static_assert(ponder_ext::ArrayMapper<std::array<int, 10>>::isArray,
                      "ponder_ext::ArrayMapper failed");
        static_assert(
            std::is_same<int, ponder_ext::ArrayMapper<std::array<int, 10>>::ElementType>::value,
            "ponder_ext::ArrayMapper failed");
    }

    SECTION("std::vector")
    {
        static_assert(ponder_ext::ArrayMapper<std::vector<int>>::isArray,
                      "ponder_ext::ArrayMapper failed");
        static_assert(
            std::is_same<int, ponder_ext::ArrayMapper<std::vector<int>>::ElementType>::value,
            "ponder_ext::ArrayMapper failed");
    }

    SECTION("std::list")
    {
        static_assert(ponder_ext::ArrayMapper<std::list<int>>::isArray,
                      "ponder_ext::ArrayMapper failed");
        static_assert(
            std::is_same<int, ponder_ext::ArrayMapper<std::list<int>>::ElementType>::value,
            "ponder_ext::ArrayMapper failed");
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Lexical cast is used")
{
    SECTION("lexical_cast_to_string")
    {
        const unsigned int ui = 234;
        REQUIRE(ponder::detail::convert<ponder::String>(ui) == std::to_string(ui));
    
        const int i = -17;
        REQUIRE(ponder::detail::convert<ponder::String>(i) == std::to_string(i));
    
        const float f = 108.75f;
        REQUIRE(ponder::detail::convert<ponder::String>(f) == "108.75");

        const double d = 108.125;
        REQUIRE(ponder::detail::convert<ponder::String>(d) == "108.125");

        const bool bt = true, bf = false;
        REQUIRE(ponder::detail::convert<ponder::String>(bt) == "1");
        REQUIRE(ponder::detail::convert<ponder::String>(bf) == "0");
    }

    SECTION("lexical_cast_to_bool")
    {
        const ponder::String b1("1");
        REQUIRE(ponder::detail::convert<bool>(b1) == true);

        const ponder::String b2("0");
        REQUIRE(ponder::detail::convert<bool>(b2) == false);

        const ponder::String bt("true");
        REQUIRE(ponder::detail::convert<bool>(bt) == true);

        const ponder::String bf("false");
        REQUIRE(ponder::detail::convert<bool>(bf) == false);
    }

    SECTION("lexical_cast_to_char")
    {
        REQUIRE(ponder::detail::convert<char>(ponder::String("0")) == '0');
        REQUIRE(ponder::detail::convert<char>(ponder::String("g")) == 'g');
        REQUIRE_THROWS_AS(ponder::detail::convert<char>(ponder::String()),
                          ponder::detail::bad_conversion);
        REQUIRE_THROWS_AS(ponder::detail::convert<char>(ponder::String("27")),
                          ponder::detail::bad_conversion);
    
        REQUIRE(ponder::detail::convert<unsigned char>(ponder::String("0")) == '0');
        REQUIRE(ponder::detail::convert<unsigned char>(ponder::String("g")) == 'g');
        REQUIRE_THROWS_AS(ponder::detail::convert<unsigned char>(ponder::String()),
                          ponder::detail::bad_conversion);
        REQUIRE_THROWS_AS(ponder::detail::convert<unsigned char>(ponder::String("27")),
                          ponder::detail::bad_conversion);
    }

    SECTION("lexical_cast_to_short")
    {
        REQUIRE(ponder::detail::convert<short>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<short>(ponder::String("2600")) == 2600);
        REQUIRE(ponder::detail::convert<short>(ponder::String("-27")) == -27);
    
        REQUIRE(ponder::detail::convert<unsigned short>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<unsigned short>(ponder::String("2600")) == 2600u);
        REQUIRE(ponder::detail::convert<unsigned short>(ponder::String("-27"))
                == static_cast<unsigned short>(-27));
    }

    SECTION("lexical_cast_to_int")
    {
        REQUIRE(ponder::detail::convert<int>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<int>(ponder::String("123456789")) == 123456789);
        REQUIRE(ponder::detail::convert<int>(ponder::String("-27")) == -27);

        REQUIRE(ponder::detail::convert<unsigned int>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<unsigned int>(ponder::String("123456789")) == 123456789u);
        REQUIRE(ponder::detail::convert<unsigned int>(ponder::String("-27"))
                == static_cast<unsigned int>(-27));
    
        REQUIRE_THROWS_AS(ponder::detail::convert<int>(ponder::String("bad number")),
                          ponder::detail::bad_conversion);
    }

    SECTION("lexical_cast_to_long")
    {
        REQUIRE(ponder::detail::convert<long long>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<long long>(ponder::String("1125899906842624"))
                == 1125899906842624ll);
        REQUIRE(ponder::detail::convert<long long>(ponder::String("-27")) == -27);
    
        REQUIRE(ponder::detail::convert<unsigned long long>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<unsigned long long>(ponder::String("1125899906842624"))
                == 1125899906842624ull);
        REQUIRE(ponder::detail::convert<unsigned long long>(ponder::String("-27"))
                == static_cast<unsigned long long>(-27));
    }

    SECTION("lexical_cast_to_float")
    {
        REQUIRE(ponder::detail::convert<float>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<float>(ponder::String("100.25")) == 100.25f);
        REQUIRE(ponder::detail::convert<float>(ponder::String("-27.75")) == -27.75f);
    }

    SECTION("lexical_cast_to_double")
    {
        REQUIRE(ponder::detail::convert<double>(ponder::String("0")) == 0);
        REQUIRE(ponder::detail::convert<double>(ponder::String("100.25")) == 100.25);
        REQUIRE(ponder::detail::convert<double>(ponder::String("-27.75")) == -27.75);
    }
}

//----------------------------------------------------------------------------------------

// From: http://en.cppreference.com/w/cpp/utility/integer_sequence

template<typename R, typename Array, std::size_t... I>
R a2t_impl(const Array& a, _PONDER_SEQNS::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}

template< typename R,
          typename T,
          std::size_t N,
          typename Indices = _PONDER_SEQNS::make_index_sequence<N> >
R a2t(const std::array<T, N>& a)
{
    return a2t_impl<R>(a, Indices());
}

TEST_CASE("Check Ponder utilities work correctly")
{
    SECTION("integer_sequence")
    {
        auto is = _PONDER_SEQNS::make_index_sequence<3>();
        REQUIRE(is.size() == 3);

        std::array<int, 4> array {{1,2,3,4}};
    
        // convert an array into a tuple
        auto tuple = a2t<std::tuple<int, int, int, int>>(array);
        static_assert(std::is_same<decltype(tuple), std::tuple<int, int, int, int>>::value, "");
    }
    
    SECTION("allTrue")
    {
        REQUIRE(ponder::detail::allTrue() == true);
        REQUIRE(ponder::detail::allTrue(true) == true);
        REQUIRE(ponder::detail::allTrue(true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true, true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true, true, true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true, true, true, true, true) == true);
        REQUIRE(ponder::detail::allTrue(true, true, true, true, true, true, true, true) == true);
    
        REQUIRE(ponder::detail::allTrue(false) == false);
        REQUIRE(ponder::detail::allTrue(true, false) == false);
        REQUIRE(ponder::detail::allTrue(true, false, true) == false);
        REQUIRE(ponder::detail::allTrue(true, true, false, true) == false);
        REQUIRE(ponder::detail::allTrue(true, true, true, false, true) == false);
        REQUIRE(ponder::detail::allTrue(true, false, true, true, true, true) == false);
        REQUIRE(ponder::detail::allTrue(true, true, false, true, true, true, true) == false);
        REQUIRE(ponder::detail::allTrue(true, false, true, true, true, false, true, true) == false);
    }
    
    SECTION("type to string")
    {
        REQUIRE(strcmp(ponder::detail::valueTypeAsString(ponder::ValueKind::None), "none")==0);
        REQUIRE(strcmp(ponder::detail::valueTypeAsString(ponder::ValueKind::Real), "real")==0);
        REQUIRE(strcmp(ponder::detail::valueTypeAsString(ponder::ValueKind::User), "user")==0);
    }
}

//----------------------------------------------------------------------------------------

TEST_CASE("Check IdTraits")
{
    SECTION("cstr")
    {
        const char *t1 = "flibaddydib";
        ponder::Id id(t1);
        ponder::IdRef ir(id);
        
        REQUIRE(strcmp(ponder::id::c_str(ir), t1) == 0);
    }
}

//----------------------------------------------------------------------------------------

#ifdef TEST_BOOST
// This library used to use Boost. These checks are too make sure the functionality
// we rely on is the same as the one replaced.
TEST_CASE("Check functionality same as Boost")
{
    SECTION("check traits same as Boost")
    {
        typedef void (*fn1_t)(void);
        
        static_assert(std::is_same<void(),
                      boost::function_types::function_type<fn1_t>::type>::value,
                      "boost::function_types problem");
                      
        static_assert(std::is_same<void(), ponder::detail::FunctionTraits<fn1_t>::type>::value,
                      "ponder::detail::FunctionTraits problem");
    
        typedef int (*fn2_t)(int,const char*,float&);
        
        static_assert(std::is_same<int(int,const char*,float&),
                      boost::function_types::function_type<fn2_t>::type>::value,
                      "boost::function_types problem");
        static_assert(std::is_same<int(int,const char*,float&),
                      ponder::detail::FunctionTraits<fn2_t>::type>::value,
                      "ponder::detail::FunctionTraits problem");
    
        struct TestClass {
            int foo(float) {return 0;}
        };

        typedef int (TestClass::*fn3_t)(float);
        
        static_assert(std::is_same<int(TestClass&,float),
                      boost::function_types::function_type<fn3_t>::type>::value,
                      "boost::function_types problem");
                      
        static_assert(std::is_same<int(TestClass&,float),
                      ponder::detail::MethodDetails<fn3_t>::FunctionKind>::value,
                      "ponder::detail::MethodDetails problem");
                      
        static_assert(std::is_same<int(TestClass&,float),
                      ponder::detail::FunctionTraits<fn3_t>::type>::value,
                      "ponder::detail::FunctionTraits problem");
    }

    SECTION("boost_function")
    {
        typedef void (*fn1_t)(void);
        static_assert(
            std::is_same<void(), boost::function_types::function_type<fn1_t>::type>::value,
            "boost::function_types problem");
    
        typedef int (*fn2_t)(int,const char*,float&);
        static_assert(std::is_same<int(int,const char*,float&),
             boost::function_types::function_type<fn2_t>::type>::value,
             "boost::function_types problem");
    
        struct TestClass {
            int foo(float) {return 0;}
        };

        typedef int (TestClass::*fn3_t)(float);
        static_assert(std::is_same<int(TestClass&,float),
             boost::function_types::function_type<fn3_t>::type>::value,
             "boost::function_types problem");
    }

    SECTION("boost_callable")
    {
        static_assert( ! boost::function_types::is_callable_builtin<void>::value,
                      "boost::callable problem");
        static_assert( ! boost::function_types::is_callable_builtin<int>::value,
                      "boost::callable problem");
        static_assert( ! boost::function_types::is_callable_builtin<char*>::value,
                      "boost::callable problem");
    
        struct TestClass {
            int foo(float) {return 0;}
            int i;
            int arr[5];
        };
        static_assert(boost::function_types::is_callable_builtin<void()>::value,
                      "boost::callable problem");
        static_assert(boost::function_types::is_callable_builtin<int(TestClass::*)(float)>::value,
                      "boost::callable problem");
    
        static_assert(boost::function_types::is_callable_builtin<int(TestClass::*)>::value,
                      "boost::callable problem");
        static_assert(boost::function_types::is_callable_builtin<int(TestClass::*)[5]>::value,
                      "boost::callable problem");
    }

    SECTION("boost_result_type")
    {
        struct TestClass {
            int foo(float) {return 0;}
        };
        static_assert(
                  std::is_same<int, boost::function_types::result_type<int()>::type>::value,
                  "boost::ret result_type");
        
        static_assert(
            std::is_same<int,
                         boost::function_types::result_type<int(TestClass::*)(void)>::type>::value,
                      "boost::ret result_type");
        
        static_assert(
            std::is_same<float,
                    boost::function_types::result_type<float(TestClass::*)(void)>::type>::value,
                    "boost::ret result_type");
    }    
}

#endif // TEST_BOOST

//----------------------------------------------------------------------------------------


