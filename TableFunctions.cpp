///
// Created by BINOFL on 2020/12/6.
//

#include "TableFunctions.h"
#include <stdlib.h>
#include <io.h>
#include "IOFunctions.h"
#include "time.h"
#include <stdio.h>
#include "iomanip"
#include "dirent.h"
#include "vector"
#include "fstream"
#include "sstream"

const static char *path = "..\\databaseTables\\";

// TODO: 输入输出模块

void OutputDisplay(string *segmentName,
                   int *display,
                   struct Node *dataHead,
                   int *typeArray,
                   int totalLength) {
    int num_int = 0, num_double = 0, num_string = 0;
    int *displayIndex = new int[totalLength]; // 记录要输出的字段在对应类型的数组中的下标
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
//        cout << "读到的字段名为----------" << segmentName[i] << "---------\n";
    }
    for (int i = 0; i < totalLength * 20; ++i) {
        cout << "+";
    }
    cout << endl;
    // 获取要展示的字段在对应类型的数组的下标
    for (int i = 0; i < totalLength; i++) {
        if (display[i] == 1) {
            cout << std::left << setw(20) << segmentName[i];
            if (typeArray[i] == 0) {
                displayIndex[i] = num_int;
            } else if (typeArray[i] == 1) {
                displayIndex[i] = num_double;
            } else {
                displayIndex[i] = num_string;
            }
        }
        if (typeArray[i] == 0) {
            num_int++;
        } else if (typeArray[i] == 1) {
            num_double++;
        } else {
            num_string++;
        }
    }
    cout << endl;
    struct Node *p = new Node;
    p = dataHead;
    // 遍历所有数据并打印
    while (p != NULL) {
        for (int i = 0; i < totalLength; ++i) {
            if (display[i] == 1) {
                if (typeArray[i] == 0) {
                    cout << std::left << setw(20) << p->intArray[displayIndex[i]];
                } else if (typeArray[i] == 1) {
                    cout << std::left << setw(20) << setprecision(4) << p->doubleArray[displayIndex[i]];
                } else {
                    cout << std::left << setw(20) << p->stringArray[displayIndex[i]];
                }
            }
        }
        cout << endl;
        p = p->next;
    }
    for (int i = 0; i < totalLength * 20; ++i) {
        cout << "+";
    }
    cout << endl;
}

void OutputDisplay2(string *segmentName,
                    int *display,
                    struct Node *dataHead,
                    int *typeArray,
                    int totalLength) {
    int num_int = 0, num_double = 0, num_string = 0;
    int *displayIndex = new int[totalLength]; // 记录要输出的字段在对应类型的数组中的下标
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
//        cout << "读到的字段名为----------" << segmentName[i] << "---------\n";
    }
    for (int i = 0; i < totalLength * 20; ++i) {
        cout << "+";
    }
    cout << endl;
    for (int i = 0; i < totalLength; i++) {
        if (display[i] == 1) {
            cout << std::left << setw(20) << segmentName[i];
            if (typeArray[i] == 0) {
                displayIndex[i] = num_int;
            } else if (typeArray[i] == 1) {
                displayIndex[i] = num_double;
            } else {
                displayIndex[i] = num_string;
            }
        }
        if (typeArray[i] == 0) {
            num_int++;
        } else if (typeArray[i] == 1) {
            num_double++;
        } else {
            num_string++;
        }
    }
    cout << endl;
    struct Node *p = new Node;
    p = dataHead;
    while (p != NULL) {
        for (int i = 0; i < totalLength; ++i) {
            if (display[i] == 1) {
                if (typeArray[i] == 0) {
                    cout << std::left << setw(20) << p->intArray[displayIndex[i]];
                } else if (typeArray[i] == 1) {
                    cout << std::left << setw(20) << setprecision(4) << p->doubleArray[displayIndex[i]];
                } else {
                    cout << std::left << setw(20) << p->stringArray[displayIndex[i]];
                }
            }
        }
        cout << endl;
        p = p->next_info;
    }
    for (int i = 0; i < totalLength * 20; ++i) {
        cout << "+";
    }
    cout << endl;
}


