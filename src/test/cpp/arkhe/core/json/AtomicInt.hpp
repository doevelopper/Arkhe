#ifndef ARKHE_CORE_ATOMICINT_HPP
#define ARKHE_CORE_ATOMICINT_HPP
#include <atomic>
namespace Json 
{
    class AtomicInt
    {
    public:
        bool ref();
        bool deref();
        int load();
    private:
        std::atomic<int> x { 0 };
    };
}
#endif