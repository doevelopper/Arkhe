#include <QStringListIterator>
#include <QDebug>
#include <arkhe/osgi/core/framework/Version.hpp>

const QString osgi::core::Version::SEPARATOR = ".";
const QRegExp osgi::core::Version::REGEXP = QRegExp("[a-zA-Z0-9_\\-]*");

// osgi::core::Version::Version()
// {
// }

osgi::core::Version::Version(bool undefined)
  : majorVersion(0)
  , minorVersion(0)
  , microVersion(0)
  , qualifier("")
  , undefined(undefined)
{

}

osgi::core::Version::Version(unsigned int majorVersion, unsigned int minorVersion, unsigned int microVersion)
  : majorVersion(majorVersion)
  , minorVersion(minorVersion)
  , microVersion(microVersion)
  , qualifier("")
  , undefined(false)
{

}

osgi::core::Version::Version(const Version& version)
: majorVersion(version.majorVersion)
, minorVersion(version.minorVersion)
, microVersion(version.microVersion)
, qualifier(version.qualifier)
, undefined(version.undefined)
{

}

osgi::core::Version::Version(const QString& version)
  : majorVersion(0)
  , minorVersion(0)
  , microVersion(0)
  , undefined(true)
{
	unsigned int maj = 0;
	unsigned int min = 0;
	unsigned int mic = 0;
	QString qual("");

	QStringList st = version.split(SEPARATOR);

	if (st.empty()) return;

	QStringListIterator i(st);

	bool ok = true;
	maj = i.next().toUInt(&ok);

	if (i.hasNext())
	{
		min = i.next().toUInt(&ok);
		if (i.hasNext())
		{
			mic = i.next().toUInt(&ok);
			if (i.hasNext())
			{
				qual = i.next();
				if (i.hasNext())
				{
					ok = false;
				}
			}
		}
	}

	// if (!ok) throw InvalidArgumentException("invalid format");

	majorVersion = maj;
	minorVersion = min;
	microVersion = mic;
	qualifier = qual;
	this->validate();
}

osgi::core::Version::~Version()
{
}


osgi::core::Version osgi::core::Version::emptyVersion()
{
  static osgi::core::Version emptyV(false);
  return emptyV;
}

osgi::core::Version osgi::core::Version::undefinedVersion()
{
  static Version undefinedV(true);
  return undefinedV;
}

osgi::core::Version& osgi::core::Version::operator=(const Version& v)
{
  majorVersion = v.majorVersion;
  minorVersion = v.minorVersion;
  microVersion = v.microVersion;
  qualifier = v.qualifier;
  undefined = v.undefined;
  return *this;
}

osgi::core::Version osgi::core::Version::parseVersion(const QString& version)
{
	if (version.isEmpty())
	{
		return emptyVersion();
	}

	QString version2 = version.trimmed();
	if (version2.isEmpty())
	{
		return emptyVersion();
	}

	return Version(version2);
}

bool osgi::core::Version::isUndefined() const
{
	return undefined;
}

unsigned int osgi::core::Version::getMajor() const
{
  // if (undefined) throw IllegalStateException("Version undefined");
	return majorVersion;
}

unsigned int osgi::core::Version::getMinor() const
{
  // if (undefined) throw IllegalStateException("Version undefined");
	return minorVersion;
}

unsigned int osgi::core::Version::getMicro() const
{
  // if (undefined) throw IllegalStateException("Version undefined");
	return microVersion;
}

QString osgi::core::Version::getQualifier() const
{
	// if (undefined) throw IllegalStateException("Version undefined");
	return qualifier;
}

QString osgi::core::Version::toString() const
{
	if (undefined) return "undefined";

	QString result;
	result += QString::number(majorVersion) + SEPARATOR + QString::number(minorVersion) + SEPARATOR + QString::number(microVersion);
	if (!qualifier.isEmpty())
	{
		result += SEPARATOR + qualifier;
	}
	return result;
}

bool osgi::core::Version::operator==(const Version& other) const
{
	if (&other == this)
	{ // quicktest
		return true;
	}

	if (other.undefined && this->undefined) return true;
	// if (this->undefined) throw IllegalStateException("Version undefined");
	if (other.undefined) return false;

	return (majorVersion == other.majorVersion) && (minorVersion == other.minorVersion) && (microVersion
			== other.microVersion) && qualifier == other.qualifier;
}

int osgi::core::Version::compare(const Version& other) const
{
	if (&other == this)
	{ // quicktest
		return 0;
	}

	if (this->undefined || other.undefined)
    // throw IllegalStateException("Cannot compare undefined version");

	if (majorVersion < other.majorVersion)
	{
		return -1;
	}

	if (majorVersion == other.majorVersion)
	{

		if (minorVersion < other.minorVersion)
		{
			return -1;
		}

		if (minorVersion == other.minorVersion)
		{

			if (microVersion < other.microVersion)
			{
				return -1;
			}

			if (microVersion == other.microVersion)
			{
				return qualifier.compare(other.qualifier);
			}
		}
	}
  return 1;
}

bool osgi::core::Version::operator <(const Version &object) const
{
  return this->compare(object) < 0;
}

void osgi::core::Version::validate()
{
  // if (!RegExp.exactMatch(qualifier))
    // throw InvalidArgumentException(QString("invalid qualifier: ") + qualifier);

  undefined = false;
}

QDebug operator<<(QDebug dbg, const osgi::core::Version& v)
{
	dbg << v.toString();
	return dbg.maybeSpace();
}

