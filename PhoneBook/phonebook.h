#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QWidget>
#include "contactlist.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class PhoneBook : public QWidget
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = nullptr);
    enum Mode {NavigationMode, AddingMode, EditingMode};

public slots:
    void add();
    void submit();
    void cancel();
    void edit();
    void remove();

    void next();
    void previous();

    void nameSearch();
    void phonenumberSearch();
    void emailSearch();
    void addressSearch();

    void saveFile();
    void loadFile();

private:
    void updateInterface(Mode mode);

    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    QPushButton *nextButton;
    QPushButton *previousButton;

    QPushButton *nameButton;
    QPushButton *phonenumberButton;
    QPushButton *emailButton;
    QPushButton *addressButton;

    QPushButton *saveButton;
    QPushButton *loadButton;

    QLineEdit *nameLine;
    QLineEdit *phonenumberLine;
    QLineEdit *emailLine;
    QLineEdit *addressLine;

    QLineEdit *searchLine;

    ContactList contactList;

    QString oldName;
    QString oldPhonenumber;
    QString oldEmail;
    QString oldAddress;

    Mode currentMode;
};

#endif
