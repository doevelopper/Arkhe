#ifndef ARKHE_OSGI_CORE_FRAMEWORK_VERSION_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_VERSION_HPP

#include <QString>
#include <QRegExp>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT Version
		{

		public:
			// Version();
			virtual ~Version();
			/*!
			 * The empty version "0.0.0".
			 */
			static Version emptyVersion();
			static Version undefinedVersion();
			Version(unsigned int majorVersion, unsigned int minorVersion, unsigned int microVersion);
			Version(unsigned int majorVersion, unsigned int minorVersion, unsigned int microVersion, const QString& qualifier);
			Version(const QString& version);
			Version(const Version& version);
			static Version parseVersion(const QString& version);
			bool isUndefined() const;
			unsigned int getMajor() const;
			unsigned int getMinor() const;
			unsigned int getMicro() const;
			QString getQualifier() const;
			QString toString() const;
			bool operator==(const Version& object) const;
			int compare(const Version& object) const;
			bool operator<(const Version& object) const;
		protected:

		private:
			void validate();
			Version& operator=(const Version& v);
			Version(bool undefined = false);

			friend class PluginPrivate;
			friend class VersionRange;

			unsigned int majorVersion;
			unsigned int minorVersion;
			unsigned int microVersion;
			QString      qualifier;

			static const QString SEPARATOR;
			static const QRegExp REGEXP;
			bool undefined;
		};		
			ARKHE_CORE_PLUGIN_FW_EXPORT QDebug operator<<(QDebug dbg, const Version& v);
	}
}
#endif
