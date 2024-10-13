#include "MyDirData.h"
#include <QDir>
#include <queue>

using namespace std;

std::shared_ptr<MyDirData>
MyDirData::CreateMyDirDataTreeByDirPath(QString path) {
    QDir baseDir(path);
    std::shared_ptr<MyDirData> baseDirPtr = std::make_shared<MyDirData>();
    baseDirPtr->dirPath = path;
    baseDirPtr->name = baseDir.dirName();
    baseDirPtr->AddFileList();
    queue<shared_ptr<MyDirData>> dirQueue;
    dirQueue.push(baseDirPtr);
    while (!dirQueue.empty()) {
        auto currPtr = dirQueue.front();
        qDebug() << currPtr->dirPath;
        dirQueue.pop();
        QDir dir(currPtr->dirPath);
        auto dirList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
        for (auto &item : dirList){
            std::shared_ptr<MyDirData> dirPtr = std::make_shared<MyDirData>();
            dirPtr->dirPath = item.filePath();
            dirPtr->name = item.fileName();
            dirPtr->parent = currPtr;
            currPtr->childs.push_back(dirPtr);
            dirQueue.push(dirPtr);
        }
    }
    return baseDirPtr;
}

void MyDirData::AddFileList()
{
    QDir dir(this->dirPath);
    auto dirList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    for (auto item : dirList){
        this->fileNameList.push_back(item.fileName());
    }
}
