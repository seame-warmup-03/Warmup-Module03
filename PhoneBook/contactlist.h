#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QWidget>
#include "contact.h"

class ContactList
{
private:
    QList<Contact> contacts;

public:
    ContactList(){}

    void add(QString name, QString phonenumber, QString email, QString address);
    void remove(int idx);

    int nameSearch(QString data);
    int phonenumberSearch(QString data);
    int emailSearch(QString data);
    int addressSearch(QString data);
    QList<QString> idxSearch(int idx);

    bool isEmpty();
    int size();
    void clear();

    ~ContactList(){}
};

#endif // CONTACTLIST_H
