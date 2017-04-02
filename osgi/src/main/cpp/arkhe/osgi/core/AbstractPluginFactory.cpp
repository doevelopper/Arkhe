#include <arkhe/osgi/core/AbstractPluginFactory.hpp>
#include <arkhe/osgi/core/FactoryPluginItem.hpp>
template<typename BaseClassType>
osgi::core::AbstractFactoryItem<BaseClassType>* osgi::core::AbstractPluginFactory<BaseClassType>::createFactoryFileBasedItem()
{
    return new osgi::core::FactoryPluginItem<BaseClassType>();
}


template<typename BaseClassType>
bool osgi::core::AbstractPluginFactory<BaseClassType>::isValidFile(const QFileInfo& fileInfo)const
{
    return (this->AbstractFileBasedFactory<BaseClassType>::isValidFile(fileInfo) && QLibrary::isLibrary(fileInfo.fileName()));
}

