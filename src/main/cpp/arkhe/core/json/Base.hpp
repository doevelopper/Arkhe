#ifndef ARKHE_CORE_BASE_HPP
#define ARKHE_CORE_BASE_HPP


#include <arkhe/core/json/LittleEndianSignedBitfield.hpp>
#include <arkhe/core/json/LittleEndianBitfield.hpp>

namespace Json 
{
    class Base
    {
    public:        
        Base();
        virtual ~Base();

        uint32_t size;
        
        union 
        {
            uint32_t _dummy;
            LittleEndianBitfield<0, 1> is_object;
            LittleEndianBitfield<1, 31> length;
        };

        offset tableOffset;
        // content follows here

        bool isObject() const;
        bool isArray()  const;
        offset *table() const;

        int reserveSpace(uint32_t dataSize, int posInTable, uint32_t numItems, bool replace);
        void removeItems(int pos, int numItems);
    };
}
#endif
