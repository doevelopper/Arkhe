#ifndef ARKHE_CORE_LITTLEENDIANSIGNEDBITFIELD_HPP
#define ARKHE_CORE_LITTLEENDIANSIGNEDBITFIELD_HPP
#include <cstdint>
namespace Json 
{
    template<int pos, int width>
    class LittleEndianSignedBitfield
    {
    public:
        LittleEndianSignedBitfield();
        virtual ~LittleEndianSignedBitfield();
        
        uint32_t val;

        enum 
        {
            mask = ((1u << width) - 1) << pos
        };

        void operator=(int t) 
        {
            uint32_t i = val;
            i &= ~mask;
            i |= t << pos;
            val = i;
        }
        
        operator int() const 
        {
            uint32_t i = val;
            i <<= 32 - width - pos;
            int t = (int) i;
            t >>= pos;
            return t;
        }

        bool operator!() const 
        { 
            return !operator int(); 
        }
        
        bool operator==(int t) 
        { 
            return int(*this) == t; 
        }
        
        bool operator!=(int t) 
        { 
            return int(*this) != t; 
        }
        
        bool operator<(int t) 
        { 
            return int(*this) < t; 
        }
        
        bool operator>(int t) 
        { 
            return int(*this) > t; 
        }
        
        bool operator<=(int t) 
        { 
            return int(*this) <= t; 
        }
        
        bool operator>=(int t) 
        { 
            return int(*this) >= t; 
        }
        
        void operator+=(int i) 
        { 
            *this = (int(*this) + i); 
        }
        
        void operator-=(int i) 
        { 
            *this = (int(*this) - i); 
        }
    };
}
#endif