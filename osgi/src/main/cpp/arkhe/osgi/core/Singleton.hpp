#ifndef ARKHE_OSGI_SINGLETON_HPP
#define ARKHE_OSGI_SINGLETON_HPP

#include <QDebug>

#include <arkhe/osgi/osgi.hpp>


/// Should be included as a class protected member
#define SINGLETON_DECLARE(NAME)                \
static NAME* Instance;                             \
static void classInitialize();                     \
static void classFinalize();                       \
friend class NAME##Initialize;                     \
typedef NAME Self;


#define SINGLETON_DECLARE_INITIALIZER(EXPORT_DIRECTIVE,NAME)   \
class EXPORT_DIRECTIVE NAME##Initialize                            \
{                                                                  \
public:                                                            \
  typedef NAME##Initialize Self;                                   \
                                                                   \
  NAME##Initialize();                                              \
  ~NAME##Initialize();                                             \
private:                                                           \
  static unsigned int Count;                                       \
};                                                                 \
                                                                   \
static NAME##Initialize NAME##Initializer;


/// Implementation of %NAME##%Initialize class.

/// Note: NAME##%Initialize::%Count and NAME::%Instance Must NOT be initialized.
/// Default initialization to zero is necessary.

#define SINGLETON_DEFINE_INITIALIZER(NAME)      \
NAME##Initialize::NAME##Initialize()                \
{                                                   \
  if(++Self::Count == 1)                            \
    { NAME::classInitialize(); }                    \
}                                                   \
                                                    \
NAME##Initialize::~NAME##Initialize()               \
{                                                   \
  if(--Self::Count == 0)                            \
    { NAME::classFinalize(); }                      \
}                                                   \
                                                    \
unsigned int NAME##Initialize::Count;               \
NAME* NAME::Instance;


/// This should be added at the end of the CPP file

#define SINGLETON_DEFINE(NAME)                  \
void NAME::classInitialize()                        \
{                                                   \
  Self::Instance = new NAME;                        \
}                                                   \
                                                    \
void NAME::classFinalize()                          \
{                                                   \
  delete Self::Instance;                            \
}                                                   \
                                                    \
SINGLETON_DEFINE_INITIALIZER(NAME)


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		
	}
}
#endif
