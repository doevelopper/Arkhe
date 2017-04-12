
#include <arkhe/core/json/Json.hpp>
#include <arkhe/core/json/String.hpp>

// const Json::Base Json::emptyArray = { sizeof(Json::Base), { 0 }, 0 };
// const Json::Base Json::emptyObject = { sizeof(Json::Base), { 0 }, 0 };

int Json::qStringSize (const std::string & ba)
{
    int l = 4 + static_cast<int>( ba.length());

    return Json::alignedSize(l);
}

void Json::copyString (char * dest, const std::string & str)
{
    Json::String string(dest);
    string = str;
}

void Json::toInternal (char * addr, const char * data, int size)
{
    memcpy(addr, &size, 4);
    memcpy(addr + 4, data, size);
}

int Json::compressedNumber (double d)
{
    // this relies on details of how ieee floats are represented
    const int exponent_off = 52;
    const uint64_t fraction_mask = 0x000fffffffffffffull;
    const uint64_t exponent_mask = 0x7ff0000000000000ull;

    uint64_t val;
    memcpy (&val, &d, sizeof( double ));
    int exp = (int)(( val & exponent_mask ) >> exponent_off ) - 1023;

    if( exp < 0
        || exp > 25 )
    {
        return INT_MAX;
    }

    uint64_t non_int = val & ( fraction_mask >> exp );

    if( non_int )
    {
        return INT_MAX;
    }

    bool neg = ( val >> 63 ) != 0;
    val &= fraction_mask;
    val |= ((uint64_t)1 << 52 );
    int res = (int)( val >> ( 52 - exp ));

    return ( neg ? -res : res );
}

/*
        string = quotation-mark *char quotation-mark

        char = unescaped /
               escape (
                   %x22 /          ; "    quotation mark  U+0022
                   %x5C /          ; \    reverse solidus U+005C
                   %x2F /          ; /    solidus         U+002F
                   %x62 /          ; b    backspace       U+0008
                   %x66 /          ; f    form feed       U+000C
                   %x6E /          ; n    line feed       U+000A
                   %x72 /          ; r    carriage return U+000D
                   %x74 /          ; t    tab             U+0009
                   %x75 4HEXDIG )  ; uXXXX                U+XXXX

        escape = %x5C              ; \

        quotation-mark = %x22      ; "

        unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
 */
bool Json::addHexDigit (char digit, uint32_t * result)
{
    *result <<= 4;

    if( digit >= '0'
        && digit <= '9' )
    {
        *result |= ( digit - '0' );
    }
    else
    if( digit >= 'a'
        && digit <= 'f' )
    {
        *result |= ( digit - 'a' ) + 10;
    }
    else
    if( digit >= 'A'
        && digit <= 'F' )
    {
        *result |= ( digit - 'A' ) + 10;
    }
    else
    {
        return ( false );
    }

    return ( true );
}
