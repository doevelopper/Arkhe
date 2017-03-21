#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <arkhe/osgi/osgi.hpp>

osgi::SetName::SetName(const QString& name)
  : Name(name)
{
}

qint64 osgi::msecsTo(const QDateTime& t1, const QDateTime& t2)
{
  QDateTime utcT1 = t1.toUTC();
  QDateTime utcT2 = t2.toUTC();

  return static_cast<qint64>(utcT1.daysTo(utcT2))
       * static_cast<qint64>(1000*3600*24)
       + static_cast<qint64>(utcT1.time().msecsTo(utcT2.time()));
}

QString osgi::qtHandleToString(Qt::HANDLE handle)
{
    QString str;
    QTextStream s(&str);
    s << handle;
    return str;
}


double osgi::closestPowerOfTen(double _value)
{
    const double sign = _value >= 0. ? 1 : -1;
    const double value = qAbs(_value);
    if (value == 0.
                || value == std::numeric_limits<double>::infinity()
                || value != value // is NaN
                || value < std::numeric_limits<double>::epsilon()) // is denormalized
    {
        return _value;
    }

    double magnitude = 1.;
    double nextMagnitude = magnitude;

    if (value >= 1.)
    {
        do
        {
            magnitude = nextMagnitude;
            nextMagnitude *= 10.;
        }
        while ( (value - magnitude)  > (nextMagnitude - value) );
    }
    else
    {
        do
        {
            magnitude = nextMagnitude;
            nextMagnitude /= 10.;
        }
        while ( (value - magnitude)  < (nextMagnitude - value) );
    }
  return magnitude * sign;
}


bool osgi::removeDirRecursively(const QString & dirName)
{
  bool result = false;
  QDir dir(dirName);

  if (dir.exists(dirName))
    {
    foreach (QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
      {
      if (info.isDir())
        {
        result = osgi::removeDirRecursively(info.absoluteFilePath());
        }
      else
        {
        result = QFile::remove(info.absoluteFilePath());
        }

      if (!result)
        {
        return result;
        }
      }
    result = dir.rmdir(dirName);
    }

  return result;
}

bool osgi::copyDirRecursively(const QString &srcPath, const QString &dstPath)
{
  // See http://stackoverflow.com/questions/2536524/copy-directory-using-qt
    if (!QFile::exists(srcPath))
    {
        qCritical() << "osgi::copyDirRecursively: Failed to copy nonexistent directory" << srcPath;
        return false;
    }

    QDir srcDir(srcPath);
    if (!srcDir.relativeFilePath(dstPath).startsWith(".."))
    {
        qCritical() << "osgi::copyDirRecursively: Cannot copy directory" << srcPath << "into itself" << dstPath;
        return false;
    }


    QDir parentDstDir(QFileInfo(dstPath).path());
    if (!QFile::exists(dstPath) && !parentDstDir.mkdir(QFileInfo(dstPath).fileName()))
    {
        qCritical() << "osgi::copyDirRecursively: Failed to create destination directory" << QFileInfo(dstPath).fileName();
        return false;
    }

    foreach(const QFileInfo &info, srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
    {
        QString srcItemPath = srcPath + "/" + info.fileName();
        QString dstItemPath = dstPath + "/" + info.fileName();
        if (info.isDir())
        {
            if (!osgi::copyDirRecursively(srcItemPath, dstItemPath))
            {
                qCritical() << "osgi::copyDirRecursively: Failed to copy files from " << srcItemPath << " into " << dstItemPath;
                return false;
            }
        }
        else if (info.isFile())
        {
            if (!QFile::copy(srcItemPath, dstItemPath))
            {
                return false;
            }
        }
        else
        {
            qWarning() << "osgi::copyDirRecursively: Unhandled item" << info.filePath();
        }
    }
  return true;
}
