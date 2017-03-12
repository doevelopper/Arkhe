#ifndef ARKHE_CORE_PARSER_HPP
#define ARKHE_CORE_PARSER_HPP
#include <cstdint>
#include <arkhe/core/json/JsonParseError.hpp>
#include <arkhe/core/json/Entry.hpp>
#include <arkhe/core/json/JsonDocument.hpp>
namespace Json 
{
    class Parser
    {
    public:
  
        Parser();
        virtual ~Parser();
        Parser(const char *json, int length);

        JsonDocument parse(JsonParseError *error);

        class ParsedObject
        {
        public:
            ParsedObject(Parser *p, int pos) : parser(p), objectPosition(pos) 
            {
                offsets.reserve(64);
            }
            
            void insert(uint32_t offset);

            Parser *parser;
            int objectPosition;
            std::vector<uint32_t> offsets;

            Entry *entryAt(size_t i) const 
            {
                return reinterpret_cast<Entry *>(parser->data + objectPosition + offsets[i]);
            }
        };
        
    private:
        void eatBOM();
        bool eatSpace();
        char nextToken();

        bool parseObject();
        bool parseArray();
        bool parseMember(int baseOffset);
        bool parseString();
        bool parseEscapeSequence();
        bool parseValue(Value *val, int baseOffset);
        bool parseNumber(Value *val, int baseOffset);

        void addChar(char c) 
        {
            const int pos = reserveSpace(1);
            data[pos] = c;
        }

        const char *head;
        const char *json;
        const char *end;

        char *data;
        int dataLength;
        int current;
        int nestingLevel;
        JsonParseError::ParseError lastError;

        int reserveSpace(int space) 
        {
            if (current + space >= dataLength) 
            {
                dataLength = 2*dataLength + space;
                data = (char *)realloc(data, dataLength);
            }

            int pos = current;
            current += space;
            return pos;
        }
    };
}
#endif

