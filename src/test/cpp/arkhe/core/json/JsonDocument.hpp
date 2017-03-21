#ifndef ARKHE_CORE_JSONDOCUMENT_HPP
#define ARKHE_CORE_JSONDOCUMENT_HPP
#include <string>
#include <arkhe/core/json/JsonObject.hpp>
#include <arkhe/core/json/JsonArray.hpp>
#include <arkhe/core/json/JsonParseError.hpp>
#include <arkhe/core/json/Data.hpp>
namespace Json 
{
    class JsonDocument
    {
    public:        
        JsonDocument();
        virtual ~JsonDocument();
        explicit JsonDocument(const JsonObject &object);
        explicit JsonDocument(const JsonArray &array);
        
        static const uint32_t BinaryFormatTag = ('q') | ('b' << 8) | ('j' << 16) | ('s' << 24);

        JsonDocument(const JsonDocument &other);
        JsonDocument &operator =(const JsonDocument &other);

        enum DataValidation 
        {
            Validate,
            BypassValidation
        };

        static JsonDocument fromRawData(const char *data, int size, DataValidation validation = Validate);
        const char *rawData(int *size) const;

        static JsonDocument fromBinaryData(const std::string &data, DataValidation validation  = Validate);
        std::string toBinaryData() const;

        enum JsonFormat 
        {
            Indented,
            Compact
        };

        static JsonDocument fromJson(const std::string &json, JsonParseError *error = nullptr);

        std::string toJson(JsonFormat format = Indented) const;

        bool isEmpty() const;
        bool isArray() const;
        bool isObject() const;

        JsonObject object() const;
        JsonArray array() const;

        void setObject(const JsonObject &object);
        void setArray(const JsonArray &array);

        bool operator==(const JsonDocument &other) const;
        bool operator!=(const JsonDocument &other) const 
        { 
            return !(*this == other); 
        }

        bool isNull() const;

    private:
        friend class JsonValue;
        friend class Data;
        friend class Parser;

        JsonDocument(Data *data);
        Data *d;
    };
}
#endif
