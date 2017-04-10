#include <arkhe/osgi/core/Exception.hpp>
#include <arkhe/osgi/core/framework/VersionRange.hpp>

osgi::core::VersionRange::VersionRange()
{
	low = Version(Version::emptyVersion());
	high = Version();
	lowIncluded = true;
	highIncluded = false;
}

osgi::core::VersionRange::~VersionRange()
{
}

osgi::core::VersionRange osgi::core::VersionRange::defaultVersionRange()
{
	static VersionRange defaultVR;
	return defaultVR;
}

osgi::core::VersionRange::VersionRange(const QString& vr)
{
	bool op = vr.startsWith("(");
	bool ob = vr.startsWith("[");

	if (op || ob) 
	{
		bool cp = vr.endsWith(")");
		bool cb = vr.endsWith("]");
		int comma = vr.indexOf(',');

		if (comma > 0 && (cp || cb))
		{
			low = Version(vr.mid(1, comma-1).trimmed());
			high = Version(vr.mid(comma+1, vr.length()-comma-2).trimmed());
			lowIncluded = ob;
			highIncluded = cb;
		}
		else
		{
			// throw InvalidArgumentException("Illegal version range: " + vr);
		}
	}
	else
	{
		low = Version(vr);
		high = Version();
		lowIncluded = true;
		highIncluded = false;
	}
}

bool osgi::core::VersionRange::isSpecified() const
{
	return !(*this == defaultVersionRange());
}

bool osgi::core::VersionRange::withinRange(const Version& ver) const
{
	if (*this == defaultVersionRange())
	{
		return true;
	}

	int c = low.compare(ver);

	if (c < 0 || (c == 0 && lowIncluded))
	{
		if (high.isUndefined())
		{
			return true;
		}

		c = high.compare(ver);

		return c > 0 || (c == 0 && highIncluded);
	}

	return false;
}

bool osgi::core::VersionRange::withinRange(const VersionRange& range) const
{
	if (*this == range) 
	{
		return true;
	}

	int c = low.compare(range.low);

	if (c < 0 || (c == 0 && lowIncluded == range.lowIncluded))
	{
		if (high.isUndefined())
		{
			return true;
		}

		c = high.compare(range.high);
		return c > 0 || (c == 0 && highIncluded == range.highIncluded);
	}

	return false;
}


int osgi::core::VersionRange::compare(const VersionRange& obj) const
{
  return low.compare(obj.low);
}


QString osgi::core::VersionRange::toString() const
{
	if (!high.isUndefined())
	{
		QString res;
		if (lowIncluded)
		{
			res += '[';
		}
		else
		{
			res += '(';
		}

		res += low.toString() + "," + high.toString();

		if (highIncluded)
		{
			res += ']';
		}
		else
		{
			res += ')';
		}

		return res;
	}
	else
	{
		return low.toString();
	}
}


bool osgi::core::VersionRange::operator==(const VersionRange& r) const
{
	if (low == r.low)
	{
		if (!high.isUndefined())
		{
			return (high == r.high)  &&  (lowIncluded == r.lowIncluded) && (highIncluded == r.highIncluded);
		}
		else
		{
			return true;
		}
	}
	return false;
}


