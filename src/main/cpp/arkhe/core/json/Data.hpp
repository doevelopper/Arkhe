#ifndef ARKHE_CORE_DATA_HPP
#define ARKHE_CORE_DATA_HPP

#include <arkhe/core/json/Object.hpp>
#include <arkhe/core/json/AtomicInt.hpp>
#include <arkhe/core/json/JsonValue.hpp>
#include <arkhe/core/json/Header.hpp>

namespace Json 
{
	class Array ;
	class JsonObject ;
	class JsonArray ;

    class Data
    {
    public:        
        Data();
        virtual ~Data();
        Data(char *raw, int a);
        Data(int reserved, JsonValue::Type valueType);

        uint32_t offsetOf(const void *ptr) const ;
        JsonObject toObject(Object *o) const;
        JsonArray toArray(Array *a) const;
        Data *clone(Base *b, int reserve = 0);
        void compact();
        bool valid() const;

        enum Validation 
        {
            Unchecked,
            Validated,
            Invalid
        };
        
        AtomicInt ref;
        int alloc;
        
        union 
        {
            char *rawData;
            Header *header;
        };
        
        uint32_t compactionCounter : 31;
        uint32_t ownsData : 1;

    private:

        Data(const Data &);
        void operator=(const Data &);
    };
}
#endif
