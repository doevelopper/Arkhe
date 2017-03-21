#include <arkhe/osgi/core/AbstractPluginFactory.hpp>
#include <arkhe/osgi/core/FactoryPluginItem.hpp>
template<typename BaseClassType>
osgi::AbstractFactoryItem<BaseClassType>* osgi::AbstractPluginFactory<BaseClassType>::createFactoryFileBasedItem()
{
    return new osgi::FactoryPluginItem<BaseClassType>();
}


template<typename BaseClassType>
bool osgi::AbstractPluginFactory<BaseClassType>::isValidFile(const QFileInfo& fileInfo)const
{
    return (this->AbstractFileBasedFactory<BaseClassType>::isValidFile(fileInfo) && QLibrary::isLibrary(fileInfo.fileName()));
}

