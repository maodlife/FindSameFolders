#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Solution.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFolderBtn1_clicked();

    void on_openFolderBtn2_clicked();

    void on_findBtn_clicked();

private:
    Ui::MainWindow *ui;
    Solution solution;
};
#endif // MAINWINDOW_H
