#include <arkhe/osgi/core/AbstractLibraryFactory.hpp>
#include <arkhe/osgi/core/FactoryLibraryItem.hpp>

template<typename BaseClassType>
osgi::core::AbstractLibraryFactory<BaseClassType>::AbstractLibraryFactory()
{
    
}

template<typename BaseClassType>
osgi::core::AbstractLibraryFactory<BaseClassType>::~AbstractLibraryFactory()
{
    
}

template<typename BaseClassType>
void osgi::core::AbstractLibraryFactory<BaseClassType>::setSymbols(const QStringList& symbols)
{
    this->Symbols = symbols;
}

template<typename BaseClassType>
bool osgi::core::AbstractLibraryFactory<BaseClassType>::isValidFile(const QFileInfo& file)const
{
    return this->osgi::core::AbstractFileBasedFactory<BaseClassType>::isValidFile(file) && QLibrary::isLibrary(file.fileName());
}

template<typename BaseClassType>
void osgi::core::AbstractLibraryFactory<BaseClassType>::initItem(osgi::core::AbstractFactoryItem<BaseClassType>* item)
{
    this->AbstractFileBasedFactory<BaseClassType>::initItem(item);
    dynamic_cast<FactoryLibraryItem<BaseClassType>*>(item)->setSymbols(this->Symbols);
}
