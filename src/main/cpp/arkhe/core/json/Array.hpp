#ifndef ARKHE_CORE_ARRAY_HPP
#define ARKHE_CORE_ARRAY_HPP

#include <arkhe/core/json/Base.hpp>
#include <arkhe/core/json/Value.hpp>
namespace Json 
{
    class Array : public Base
    {
    public:        
        Array();
        virtual ~Array();

        // Json::Value at(int i) const 
        // { 
            //return *(Json::Value *) (table() + i); 
        // }
        
        // Json::Value &operator[](int i) 
        // { 
            //return *(Json::Value *) (table() + i); 
        // }

        bool isValid() const;
    };
}
#endif
