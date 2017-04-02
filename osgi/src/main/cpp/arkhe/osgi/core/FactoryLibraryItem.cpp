#include <arkhe/osgi/core/FactoryLibraryItem.hpp>

template<typename BaseClassType>
osgi::core::FactoryLibraryItem<BaseClassType>::FactoryLibraryItem()
{
    
}

template<typename BaseClassType>
osgi::core::FactoryLibraryItem<BaseClassType>::~FactoryLibraryItem()
{
    
}

template<typename BaseClassType>
bool osgi::core::FactoryLibraryItem<BaseClassType>::load()
{
    this->Library.setFileName(this->path());
    bool loaded = this->Library.load();
    if (loaded)
    {
        if (!this->resolve())
        {
            this->appendLoadErrorString(this->Library.errorString());
            return (false);
        }

        return (true);
    }
    else
    {
        this->appendLoadErrorString(this->Library.errorString());
    }

    return (false);
}

template<typename BaseClassType>
void osgi::core::FactoryLibraryItem<BaseClassType>::setSymbols(const QStringList& symbols)
{ 
    this->Symbols = symbols; 
}

template<typename BaseClassType>
void osgi::core::FactoryLibraryItem<BaseClassType>::setLoadHints(QLibrary::LoadHints hints)
{
    this->Library.setLoadHints(hints);
}

template<typename BaseClassType>
bool osgi::core::FactoryLibraryItem<BaseClassType>::resolve()
{
    foreach(const QString& symbol, this->Symbols)
    {
        // Sanity checks
        if (symbol.isEmpty()) 
        {
            this->appendLoadErrorString(QLatin1String("Failed to resolve empty symbol !"));
            continue;
        }

        // Skip if the symbols has already been resolved
        if (this->ResolvedSymbols.contains(symbol))
        {
            this->appendLoadWarningString(QString("Symbol '%1' already resolved").arg(symbol));
            continue;
        }

        SymbolAddressType resolvedSymbol = this->Library.resolve(symbol.toLatin1());
        if (!resolvedSymbol)
        {
            this->appendLoadErrorString(QString("Failed to resolve mandatory symbol '%1'").arg(symbol));
            return (false);
        }

        this->ResolvedSymbols[symbol] = resolvedSymbol;
    }

    return (true);
}


template<typename BaseClassType>
typename osgi::core::FactoryLibraryItem<BaseClassType>::SymbolAddressType
osgi::core::FactoryLibraryItem<BaseClassType>::symbolAddress(const QString& symbol)const
{
    ConstIterator iter = this->ResolvedSymbols.find(symbol);
    if ( iter == this->ResolvedSymbols.constEnd())
    {
        return this->Library.resolve(symbol.toLatin1());
    }
    
    return iter.value();
}

