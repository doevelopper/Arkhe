#include <arkhe/osgi/core/Logger.hpp>

osgi::core::Logger::Logger()
{
	
}

osgi::core::Logger::~Logger()
{
	
}

osgi::core::Logger::Logger(QString name, QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new LoggerPrivate)
{
  Q_UNUSED(name);
  // Q_D(Logger);
  //d->Logger = Log4cxx::Logger::logger( name.toStdString().c_str());
}

void osgi::core::Logger::configure()
{
	//Log4cxx::BasicConfigurator::configure();
}

void osgi::core::Logger::debug(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->debug(s);
  qDebug().nospace() << qPrintable(s);
}

//-----------------------------------------------------------------------------
void osgi::core::Logger::info(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->info(s);
  qDebug().nospace() << qPrintable(s);
}

//-----------------------------------------------------------------------------
void osgi::core::Logger::trace(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->trace(s);
  qDebug().nospace() << qPrintable(s);
}

//-----------------------------------------------------------------------------
void osgi::core::Logger::warn(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->warn(s);
  qWarning().nospace() << qPrintable(s);
}

//-----------------------------------------------------------------------------
void osgi::core::Logger::error(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->error(s);
  qCritical().nospace() << qPrintable(s);
}

//-----------------------------------------------------------------------------
void osgi::core::Logger::fatal(const QString& s)
{
  //Q_D(osgi::Logger);
  //d->Logger->fatal(s);
  qCritical().nospace() << qPrintable(s);
}

void osgi::core::Logger::setOff()
{
  //Q_D(osgi::Logger);
  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::OFF_INT));
}

void osgi::core::Logger::setDebug()
{
//  //Q_D(osgi::Logger);
//  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::DEBUG_INT));
}

void osgi::core::Logger::setInfo()
{
//  //Q_D(osgi::Logger);
//  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::INFO_INT));
}

void osgi::core::Logger::setTrace()
{
//  //Q_D(osgi::Logger);
//  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::TRACE_INT));
}

void osgi::core::Logger::setWarn()
{
  //Q_D(osgi::Logger);
  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::WARN_INT));
}

void osgi::core::Logger::setError()
{
  //Q_D(osgi::Logger);
  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::ERROR_INT));
}

void osgi::core::Logger::setFatal()
{
//  //Q_D(osgi::Logger);
//  //d->Logger->setLevel(Log4cxx::Level(Log4cxx::Level::FATAL_INT));
}

//bool osgi::core::Logger::isOffEnabled()
//{
//  //Q_D(osgi::Logger); //Not sure
//  //return d->Logger->isEnabledFor(Log4cxx::Level(Log4cxx::Level::OFF_INT));
//}

//bool osgi::core::Logger::isDebugEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isDebugEnabled();
//}

//bool osgi::core::Logger::isInfoEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isInfoEnabled();
//}

//bool osgi::core::Logger::isTraceEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isTraceEnabled();
//}

//bool osgi::core::Logger::isWarnEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isWarnEnabled();
//}

//bool osgi::core::Logger::isErrorEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isErrorEnabled();
//}

//bool osgi::core::Logger::isFatalEnabled()
//{
//  //Q_D(osgi::Logger);
//  //return d->Logger->isFatalEnabled();
//}
