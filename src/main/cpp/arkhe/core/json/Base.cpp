
#include <arkhe/core/json/Json.hpp>
#include <arkhe/core/json/Base.hpp>
#include <arkhe/core/json/Value.hpp>

Json::Base::Base()
{
}

Json::Base::~Base()
{
}

bool Json::Base::isObject () const
{
    return !!is_object;
}

bool Json::Base::isArray () const
{
    return !isObject();
}

Json::offset * Json::Base::table () const
{
    return ((offset *) (((char *) this ) + tableOffset ));
}

int Json::Base::reserveSpace (uint32_t dataSize, int posInTable, uint32_t numItems, bool replace)
{
    // assert(posInTable >= 0 && posInTable <= (int)length);
    if( size + dataSize >= Value::MaxSize )
    {
        fprintf(stderr,
                "Json: Document too large to store in data structure %d %d %d\n",
                (uint32_t)size,
                dataSize,
                Value::MaxSize
                );

        return 0;
    }

    offset off = tableOffset;

    // move table to new position
    if( replace )
    {
        memmove((char *)( table()) + dataSize, table(), length * sizeof( offset ));
    }
    else
    {
        memmove((char *)( table() + posInTable + numItems ) + dataSize,
                table() + posInTable, ( length - posInTable ) * sizeof( offset )
                );
        memmove((char *)( table()) + dataSize, table(), posInTable * sizeof( offset ));
    }

    tableOffset += dataSize;

    for( int i = 0 ; i < (int)numItems ; ++i )
    {
        table() [posInTable + i] = off;
    }

    size += dataSize;

    if( !replace )
    {
        length += numItems;
        size   += numItems * sizeof( offset );
    }

    return off;
}

void Json::Base::removeItems (int pos, int numItems)
{
    // assert(pos >= 0 && pos <= (int)length);
    if( pos + numItems < (int)length )
    {
        memmove(table() + pos, table() + pos + numItems, ( length - pos - numItems ) * sizeof( offset ));
    }

    length -= numItems;
}