// TODO: 表模块
int DisplayTables() {
    DIR *dirp;
    dirent *direntp;
    dirp = opendir(path);
    string tmp = ".csv";
    string tableName;
    int i = 1;
    cout << "***************************************************\n";
    cout << "数据库中现在有如下的数据表:" << endl;
    if (dirp != NULL) {
        for (int j = 1; j <= 2; j++) { // 先将文件夹.与..读取掉
            direntp = readdir(dirp);
        }
        while (1) {
            direntp = readdir(dirp);
            if (direntp == NULL) {
                break;
            }
            string s = direntp->d_name;
            int x = s.find(tmp, 0);
            if (x > 0) {
                int num = 0;
                tableName.assign(s, 0, x);
                Table *table = ReadTable(tableName);
                Node *node = table->nodeHead;
                while (node) {
                    num++;
                    node = node->next;
                }
                DeleteTable(table);
                cout << "No." << i++
                     << "TableName:" << tableName
                     << "\tSegmentNum:" << table->segmentNum
                     << "\tRowNum:" << num << endl;
//                     << "\tSize:" << c_file.size
//                     << "KB\tLastModified:" << ctime(&(c_file.time_write));
            }

        }
        closedir(dirp);
        if (i == 1) {
            cout << "数据库中无表!" << endl;
            cout << "***************************************************\n";
            return 0;
        }
        cout << "***************************************************\n";
        return 1;
    }
    return 0;
}

struct Table *ReadTable(string tableName) {
    string filePath = "..\\databaseTables\\" + tableName + ".csv";
//    cout << "文件路径是*********" << filePath << "*******\n";
    if (access(filePath.c_str(), 0) != 0) {
        cout << "您输入的表不存在！\n";
        struct Table *table = NULL;
        return table;
    } else {
        ifstream fp(filePath.c_str());
        struct Table *table = new Table;
        int i;
        if (!fp.is_open()) {
            cout << "读取表数据时发生错误，请稍后重试\n";
            table = NULL;
        } else { // 表内容格式：字段数、字段类型、字段顺序、字段名字、数据内容
            string line; // 读取csv文件每一行
            string field; // 读取用','隔开的每一项
            getline(fp, line); // 读取字段数
            int segmentNum = String2Int(line);
            string *segmentType = new string[segmentNum]; // 读取字段类型
            getline(fp, line);
            istringstream sin(line);
            i = 0;
            while (getline(sin, field, ',')) {
                segmentType[i++] = field;
            }
            for (int i = 0; i < segmentNum; ++i) {
//                cout << "读入的字段类型为********" << segmentType[i] << "*******\n";
            }
            int *typeArray = new int[segmentNum]; // 读取字段顺序
            getline(fp, line);
//            cout << "~~~~~~~~读到的一行是:" << line << endl;
            istringstream sin1(line);
            i = 0;
            while (getline(sin1, field, ',')) {
//                cout << "+++++++读入的值是" << field << endl;
                typeArray[i++] = String2Int(field);
            }
            for (int j = 0; j < segmentNum; ++j) {
//                cout << "--------typeArray[" << j << "]是" << typeArray[j] << endl;
            }
            int *display = new int[segmentNum]; // 设置显示数组，全部初始化为1，代表全部显示
            for (int i = 0; i < segmentNum; ++i) {
                display[i] = 1;
            }
            string *segmentName = new string[segmentNum]; // 读取字段名字
            getline(fp, line);
            istringstream sin2(line);
            i = 0;
            while (getline(sin2, field, ',')) {
                segmentName[i++] = field;
            }
            for (int i = 0; i < segmentNum; ++i) {
//                cout << "读入的字段名为********" << segmentName[i] << "*******\n";
            }
            struct Node *dataHead = new Node;
            struct Node *tempHead = new Node;
            tempHead->next = dataHead;
            while (getline(fp, line)) { // 逐行读取数据条
//                cout << "%%%%%%%%%%%%%%读取到的数据条为:" << line << endl;
                struct Node *tempNode = new Node;
                int num_int = 0, num_double = 0, num_string = 0;
                for (int i = 0; i < segmentNum; ++i) { // 对于每个字段，根据字段类型来进行赋值
                    if (typeArray[i] == 0) {
                        num_int++;
                    } else if (typeArray[i] == 1) {
                        num_double++;
                    } else {
                        num_string++;
                    }
                }
                tempNode->num_int = num_int;
                tempNode->num_double = num_double;
                tempNode->num_string = num_string;
                if (num_int != 0) {
                    tempNode->intArray = new int[num_int];
                } else {
                    tempNode->intArray = NULL;
                }
                if (num_double != 0) {
                    tempNode->doubleArray = new double[num_double];
                } else {
                    tempNode->doubleArray = NULL;
                }
                if (num_string != 0) {
                    tempNode->stringArray = new string[num_string];
                } else {
                    tempNode->stringArray = NULL;
                }
//                cout << "你好\n";
                vector<string> content; // 读取一行内容
                istringstream sin3(line);
                while (getline(sin3, field, ',')) {
//                    cout << "&&&&&&&&读到的值为" << field << endl;
                    content.push_back(field);
                }
                for (int i = 0; i < segmentNum; ++i) {
                    int num_int = 0, num_double = 0, num_string = 0;
                    if (typeArray[i] == 0) {
                        tempNode->intArray[num_int++] = String2Int(content[i]);
                    } else if (typeArray[i] == 1) {
                        tempNode->doubleArray[num_double++] = String2Double(content[i]);
                    } else {
                        tempNode->stringArray[num_string] = content[i];
                    }
                }
                tempNode->next = nullptr;
                tempNode->next_info = nullptr;
                tempNode->nodeIndex = String2Int(content[segmentNum]);
                if (tempHead->next == dataHead) {
                    dataHead = tempNode;
                    tempHead = dataHead;
                } else {
                    tempHead->next = tempNode;
                    tempHead = tempHead->next;
                }
            }
            fp.close();
            table->tableName = tableName;
            table->segmentNum = segmentNum;
            table->segmentType = segmentType;
            table->typeArray = typeArray;
            table->segmentName = segmentName;
            if (tempHead->next == dataHead) {
                table->nodeHead = NULL;
            } else {
                table->nodeHead = dataHead;
            }
            table->displayArray = display;
        }
        return table;
    }
}

