
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __DBUSXX_OBJECT_MANAGER_ADAPTOR_MARSHAL_H
#define __DBUSXX_OBJECT_MANAGER_ADAPTOR_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>
#include <stdint.h>

namespace DBus {

/// @cond INTERNAL_API

class DXXAPI ObjectManagerAdaptor
: public ::DBus::InterfaceAdaptor
{
public:

    ObjectManagerAdaptor();

    const ::DBus::IntrospectedInterface * introspect() const;

public:

    /* properties exposed by this interface, use
     * property() and property(value) to get and set a particular property
     */

public:

    typedef std::map< ::DBus::Path, std::map< std::string, std::map< std::string, ::DBus::Variant > > > ManagedObjectsReturn_t;

    /* methods exported by this interface,
     * you will have to implement them in your ObjectAdaptor
     */
    ManagedObjectsReturn_t & GetManagedObjects(ManagedObjectsReturn_t &);

public:

    /* signal emitters for this interface
     */
    void InterfacesAdded(const ::DBus::Path& arg1, const std::map< std::string, std::map< std::string, ::DBus::Variant > >& arg2)
    {
        ::DBus::SignalMessage sig("InterfacesAdded");
        ::DBus::MessageIter wi = sig.writer();
        wi << arg1;
        wi << arg2;
        emit_signal(sig);
    }
    void InterfacesRemoved(const ::DBus::Path& arg1, const std::vector< ::DBus::Struct< std::string > >& arg2)
    {
        ::DBus::SignalMessage sig("InterfacesRemoved");
        ::DBus::MessageIter wi = sig.writer();
        wi << arg1;
        wi << arg2;
        emit_signal(sig);
    }

private:

    /* unmarshalers (to unpack the DBus message before calling the actual interface method)
     */
    ::DBus::Message _GetManagedObjects_stub(const ::DBus::CallMessage &call);
};

/// @endcond

}
#endif //__DBUSXX_OBJECT_MANAGER_ADAPTOR_MARSHAL_H
