#ifndef ARKHE_CORE_JSONVALUEREFPTR_HPP
#define ARKHE_CORE_JSONVALUEREFPTR_HPP

// #include <arkhe/core/json/JsonValueRef.hpp>
// #include <arkhe/core/json/JsonArray.hpp>
// #include <arkhe/core/json/JsonObject.hpp>
namespace Json 
{
	class JsonValueRef;
	class JsonArray;
	class JsonObject;

    class JsonValueRefPtr
    {
        // JsonValueRef valueRef;
    public:
		JsonValueRefPtr();
		virtual ~JsonValueRefPtr();
	
        // JsonValueRefPtr(Json::JsonArray *array, int idx);
        // JsonValueRefPtr(Json::JsonObject *object, int idx);

        JsonValueRef& operator*()
        {
            // return valueRef;
        }
        JsonValueRef* operator->()
        {
            // return &valueRef;
        }
    };
}

#endif