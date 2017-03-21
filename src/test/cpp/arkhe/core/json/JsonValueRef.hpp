#ifndef ARKHE_CORE_JSONVALUEREF_HPP
#define ARKHE_CORE_JSONVALUEREF_HPP

#include <arkhe/core/json/JsonArray.hpp>
#include <arkhe/core/json/JsonObject.hpp>
#include <arkhe/core/json/JsonValue.hpp>

namespace Json 
{
    class JsonValueRef
    {
    public:
		JsonValueRef();
		virtual ~JsonValueRef();/*
        JsonValueRef(Json::JsonArray *array, int idx);
        JsonValueRef(Json::JsonObject *object, int idx);
    
        operator Json::JsonValue() const
        {
            return toValue();
        }

        JsonValueRef &operator=(const Json::JsonValue &val);
        JsonValueRef &operator=(const JsonValueRef &val);
    
        JsonValue::Type type() const ;
        bool isNull() const;
        bool isBool() const;
        bool isDouble() const;
        bool isString() const;
        bool isArray() const;
        bool isObject() const;
        bool isUndefined() const;
    
        std::string toString() const;
        Json::JsonArray toArray() const;
        Json::JsonObject toObject() const;
    
        bool toBool(bool defaultValue = false) const;
        int toInt(int defaultValue = 0) const;
        double toDouble(double defaultValue = 0) const;
        std::string toString(const std::string &defaultValue) const;
    
        bool operator==(const Json::JsonValue &other) const
        {
            return toValue() == other;
        }
        bool operator!=(const Json::JsonValue &other) const
        {
            return toValue() != other;
        }

    private:
        Json::JsonValue toValue() const;
    
        union
        {
            Json::JsonArray *a;
            Json::JsonObject *o;
        };
        uint32_t is_object : 1;
        uint32_t index : 31;*/
    };
}
#endif