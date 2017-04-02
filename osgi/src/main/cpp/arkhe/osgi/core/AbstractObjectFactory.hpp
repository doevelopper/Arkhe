#ifndef ARKHE_OSGI_ABSTRACTOBJECTFACTORY_HPP
#define ARKHE_OSGI_ABSTRACTOBJECTFACTORY_HPP

#include <QFileInfo>
#include <QLibrary>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
#include <arkhe/osgi/core/AbstractFactory.hpp>

/*!
 * @brief .
 */
namespace osgi
{
	namespace core 
	{
		template<typename BaseClassType>
		class AbstractObjectFactory : public AbstractFactory<BaseClassType>
		{
		public:
			explicit AbstractObjectFactory();
			virtual ~AbstractObjectFactory();
			
			template<typename ClassType>
			bool registerObject(const QString& key);
		protected:

		private:
			AbstractObjectFactory(const AbstractObjectFactory &);  /// Not implemented
			void operator=(const AbstractObjectFactory&); /// Not implemented
		};
	}
}
#endif
