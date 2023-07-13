#include <QWidget>
#include "contactlist.h"

void ContactList::add(QString name, QString phonenumber, QString email, QString address)
{
    Contact temp(name, phonenumber, email, address);
    contacts.push_back(temp);
}

void ContactList::remove(int idx)
{
    int len = contacts.size();
    int distance = len - 1 - idx;
    for(int i = 0; i < distance; i++)
    {
        Contact temp = contacts[len - 1];
        contacts.pop_back();
        contacts.push_front(temp);
    }
    contacts.pop_back();
}

int ContactList::nameSearch(QString data)
{
    for(int i = 0; i < contacts.size(); i++)
    {
        if(!QString::compare(data, contacts[i].getName()))
            return i;
    }
    return -1;
}

int ContactList::phonenumberSearch(QString data)
{
    for(int i = 0; i < contacts.size(); i++)
    {
        if(!QString::compare(data, contacts[i].getPhonenumber()))
            return i;
    }
    return -1;
}

int ContactList::emailSearch(QString data)
{
    for(int i = 0; i < contacts.size(); i++)
    {
        if(!QString::compare(data, contacts[i].getEmail()))
            return i;
    }
    return -1;
}

int ContactList::addressSearch(QString data)
{
    for(int i = 0; i < contacts.size(); i++)
    {
        if(!QString::compare(data, contacts[i].getAddress()))
            return i;
    }
    return -1;
}

QList<QString> ContactList::idxSearch(int idx)
{
    QList<QString> temp;
    temp.push_back(contacts[idx].getName());
    temp.push_back(contacts[idx].getPhonenumber());
    temp.push_back(contacts[idx].getEmail());
    temp.push_back(contacts[idx].getAddress());
    return temp;
}

bool ContactList::isEmpty()
{
    return contacts.empty();
}

int ContactList::size()
{
    return contacts.size();
}

void ContactList::clear()
{
    contacts.clear();
}
