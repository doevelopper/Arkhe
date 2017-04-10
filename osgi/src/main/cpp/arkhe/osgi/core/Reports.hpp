#ifndef ARKHE_OSGI_REPORTS_HPP
#define ARKHE_OSGI_REPORTS_HPP

#include <QtCore/qglobal.h>
#include <QByteArray>
#include <QString>

namespace osgi
{
	namespace core 
	{
		class Reports
		{
		public:
		  Reports();
		  virtual ~Reports();
		  static const char APPLICATION_NAME[];
		  static const char URL_BUGTRACKER[] ;
		  QByteArray fileContents(const QString &filePath);
		};
	}
}
#endif
