#ifndef ARKHE_CORE_LITTLEENDIANBITFIELD_HPP
#define ARKHE_CORE_LITTLEENDIANBITFIELD_HPP
#include <cstdint>
namespace Json 
{
    using  offset = uint32_t ;
    
    template<int pos, int width>
    class LittleEndianBitfield
    {
    public:
        LittleEndianBitfield();
        virtual ~LittleEndianBitfield();
        uint32_t val;
        enum 
        {
            mask = ((1u << width) - 1) << pos
        };

        void operator=(uint32_t t) 
        {
            uint32_t i = val;
            i &= ~mask;
            i |= t << pos;
            val = i;
        }
        
        operator uint32_t() const 
        {
            uint32_t t = val;
            t &= mask;
            t >>= pos;
            return t;
        }
        
        bool operator!() const 
        { 
            return !operator uint32_t(); 
        }
        
        bool operator==(uint32_t t) 
        { 
            return uint32_t(*this) == t; 
        }
        
        bool operator!=(uint32_t t) 
        { 
            return uint32_t(*this) != t; 
        }
        
        bool operator<(uint32_t t) 
        { 
            return uint32_t(*this) < t; 
        }
        
        bool operator>(uint32_t t) 
        { 
            return uint32_t(*this) > t; 
        }
        
        bool operator<=(uint32_t t) 
        { 
            return uint32_t(*this) <= t; 
        }
        
        bool operator>=(uint32_t t) 
        { 
            return uint32_t(*this) >= t; 
        }
        
        void operator+=(uint32_t i) 
        { 
            *this = (uint32_t(*this) + i); 
        }
        
        void operator-=(uint32_t i) 
        { 
            *this = (uint32_t(*this) - i); 
        }
    };
}
#endif