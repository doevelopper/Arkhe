#ifndef ARKHE_CORE_HEADER_HPP
#define ARKHE_CORE_HEADER_HPP
#include <arkhe/core/json/Base.hpp>
namespace Json 
{
    class Header
    {
    public:
        Header();
        virtual ~Header();
        
        uint32_t tag;
        uint32_t version;
        Json::Base *root();
    };
}
#endif