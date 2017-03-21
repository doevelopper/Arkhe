#ifndef ARKHE_OSGI_ABSTRACTFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTFACTORY_HPP

#include <QDebug>
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactoryItem.hpp>

/*!
 * @brief AbstractFactory is the base class of all the factory where items need,
 *        to be registered before being instantiated.
 */
namespace osgi
{
	//class AbstractFactoryItem;

	template<typename BaseClassType>
	class AbstractFactory
	{
	public:
		using HashType = QHash<QString, QSharedPointer<AbstractFactoryItem<BaseClassType> > >;
		
		AbstractFactory();
		virtual ~AbstractFactory();
		virtual void printAdditionalInfo();

		virtual BaseClassType * instantiate(const QString& itemKey);
		virtual BaseClassType * instance(const QString& itemKey);
		void uninstantiate(const QString& itemKey);
		virtual QString path(const QString& itemKey)
		{
			Q_UNUSED(itemKey);
			return QString();
		}

		void setSharedItems(const QSharedPointer<HashType>& items);
		QSharedPointer<HashType> sharedItems();

		QStringList itemKeys() const;

		virtual void registerItems()
		{
		}

		void setVerbose(bool value);
		bool verbose()const;

	protected:
	
		void displayStatusMessage(const QtMsgType& type, const QString& description, const QString& status, bool display);
		bool registerItem(const QString& key, const QSharedPointer<AbstractFactoryItem<BaseClassType> > & item);
		AbstractFactoryItem<BaseClassType> * item(const QString& itemKey)const;
		AbstractFactoryItem<BaseClassType> * sharedItem(const QString& itemKey)const;
	  
		typedef typename HashType::const_iterator ConstIterator;
		typedef typename HashType::iterator       Iterator;
	  
	private:
		//!TODO  To implement
		//! @{
		AbstractFactory(const AbstractFactory &); 
		void operator=(const AbstractFactory&); 
	    //! @}
		HashType RegisteredItemMap;
		QSharedPointer<HashType> SharedRegisteredItemMap;
		bool Verbose;
	};
		
}
#endif
