#ifndef SOLUTION_H
#define SOLUTION_H

#include <QDir>
#include <QtCore/qobject.h>
#include <qstring.h>
#include <unordered_map>
#include <vector>

class Solution {
public:
    QString folderPath1;
    QString folderPath2;

    std::vector<QString> FindSameFolderPath();
private:
    struct FolderDataItem{
        QString folderPath;  // 绝对路径
        bool isCheck = false;
    };

    void ConvertFolderToMap(QString relativeFolderPath, std::unordered_multimap<QString, FolderDataItem> &map);
    void FindSameFolderPathCore(QString currFolder2Path, std::vector<QString> &result, std::unordered_multimap<QString, FolderDataItem> &map);
    bool CheckIsSame(QString folderPathLeft, QString folderPathRight);
};

#endif // SOLUTION_H
