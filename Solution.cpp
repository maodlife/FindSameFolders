#include "Solution.h"
#include "MyDirData.h"
#include <QDebug>
#include <QDir>
#include <QtCore/qobject.h>
#include <vector>

using namespace std;

vector<QString> Solution::FindSameFolderPath() {
    vector<QString> ret;
    auto leftDirDataTreePtr =
        MyDirData::CreateMyDirDataTreeByDirPath(folderPath1);
    auto rightDirDataTreePtr =
        MyDirData::CreateMyDirDataTreeByDirPath(folderPath2);
    std::unordered_multimap<QString, std::shared_ptr<MyDirData>>
        leftDirName2DataPtr;
    ConverDirDataTreeToMap(leftDirDataTreePtr, leftDirName2DataPtr);
    FindSameFolderPathCore(rightDirDataTreePtr, leftDirName2DataPtr);
    return ret;
}

void Solution::ConverDirDataTreeToMap(
    std::shared_ptr<MyDirData> dirDataPtr,
    std::unordered_multimap<QString, std::shared_ptr<MyDirData>>
        &dirName2DirDataPtr) {
    qDebug() << "ConverDirDataTreeToMap: " << dirDataPtr->dirPath;
    dirName2DirDataPtr.emplace(dirDataPtr->name, dirDataPtr);
    for (const auto &ptr : dirDataPtr->childs){
        ConverDirDataTreeToMap(ptr, dirName2DirDataPtr);
    }
}

void Solution::FindSameFolderPathCore(std::shared_ptr<MyDirData> currDirPtr, std::unordered_multimap<QString, std::shared_ptr<MyDirData> > &dirName2DirDataPtr)
{
    auto itPair = dirName2DirDataPtr.equal_range(currDirPtr->name);
    bool haveSame = false;
    for (auto it = itPair.first; it != itPair.second; ++it){
        if (CheckIsSame(it->second, currDirPtr)){
            // 找到了
            haveSame = true;
            sameDirPtrPairVec.emplace_back(it->second, currDirPtr);
        }
    }
    if (!haveSame){
        // 没找到，递归子文件夹
        for (auto &subDirPtr : currDirPtr->childs){
            FindSameFolderPathCore(subDirPtr, dirName2DirDataPtr);
        }
    }
}

bool Solution::CheckIsSame(std::shared_ptr<MyDirData> lhs,
                           std::shared_ptr<MyDirData> rhs) {
    if (lhs->name != rhs->name)
        return false;
    if (lhs->fileNameList.size() != rhs->fileNameList.size())
        return false;
    for (int i = 0; i < lhs->fileNameList.size(); ++i) {
        if (lhs->fileNameList[i] != rhs->fileNameList[i])
            return false;
    }
    if (lhs->childs.size() != rhs->childs.size())
        return false;
    for (int i = 0; i < lhs->childs.size(); ++i) {
        if (CheckIsSame(lhs->childs[i], rhs->childs[i]) == false)
            return false;
    }
    return true;
}
