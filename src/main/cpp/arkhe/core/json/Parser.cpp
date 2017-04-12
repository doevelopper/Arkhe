
#include <ios>
#include <arkhe/core/json/Json.hpp>
#include <arkhe/core/json/Parser.hpp>
#include <arkhe/core/json/JsonParseError.hpp>

Json::Parser::Parser()
{
}

Json::Parser::~Parser()
{
}

Json::Parser::Parser(const char * json, int length)
    : head(json)
        , json(json)
        , data(0)
        , dataLength(0)
        , current(0)
        , nestingLevel(0)
        , lastError(JsonParseError::NoError)
{
    end = json + length;
}

void Json::Parser::eatBOM ()
{
    // eat UTF-8 byte order mark
    if( end - json > 3
        && (unsigned char)json [0] == 0xef
        && (unsigned char)json [1] == 0xbb
        && (unsigned char)json [2] == 0xbf )
    {
        json += 3;
    }
}

bool Json::Parser::eatSpace ()
{
    while( json < end )
    {
        if( *json > Space )
        {
            break;
        }

        if( *json != Space
            && *json != Tab
            && *json != LineFeed
            && *json != Return )
        {
            break;
        }

        ++json;
    }

    return ( json < end );
}

char Json::Parser::nextToken ()
{
    if( !eatSpace())
    {
        return 0;
    }

    char token = *json++;

    switch( token )
    {
    case BeginArray:
    case BeginObject:
    case NameSeparator:
    case ValueSeparator:
    case EndArray:
    case EndObject:
        eatSpace();
    case Quote:
        break;
    default:
        token = 0;
        break;
    }

    return token;
}

Json::JsonDocument Json::Parser::parse (Json::JsonParseError * error)
{
   #ifdef PARSER_DEBUG
        indent = 0;
        std::cerr << ">>>>> parser begin";
   #endif
    dataLength = static_cast<int>( std::max(end - json, std::ptrdiff_t(256)));
    data = (char *)malloc(dataLength);

    Header * h = (Header *)data;
    h->tag = JsonDocument::BinaryFormatTag;
    h->version = 1u;

    current = sizeof( Header );

    eatBOM();
    char token = nextToken();

    DEBUG << std::hex << (uint32_t)token;

    if( token == BeginArray )
    {
        if( !parseArray())
        {
            // goto error;
        }
    }
    else
    if( token == BeginObject )
    {
        if( !parseObject())
        {
            // goto error;
        }
    }
    else
    {
        lastError = JsonParseError::IllegalValue;

        // goto error;
    }

    eatSpace();

    if( json < end )
    {
        lastError = JsonParseError::GarbageAtEnd;
        goto error;
    }

    END;
    {
        if( error )
        {
            error->offset = 0;
            error->error  = JsonParseError::NoError;
        }

        Data * d = new Data(data, current);

        // return JsonDocument(d);
    }

error:
   #ifdef PARSER_DEBUG
        std::cerr << ">>>>> parser error";
   #endif

    if( error )
    {
        error->offset = static_cast<int>( json - head );
        error->error  = lastError;
    }

    free(data);

    return JsonDocument();
}

void Json::Parser::ParsedObject::insert (uint32_t offset)
{
    const Entry * newEntry = reinterpret_cast<const Entry *>( parser->data + objectPosition + offset );
    size_t min = 0;
    size_t n   = offsets.size();

    while( n > 0 )
    {
        size_t half   = n >> 1;
        size_t middle = min + half;

        if( *entryAt(middle) >= *newEntry )
        {
            n = half;
        }
        else
        {
            min = middle + 1;
            n  -= half + 1;
        }
    }

    if( min < offsets.size()
        && *entryAt(min) == *newEntry )
    {
        offsets [min] = offset;
    }
    else
    {
        offsets.insert(offsets.begin() + min, offset);
    }
}

/*
    object = begin-object [ member *( value-separator member ) ]
    end-object
 */
bool Json::Parser::parseObject ()
{
    if( ++nestingLevel > nestingLimit )
    {
        lastError = JsonParseError::DeepNesting;

        return false;
    }

    int objectOffset = reserveSpace(sizeof( Object ));
    BEGIN << "parseObject pos=" << objectOffset << current << json;

    ParsedObject parsedObject(this, objectOffset);

    char token = nextToken();

    while( token == Quote )
    {
        int off = current - objectOffset;

        if( !parseMember(objectOffset))
        {
            return false;
        }

        parsedObject.insert(off);
        token = nextToken();

        if( token != ValueSeparator )
        {
            break;
        }

        token = nextToken();

        if( token == EndObject )
        {
            lastError = JsonParseError::MissingObject;

            return false;
        }
    }
}

/*
    member = string name-separator value
 */
