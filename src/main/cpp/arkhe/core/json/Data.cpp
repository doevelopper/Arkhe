#include <arkhe/core/json/JsonDocument.hpp>
#include <arkhe/core/json/Data.hpp>
#include <arkhe/core/json/Array.hpp>
#include <arkhe/core/json/JsonObject.hpp>
#include <arkhe/core/json/JsonArray.hpp>

Json::Data::Data()
{
}

Json::Data::~Data()
{
    if (ownsData)
    {
        // free(rawData);        
    }
}

Json::Data::Data(char *raw, int a)
 : alloc(a)
 , rawData(raw)
 , compactionCounter(0)
 , ownsData(true)
{
    
}

Json::Data::Data(int reserved, JsonValue::Type valueType)
    : rawData(0)
    , compactionCounter(0)
    , ownsData(true)
{
        // assert(valueType == JsonValue::Array || valueType == JsonValue::Object);

        alloc = sizeof(Header) + sizeof(Base) + reserved + sizeof(offset);
        header = (Header *)malloc(alloc);
        header->tag = JsonDocument::BinaryFormatTag;
        header->version = 1;
        Base *b = header->root();
        b->size = sizeof(Base);
        b->is_object = (valueType == JsonValue::Object);
        b->tableOffset = sizeof(Base);
        b->length = 0;
}

uint32_t Json::Data::offsetOf(const void *ptr) const
{
    return (uint32_t)(((char *)ptr - rawData));
}

// JsonObject Json::Data::toObject(Object *o) const
// {
    // return JsonObject(const_cast<Data *>(this), o);
// }

// JsonArray Json::Data::toArray(Array *a) const
// {
    // return JsonArray(const_cast<Data *>(this), a);
// }

Json::Data *Json::Data::clone(Base *b, int reserve)
{
    int size = sizeof(Header) + b->size;
    
    // if (b == header->root() && ref.load() == 1 && alloc >= size + reserve)
    // {
         // return this;
    // }

    // if (reserve)
    // {
        // if (reserve < 128)
        // {
            // reserve = 128;
        // }
        
        // size = std::max(size + reserve, size *2);
    // }
    
    // char *raw = (char *)malloc(size);
    
    // memcpy(raw + sizeof(Header), b, b->size);
    
    // Header *h = (Header *)raw;
    
    // h->tag = JsonDocument::BinaryFormatTag;
    // h->version = 1;
    
    // Data *d = new Data(raw, size);

    // d->compactionCounter = (b == header->root()) ? compactionCounter : 0;
    
    // return (d);
}

void Json::Data::compact()
{
    //// assert(sizeof(Value) == sizeof(offset));

    if (!compactionCounter)
    {
        return;
    }

    Base *base = header->root();
    int reserve = 0;
    
    // if (base->is_object)
    // {
        // Object *o = static_cast<Object *>(base);
        // for (int i = 0; i < (int)o->length; ++i)
        // {
            // reserve += o->entryAt(i)->usedStorage(o);
        // }
    // }
    // else
    // {
        // Array *a = static_cast<Array *>(base);
        // for (int i = 0; i < (int)a->length; ++i)
        // {
            // reserve += (*a)[i].usedStorage(a);
        // }
    // }

    // int size = sizeof(Base) + reserve + base->length*sizeof(offset);
    // int alloc = sizeof(Header) + size;
    
    // Header *h = (Header *) malloc(alloc);
    // h->tag = JsonDocument::BinaryFormatTag;
    // h->version = 1;
    
    // Base *b = h->root();
    
    // b->size = size;
    // b->is_object = header->root()->is_object;
    // b->length = base->length;
    // b->tableOffset = reserve + sizeof(Array);

    // int offset = sizeof(Base);
    
    // if (b->is_object)
    // {
        // Object *o = static_cast<Object *>(base);
        // Object *no = static_cast<Object *>(b);

        // for (int i = 0; i < (int)o->length; ++i)
        // {
            // no->table()[i] = offset;

            // const Entry *e = o->entryAt(i);
            // Entry *ne = no->entryAt(i);
            // int s = e->size();
            // memcpy(ne, e, s);
            // offset += s;
            
            // int dataSize = e->value.usedStorage(o);
            // if (dataSize)
            // {
                // memcpy((char *)no + offset, e->value.data(o), dataSize);
                // ne->value.value = offset;
                // offset += dataSize;
            // }
        // }
    // }
    // else
    // {
        // Array *a = static_cast<Array *>(base);
        // Array *na = static_cast<Array *>(b);

        // for (int i = 0; i < (int)a->length; ++i)
        // {
            // const Value &v = (*a)[i];
            // Value &nv = (*na)[i];
            // nv = v;
            // int dataSize = v.usedStorage(a);
            // if (dataSize)
            // {
                // memcpy((char *)na + offset, v.data(a), dataSize);
                // nv.value = offset;
                // offset += dataSize;
            // }
        // }
    // }
    //// assert(offset == (int)b->tableOffset);

    // free(header);
    // header = h;
    // this->alloc = alloc;
    // compactionCounter = 0;
}

bool Json::Data::valid() const
{
    if (header->tag != JsonDocument::BinaryFormatTag || header->version != 1u)
        return false;

    bool res = false;
    if (header->root()->is_object)
	{
        // res = static_cast<Object *>(header->root())->isValid();
	}
    else
	{
        // res = static_cast<Array *>(header->root())->isValid();
	}

    return res;
}
    