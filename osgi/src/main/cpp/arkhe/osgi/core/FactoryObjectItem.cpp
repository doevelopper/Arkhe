#include <arkhe/osgi/core/FactoryObjectItem.hpp>

template<typename BaseClassType, typename ClassType>
bool osgi::FactoryObjectItem<BaseClassType,ClassType>::load()
{
  this->instantiateObjectFunc = &instantiateObject<BaseClassType, ClassType>;
  return (true);
}

template<typename BaseClassType, typename ClassType>
BaseClassType* osgi::FactoryObjectItem<BaseClassType,ClassType>::instanciator()
{
    return (this->instantiateObjectFunc());
}

