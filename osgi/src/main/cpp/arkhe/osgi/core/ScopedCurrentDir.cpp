#include <QDir>
#include <arkhe/osgi/core/ScopedCurrentDir.hpp>

osgi::core::ScopedCurrentDir::ScopedCurrentDir(const QString& path) :
  d_ptr(new ScopedCurrentDirPrivate())
{
  Q_D(ScopedCurrentDir);
  d->SavedCurrentPath = QDir::currentPath();
  QDir::setCurrent(path);
}

osgi::core::ScopedCurrentDir::~ScopedCurrentDir()
{
  Q_D(ScopedCurrentDir);
  QDir::setCurrent(d->SavedCurrentPath);
}


QString osgi::core::ScopedCurrentDir::currentPath()const
{
  return QDir::currentPath();
}

QString osgi::core::ScopedCurrentDir::savedCurrentPath()const
{
  Q_D(const ScopedCurrentDir);
  
  return (d->SavedCurrentPath);
}
