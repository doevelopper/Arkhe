#include <arkhe/core/json/JsonValue.hpp>

Json::JsonValue::JsonValue(Type type)
    : ui(0)
    , d(0)
    , t(type)
{
    
}

Json::JsonValue::~JsonValue()
{
    if (t == String && stringData && !stringData->ref.deref())
    {
        // free(stringData);
    }

    // if (d && !d->ref.deref())
    {
        // delete d;
    }
}

Json::JsonValue::JsonValue(Data *data, Base *base, const Value &v)
    : d(0)
    , t((Type)(uint32_t)v.type)
{
    switch (t)
    {
        case Undefined:
        case Null:
            dbl = 0;
            break;
        case Bool:
            b = v.toBoolean();
            break;
        case Double:
            dbl = v.toDouble(base);
            break;
        case String:
        {
            stringData = new SharedString;
            stringData->s = v.toString(base);
            stringData->ref.ref();
            break;
        }
        case Array:
        case Object:
            d = data;
            this->base = v.base(base);
            break;
    }
    
    if (d)
    {
        // d->ref.ref();
    }
}

Json::JsonValue::JsonValue(bool b)
    : d(0)
    , t(Bool)
{
    this->b = b;
}

Json::JsonValue::JsonValue(double n)
    : d(0)
    , t(Double)
{
    this->dbl = n;
}

Json::JsonValue::JsonValue(int n)
    : d(0)
    , t(Double)
{
    this->dbl = n;
}

Json::JsonValue::JsonValue(int64_t n)
    : d(0)
    , t(Double)
{
    this->dbl = double(n);
}

Json::JsonValue::JsonValue(const std::string &s)
    : d(0)
    , t(String)
{
    stringData = new SharedString;
    stringData->s = s;
    stringData->ref.ref();
}

Json::JsonValue::JsonValue(const char *s)
    : d(0)
    , t(String)
{
    stringData = new SharedString;
    stringData->s = s;
    stringData->ref.ref();
}

// Json::JsonValue::JsonValue(const JsonArray &a)
    // : d(a.d)
    // , t(Array)
// {
    // base = a.a;
    // if (d)
    // {
        // d->ref.ref();
    // }
// }

// Json::JsonValue::JsonValue(const JsonObject &o)
    // : d(o.d)
    // , t(Object)
// {
    // base = o.o;
    // if (d)
    // {
        // d->ref.ref();
    // }
// }

Json::JsonValue::JsonValue(const void *) 
: t(Null) 
{
    
}


Json::JsonValue::JsonValue(const JsonValue &other)
    : t(other.t)
{
    d = other.d;
    ui = other.ui;
    if (d)
    {
        // d->ref.ref();
    }

    if (t == String && stringData)
    {
        // stringData->ref.ref();
    }
}

// Json::JsonValue &JsonValue::operator=(const JsonValue &other)
// {
    // if (t == String && stringData && !stringData->ref.deref())
    // {
        // free(stringData);
    // }

    // t = other.t;
    // dbl = other.dbl;

    // if (d != other.d)
    // {
        // if (d && !d->ref.deref())
        // {
            // delete d;
        // }
        
        // d = other.d;
        
        // if (d)
        // {
            // d->ref.ref();
        // }

    // }

    // if (t == String && stringData)
    // {
        // stringData->ref.ref();
    // }

    // return *this;
// }

bool Json::JsonValue::toBool(bool defaultValue) const
{
    if (t != Bool)
    {
        return defaultValue;
    }

    return b;
}

int Json::JsonValue::toInt(int defaultValue) const
{
    if (t == Double && int(dbl) == dbl)
    {
        return int(dbl);
    }

    return defaultValue;
}

double Json::JsonValue::toDouble(double defaultValue) const
{
    if (t != Double)
    {
        return defaultValue;
    }

    return dbl;
}

std::string Json::JsonValue::toString(const std::string &defaultValue) const
{
    if (t != String)
    {
        return defaultValue;
    }

    return stringData->s;
}

// JsonArray Json::JsonValue::toArray(const JsonArray &defaultValue) const
// {
    // if (!d || t != Array)
    // {
        // return defaultValue;
    // }

    // return JsonArray(d, static_cast<Internal::Array *>(base));
// }

// JsonArray Json::JsonValue::toArray() const
// {
    // return toArray(JsonArray());
// }
/*
JsonObject Json::JsonValue::toObject(const JsonObject &defaultValue) const
{
    if (!d || t != Object)
    {
        return defaultValue;
    }

    return JsonObject(d, static_cast<Internal::Object *>(base));
}

JsonObject Json::JsonValue::toObject() const
{
    return toObject(JsonObject());
}
*/
bool Json::JsonValue::operator==(const JsonValue &other) const
{
    if (t != other.t)
    {
        return false;
    }

    switch (t)
    {
        case Undefined:
        case Null:
            break;
        case Bool:
            return b == other.b;
        case Double:
            return dbl == other.dbl;
        case String:
            return toString() == other.toString();
        case Array:
            if (base == other.base)
                return true;
            if (!base)
                return !other.base->length;
            if (!other.base)
                return !base->length;
            // return JsonArray(d, static_cast<Internal::Array *>(base))
                    // == JsonArray(other.d, static_cast<Internal::Array *>(other.base));
        case Object:
            if (base == other.base)
                return true;
            if (!base)
                return !other.base->length;
            if (!other.base)
                return !base->length;
            // return JsonObject(d, static_cast<Internal::Object *>(base))
                    // == JsonObject(other.d, static_cast<Internal::Object *>(other.base));
    }
    return true;
}

bool Json::JsonValue::operator!=(const JsonValue &other) const
{
    // return !(*this == other);
}

void Json::JsonValue::detach()
{
    if (!d)
    {
        return;
    }

    // Data *x = d->clone(base);
    // x->ref.ref();

    // if (!d->ref.deref())
    {
        // delete d;
    }

    // d = x;
    // base = static_cast<Internal::Object *>(d->header->root());
}


Json::JsonValue::Type Json::JsonValue::type() const 
{ 
    return t; 
}

bool Json::JsonValue::isNull() const 
{ 
    return t == Null;
}

bool Json::JsonValue::isBool() const 
{ 
    return t == Bool; 
}

bool Json::JsonValue::isDouble() const 
{ 
    return t == Double; 
}

bool Json::JsonValue::isString() const 
{ 
    return t == String; 
}

bool Json::JsonValue::isArray() const 
{ 
    return t == Array; 
}

bool Json::JsonValue::isObject() const 
{ 
    return t == Object; 

}

bool Json::JsonValue::isUndefined() const 
{ 
    return t == Undefined; 
}
