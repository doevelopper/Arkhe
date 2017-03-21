#include <arkhe/core/json/AtomicInt.hpp>
bool Json::AtomicInt::ref() 
{ 
    return ++x != 0; 
}

bool Json::AtomicInt::deref() 
{ 
    return --x != 0; 
}

int Json::AtomicInt::load() 
{ 
    return x.load(std::memory_order_seq_cst); 
}