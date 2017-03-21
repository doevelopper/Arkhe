#ifndef ARKHE_CORE_SHAREDSTRING_HPP
#define ARKHE_CORE_SHAREDSTRING_HPP

#include <string>
#include <arkhe/core/json/AtomicInt.hpp>

namespace Json 
{
    class SharedString
    {
    public:
        SharedString();
        virtual ~SharedString();
        
        AtomicInt ref;
        std::string s;
    };
}
#endif