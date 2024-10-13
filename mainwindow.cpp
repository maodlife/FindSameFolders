#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFolderBtn1_clicked()
{
    QString selectDir = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Folder",
        QDir::homePath(), // 默认路径
        QFileDialog::DontResolveSymlinks
        );
    solution.folderPath1 = selectDir;
    ui->folder_path_label1->setText(selectDir);
}


void MainWindow::on_openFolderBtn2_clicked()
{
    QString selectDir = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Folder",
        "",
        //QDir::homePath(), // 默认路径
        QFileDialog::DontResolveSymlinks
        );
    solution.folderPath2 = selectDir;
    ui->folder_path_label2->setText(selectDir);
}


void MainWindow::on_findBtn_clicked()
{
    // QString content;
    // auto task = [=, &content](){
    //     auto result = this->solution.FindSameFolderPath();
    //     for (const auto &s : result){
    //         content += s;
    //         content += "\n";
    //     }
    // };
    // auto handle = QtConcurrent::task(std::move(task)).spawn();
    // ui->resultContent->setText(content);

    auto task = [=]() {
        QString content;
        auto result = this->solution.FindSameFolderPath();
        qDebug() << "end";
        for (auto [leftPtr, rightPtr] : solution.sameDirPtrPairVec) {
            QString line = leftPtr->dirPath + "<->" + rightPtr->dirPath;
            content += line + "\n";
        }
        return content;
    };

    QFutureWatcher<QString> *watcher = new QFutureWatcher<QString>(this);

    connect(watcher, &QFutureWatcher<QString>::finished, this, [=]() {
        ui->resultContent->setText(watcher->result());
        watcher->deleteLater();  // Clean up the watcher
    });

    QFuture<QString> future = QtConcurrent::run(task);
    watcher->setFuture(future);
}

