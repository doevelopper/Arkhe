#include <arkhe/core/json/JsonValueRef.hpp>

Json::JsonValueRef::JsonValueRef()
{
	
}
Json::JsonValueRef::~JsonValueRef()
{
	
}
/*
JsonValueRef &Json::JsonValueRef::operator=(const JsonValue &val)
{
    if (is_object)
    {
        o->setValueAt(index, val);
    }
    else
    {
        a->replace(index, val);
    }

    return *this;
}

JsonValueRef &Json::JsonValueRef::operator=(const JsonValueRef &ref)
{
    if (is_object)
    {
        o->setValueAt(index, ref);
    }
    else
    {
        a->replace(index, ref);
    }

    return *this;
}

JsonArray Json::JsonValueRef::toArray() const
{
    return toValue().toArray();
}

JsonObject Json::JsonValueRef::toObject() const
{
    return toValue().toObject();
}

JsonValue Json::JsonValueRef::toValue() const
{
    if (!is_object)
    {
        return a->at(index);
    }
    return o->valueAt(index);
}


Json::JsonValueRef(JsonArray *array, int idx)
    : a(array)
    , is_object(false)
    , index(idx)
{

}

Json::JsonValueRef::JsonValueRef(JsonObject *object, int idx)
   : o(object)
   , is_object(true)
   , index(idx)
{
    
}

JsonValue::Type Json::JsonValueRef::type() const
{
    return toValue().type();
}

bool Json::JsonValueRef::isNull() const
{
    return type() == JsonValue::Null;
}

bool Json::JsonValueRef::isBool() const
{
    return type() == JsonValue::Bool;
}

bool Json::JsonValueRef::isDouble() const
{
    return type() == JsonValue::Double;
}

bool Json::JsonValueRef::isString() const
{
    return type() == JsonValue::String;
}

bool Json::JsonValueRef::isArray() const
{
    return type() == JsonValue::Array;
}

bool Json::JsonValueRef::isObject() const
{
    return type() == JsonValue::Object;
}

bool Json::JsonValueRef::isUndefined() const
{
    return type() == JsonValue::Undefined;
}

std::string Json::JsonValueRef::toString() const
{
    return toValue().toString();
}

bool Json::JsonValueRef::toBool(bool defaultValue = false) const
{
    return toValue().toBool(defaultValue);
}

int Json::JsonValueRef::toInt(int defaultValue = 0) const
{
    return toValue().toInt(defaultValue);
}

double Json::JsonValueRef::toDouble(double defaultValue = 0) const
{
    return toValue().toDouble(defaultValue);
}

std::string Json::JsonValueRef::toString(const std::string &defaultValue) const
{
    return toValue().toString(defaultValue);
}
*/
