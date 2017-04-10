#include "Reports.hpp"
#include <QDebug>
#include <QFile>

const char APPLICATION_NAME[] = "Crash Handler";
const char URL_BUGTRACKER[] = "https://bugreports.acme.io/";

osgi::core::Reports::Reports()
{

}

osgi::core::Reports::~Reports()
{

}

QByteArray osgi::core::Reports::fileContents(const QString &filePath)
{
  QFile file(filePath);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      qWarning("Warning: Could not open '%s'.", qPrintable(filePath));
      return QByteArray();
  }
  return file.readAll();
}

