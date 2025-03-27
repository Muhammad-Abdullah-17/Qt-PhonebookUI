#include "codemanager.h"
codeManager manager;
codeManager::codeManager() {}
void codeManager::refreshList(QTableWidget *table){
    table->setRowCount(0);
    int row;
    Node *temp = listHead;
    while(temp!=nullptr){
        row = table->rowCount();
        table->insertRow(row);
        table->setItem(row,0,new QTableWidgetItem(temp->name));
        table->setItem(row,1,new QTableWidgetItem(temp->contact));
        temp = temp->next;
    }
}
bool codeManager::isValidName(QString name){
    for(QChar ch : name){
        if(!ch.isLetterOrNumber() && ch != ' ' ) return false;
    }
    return true;
}
bool codeManager::isValidContact(QString contact){
    if(contact.size() != 11) return false;
    if(contact[0] != '0' && contact[1] != '3') return false;
    for(QChar ch : contact){
        if(!ch.isDigit()) return false;
    }
    return true;
}
void codeManager::addToList(QString name, QString contact)
{
    Node *newNode = new Node(name,contact);
    if(listHead == nullptr || newNode->name < listHead->name){
        newNode->next = listHead;
        listHead = newNode;
    }else{
        Node *temp = listHead;
        while(temp->next!=nullptr && temp->next->name < name) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

bool codeManager::alreadyExists(QString name){
    if(listHead==nullptr) return false;
    Node *temp = listHead;
    while(temp!=nullptr){
        if(temp->name == name) return true;
        temp = temp->next;
    }
    return false;
}

void codeManager::removeFromList(QTableWidget *table)
{
    int row = table->currentRow();
    if(row>=0){
        table->removeRow(row);
        Node *temp = listHead;
        if(row==0){
            listHead = listHead->next;
            addToStack(temp->name,temp->contact);
            delete temp;
            return;
        }
        for(int i=0;i<row-1&&temp!=nullptr;i++) temp = temp->next;
        if(temp!=nullptr&&temp->next!=nullptr){
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            addToStack(toDelete->name,toDelete->contact);
            delete toDelete;
        }
    }
}

void codeManager::filterFromList(QString name, QTableWidget *table)
{
    table->setRowCount(0);
    Node *temp = listHead;
    while(temp!=nullptr){
        if(temp->name.startsWith(name,Qt::CaseInsensitive)){
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row,0,new QTableWidgetItem(temp->name));
            table->setItem(row,1,new QTableWidgetItem(temp->contact));
        }
        temp = temp->next;
    }
}
void codeManager::addToStack(QString name, QString contact)
{
    Node *newNode = new Node(name,contact);
    if(stackHead == nullptr){
        stackHead = newNode;
        return;
    }
    newNode->next = stackHead;
    stackHead = newNode;
}

void codeManager::removeFromStack()
{
    if(stackHead == nullptr) return;
    addToList(stackHead->name,stackHead->contact);
    Node *toDelete = stackHead;
    stackHead = stackHead->next;
    delete toDelete;
}
void codeManager::saveToFile()
{
    std::ofstream file("contacts.txt",std::ios::trunc);
    if(!file) return;
    Node *temp = listHead;
    Node *toDelete;
    while(temp!=nullptr){
        file<<temp->name.toStdString() <<"\n"<< temp->contact.toStdString()<<"\n";
        toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    temp = stackHead;
    while(temp!=nullptr){
        toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    listHead = stackHead = nullptr;
    file.close();
}

void codeManager::loadFromFile(QTableWidget *table)
{
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Name","Contact"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setVisible(false);
    std::ifstream file("contacts.txt");
    if (!file || file.peek() == std::ifstream::traits_type::eof()) {
        std::ofstream newFile("contacts.txt");
        newFile.close();
        return;
    }
    std::string name,contact;
    while(getline(file,name) && getline(file,contact))
        addToList(QString::fromStdString(name),QString::fromStdString(contact));
    file.close();
}
