#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "codemanager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_txtSearch_textChanged(const QString &arg1);
    void on_btnClear_clicked();
    void on_btnExit_clicked();
    void on_btnUndo_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
