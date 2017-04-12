
#include <arkhe/core/json/Value.hpp>
#include <arkhe/core/json/Array.hpp>
#include <arkhe/core/json/Object.hpp>
#include <arkhe/core/json/String.hpp>

// const Json::Base emptyArray =
// {
// sizeof(Json::Base),
// { 0 },
// 0
// };

// const Json::Base emptyObject =
// {
// sizeof(Json::Base),
// { 0 },
// 0
// };


Json::Value::Value()
{
}

Json::Value::~Value()
{
}

double Json::Value::toDouble (const Json::Base * b) const
{
    // assert(type == JsonValue::Double);
    if( intValue )
    {
        return int_value;
    }

    double d;
    memcpy(&d, (const char *)b + value, 8);

    return d;
}

char * Json::Value::data (const Base * b) const
{
    return ((char *)b ) + value;
}

std::string Json::Value::toString (const Base * b) const
{
    Json::String s(data(b));

    return s.toString();
}

Json::Base * Json::Value::base (const Base * b) const
{
    //// assert(type == JsonValue::Array || type == JsonValue::Object);

    return reinterpret_cast<Base *>( data(b));
}

int Json::Value::usedStorage (const Base * b) const
{
    int s = 0;

    switch( type )
    {
    case JsonValue::Double:

        if( intValue )
            break;

        s = sizeof( double );
        break;
    case JsonValue::String:
    {
        char * d = data(b);
        s = sizeof( int ) + ( *(int *)d );
        break;
    }
    case JsonValue::Array:
    case JsonValue::Object:

        // s = base(b)->size;
        break;
    case JsonValue::Null:
    case JsonValue::Bool:
    default:
        break;
    }

    return alignedSize(s);
}

bool Json::Value::isValid (const Base * b) const
{
    int offset = 0;

    switch( type )
    {
    case JsonValue::Double:

        if( intValue )
            break;

    // fall through
    case JsonValue::String:
    case JsonValue::Array:
    case JsonValue::Object:
        offset = value;
        break;
    case JsonValue::Null:
    case JsonValue::Bool:
    default:
        break;
    }

    if( !offset )
    {
        return true;
    }

    if( offset + sizeof( uint32_t ) > b->tableOffset )
    {
        return false;
    }

    int s = usedStorage(b);

    if( !s )
    {
        return true;
    }

    if( s < 0
        || offset + s > (int)b->tableOffset )
    {
        return false;
    }

    if( type == JsonValue::Array )
    {
        return static_cast<Json::Array *>( base(b))->isValid();
    }

    if( type == JsonValue::Object )
    {
        return static_cast<Json::Object *>( base(b))->isValid();
    }

    return true;
}

int Json::Value::requiredStorage (JsonValue & v, bool * compressed)
{
    *compressed = false;

    switch( v.t )
    {
    case JsonValue::Double:

        // if (compressedNumber(v.dbl) != INT_MAX)
    {
        *compressed = true;

        return 0;
    }

        return sizeof( double );

    case JsonValue::String:
    {
        // std::string s = v.toString().data();
        *compressed = false;

        // return qStringSize(s);
    }
    case JsonValue::Array:
    case JsonValue::Object:

        if( v.d
            && v.d->compactionCounter )
        {
            // v.detach();
            // v.d->compact();
            // v.base = static_cast<Internal::Base *>(v.d->header->root());
        }

    // return v.base ? v.base->size : sizeof(Base);
    case JsonValue::Undefined:
    case JsonValue::Null:
    case JsonValue::Bool:
        break;
    }

    return 0;
}

uint32_t Json::Value::valueToStore (const JsonValue & v, uint32_t offset)
{
    switch( v.t )
    {
    case JsonValue::Undefined:
    case JsonValue::Null:
        break;
    case JsonValue::Bool:

        return v.b;

    case JsonValue::Double:
    {
        // int c = compressedNumber(v.dbl);
        // if (c != INT_MAX)
        // return c;
    }

    // fall through
    case JsonValue::String:
    case JsonValue::Array:
    case JsonValue::Object:

        return offset;
    }

    return 0;
}

void Json::Value::copyData (const JsonValue & v, char * dest, bool compressed)
{
    switch( v.t )
    {
    case JsonValue::Double:

        if( !compressed )
            memcpy(dest, &v.ui, 8);

        break;
    case JsonValue::String:
    {
        std::string str = v.toString();

        // copyString(dest, str);
        break;
    }
    case JsonValue::Array:
    case JsonValue::Object:
    {
        const Base * b = v.base;

        if( !b )
        {
            // b = (v.t == JsonValue::Array ? &Json::emptyArray : &Json::emptyObject);
        }

        memcpy(dest, b, b->size);
        break;
    }
    default:
        break;
    }
}
