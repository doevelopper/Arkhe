#ifndef ARKHE_CORE_JSONVALUE_HPP
#define ARKHE_CORE_JSONVALUE_HPP

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

#include <arkhe/core/json/JsonArray.hpp>
#include <arkhe/core/json/JsonObject.hpp>
// #include <arkhe/core/json/Data.hpp>
#include <arkhe/core/json/Value.hpp>
#include <arkhe/core/json/Base.hpp>
#include <arkhe/core/json/SharedString.hpp>

namespace Json 
{
    // class JsonArray;
    // class JsonObject;
    class Data;
    // class Value;
    // class Base;
    // class SharedString;

    class JsonValue
    {
    public:
        enum Type 
        {
            Null =  0x0,
            Bool = 0x1,
            Double = 0x2,
            String = 0x3,
            Array = 0x4,
            Object = 0x5,
            Undefined = 0x80
        };
        
        JsonValue(Type = Null);
        JsonValue(bool b);
        JsonValue(double n);
        JsonValue(int n);
        JsonValue(int64_t n);
        JsonValue(const std::string &s);
        JsonValue(const char *s);
        virtual ~JsonValue();
        // JsonValue(const JsonArray &a);
        // JsonValue(const JsonObject &o);

        
        JsonValue(const JsonValue &other);
        JsonValue &operator =(const JsonValue &other);
        
        Type type() const;
        bool isNull() const;
        bool isBool() const;
        bool isDouble() const;
        bool isString() const;
        bool isArray() const;
        bool isObject() const;
        bool isUndefined() const;

        /*!
            @enum JsonValue::Type
        
            This enum describes the type of the JSON value.
        
            @value Null     A Null value
            @value Bool     A boolean value. Use toBool() to convert to a bool.
            @value Double   A double. Use toDouble() to convert to a double.
            @value String   A string. Use toString() to convert to a QString.
            @value Array    An array. Use toArray() to convert to a JsonArray.
            @value Object   An object. Use toObject() to convert to a JsonObject.
            @value Undefined The value is undefined. This is usually returned as an
                            error condition, when trying to read an out of bounds value
                            in an array or a non existent key in an object.
        */

        bool toBool(bool defaultValue = false) const;
        int toInt(int defaultValue = 0) const;
        double toDouble(double defaultValue = 0) const;
        std::string toString(const std::string &defaultValue = std::string()) const;
        // JsonArray toArray() const;
        // JsonArray toArray(const JsonArray &defaultValue) const;
        // JsonObject toObject() const;
        // JsonObject toObject(const JsonObject &defaultValue) const;

        bool operator==(const JsonValue &other) const;
        bool operator!=(const JsonValue &other) const;

    // protected:

    private:    
        // avoid implicit conversions from char * to bool
        JsonValue(const void *);
        friend class Value;
        // friend class JsonArray;
        // friend class JsonObject;

        JsonValue(Data *d, Base *b, const Value& v);


        void detach();
        union 
        {
            uint64_t ui;
            bool b;
            double dbl;
            SharedString *stringData;
            Base *base;
        };
        
        Data *d; // needed for Objects and Arrays
        Type t;
    };
    
}

#endif