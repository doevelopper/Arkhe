#include <QDir>
#include <arkhe/osgi/core/ScopedCurrentDir.hpp>

osgi::ScopedCurrentDir::ScopedCurrentDir(const QString& path) :
  d_ptr(new ScopedCurrentDirPrivate())
{
  Q_D(ScopedCurrentDir);
  d->SavedCurrentPath = QDir::currentPath();
  QDir::setCurrent(path);
}

osgi::ScopedCurrentDir::~ScopedCurrentDir()
{
  Q_D(ScopedCurrentDir);
  QDir::setCurrent(d->SavedCurrentPath);
}


QString osgi::ScopedCurrentDir::currentPath()const
{
  return QDir::currentPath();
}

QString osgi::ScopedCurrentDir::savedCurrentPath()const
{
  Q_D(const ScopedCurrentDir);
  
  return (d->SavedCurrentPath);
}
