#include <arkhe/osgi/Services/Location.hpp>

const QString osgi::svc::Location::INSTANCE_FILTER = QString("(&(objectClass=") +
                                             qobject_interface_iid<Location*>() +
                                             ")(type=ctk.instance.area))";

const QString osgi::svc::Location::INSTALL_FILTER = QString("(&(objectClass=") +
                                            qobject_interface_iid<Location*>() +
                                            ")(type=ctk.install.area))";

const QString osgi::svc::Location::CONFIGURATION_FILTER = QString("(&(objectClass=") +
                                                  qobject_interface_iid<Location*>() +
                                                  ")(type=ctk.configuration.area))";

const QString osgi::svc::Location::USER_FILTER = QString("(&(objectClass=") +
                                         qobject_interface_iid<Location*>() +
                                         ")(type=ctk.user.area))";

const QString osgi::svc::Location::HOME_FILTER = QString("(&(objectClass=") +
                                             qobject_interface_iid<Location*>() +
                                             ")(type=ctk.home.location))";
											 
osgi::svc::Location::Location()
{
}

osgi::svc::Location::~Location()
{
}
