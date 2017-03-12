#ifndef ARKHE_CORE_VALUE_HPP
#define ARKHE_CORE_VALUE_HPP

#include <string>
#include <arkhe/core/json/Json.hpp>
// #include <arkhe/core/json/JsonValue.hpp>
#include <arkhe/core/json/LittleEndianBitfield.hpp>
#include <arkhe/core/json/LittleEndianBitfield.hpp>
#include <arkhe/core/json/Base.hpp>

namespace Json 
{
    // static const Base emptyArray = { sizeof(Base), { 0 }, 0 };
    // static const Base emptyObject = { sizeof(Base), { 0 }, 0 };
    class JsonValue;
    class Value
    {
    public:
        Value();
        virtual ~Value();
        
        enum 
        {
            MaxSize = (1<<27) - 1
        };
        
        union 
        {
            uint32_t _dummy;
            Json::LittleEndianBitfield<0, 3> type;
            Json::LittleEndianBitfield<3, 1> intValue;
            Json::LittleEndianBitfield<4, 1> _; // Ex-latin1Key
            Json::LittleEndianBitfield<5, 27> value;  // Used as offset in case of Entry(?)
            Json::LittleEndianSignedBitfield<5, 27> int_value;
        };

        char * data(const Base *b) const;
        int usedStorage(const Base *b) const;

        bool toBoolean() const 
        { 
            return value != 0; 
        }
        double toDouble(const Base *b) const;
        std::string toString(const Base *b) const;
        Base *base(const Base *b) const;

        bool isValid(const Base *b) const;

        static int requiredStorage(JsonValue &v, bool *compressed);
        static uint32_t valueToStore(const JsonValue &v, uint32_t offset);
        static void copyData(const JsonValue &v, char *dest, bool compressed);
		// static const Base emptyArray;
		// static const Base emptyObject;
    };
}
#endif


