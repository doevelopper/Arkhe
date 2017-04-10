#ifndef ARKHE_OSGI_CORE_FRAMEWORK_SERVICEPROPERTIES_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_SERVICEPROPERTIES_HPP

#include <QVarLengthArray>
#include <QVariant>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ServiceProperties
		{

		public:
			ServiceProperties();
			ServiceProperties(const Properties& props);
			virtual ~ServiceProperties();
			
			QVariant value(const QString& key) const;
			QVariant value(int index) const;
			int find(const QString& key) const;
			int findCaseSensitive(const QString& key) const;
			QStringList keys() const;
  
		protected:

		private:

			QVarLengthArray<QString,10> ks;
			QVarLengthArray<QVariant,10> vs;
			QMap<QString, QVariant> map;
		};		
	}
}
#endif
