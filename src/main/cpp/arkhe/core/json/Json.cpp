#include <arkhe/core/json/Json.hpp>
#include <arkhe/core/json/String.hpp>

// const Json::Base Json::emptyArray = { sizeof(Json::Base), { 0 }, 0 };
// const Json::Base Json::emptyObject = { sizeof(Json::Base), { 0 }, 0 };
	
int Json::qStringSize(const std::string &ba)
{
	int l = 4 + static_cast<int>(ba.length());
    return Json::alignedSize(l);
}

void Json::copyString(char *dest, const std::string &str)
{
    Json::String string(dest);
    string = str;
}

	
void Json::toInternal(char *addr, const char *data, int size)
{
    memcpy(addr, &size, 4);
	memcpy(addr + 4, data, size);
}



int Json::compressedNumber(double d)
{
    // this relies on details of how ieee floats are represented
    const int exponent_off = 52;
    const uint64_t fraction_mask = 0x000fffffffffffffull;
    const uint64_t exponent_mask = 0x7ff0000000000000ull;

    uint64_t val;
    memcpy (&val, &d, sizeof(double));
    int exp = (int)((val & exponent_mask) >> exponent_off) - 1023;

    if (exp < 0 || exp > 25)
    {
		return INT_MAX;
    }

    uint64_t non_int = val & (fraction_mask >> exp);
	
    if (non_int)
    {
		return INT_MAX;
    }

	bool neg = (val >> 63) != 0;
    val &= fraction_mask;
    val |= ((uint64_t)1 << 52);
    int res = (int)(val >> (52 - exp));
        
    return (neg ? -res : res);
}
    