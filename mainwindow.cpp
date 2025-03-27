#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    manager.loadFromFile(ui->tableWidget);
    manager.refreshList(ui->tableWidget);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_btnAdd_clicked(){
    QString name = ui->txtName->text();
    QString contact = ui->txtContact->text();
    if(name==""){
        QMessageBox::warning(0,"Warning","Username or Contact can't be empty");
        return;
    }
    if(contact==""){
        QMessageBox::warning(0,"Warning","Username or Contact can't be empty");
        return;
    }
    if(!manager.isValidName(name)){
        QMessageBox::warning(0,"Warning","Invalid Username or Contact");
        return;
    }
    if(!manager.isValidContact(contact)){
        QMessageBox::warning(0,"Warning","Invalid Username or Contact");
        return;
    }
    if(manager.alreadyExists(name)){
        QMessageBox::warning(0,"Warning","Username already exists");
        return;
    }
    ui->txtName->setFocus();
    ui->txtName->clear();
    ui->txtContact->clear();
    manager.addToList(name,contact);
    manager.refreshList(ui->tableWidget);
}
void MainWindow::on_btnDelete_clicked(){
    if(ui->tableWidget->selectionModel()->hasSelection()){
        manager.removeFromList(ui->tableWidget);
        return;
    }
    QMessageBox::warning(0,"Warning","First select an item from table to delete");
}
void MainWindow::on_txtSearch_textChanged(const QString &arg1){
    if(arg1.isEmpty()){
        manager.refreshList(ui->tableWidget);
        return;
    }
    manager.filterFromList(arg1,ui->tableWidget);
}
void MainWindow::on_btnClear_clicked(){
    ui->txtSearch->clear();
}
void MainWindow::on_btnExit_clicked(){
    manager.saveToFile();
    close();
}

void MainWindow::on_btnUndo_clicked(){
    manager.removeFromStack();
    manager.refreshList(ui->tableWidget);
}