int StoreTable(struct Table *table) {
    string filePath = "..\\databaseTables\\" + table->tableName + ".csv";
    ofstream fp(filePath);// 打开可读写文件，若有内容则清除内容
    if (fp.bad()) {
        cout << "创建" << table->tableName << "文件发生错误，存储失败，请稍后重试\n";
        return 0;
    } else {
        int segmentNum = table->segmentNum;
        fp << segmentNum << endl;
        for (int i = 0; i < segmentNum; ++i) { // 存储字段类型，为字符串
            fp << table->segmentType[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        for (int i = 0; i < segmentNum; ++i) { // 存储typeArray，用int标识字段的数据类型
            fp << table->typeArray[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        for (int i = 0; i < segmentNum; ++i) { // 存储字段名字
            fp << table->segmentName[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        struct Node *tempNode = table->nodeHead;
        int *indexInType = new int[segmentNum]; // 记录每个字段在对应类型的数组中的下标
        if (tempNode != NULL) {
            int num_int = 0, num_double = 0, num_string = 0;
            for (int i = 0; i < segmentNum; ++i) { // 生成每个字段在对应类型的数组中的下标
                if (table->typeArray[i] == 0) {
                    indexInType[i] = num_int++;
                } else if (table->typeArray[i] == 1) {
                    indexInType[i] = num_double++;
                } else {
                    indexInType[i] = num_string++;
                }
            }
        }
        while (tempNode != NULL) { // 写入数据条
            for (int i = 0; i < segmentNum; ++i) {
                int index = indexInType[i];
                if (table->typeArray[i] == 0) {
                    fp << tempNode->intArray[index];
                } else if (table->typeArray[i] == 1) {
                    fp << tempNode->doubleArray[index];
                } else {
                    fp << tempNode->stringArray[index];
                }
                fp << ",";
            }
            fp << tempNode->nodeIndex << endl;
            tempNode = tempNode->next;
        }
        fp.close();
        DeleteTable(table);
        return 1;
    }
}

int CreateTable() {
    int flag = 0;
    string tableName;
    while (flag == 0) {
        cout << "请输入您要新建的表的表名:";
        cin >> tableName;
        while (CorrectString(tableName) != 1) {
            cin >> tableName;
        }
        string filePath = "..\\databaseTables\\" + tableName + ".csv";
        if (access(filePath.c_str(), 0) != 0) { // 说明该表不存在，可以创建
            flag = 1;
        } else {
            cout << "该表已存在！是否要覆盖该表，输入Y以覆盖，输入N不覆盖:";
            char confirm;
            string confirmText;
            cin >> confirmText;
            while (1) {
                if (CorrectChar(confirmText) != 1) {
                    cout << "您输入的选项不存在，请重新输入:";
                    cin >> confirmText;
                } else {
                    confirm = String2Char(confirmText);
                    if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
                        cout << "您输入的选项不存在，请重新输入:";
                        cin >> confirmText;
                    } else {
                        break;
                    }
                }
            }
            if (confirm == 'Y' || confirm == 'y') {
                flag = 1;
            }
        }
    }
    cout << "请输入该表中有多少个字段:";
    string numInString;
    cin >> numInString;
    while (CorrectInt(numInString) != 1) {
        cout << "您输入的数字不符合要求，请重新输入:";
        cin >> numInString;
    }
    int segmentNum = String2Int(numInString);
    string *segmentType = new string[segmentNum];
    int *typeArray = new int[segmentNum];
    string *segmentName = new string[segmentNum];
    for (int i = 0; i < segmentNum; ++i) {
        cout << "请输入第" << i + 1 << "个字段的数据类型(int, double或者string):";
        string type;
        cin >> type;
        int isFine = 0;
        if (type == "int") {
            segmentType[i] = "int";
            typeArray[i] = 0;
            isFine = 1;
        } else if (type == "double") {
            segmentType[i] = "double";
            typeArray[i] = 1;
            isFine = 1;
        } else if (type == "string") {
//            cout << "^^^^^^^^" << segmentType[i] << "^^^^^^^^\n";
            segmentType[i] = "string";
//            cout << "^^^^^^^^" << segmentType[i] << "^^^^^^^^\n";
            typeArray[i] = 2;
            isFine = 1;
        } else {
            cout << "您输入的类型不存在，请重新输入\n";
            i--;
        }
        if (isFine == 1) {
//            cout << "****" << segmentType[i] << "****\n";
            cout << "请输入该字段的名字:";
            string name;
            cin >> name;
            while (CorrectString(name) != 1) {
                cout << "您输入的名字不合规，请重新输入:";
                cin >> name;
            }
            segmentName[i] = name;
//            cout << "you print****" << segmentName[i] << "****\n";
        }
    }
    struct Table *table = new Table;
    table->tableName = tableName;
    table->segmentNum = segmentNum;
    table->segmentType = segmentType;
    table->typeArray = typeArray;
    table->segmentName = segmentName;
    table->nodeHead = NULL;
    table->displayArray = NULL;
    int storeSuccess = StoreTable(table);
    if (storeSuccess == 1) {
        cout << "新建表成功!\n";
        return 1;
    } else {
        cout << "抱歉，出了一些问题，新建失败，请稍后重试.\n";
        return 0;
    }
}


int ChangeTable(int num) {
    string tableName, segmentName, segmentNewName;
    string oldPath;
    struct Table *table;
//    // 先展示表目录
//    DisplayTables();
    cout << "请输入要修改的表名，输入-1以结束:";
    cin >> tableName;
    // 判断输入的表名是否存在（轮询）
    while (!(table = ReadTable(tableName))) {
        if (tableName == "-1") {
            return 0;
        }
        cout << "请重新输入要修改的表名：";
        cin >> tableName;
    }
    oldPath = string(path) + tableName + ".csv";
    // 修改表名
    if (num == 0) {
        cout << "请输入新表名：";
        cin >> table->tableName;
        //
        string newPath = string(path) + table->tableName + ".csv";
        if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
            cout << "表名修改成功！" << endl;
            DisplayTables();
        } else
            cout << "表名修改失败！" << endl;
    }
        // 修改字段名
    else if (num == 1) {
        if (table) {
            // 展示所有字段
            cout << tableName << "表的所有字段：";
            for (int i = 0; i < table->segmentNum; ++i) {
                cout << std::left << setw(10) << table->segmentName[i];
            }
            cout << endl;

            // 轮询是否继续修改字段名
            while (1) {
                cout << "请输入要修改的字段：";
                cin >> segmentName;
                int segmentFound = 0;
                // 匹配字段名
                for (int i = 0; i < table->segmentNum; ++i) {
                    if (segmentName == table->segmentName[i]) {
                        segmentFound = 1;
                        cout << "请输入新字段名：";
                        cin >> table->segmentName[i];
                    }
                }
                if (segmentFound == 0) {
                    cout << "字段不存在，请检查字段名输入是否正确！\n";
                } else {
                    cout << "是否继续修改字段名：\n"
                         << "输入 0 : 继续修改\n"
                         << "输入其他 : 退出\n";
                    string str;
                    cin >> str;
                    if (str != "0") {
                        break;
                    }
                }
            }
            // 判断表存储是否成功
            if (StoreTable(table) && remove(oldPath.c_str()) == 0) {
                cout << "字段修改成功！\n";
                table = ReadTable(tableName);
                cout << tableName << " 表的所有字段：";
                for (int i = 0; i < table->segmentNum; ++i) {
                    cout << std::left << setw(10) << table->segmentName[i];
                }
                cout << endl;
                return 1;
            } else {
                cout << "字段修改失败！\n";
                return 0;
            }
        }
    }
    return 0;
}

int DeleteTable(string tableName) {
    // 拼接路径
    string filePath = string(path) + tableName + ".csv";

    // 判断表名是否存在（轮询）
    while (access(filePath.c_str(), 0) != 0) {
        cout << "您输入的表不存在！\n";
        cout << "请重新输入要删除的表名：";
        cin >> tableName;
    }

    // 判断删除文件是否成功
    if (remove(filePath.c_str()) == 0) {
        cout << "表删除成功！\n";
        DisplayTables();
        return 1;
    } else {
        cout << "表删除失败！\n";
        return 0;
    }
}

// TODO: 数据模块

void InsertData(string tableName) {
    struct Table *table;
    // 轮询检查表是否存在
    while (!(table = ReadTable(tableName))) {
        cout << "您输入的表不存在！\n";
        cout << "请重新输入要修改的表名：";
        cin >> tableName;
    }
    struct Node *temp = table->nodeHead;

    // 展示所有字段名及其类型
    int segmentNum = table->segmentNum;
    for (int i = 0; i < segmentNum; i++) {
        cout << table->segmentName[i] << "(" << table->segmentType[i] << ")\t";
    }
    cout << endl;
    string *dataString = new string[segmentNum];
    int *dataInt = new int[segmentNum];
    double *dataDouble = new double[segmentNum];
    int intNum, doubleNum, stringNum;
    int intIndex, doubleIndex, stringIndex;
    while (1) {
        intNum = 0, doubleNum = 0, stringNum = 0;
        for (int i = 0; i < segmentNum; ++i) {
            // 轮询输入字段内容
            while (1) {
                cout << "请输入第" << i + 1 << "个字段的内容:";
                cin >> dataString[i];
//                cout << "*************第" << i << "个字段的type是" << table->typeArray[i] << endl;
//                cout << "*************您输入的是:" << dataString[i] << endl;
                if (table->typeArray[i] == 0) {
                    if (CorrectInt(dataString[i])) {
                        dataInt[i] = String2Int(dataString[i]);
                        intNum++;
                        break;
                    } else {
                        cout << "输入的类型非法，请输入int类型！";
                    }
                } else if (table->typeArray[i] == 1) {
                    if (CorrectDouble(dataString[i])) {
                        dataDouble[i] = String2Double(dataString[i]);
                        doubleNum++;
                        break;
                    } else {
                        cout << "输入的类型非法，请输入double类型！";
                    }
                } else {
                    if (CorrectString(dataString[i])) {
                        stringNum++;
                        break;
                    } else {
                        cout << "输入的类型非法，请输入string类型！";
                    }
                }
            }
        }

        intIndex = 0, doubleIndex = 0, stringIndex = 0;
        struct Node *node = new Node;
        node->next = NULL;
        node->next_info = NULL;

        node->num_int = intNum;
        node->num_double = doubleNum;
        node->num_string = stringNum;

        if (intNum != 0) {
            node->intArray = new int[intNum];
        } else {
            node->intArray = NULL;
        }
        if (doubleNum != 0) {
            node->doubleArray = new double[doubleNum];
        } else {
            node->doubleArray = NULL;
        }
        if (stringNum != 0) {
            node->stringArray = new string[stringNum];
        } else {
            node->stringArray = NULL;
        }

        for (int i = 0; i < segmentNum; ++i) {
            if (table->typeArray[i] == 0) {
                node->intArray[intIndex++] = dataInt[i];
//                cout << "********" << dataInt[i] << "*******";
            } else if (table->typeArray[i] == 1) {
                node->doubleArray[doubleIndex++] = dataDouble[i];
//                cout << "********" << dataDouble[i] << "*******";
            } else {
//                cout << "********" << dataString[i] << "*******";
                node->stringArray[stringIndex++] = dataString[i];
            }
        }

        if (!temp) {
            node->nodeIndex = 0;
            table->nodeHead = node;
            temp = table->nodeHead;
        } else {
            while (temp->next) {
                temp = temp->next;
            }
            node->nodeIndex = temp->nodeIndex + 1;
            temp->next = node;
        }

        cout << "是否继续增加数据：\n"
             << "输入 0 : 继续增加\n"
             << "输入其他 : 退出\n";
        string str;
        cin >> str;
        if (str != "0") {
            break;
        }
    }

    if (StoreTable(table)) {
        cout << "数据增加成功！\n";
    } else {
        cout << "数据增加失败!\n";
    }
}

void EditData(string tableName) {
    struct Table *table = ReadTable(tableName);
    int len = table->segmentNum;
    int *resIndex = InfoData(1, table);//先查询数据
    /*记录字段在对应类型的数组中的下标*/
    int totalLength = table->segmentNum; // 取得字段总个数
    int num_int = 0, num_double = 0, num_string = 0;//分别代表在intArray的下标，在doubleArray中的下标，在stringArray的下标
    int *displayIndex = new int[totalLength]; // 记录字段在对应类型的数组中的下标的数组
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
    }
    for (int i = 0; i < totalLength; i++) {

        if (table->typeArray[i] == 1) {
            displayIndex[i] = num_int;
            num_int++;
        } else if (table->typeArray[i] == 2) {
            displayIndex[i] = num_double;
            num_double++;
        } else {
            displayIndex[i] = num_string;
            num_string++;
        }
    }
    if (resIndex != nullptr) {
        int okNum = _msize(resIndex) / sizeof(int);
        cout << "--------------以上是符合条件的数据,您将会修改这些数据------------" << endl;
        while (1) {
            /*输出提示语*/
            cout << "表有如下字段：\n";
            for (int i = 0; i < len; ++i) {
                cout << i + 1 << ". " << table->segmentName[i] << " ";
            }
            cout << "\n请输入修改字段的编号,输入0返回\n";

            /*获取用户输入的编号*/
            struct Node *p = table->nodeHead;
            int count = 0;
            int nextcount = 0;
            int index;
            string indexRes;
            cin >> indexRes;
            int indexFlag = CorrectInt(indexRes);//合法性检验


            if (indexFlag) {//这里面输入item
                index = String2Int(indexRes);
                if (index == 0) {
                    return;
                }
                if (0 < index && index <= len) {

                    int type = table->typeArray[index - 1];
                    int itemFlag = -1;

                    if (type == 0) {//如果字段类型是int

                        /*编号经过合法性检验之后，获取用户输入的字段内容*/
                        cout << "请输入该字段修改后的值\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectInt(itemRes);//内容的合法性检验

                        /*内容经过合法性检验之后，进行修改*/
                        if (itemFlag == 1) {
                            int targetInt = String2Int(itemRes);
                            /*遍历数据表*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->intArray[displayIndex[index - 1]] = targetInt;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }

                            //展示修改结果
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);

                        } else {
                            cout << "内容有误，请重新输入\n";
                        }
                    }
                    if (type == 1) {//如果字段类型是double

                        /*编号经过合法性检验之后，获取用户输入的字段内容*/
                        cout << "请输入该字段修改后的值\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectDouble(itemRes);//内容的合法性检验

                        /*内容经过合法性检验之后，进行修改*/
                        if (itemFlag == 1) {//这里面进行寻找符合条件的值
                            double targetDouble = String2Double(itemRes);
//                            cout << "$$$$$$$" << targetDouble << endl;
                            /*遍历数据表*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->doubleArray[displayIndex[index - 1]] = targetDouble;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }
                            //展示修改结果
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);
                        } else {
                            cout << "内容有误，请重新输入\n";
                        }
                    }
                    if (type == 2) {//如果字段类型是string

                        /*编号经过合法性检验之后，获取用户输入的字段内容*/
                        cout << "请输入该字段修改后的值\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectString(itemRes);//内容的合法性检验

                        /*内容经过合法性检验之后，进行修改*/
                        if (itemFlag == 1) {//这里面进行寻找符合条件的值
                            string targetString = itemRes;
                            /*遍历数据表*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->stringArray[displayIndex[index - 1]] = targetString;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }
                            //展示修改结果
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);
                        } else {
                            cout << "内容有误，请重新输入\n";
                        }
                    }


                } else {
                    cout << "编号有误\n";
                }
            } else {
                cout << "编号有误\n";
            }

            /*询问用户是否继续修改，获取用户的选择*/
            cout << "是否继续修改数据？输入1继续，输入其他退出修改\n";
            string confirmString2;
            cin >> confirmString2;
            int confirmFlag2 = CorrectInt(confirmString2);
            if (confirmFlag2) {
                int confirm = String2Int(confirmString2);
                if (confirm != 1) {
                    break;
                }
            } else {
                break;
            }
        }
        /*储存修改后的表*/
        StoreTable(table);
    }
}

void DeleteData(string tableName) {
    struct Table *table = ReadTable(tableName);
    while (1) {

        int *resIndex = InfoData(1, table);//先查询数据
        if (resIndex == nullptr) {
            break;
        }

        /*输出提示，获取用户是否确认删除*/
        cout << "是否确认删除这几行数据？输入1确认，输入其他取消\n";
        string confirmString;
        cin >> confirmString;
        int confirmFlag = CorrectInt(confirmString);
        if (confirmFlag) {
            /*通过合法性检验之后，遍历数据表*/
            Node *trueHead = NULL;
            struct Node *p = new Node;
            p->next = table->nodeHead;
            struct Node *pNext = p->next;
            int count = 0;
            int nextCount = 0;
            int confirm = String2Int(confirmString);
            if (confirm == 1) {
                /*执行删除操作*/
                while (pNext != NULL) {
                    if (count == resIndex[nextCount]) {
                        p->next = pNext->next;
                        pNext = p->next;
                        nextCount++;
                    } else {
                        p = p->next;
                        if (trueHead == NULL) {
                            trueHead = p;
                        }
                        pNext = p->next;
                    }
                    count++;
                }
                table->nodeHead = trueHead;
                /*展示删除后内容*/
                OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                              table->segmentNum);
                /*更新数据index*/
                int newIndex = 0;
                p = table->nodeHead;
                while (p != NULL) {
                    p->nodeIndex = newIndex++;
                    p = p->next;
                }
            }

        }

        /*询问用户是否继续删除并且获取用户指令*/
        cout << "是否继续删除数据？输入1继续，输入其他退出删除\n";
        string confirmString2;
        cin >> confirmString2;
        int confirmFlag2 = CorrectInt(confirmString2);
        if (confirmFlag2) {
            int confirm = String2Int(confirmString2);
            if (confirm != 1) {
                break;
            }
        } else {
            break;
        }
    }

    /*储存删除后的表*/
    StoreTable(table);
}

int *InfoData(int flag, struct Table *table) {
    string *infoSegmentName = table->segmentName;//字段名数组
    int *infoDisplayArray = table->displayArray;//表的展示哪个字段的（指针）数组
    int len = 0;//字段数
    len = table->segmentNum;//表的真实字段数

    /*记录字段在对应类型的数组中的下标*/
    int totalLength = table->segmentNum; // 取得字段总个数
    int num_int = 0, num_double = 0, num_string = 0;//在intArray的下标，在doubleArray中的下标，在stringArray的下标
    int *displayIndex = new int[totalLength]; // 记录字段在对应类型的数组中的下标的数组
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
    }
    for (int i = 0; i < totalLength; i++) {

        if (table->typeArray[i] == 1) {
            displayIndex[i] = num_int;
            num_int++;
        } else if (table->typeArray[i] == 2) {
            displayIndex[i] = num_double;
            num_double++;
        } else {
            displayIndex[i] = num_string;
            num_string++;
        }
    }

    struct Node *p = table->nodeHead;//表的第一条数据的指针
    struct Node *infoResultNode = nullptr;//查询结果的头指针
    struct Node *nextInfoNode = nullptr;//下一条查询结果的指针

    int timesFlag = 0;//记录是否是第一次进入查询，0是第一次，1不是
    while (1) {
        if (timesFlag == 1) {//当不是第一次进入，p指针等于查询结果的头指针
            p = infoResultNode;
        }

        int index;//这个表中第几条数据表

        /*输出提示语*/
        cout << "表有如下字段：\n";
        for (int i = 0; i < len; ++i) {
            cout << i + 1 << ". " << infoSegmentName[i] << " ";
        }
        cout << "\n请输入约束条件字段的编号,输入0返回\n";

        /*输入编号*/
        string indexRes;
        cin >> indexRes;
        int indexFlag = CorrectInt(indexRes);//判断合法性（是否是int）

        if (indexFlag) {//如果合法

            index = String2Int(indexRes);
            if (index == 0) {
                return 0;
            }
            if (0 < index && index <= len) {//判断合法性（范围是否合法）

                //如果合法，获取字段的值
                cout << "请输入约束条件的值\n";
                string itemRes;
                cin >> itemRes;
                int type = table->typeArray[index - 1];
                int itemFlag = -1;

                if (type == 0) {//如果字段类型是int
                    itemFlag = CorrectInt(itemRes);//合法性判断

                    /*经过合法性判断后，这里面进行寻找符合条件的值*/
                    if (itemFlag == 1) {
                        int targetInt = String2Int(itemRes);

                        /*遍历数据表*/
                        while (p != NULL) {
                            int resInt = p->intArray[displayIndex[index - 1]];//获取某一条数据的对应字段的值
                            if (resInt == targetInt) {
                                if (infoResultNode == nullptr) {
                                    nextInfoNode = p;
                                    infoResultNode = nextInfoNode;
                                } else {
                                    nextInfoNode->next_info = p;
                                    nextInfoNode = nextInfoNode->next_info;
                                }
                            }
                            if (timesFlag == 1) {
                                p = p->next_info;
                            } else {
                                p = p->next;
                            }
                        }

                    } else {
                        cout << "内容有误，请重新输入\n";
                    }
                } else if (type == 1) {//如果字段类型是double
                    itemFlag = CorrectDouble(itemRes);//合法性判断

                    /*经过合法性判断后，这里面进行寻找符合条件的值*/
                    if (itemFlag == 1) {
                        double targetDouble = String2Double(itemRes);

                        /*遍历数据表*/
                        while (p != NULL) {
                            int resDouble = p->doubleArray[displayIndex[index - 1]];//获取某一条数据的对应字段的值
                            if (resDouble == targetDouble) {
                                if (infoResultNode == NULL) {
                                    nextInfoNode = p;
                                    infoResultNode = nextInfoNode;
                                } else {
                                    nextInfoNode->next_info = p;
                                    nextInfoNode = nextInfoNode->next_info;
                                }
                            }
                            if (timesFlag == 1) {
                                p = p->next_info;
                            } else {
                                p = p->next;
                            }
                        }
                    } else {
                        cout << "内容有误，请重新输入\n";
                    }
                } else {//如果字段类型是string
                    itemFlag = CorrectString(itemRes);//合法性判断

                    /*经过合法性判断后，这里面进行寻找符合条件的值*/
                    if (itemFlag == 1) {
                        string targetString = itemRes;

                        /*遍历数据表*/
                        while (p != NULL) {
                            string resString = p->stringArray[displayIndex[index - 1]];//获取某一条数据的对应字段的值
                            if (resString == targetString) {
                                if (infoResultNode == nullptr) {
                                    nextInfoNode = p;
                                    infoResultNode = nextInfoNode;
                                } else {
                                    nextInfoNode->next_info = p;
                                    nextInfoNode = nextInfoNode->next_info;
                                }
                            }
                            if (timesFlag == 1) {//如果不是第一次进入，遍历的方式通过遍历上一次查询的结果链表
                                p = p->next_info;
                            } else {
                                p = p->next;//如果是第一次进入，遍历的方式通过遍历表
                            }
                        }
                    } else {
                        cout << "内容有误，请重新输入\n";
                    }
                }


            } else {
                cout << "编号有误\n";
            }
        } else {
            cout << "编号有误\n";
        }

        /*输出提示语并且获取用户是否继续查找，如果继续查找，就继续循环，如果不查找了就break；*/
        if (infoResultNode == NULL) {
            cout << "没有符合要求的查询结果\n";
            return nullptr;
        } else {
            if (timesFlag == 0) {
                timesFlag = 1;
            }
            break;
        }

    }

    /*至此，infoResultNode已经查找好了*/

    /*把每一条查找结果的下标存在indexArray，等下要返回*/
    int nodeNum = 0;
    struct Node *p2;
    p2 = infoResultNode;
    while (p2 != NULL) {
        nodeNum++;
        p2 = p2->next_info;
    }
    int *indexArray = new int[nodeNum];//存储的indexArray
    int nodeIndex = 0;//
    p2 = infoResultNode;
    while (p2 != NULL) {
        indexArray[nodeIndex] = p2->nodeIndex;
        nodeIndex++;
        p2 = p2->next_info;
    }

    int *showArray = new int[len];
    /*如果是主函数调用的查询函数，就要选择展示字段*/
    if (flag == 0) {
        int breakFlag = 0;
        while (1) {

            /*输出提示语*/
            cout << "请选择要展示的字段\n";
            cout << "表有如下字段：\n";
            for (int i = 0; i < len; ++i) {
                cout << i + 1 << ". " << infoSegmentName[i] << " ";
            }
            cout << endl;
            /*输入展示的字段下标*/
            while (1) {
                cout << "请输入约束条件字段的编号,输入0结束，输入-1展示全部字段:";
                int showIndex;
                cin >> showIndex;
                if (showIndex == 0) {
                    breakFlag = 1;
                    break;
                } else if (showIndex < -1 || showIndex > len) {
                    cout << "编号有误，请重新输入\n";
                    break;
                } else if (showIndex == -1) {
//                    memset(showArray, 1, table->segmentNum);
                    for (int i = 0; i < table->segmentNum; ++i) {
                        showArray[i] = 1;
                    }
                    cout << "输出全部字段:\n";
                    breakFlag = 1;
                } else {
                    showArray[showIndex - 1] = 1;
                }
                if (breakFlag) {
                    break;
                }
            }
            break;
        }
        cout << endl;
        /*选择完字段之后，展示内容*/
        OutputDisplay2(table->segmentName, showArray, infoResultNode, table->typeArray, table->segmentNum);
        DeleteTable(table);
        /*返回查找结果的下标集合*/
        return indexArray;
    } else {
/*上面已经把找到的结果放在infoResultNode了，现在进行展示*/
        OutputDisplay2(table
                               ->segmentName, table->displayArray, infoResultNode, table->typeArray,
                       table->segmentNum);//展示现在的查询情况给用户
/*返回查找结果的下标集合*/
        return
                indexArray;
    }

}

void DeleteTable(Table *table) {
    delete[] table->segmentType;
    delete[] table->segmentName;
    delete[] table->displayArray;
    delete[] table->typeArray;
    if (table->nodeHead != nullptr) DeleteNode(table->nodeHead);
}

void DeleteNode(Node *node) {
    if (node->stringArray != nullptr) delete[] node->stringArray;
    if (node->doubleArray != nullptr) delete[] node->doubleArray;
    if (node->intArray != nullptr) delete[] node->intArray;
    Node *p = node;
    Node *q;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
}


