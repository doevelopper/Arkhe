#include <arkhe/osgi/core/BacktraceCollectorPrivate.hpp>

osgi::core::BacktraceCollectorPrivate::BacktraceCollectorPrivate()
  : errorOccurred(false)
{

}

osgi::core::BacktraceCollectorPrivate::~BacktraceCollectorPrivate()
{

}

void osgi::core::BacktraceCollectorPrivate::setOutput(const QString &value)
{
  output = value;
}
bool osgi::core::BacktraceCollectorPrivate::getErrorOccurred() const
{
  return errorOccurred;
}

void osgi::core::BacktraceCollectorPrivate::setErrorOccurred(bool value)
{
  errorOccurred = value;
}

// QScopedPointer<QTemporaryFile> osgi::core::BacktraceCollectorPrivate::getCommandFile() const
// {
  // return commandFile;
// }

QProcess osgi::core::BacktraceCollectorPrivate::getDebugger() const
{
  return debugger;
}

void osgi::core::BacktraceCollectorPrivate::setDebugger(const QProcess &value)
{
  debugger = value;
}

QString osgi::core::BacktraceCollectorPrivate::getOutput() const
{
  return output;
}

// void osgi::core::BacktraceCollectorPrivate::setCommandFile(const QScopedPointer<QTemporaryFile> &value)
// {
  // commandFile = value;
// }

