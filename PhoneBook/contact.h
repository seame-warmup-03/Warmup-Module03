#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>

class Contact
{
private:
    QString name;
    QString phonenumber;
    QString email;
    QString address;

public:
    Contact(QString _name, QString _phonenumber, QString _email, QString _address);

    void setName(QString _name);
    void setPhonenumber(QString _phonenumber);
    void setEmail(QString _email);
    void setAddress(QString _address);

    QString getName();
    QString getPhonenumber();
    QString getEmail();
    QString getAddress();

    ~Contact(){}
};

#endif // CONTACT_H
