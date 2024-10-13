#ifndef MYDIRDATA_H
#define MYDIRDATA_H

#include <memory>
#include <vector>
#include <QString>

class MyDirData{
public:
    std::weak_ptr<MyDirData> parent;  // 父目录
    std::vector<std::shared_ptr<MyDirData>> childs;  // 子目录
    std::vector<QString> fileNameList;  // 子文件名列表
    QString dirPath;  // 绝对路径
    QString name;  // 自己的名字

    static std::shared_ptr<MyDirData> CreateMyDirDataTreeByDirPath(QString path);
private:
    void AddFileList();
};

#endif // MYDIRDATA_H
