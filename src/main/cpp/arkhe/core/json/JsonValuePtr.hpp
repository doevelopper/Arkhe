#ifndef ARKHE_CORE_JSONVALUEPTR_HPP
#define ARKHE_CORE_JSONVALUEPTR_HPP
#include <arkhe/core/json/JsonValue.hpp>
namespace Json 
{
    class JsonValuePtr
    {
        // Json::JsonValue value;
    public:
		JsonValuePtr();
		virtual ~JsonValuePtr();
/*		
        explicit JsonValuePtr(const Json::JsonValue& val)
        : value(val) {}

        Json::JsonValue& operator*() { return value; }
        Json::JsonValue* operator->() { return &value; }
*/
    };
}

#endif