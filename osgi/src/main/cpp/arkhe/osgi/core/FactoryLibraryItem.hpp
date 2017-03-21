#ifndef ARKHE_OSGI_FACTORYLIBRARYITEM_HPP
#define ARKHE_OSGI_FACTORYLIBRARYITEM_HPP

#include <QFileInfo>
#include <QLibrary>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class FactoryLibraryItem : public AbstractFactoryFileBasedItem<BaseClassType>
	{
	public:
        FactoryLibraryItem();
        virtual ~FactoryLibraryItem();
          //explicit ctkFactoryLibraryItem(const QString& path);
        virtual bool load();
        using SymbolAddressType=QFunctionPointer;
        void setSymbols(const QStringList& symbols);
        void setLoadHints(QLibrary::LoadHints hints);
        bool resolve();
        SymbolAddressType symbolAddress(const QString& symbol)const;
	protected:

        using  ConstIterator = typename QHash<QString, SymbolAddressType>::const_iterator;
        using  Iterator = typename QHash<QString, SymbolAddressType>::iterator;
        mutable QLibrary Library;
        QHash<QString, SymbolAddressType> ResolvedSymbols;
        QStringList    Symbols;

	private:

	};
		
}
#endif