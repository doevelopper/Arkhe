#ifndef ARKHE_OSGI_ABSTRACTFILEBASEDFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTFILEBASEDFACTORY_HPP

#include <QFileInfo>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
//#include <arkhe/osgi/core/AbstractFactoryItem.hpp>
#include <arkhe/osgi/core/AbstractFactory.hpp>
/*!
 * @brief AbstractFactory is the base class of all the factory where items need,
 *        to be registered before being instantiated.
 */
namespace osgi
{
    template<typename BaseClassType>
    class AbstractFactoryItem;

	template<typename BaseClassType>
	class AbstractFileBasedFactory : public AbstractFactory<BaseClassType>
	{
	public:
        virtual bool isValidFile(const QFileInfo& file)const;
        QString itemKey(const QFileInfo& file)const;
        QString registerFileItem(const QFileInfo& file);
        virtual QString pathway(const QString& key);
	protected:
	  
	private:
        void registerAllFileItems(const QStringList& directories);
        bool registerFileItem(const QString& key, const QFileInfo& file);
        virtual AbstractFactoryItem<BaseClassType>* createFactoryFileBasedItem();
        virtual void initItem(AbstractFactoryItem<BaseClassType>* item);
        virtual QString fileNameToKey(const QString& path)const;
	};
		
}
#endif
