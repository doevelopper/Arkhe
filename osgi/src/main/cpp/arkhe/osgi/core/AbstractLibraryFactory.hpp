#ifndef ARKHE_OSGI_ABSTRACTLIBRARYFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTLIBRARYFACTORY_HPP

#include <QFileInfo>
#include <QLibrary>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFileBasedFactory.hpp>

/*!
 * @brief .
 */
namespace osgi
{

	template<typename BaseClassType>
	class AbstractLibraryFactory : public AbstractFileBasedFactory<BaseClassType>
	{
	public:
        AbstractLibraryFactory();
        virtual ~AbstractLibraryFactory();
        void setSymbols(const QStringList& symbols);
	protected:

        virtual bool isValidFile(const QFileInfo& file)const;
        virtual void initItem(osgi::AbstractFactoryItem<BaseClassType>* item);

	private:
        QStringList Symbols;
	};
		
}
#endif