bool Json::Parser::parseMember (int baseOffset)
{
    int entryOffset = reserveSpace(sizeof( Entry ));
    BEGIN << "parseMember pos=" << entryOffset;

    if( !parseString())
    {
        return false;
    }

    /*
       char token = nextToken();

       if (token != NameSeparator)
       {
           lastError = JsonParseError::MissingNameSeparator;
           return false;
       }

       Value val;
       if (!parseValue(&val, baseOffset))
       {
           return false;
       }

       // finalize the entry
       Entry *e = (Entry *)(data + entryOffset);
       e->value = val;

       END;
     */
    return true;
}

/*
    array = begin-array [ value *( value-separator value ) ] end-array
 */
bool Json::Parser::parseArray ()
{
}

/*
   value = false / null / true / object / array / number / string

 */

bool Json::Parser::parseValue (Value * val, int baseOffset)
{
}

/*
        number = [ minus ] int [ frac ] [ exp ]
        decimal-point = %x2E       ; .
        digit1-9 = %x31-39         ; 1-9
        e = %x65 / %x45            ; e E
        exp = e [ minus / plus ] 1*DIGIT
        frac = decimal-point 1*DIGIT
        int = zero / ( digit1-9 *DIGIT )
        minus = %x2D               ; -
        plus = %x2B                ; +
        zero = %x30                ; 0

 */

bool Json::Parser::parseNumber (Value * val, int baseOffset)
{
}

bool Json::Parser::parseEscapeSequence ()
{
    DEBUG << "scan escape" << (char)*json;
    const char escaped = *json++;

    switch( escaped )
    {
    case '"':
        addChar('"');
        break;
    case '\\':
        addChar('\\');
        break;
    case '/':
        addChar('/');
        break;
    case 'b':
        addChar(0x8);
        break;
    case 'f':
        addChar(0xc);
        break;
    case 'n':
        addChar(0xa);
        break;
    case 'r':
        addChar(0xd);
        break;
    case 't':
        addChar(0x9);
        break;
    case 'u':
    {
        uint32_t c = 0;

        if( json > end - 4 )
        {
            return false;
        }

        for( int i = 0 ; i < 4 ; ++i )
        {
            // if (!addHexDigit(*json, &c))
            {
                return false;
            }
            ++json;
        }

        if( c < 0x80 )
        {
            addChar(c);
            break;
        }

        if( c < 0x800 )
        {
            addChar(192 + c / 64);
            addChar(128 + c % 64);
            break;
        }

        if( c - 0xd800u < 0x800 )
        {
            return false;
        }

        if( c < 0x10000 )
        {
            addChar(224 + c / 4096);
            addChar(128 + c / 64 % 64);
            addChar(128 + c % 64);
            break;
        }

        if( c < 0x110000 )
        {
            addChar(240 + c / 262144);
            addChar(128 + c / 4096 % 64);
            addChar(128 + c / 64 % 64);
            addChar(128 + c % 64);
            break;
        }

        return ( false );
    }
    default:

        // this is not as strict as one could be, but allows for more Json files
        // to be parsed correctly.
        addChar(escaped);
        break;
    }

    return ( true );
}

bool Json::Parser::parseString ()
{
    const char * inStart = json;

    // First try quick pass without escapes.
    if( true )
    {
        while( 1 )
        {
            if( json >= end )
            {
                ++json;
                lastError = JsonParseError::UnterminatedString;

                return ( false );
            }

            const char c = *json;

            if( c == '"' )
            {
                // write string length and padding.
                const int len = static_cast<int>( json - inStart );
                const int pos = reserveSpace(4 + alignedSize(len));

                // toInternal(data + pos, inStart, len);
                END;

                ++json;

                return true;
            }

            if( c == '\\' )
            {
                break;
            }

            ++json;
        }
    }

    // Try again with escapes.
    const int outStart = reserveSpace(4);
    json = inStart;

    while( 1 )
    {
        if( json >= end )
        {
            ++json;
            lastError = JsonParseError::UnterminatedString;

            return false;
        }

        if( *json == '"' )
        {
            ++json;

            // write string length and padding.
            *(int *)( data + outStart ) = current - outStart - 4;
            reserveSpace(( 4 - current ) & 3);
            END;

            return true;
        }

        if( *json == '\\' )
        {
            ++json;

            if( json >= end
                || !parseEscapeSequence())
            {
                lastError = JsonParseError::IllegalEscapeSequence;

                return false;
            }
        }
        else
        {
            addChar(*json++);
        }
    }
}

int Json::Parser::reserveSpace (int space)
{
    if( current + space >= dataLength )
    {
        dataLength = 2 * dataLength + space;
        data = (char *)realloc(data, dataLength);
    }

    int pos = current;
    current += space;

    return pos;
}
