#include <QWidget>
#include "contact.h"

Contact::Contact(QString _name, QString _phonenumber, QString _email, QString _address)
    : name(_name), phonenumber(_phonenumber), email(_email), address(_address)
{}

void Contact::setName(QString _name)
{
    name = _name;
}

void Contact::setPhonenumber(QString _phonenumber)
{
    phonenumber = _phonenumber;
}

void Contact::setEmail(QString _email)
{
    email = _email;
}

void Contact::setAddress(QString _address)
{
    address = _address;
}

QString Contact::getName()
{
    return name;
}

QString Contact::getPhonenumber()
{
    return phonenumber;
}

QString Contact::getEmail()
{
    return email;
}

QString Contact::getAddress()
{
    return address;
}
