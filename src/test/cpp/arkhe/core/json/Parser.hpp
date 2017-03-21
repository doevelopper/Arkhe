#ifndef ARKHE_CORE_PARSER_HPP
#define ARKHE_CORE_PARSER_HPP
#include <cstdint>
#include <iostream>
#include <arkhe/core/json/JsonParseError.hpp>
#include <arkhe/core/json/Entry.hpp>
#include <arkhe/core/json/JsonDocument.hpp>

#ifdef PARSER_DEBUG
    static int indent = 0;
    #define BEGIN std::cerr << std::string(4*indent++, ' ').data() << " pos=" << current
    #define END --indent
    #define DEBUG std::cerr << std::string(4*indent, ' ').data()
#else
    #define BEGIN if (1) ; else std::cerr
    #define END do {} while (0)
    #define DEBUG if (1) ; else std::cerr
#endif

static const int nestingLimit = 1024;

namespace Json 
{
    class Parser
    {
    public:
        enum
        {
            Space = 0x20,
            Tab = 0x09,
            LineFeed = 0x0a,
            Return = 0x0d,
            BeginArray = 0x5b,
            BeginObject = 0x7b,
            EndArray = 0x5d,
            EndObject = 0x7d,
            NameSeparator = 0x3a,
            ValueSeparator = 0x2c,
            Quote = 0x22
        };
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

        int reserveSpace(int space);
    };
}
#endif

