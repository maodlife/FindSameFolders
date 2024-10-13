#include "Solution.h"
#include <QDir>
#include <QDebug>
#include <QtCore/qobject.h>
#include <vector>

using namespace std;

vector<QString> Solution::FindSameFolderPath() {
    vector<QString> ret;
    std::unordered_multimap<QString, Solution::FolderDataItem> folder1Map;
    ConvertFolderToMap(folderPath1, folder1Map);
    FindSameFolderPathCore(folderPath2, ret, folder1Map);
    return ret;
}

void Solution::ConvertFolderToMap(QString folderPath, std::unordered_multimap<QString, Solution::FolderDataItem> &map){
    qDebug() << folderPath;
    QDir dir(folderPath);

    Solution::FolderDataItem folderDataItem;
    folderDataItem.folderPath = folderPath;
    folderDataItem.isCheck = false;
    map.emplace(dir.dirName(), folderDataItem);  // 用文件夹名做key

    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    for (auto &item : list){
        ConvertFolderToMap(item.filePath(), map);
    }
}

void Solution::FindSameFolderPathCore(
    QString currFolder2Path, std::vector<QString> &result,
    std::unordered_multimap<QString, FolderDataItem> &map) {
    qDebug() << currFolder2Path;
    QDir dir(currFolder2Path);
    auto sameNameFolderRange = map.equal_range(dir.dirName());
    bool found = false;
    for (auto it = sameNameFolderRange.first; it != sameNameFolderRange.second; ++it) {
        FolderDataItem leftDataItem = it->second;
        bool isSame = CheckIsSame(leftDataItem.folderPath, currFolder2Path);
        if (isSame){
            // 找到了
            found = true;
            // 添加到结果中
            QString line;
            line += leftDataItem.folderPath;
            line += "<--->";
            line += currFolder2Path;
            result.push_back(line);
        }
    }
    if (found == false){
        // 没找到，继续递归查找
        auto dirList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
        for (const auto &subDir : dirList){
            FindSameFolderPathCore(subDir.filePath(), result, map);
        }
    }
}

// requires: 文件夹名相同
bool Solution::CheckIsSame(QString folderPathLeft, QString folderPathRight)
{
    // 比较文件
    QDir dirL(folderPathLeft);
    QDir dirR(folderPathRight);
    QFileInfoList fileListL = dirL.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    QFileInfoList fileListR = dirR.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    if (fileListL.count() != fileListR.count()) {
        return false;
    }
    auto fileCmp = [](const QFileInfo &lhs, const QFileInfo &rhs){
        return lhs.fileName().compare(rhs.fileName());
    };
    std::sort(fileListL.begin(), fileListL.end(), fileCmp);
    std::sort(fileListR.begin(), fileListR.end(), fileCmp);
    for (int i = 0; i < fileListL.count(); ++i){
        auto fileL = fileListL[i];
        auto fileR = fileListR[i];
        if (fileL.fileName() != fileR.fileName()){
            return false;
        }
    }
    // 递归比较子文件夹
    QFileInfoList dirListL = dirL.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    QFileInfoList dirListR = dirR.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    if (dirListL.count() != dirListR.count()){
        return false;
    }
    std::sort(dirListL.begin(), dirListL.end(), fileCmp);
    std::sort(dirListR.begin(), dirListR.end(), fileCmp);
    for (int i = 0; i < dirListL.count(); ++i){
        auto dirL = dirListL[i];
        auto dirR = dirListR[i];
        if (dirL.fileName() != dirR.fileName()){
            return false;
            bool ret = CheckIsSame(dirL.filePath(), dirR.filePath());
            if (!ret)
                return false;
        }
    }
    return true;
}
