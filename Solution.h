#ifndef SOLUTION_H
#define SOLUTION_H

#include "MyDirData.h"
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
    std::vector<std::pair<std::shared_ptr<MyDirData>, std::shared_ptr<MyDirData>>> sameDirPtrPairVec;

private:
    void ConverDirDataTreeToMap(
        std::shared_ptr<MyDirData> dirDataPtr,
        std::unordered_multimap<QString, std::shared_ptr<MyDirData>>
            &dirName2DirDataPtr);
    void FindSameFolderPathCore(std::shared_ptr<MyDirData> currDirPtr,
                                std::unordered_multimap<QString, std::shared_ptr<MyDirData>>
                                    &dirName2DirDataPtr);
    bool CheckIsSame(std::shared_ptr<MyDirData> lhs, std::shared_ptr<MyDirData> rhs);
};

#endif // SOLUTION_H
