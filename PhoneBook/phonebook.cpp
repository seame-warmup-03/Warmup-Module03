#include <QtWidgets>
#include "phonebook.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *phonenumberLabel = new QLabel(tr("Phone Number:"));
    phonenumberLine = new QLineEdit;
    phonenumberLine->setReadOnly(true);

    QLabel *emailLabel = new QLabel(tr("Email:"));
    emailLine = new QLineEdit;
    emailLine->setReadOnly(true);

    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressLine = new QLineEdit;
    addressLine->setReadOnly(true);

    QLabel *searchLabel = new QLabel(tr("Search by:"));
    searchLine = new QLineEdit;
    searchLine->setReadOnly(false);

    QLabel *emptyLabel = new QLabel(tr(" "));

    addButton = new QPushButton(tr("Add"));
    addButton->show();
    submitButton = new QPushButton(tr("Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->hide();
    editButton = new QPushButton(tr("Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("Remove"));
    removeButton->setEnabled(false);

    nextButton = new QPushButton(tr("Next ->"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("<- Previous"));
    previousButton->setEnabled(false);

    nameButton = new QPushButton(tr("Name"));
    nameButton->setEnabled(false);
    phonenumberButton = new QPushButton(tr("Phonenumber"));
    phonenumberButton->setEnabled(false);
    emailButton = new QPushButton(tr("Email"));
    emailButton->setEnabled(false);
    addressButton = new QPushButton(tr("Address"));
    addressButton->setEnabled(false);

    saveButton = new QPushButton(tr("Save..."));
    saveButton->setToolTip(tr("Save contacts to a file"));
    saveButton->setEnabled(false);
    loadButton = new QPushButton(tr("Load..."));
    loadButton->setToolTip(tr("Load contacts from a file"));
    loadButton->setEnabled(true);

    connect(addButton, &QPushButton::clicked, this, &PhoneBook::add);
    connect(submitButton, &QPushButton::clicked, this, &PhoneBook::submit);
    connect(cancelButton, &QPushButton::clicked, this, &PhoneBook::cancel);
    connect(editButton, &QPushButton::clicked, this, &PhoneBook::edit);
    connect(removeButton, &QPushButton::clicked, this, &PhoneBook::remove);

    connect(nextButton, &QPushButton::clicked, this, &PhoneBook::next);
    connect(previousButton, &QPushButton::clicked, this, &PhoneBook::previous);

    connect(nameButton, &QPushButton::clicked, this, &PhoneBook::nameSearch);
    connect(phonenumberButton, &QPushButton::clicked, this, &PhoneBook::phonenumberSearch);
    connect(emailButton, &QPushButton::clicked, this, &PhoneBook::emailSearch);
    connect(addressButton, &QPushButton::clicked, this, &PhoneBook::addressSearch);

    connect(saveButton, &QPushButton::clicked, this, &PhoneBook::saveFile);
    connect(loadButton, &QPushButton::clicked, this, &PhoneBook::loadFile);

    QHBoxLayout *buttonLayout1 = new QHBoxLayout;
    buttonLayout1->addWidget(previousButton);
    buttonLayout1->addWidget(nextButton);

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(nameButton);
    buttonLayout2->addWidget(phonenumberButton);
    buttonLayout2->addWidget(emailButton);
    buttonLayout2->addWidget(addressButton);

    QHBoxLayout *buttonLayout3 = new QHBoxLayout;
    buttonLayout3->addWidget(saveButton);
    buttonLayout3->addWidget(loadButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addButton, 0, 2);
    mainLayout->addWidget(phonenumberLabel, 1, 0);
    mainLayout->addWidget(phonenumberLine, 1, 1);
    mainLayout->addWidget(editButton, 1, 2);
    mainLayout->addWidget(emailLabel, 2, 0);
    mainLayout->addWidget(emailLine, 2, 1);
    mainLayout->addWidget(removeButton, 2, 2);
    mainLayout->addWidget(addressLabel, 3, 0);
    mainLayout->addWidget(addressLine, 3, 1);
    mainLayout->addWidget(submitButton, 3, 2);
    mainLayout->addLayout(buttonLayout1, 4, 1);
    mainLayout->addWidget(cancelButton, 4, 2);
    mainLayout->addWidget(emptyLabel, 5, 1);
    mainLayout->addWidget(emptyLabel, 6, 1);
    mainLayout->addWidget(searchLine, 7, 1);
    mainLayout->addWidget(searchLabel, 8, 0);
    mainLayout->addLayout(buttonLayout2, 8, 1);
    mainLayout->addWidget(emptyLabel, 9, 1);
    mainLayout->addWidget(emptyLabel, 10, 1);
    mainLayout->addLayout(buttonLayout3, 11, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Phone Book"));
}

void PhoneBook::add()
{
    oldName = nameLine->text();
    oldPhonenumber = phonenumberLine->text();
    oldEmail = emailLine->text();
    oldAddress = addressLine->text();

    nameLine->clear();
    phonenumberLine->clear();
    emailLine->clear();
    addressLine->clear();

    updateInterface(AddingMode);
}

void PhoneBook::submit()
{
    QString name = nameLine->text();
    QString phonenumber = phonenumberLine->text();
    QString email = emailLine->text();
    QString address = addressLine->text();

    if(name.isEmpty() || phonenumber.isEmpty() || email.isEmpty() || address.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter the information."));
        return;
    }

    if(currentMode == AddingMode)
    {
        if(contactList.phonenumberSearch(phonenumber) == -1)
        {
            contactList.add(name, phonenumber, email, address);
            QMessageBox::information(this, tr("Add Successful"),
                tr("\"%1\" has been added to your phone book.").arg(name));
        }
        else
        {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                tr("Sorry, Phonenumber \"%1\" is already in your phone book.").arg(phonenumber));
        }
    }
    else if(currentMode == EditingMode)
    {
        if(oldPhonenumber != phonenumber)
        {
            if(contactList.phonenumberSearch(phonenumber) == -1)
            {
                QMessageBox::information(this, tr("Edit Successful"),
                    tr("\"%1\" has been edited in your phone book.").arg(oldName));
                contactList.remove(contactList.phonenumberSearch(oldPhonenumber));
                contactList.add(name, phonenumber, email, address);
            }
            else
            {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                    tr("Sorry, Phonenumber \"%1\" is already in your phone book.").arg(phonenumber));
            }
        }
        else
        {
            QMessageBox::information(this, tr("Edit Successful"),
                tr("\"%1\" has been edited in your phone book.").arg(name));
            contactList.remove(contactList.phonenumberSearch(phonenumber));
            contactList.add(name, phonenumber, email, address);
        }
    }

    updateInterface(NavigationMode);
}

void PhoneBook::cancel()
{
    nameLine->setText(oldName);
    phonenumberLine->setText((oldPhonenumber));
    emailLine->setText(oldEmail);
    addressLine->setText(oldAddress);

    updateInterface(NavigationMode);
}

void PhoneBook::edit()
{
    oldName = nameLine->text();
    oldPhonenumber = phonenumberLine->text();
    oldEmail = emailLine->text();
    oldAddress = addressLine->text();

    updateInterface(EditingMode);
}

void PhoneBook::remove()
{
    QString name = nameLine->text();
    QString phonenumber = phonenumberLine->text();

    int button = QMessageBox::question(this, tr("Confirm Remove"),
        tr("Are you sure you want to remove \"%1\"?").arg(name),
        QMessageBox::Yes | QMessageBox::No);

    if(button == QMessageBox::Yes)
    {
        previous();
        contactList.remove(contactList.phonenumberSearch(phonenumber));

        QMessageBox::information(this, tr("Remove Successful"),
            tr("\"%1\" has been removed from your phone book.").arg(name));
    }

    updateInterface(NavigationMode);
}

void PhoneBook::next()
{
    QString name = nameLine->text();
    int idx = contactList.nameSearch(name);

    if(idx != contactList.size() - 1)
        idx++;
    else
        idx = 0;

    QList<QString> temp = contactList.idxSearch(idx);
    nameLine->setText(temp[0]);
    phonenumberLine->setText(temp[1]);
    emailLine->setText(temp[2]);
    addressLine->setText(temp[3]);
}

void PhoneBook::previous()
{
    QString name = nameLine->text();
    int idx = contactList.nameSearch(name);

    if(idx != 0)
        idx--;
    else
        idx = contactList.size() - 1;

    QList<QString> temp = contactList.idxSearch(idx);
    nameLine->setText(temp[0]);
    phonenumberLine->setText(temp[1]);
    emailLine->setText(temp[2]);
    addressLine->setText(temp[3]);
}

void PhoneBook::nameSearch()
{
    QString name = searchLine->text();
    if(contactList.nameSearch(name) == -1)
    {
        QMessageBox::information(this, tr("Contact Not Found"),
            tr("Sorry, \"%1\" is not in your phone book.").arg(name));
    }
    else
    {
        QList<QString> temp = contactList.idxSearch(contactList.nameSearch(name));
        nameLine->setText(temp[0]);
        phonenumberLine->setText(temp[1]);
        emailLine->setText(temp[2]);
        addressLine->setText(temp[3]);
    }
    searchLine->clear();
}

void PhoneBook::phonenumberSearch()
{
    QString phonenumber = searchLine->text();
    if(contactList.phonenumberSearch(phonenumber) == -1)
    {
        QMessageBox::information(this, tr("Contact Not Found"),
                                 tr("Sorry, \"%1\" is not in your phone book.").arg(phonenumber));
    }
    else
    {
        QList<QString> temp = contactList.idxSearch(contactList.phonenumberSearch(phonenumber));
        nameLine->setText(temp[0]);
        phonenumberLine->setText(temp[1]);
        emailLine->setText(temp[2]);
        addressLine->setText(temp[3]);
    }
    searchLine->clear();
}

void PhoneBook::emailSearch()
{
    QString email = searchLine->text();
    if(contactList.emailSearch(email) == -1)
    {
        QMessageBox::information(this, tr("Contact Not Found"),
                                 tr("Sorry, \"%1\" is not in your phone book.").arg(email));
    }
    else
    {
        QList<QString> temp = contactList.idxSearch(contactList.emailSearch(email));
        nameLine->setText(temp[0]);
        phonenumberLine->setText(temp[1]);
        emailLine->setText(temp[2]);
        addressLine->setText(temp[3]);
    }
    searchLine->clear();
}

void PhoneBook::addressSearch()
{
    QString address = searchLine->text();
    if(contactList.addressSearch(address) == -1)
    {
        QMessageBox::information(this, tr("Contact Not Found"),
                                 tr("Sorry, \"%1\" is not in your phone book.").arg(address));
    }
    else
    {
        QList<QString> temp = contactList.idxSearch(contactList.addressSearch(address));
        nameLine->setText(temp[0]);
        phonenumberLine->setText(temp[1]);
        emailLine->setText(temp[2]);
        addressLine->setText(temp[3]);
    }
    searchLine->clear();
}

void PhoneBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch(currentMode)
    {
    case AddingMode:
    case EditingMode:
        nameLine->setReadOnly(false);
        phonenumberLine->setReadOnly(false);
        emailLine->setReadOnly(false);
        addressLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);
        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();

        nameButton->setEnabled(false);
        phonenumberButton->setEnabled(false);
        emailButton->setEnabled(false);
        addressButton->setEnabled(false);

        saveButton->setEnabled(false);
        loadButton->setEnabled(false);
        break;

    case NavigationMode:
        if(contactList.isEmpty())
        {
            nameLine->clear();
            phonenumberLine->clear();
            emailLine->clear();
            addressLine->clear();
        }

        nameLine->setReadOnly(true);
        phonenumberLine->setReadOnly(true);
        emailLine->setReadOnly(true);
        addressLine->setReadOnly(true);

        addButton->setEnabled(true);

        int number = contactList.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number > 1);

        submitButton->hide();
        cancelButton->hide();

        nameButton->setEnabled(number > 1);
        phonenumberButton->setEnabled(number > 1);
        emailButton->setEnabled(number > 1);
        addressButton->setEnabled(number > 1);

        saveButton->setEnabled(number >= 1);
        loadButton->setEnabled(true);
        break;
    }
}

void PhoneBook::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Phone Book"), "",
        tr("Phone Book (*.abk);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_15);


        QList<QList<QString>> temp;
        for(int i = 0; i < contactList.size(); i++)
        {
            temp.push_back(contactList.idxSearch(i));
        }


        out << temp;
    }
}

void PhoneBook::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Phone Book"), "",
        tr("Phone Book (*.abk);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_15);

        contactList.clear();

        QList<QList<QString>> temp;
        in >> temp;

        for(int i = 0; i < temp.size(); i++)
        {
            contactList.add(temp[i][0], temp[i][1], temp[i][2], temp[i][3]);
        }

        if (contactList.isEmpty())
        {
            QMessageBox::information(this, tr("No contacts in file"),
                tr("The file you are attempting to open contains no contacts."));
        }
        else
        {
            QList<QString> temp = contactList.idxSearch(0);
            nameLine->setText(temp[0]);
            phonenumberLine->setText(temp[1]);
            emailLine->setText(temp[2]);
            addressLine->setText(temp[3]);
        }
    }

    updateInterface(NavigationMode);
}
