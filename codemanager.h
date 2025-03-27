#ifndef CODEMANAGER_H
#define CODEMANAGER_H
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <fstream>
#include <sstream>
class codeManager
{
    class Node{
    public:
        QString name;
        QString contact;
        Node *next = nullptr;
        Node(QString name,QString contact){
            this->name = name;
            this->contact = contact;
        }
    };
public:
    Node *listHead = nullptr;
    Node *stackHead = nullptr;
    codeManager();
    void refreshList(QTableWidget *table);
    bool isValidName(QString name);
    bool isValidContact(QString contact);
    void addToList(QString name, QString contact);
    bool alreadyExists(QString name);
    void removeFromList(QTableWidget *table);
    void filterFromList(QString name,QTableWidget *table);
    void addToStack(QString name, QString contact);
    void removeFromStack();
    void saveToFile();
    void loadFromFile(QTableWidget *table);
};
extern codeManager manager;
#endif // CODEMANAGER_H
