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

// TODO: �������ģ��

void OutputDisplay(string *segmentName,
                   int *display,
                   struct Node *dataHead,
                   int *typeArray,
                   int totalLength) {
    int num_int = 0, num_double = 0, num_string = 0;
    int *displayIndex = new int[totalLength]; // ��¼Ҫ������ֶ��ڶ�Ӧ���͵������е��±�
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
//        cout << "�������ֶ���Ϊ----------" << segmentName[i] << "---------\n";
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
    int *displayIndex = new int[totalLength]; // ��¼Ҫ������ֶ��ڶ�Ӧ���͵������е��±�
    for (int i = 0; i < totalLength; i++) {
        displayIndex[i] = 0;
//        cout << "�������ֶ���Ϊ----------" << segmentName[i] << "---------\n";
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


// TODO: ��ģ��
int DisplayTables() {
    DIR *dirp;
    dirent *direntp;
    dirp = opendir(path);
    string tmp = ".csv";
    string tableName;
    int i = 1;
    cout << "***************************************************\n";
    cout << "���ݿ������������µ����ݱ�:" << endl;
    if (dirp != NULL) {
        for (int j = 1; j <= 2; j++) { // �Ƚ��ļ���.��..��ȡ��
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
            cout << "���ݿ����ޱ�!" << endl;
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
//    cout << "�ļ�·����*********" << filePath << "*******\n";
    if (access(filePath.c_str(), 0) != 0) {
        cout << "������ı����ڣ�\n";
        struct Table *table = NULL;
        return table;
    } else {
        ifstream fp(filePath.c_str());
        struct Table *table = new Table;
        int i;
        if (!fp.is_open()) {
            cout << "��ȡ������ʱ�����������Ժ�����\n";
            table = NULL;
        } else { // �����ݸ�ʽ���ֶ������ֶ����͡��ֶ�˳���ֶ����֡���������
            string line; // ��ȡcsv�ļ�ÿһ��
            string field; // ��ȡ��','������ÿһ��
            getline(fp, line); // ��ȡ�ֶ���
            int segmentNum = String2Int(line);
            string *segmentType = new string[segmentNum]; // ��ȡ�ֶ�����
            getline(fp, line);
            istringstream sin(line);
            i = 0;
            while (getline(sin, field, ',')) {
                segmentType[i++] = field;
            }
            for (int i = 0; i < segmentNum; ++i) {
//                cout << "������ֶ�����Ϊ********" << segmentType[i] << "*******\n";
            }
            int *typeArray = new int[segmentNum]; // ��ȡ�ֶ�˳��
            getline(fp, line);
//            cout << "~~~~~~~~������һ����:" << line << endl;
            istringstream sin1(line);
            i = 0;
            while (getline(sin1, field, ',')) {
//                cout << "+++++++�����ֵ��" << field << endl;
                typeArray[i++] = String2Int(field);
            }
            for (int j = 0; j < segmentNum; ++j) {
//                cout << "--------typeArray[" << j << "]��" << typeArray[j] << endl;
            }
            int *display = new int[segmentNum]; // ������ʾ���飬ȫ����ʼ��Ϊ1������ȫ����ʾ
            for (int i = 0; i < segmentNum; ++i) {
                display[i] = 1;
            }
            string *segmentName = new string[segmentNum]; // ��ȡ�ֶ�����
            getline(fp, line);
            istringstream sin2(line);
            i = 0;
            while (getline(sin2, field, ',')) {
                segmentName[i++] = field;
            }
            for (int i = 0; i < segmentNum; ++i) {
//                cout << "������ֶ���Ϊ********" << segmentName[i] << "*******\n";
            }
            struct Node *dataHead = new Node;
            struct Node *tempHead = new Node;
            tempHead->next = dataHead;
            while (getline(fp, line)) { // ���ж�ȡ������
//                cout << "%%%%%%%%%%%%%%��ȡ����������Ϊ:" << line << endl;
                struct Node *tempNode = new Node;
                int num_int = 0, num_double = 0, num_string = 0;
                for (int i = 0; i < segmentNum; ++i) { // ����ÿ���ֶΣ������ֶ����������и�ֵ
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
//                cout << "���\n";
                vector<string> content; // ��ȡһ������
                istringstream sin3(line);
                while (getline(sin3, field, ',')) {
//                    cout << "&&&&&&&&������ֵΪ" << field << endl;
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
    ofstream fp(filePath);// �򿪿ɶ�д�ļ��������������������
    if (fp.bad()) {
        cout << "����" << table->tableName << "�ļ��������󣬴洢ʧ�ܣ����Ժ�����\n";
        return 0;
    } else {
        int segmentNum = table->segmentNum;
        fp << segmentNum << endl;
        for (int i = 0; i < segmentNum; ++i) { // �洢�ֶ����ͣ�Ϊ�ַ���
            fp << table->segmentType[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        for (int i = 0; i < segmentNum; ++i) { // �洢typeArray����int��ʶ�ֶε���������
            fp << table->typeArray[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        for (int i = 0; i < segmentNum; ++i) { // �洢�ֶ�����
            fp << table->segmentName[i];
            if (i != segmentNum - 1) {
                fp << ",";
            } else {
                fp << endl;
            }
        }
        struct Node *tempNode = table->nodeHead;
        int *indexInType = new int[segmentNum]; // ��¼ÿ���ֶ��ڶ�Ӧ���͵������е��±�
        if (tempNode != NULL) {
            int num_int = 0, num_double = 0, num_string = 0;
            for (int i = 0; i < segmentNum; ++i) { // ����ÿ���ֶ��ڶ�Ӧ���͵������е��±�
                if (table->typeArray[i] == 0) {
                    indexInType[i] = num_int++;
                } else if (table->typeArray[i] == 1) {
                    indexInType[i] = num_double++;
                } else {
                    indexInType[i] = num_string++;
                }
            }
        }
        while (tempNode != NULL) { // д��������
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
        cout << "��������Ҫ�½��ı�ı���:";
        cin >> tableName;
        while (CorrectString(tableName) != 1) {
            cin >> tableName;
        }
        string filePath = "..\\databaseTables\\" + tableName + ".csv";
        if (access(filePath.c_str(), 0) != 0) { // ˵���ñ����ڣ����Դ���
            flag = 1;
        } else {
            cout << "�ñ��Ѵ��ڣ��Ƿ�Ҫ���Ǹñ�����Y�Ը��ǣ�����N������:";
            char confirm;
            string confirmText;
            cin >> confirmText;
            while (1) {
                if (CorrectChar(confirmText) != 1) {
                    cout << "�������ѡ����ڣ�����������:";
                    cin >> confirmText;
                } else {
                    confirm = String2Char(confirmText);
                    if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
                        cout << "�������ѡ����ڣ�����������:";
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
    cout << "������ñ����ж��ٸ��ֶ�:";
    string numInString;
    cin >> numInString;
    while (CorrectInt(numInString) != 1) {
        cout << "����������ֲ�����Ҫ������������:";
        cin >> numInString;
    }
    int segmentNum = String2Int(numInString);
    string *segmentType = new string[segmentNum];
    int *typeArray = new int[segmentNum];
    string *segmentName = new string[segmentNum];
    for (int i = 0; i < segmentNum; ++i) {
        cout << "�������" << i + 1 << "���ֶε���������(int, double����string):";
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
            cout << "����������Ͳ����ڣ�����������\n";
            i--;
        }
        if (isFine == 1) {
//            cout << "****" << segmentType[i] << "****\n";
            cout << "��������ֶε�����:";
            string name;
            cin >> name;
            while (CorrectString(name) != 1) {
                cout << "����������ֲ��Ϲ棬����������:";
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
        cout << "�½���ɹ�!\n";
        return 1;
    } else {
        cout << "��Ǹ������һЩ���⣬�½�ʧ�ܣ����Ժ�����.\n";
        return 0;
    }
}


int ChangeTable(int num) {
    string tableName, segmentName, segmentNewName;
    string oldPath;
    struct Table *table;
//    // ��չʾ��Ŀ¼
//    DisplayTables();
    cout << "������Ҫ�޸ĵı���������-1�Խ���:";
    cin >> tableName;
    // �ж�����ı����Ƿ���ڣ���ѯ��
    while (!(table = ReadTable(tableName))) {
        if (tableName == "-1") {
            return 0;
        }
        cout << "����������Ҫ�޸ĵı�����";
        cin >> tableName;
    }
    oldPath = string(path) + tableName + ".csv";
    // �޸ı���
    if (num == 0) {
        cout << "�������±�����";
        cin >> table->tableName;
        //
        string newPath = string(path) + table->tableName + ".csv";
        if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
            cout << "�����޸ĳɹ���" << endl;
            DisplayTables();
        } else
            cout << "�����޸�ʧ�ܣ�" << endl;
    }
        // �޸��ֶ���
    else if (num == 1) {
        if (table) {
            // չʾ�����ֶ�
            cout << tableName << "��������ֶΣ�";
            for (int i = 0; i < table->segmentNum; ++i) {
                cout << std::left << setw(10) << table->segmentName[i];
            }
            cout << endl;

            // ��ѯ�Ƿ�����޸��ֶ���
            while (1) {
                cout << "������Ҫ�޸ĵ��ֶΣ�";
                cin >> segmentName;
                int segmentFound = 0;
                // ƥ���ֶ���
                for (int i = 0; i < table->segmentNum; ++i) {
                    if (segmentName == table->segmentName[i]) {
                        segmentFound = 1;
                        cout << "���������ֶ�����";
                        cin >> table->segmentName[i];
                    }
                }
                if (segmentFound == 0) {
                    cout << "�ֶβ����ڣ������ֶ��������Ƿ���ȷ��\n";
                } else {
                    cout << "�Ƿ�����޸��ֶ�����\n"
                         << "���� 0 : �����޸�\n"
                         << "�������� : �˳�\n";
                    string str;
                    cin >> str;
                    if (str != "0") {
                        break;
                    }
                }
            }
            // �жϱ�洢�Ƿ�ɹ�
            if (StoreTable(table) && remove(oldPath.c_str()) == 0) {
                cout << "�ֶ��޸ĳɹ���\n";
                table = ReadTable(tableName);
                cout << tableName << " ��������ֶΣ�";
                for (int i = 0; i < table->segmentNum; ++i) {
                    cout << std::left << setw(10) << table->segmentName[i];
                }
                cout << endl;
                return 1;
            } else {
                cout << "�ֶ��޸�ʧ�ܣ�\n";
                return 0;
            }
        }
    }
    return 0;
}

int DeleteTable(string tableName) {
    // ƴ��·��
    string filePath = string(path) + tableName + ".csv";

    // �жϱ����Ƿ���ڣ���ѯ��
    while (access(filePath.c_str(), 0) != 0) {
        cout << "������ı����ڣ�\n";
        cout << "����������Ҫɾ���ı�����";
        cin >> tableName;
    }

    // �ж�ɾ���ļ��Ƿ�ɹ�
    if (remove(filePath.c_str()) == 0) {
        cout << "��ɾ���ɹ���\n";
        DisplayTables();
        return 1;
    } else {
        cout << "��ɾ��ʧ�ܣ�\n";
        return 0;
    }
}

// TODO: ����ģ��

void InsertData(string tableName) {
    struct Table *table;
    // ��ѯ�����Ƿ����
    while (!(table = ReadTable(tableName))) {
        cout << "������ı����ڣ�\n";
        cout << "����������Ҫ�޸ĵı�����";
        cin >> tableName;
    }
    struct Node *temp = table->nodeHead;

    // չʾ�����ֶ�����������
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
            // ��ѯ�����ֶ�����
            while (1) {
                cout << "�������" << i + 1 << "���ֶε�����:";
                cin >> dataString[i];
//                cout << "*************��" << i << "���ֶε�type��" << table->typeArray[i] << endl;
//                cout << "*************���������:" << dataString[i] << endl;
                if (table->typeArray[i] == 0) {
                    if (CorrectInt(dataString[i])) {
                        dataInt[i] = String2Int(dataString[i]);
                        intNum++;
                        break;
                    } else {
                        cout << "��������ͷǷ���������int���ͣ�";
                    }
                } else if (table->typeArray[i] == 1) {
                    if (CorrectDouble(dataString[i])) {
                        dataDouble[i] = String2Double(dataString[i]);
                        doubleNum++;
                        break;
                    } else {
                        cout << "��������ͷǷ���������double���ͣ�";
                    }
                } else {
                    if (CorrectString(dataString[i])) {
                        stringNum++;
                        break;
                    } else {
                        cout << "��������ͷǷ���������string���ͣ�";
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

        cout << "�Ƿ�����������ݣ�\n"
             << "���� 0 : ��������\n"
             << "�������� : �˳�\n";
        string str;
        cin >> str;
        if (str != "0") {
            break;
        }
    }

    if (StoreTable(table)) {
        cout << "�������ӳɹ���\n";
    } else {
        cout << "��������ʧ��!\n";
    }
}

void EditData(string tableName) {
    struct Table *table = ReadTable(tableName);
    int len = table->segmentNum;
    int *resIndex = InfoData(1, table);//�Ȳ�ѯ����
    /*��¼�ֶ��ڶ�Ӧ���͵������е��±�*/
    int totalLength = table->segmentNum; // ȡ���ֶ��ܸ���
    int num_int = 0, num_double = 0, num_string = 0;//�ֱ������intArray���±꣬��doubleArray�е��±꣬��stringArray���±�
    int *displayIndex = new int[totalLength]; // ��¼�ֶ��ڶ�Ӧ���͵������е��±������
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
        cout << "--------------�����Ƿ�������������,�������޸���Щ����------------" << endl;
        while (1) {
            /*�����ʾ��*/
            cout << "���������ֶΣ�\n";
            for (int i = 0; i < len; ++i) {
                cout << i + 1 << ". " << table->segmentName[i] << " ";
            }
            cout << "\n�������޸��ֶεı��,����0����\n";

            /*��ȡ�û�����ı��*/
            struct Node *p = table->nodeHead;
            int count = 0;
            int nextcount = 0;
            int index;
            string indexRes;
            cin >> indexRes;
            int indexFlag = CorrectInt(indexRes);//�Ϸ��Լ���


            if (indexFlag) {//����������item
                index = String2Int(indexRes);
                if (index == 0) {
                    return;
                }
                if (0 < index && index <= len) {

                    int type = table->typeArray[index - 1];
                    int itemFlag = -1;

                    if (type == 0) {//����ֶ�������int

                        /*��ž����Ϸ��Լ���֮�󣬻�ȡ�û�������ֶ�����*/
                        cout << "��������ֶ��޸ĺ��ֵ\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectInt(itemRes);//���ݵĺϷ��Լ���

                        /*���ݾ����Ϸ��Լ���֮�󣬽����޸�*/
                        if (itemFlag == 1) {
                            int targetInt = String2Int(itemRes);
                            /*�������ݱ�*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->intArray[displayIndex[index - 1]] = targetInt;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }

                            //չʾ�޸Ľ��
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);

                        } else {
                            cout << "������������������\n";
                        }
                    }
                    if (type == 1) {//����ֶ�������double

                        /*��ž����Ϸ��Լ���֮�󣬻�ȡ�û�������ֶ�����*/
                        cout << "��������ֶ��޸ĺ��ֵ\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectDouble(itemRes);//���ݵĺϷ��Լ���

                        /*���ݾ����Ϸ��Լ���֮�󣬽����޸�*/
                        if (itemFlag == 1) {//���������Ѱ�ҷ���������ֵ
                            double targetDouble = String2Double(itemRes);
//                            cout << "$$$$$$$" << targetDouble << endl;
                            /*�������ݱ�*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->doubleArray[displayIndex[index - 1]] = targetDouble;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }
                            //չʾ�޸Ľ��
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);
                        } else {
                            cout << "������������������\n";
                        }
                    }
                    if (type == 2) {//����ֶ�������string

                        /*��ž����Ϸ��Լ���֮�󣬻�ȡ�û�������ֶ�����*/
                        cout << "��������ֶ��޸ĺ��ֵ\n";
                        string itemRes;
                        cin >> itemRes;
                        itemFlag = CorrectString(itemRes);//���ݵĺϷ��Լ���

                        /*���ݾ����Ϸ��Լ���֮�󣬽����޸�*/
                        if (itemFlag == 1) {//���������Ѱ�ҷ���������ֵ
                            string targetString = itemRes;
                            /*�������ݱ�*/
                            while (p != NULL && nextcount <= okNum) {
                                if (count == resIndex[nextcount]) {
                                    p->stringArray[displayIndex[index - 1]] = targetString;
                                    nextcount++;
                                }
                                p = p->next;
                                count++;
                            }
                            //չʾ�޸Ľ��
                            OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                                          table->segmentNum);
                        } else {
                            cout << "������������������\n";
                        }
                    }


                } else {
                    cout << "�������\n";
                }
            } else {
                cout << "�������\n";
            }

            /*ѯ���û��Ƿ�����޸ģ���ȡ�û���ѡ��*/
            cout << "�Ƿ�����޸����ݣ�����1���������������˳��޸�\n";
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
        /*�����޸ĺ�ı�*/
        StoreTable(table);
    }
}

void DeleteData(string tableName) {
    struct Table *table = ReadTable(tableName);
    while (1) {

        int *resIndex = InfoData(1, table);//�Ȳ�ѯ����
        if (resIndex == nullptr) {
            break;
        }

        /*�����ʾ����ȡ�û��Ƿ�ȷ��ɾ��*/
        cout << "�Ƿ�ȷ��ɾ���⼸�����ݣ�����1ȷ�ϣ���������ȡ��\n";
        string confirmString;
        cin >> confirmString;
        int confirmFlag = CorrectInt(confirmString);
        if (confirmFlag) {
            /*ͨ���Ϸ��Լ���֮�󣬱������ݱ�*/
            Node *trueHead = NULL;
            struct Node *p = new Node;
            p->next = table->nodeHead;
            struct Node *pNext = p->next;
            int count = 0;
            int nextCount = 0;
            int confirm = String2Int(confirmString);
            if (confirm == 1) {
                /*ִ��ɾ������*/
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
                /*չʾɾ��������*/
                OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray,
                              table->segmentNum);
                /*��������index*/
                int newIndex = 0;
                p = table->nodeHead;
                while (p != NULL) {
                    p->nodeIndex = newIndex++;
                    p = p->next;
                }
            }

        }

        /*ѯ���û��Ƿ����ɾ�����һ�ȡ�û�ָ��*/
        cout << "�Ƿ����ɾ�����ݣ�����1���������������˳�ɾ��\n";
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

    /*����ɾ����ı�*/
    StoreTable(table);
}

int *InfoData(int flag, struct Table *table) {
    string *infoSegmentName = table->segmentName;//�ֶ�������
    int *infoDisplayArray = table->displayArray;//���չʾ�ĸ��ֶεģ�ָ�룩����
    int len = 0;//�ֶ���
    len = table->segmentNum;//�����ʵ�ֶ���

    /*��¼�ֶ��ڶ�Ӧ���͵������е��±�*/
    int totalLength = table->segmentNum; // ȡ���ֶ��ܸ���
    int num_int = 0, num_double = 0, num_string = 0;//��intArray���±꣬��doubleArray�е��±꣬��stringArray���±�
    int *displayIndex = new int[totalLength]; // ��¼�ֶ��ڶ�Ӧ���͵������е��±������
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

    struct Node *p = table->nodeHead;//��ĵ�һ�����ݵ�ָ��
    struct Node *infoResultNode = nullptr;//��ѯ�����ͷָ��
    struct Node *nextInfoNode = nullptr;//��һ����ѯ�����ָ��

    int timesFlag = 0;//��¼�Ƿ��ǵ�һ�ν����ѯ��0�ǵ�һ�Σ�1����
    while (1) {
        if (timesFlag == 1) {//�����ǵ�һ�ν��룬pָ����ڲ�ѯ�����ͷָ��
            p = infoResultNode;
        }

        int index;//������еڼ������ݱ�

        /*�����ʾ��*/
        cout << "���������ֶΣ�\n";
        for (int i = 0; i < len; ++i) {
            cout << i + 1 << ". " << infoSegmentName[i] << " ";
        }
        cout << "\n������Լ�������ֶεı��,����0����\n";

        /*������*/
        string indexRes;
        cin >> indexRes;
        int indexFlag = CorrectInt(indexRes);//�жϺϷ��ԣ��Ƿ���int��

        if (indexFlag) {//����Ϸ�

            index = String2Int(indexRes);
            if (index == 0) {
                return 0;
            }
            if (0 < index && index <= len) {//�жϺϷ��ԣ���Χ�Ƿ�Ϸ���

                //����Ϸ�����ȡ�ֶε�ֵ
                cout << "������Լ��������ֵ\n";
                string itemRes;
                cin >> itemRes;
                int type = table->typeArray[index - 1];
                int itemFlag = -1;

                if (type == 0) {//����ֶ�������int
                    itemFlag = CorrectInt(itemRes);//�Ϸ����ж�

                    /*�����Ϸ����жϺ����������Ѱ�ҷ���������ֵ*/
                    if (itemFlag == 1) {
                        int targetInt = String2Int(itemRes);

                        /*�������ݱ�*/
                        while (p != NULL) {
                            int resInt = p->intArray[displayIndex[index - 1]];//��ȡĳһ�����ݵĶ�Ӧ�ֶε�ֵ
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
                        cout << "������������������\n";
                    }
                } else if (type == 1) {//����ֶ�������double
                    itemFlag = CorrectDouble(itemRes);//�Ϸ����ж�

                    /*�����Ϸ����жϺ����������Ѱ�ҷ���������ֵ*/
                    if (itemFlag == 1) {
                        double targetDouble = String2Double(itemRes);

                        /*�������ݱ�*/
                        while (p != NULL) {
                            int resDouble = p->doubleArray[displayIndex[index - 1]];//��ȡĳһ�����ݵĶ�Ӧ�ֶε�ֵ
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
                        cout << "������������������\n";
                    }
                } else {//����ֶ�������string
                    itemFlag = CorrectString(itemRes);//�Ϸ����ж�

                    /*�����Ϸ����жϺ����������Ѱ�ҷ���������ֵ*/
                    if (itemFlag == 1) {
                        string targetString = itemRes;

                        /*�������ݱ�*/
                        while (p != NULL) {
                            string resString = p->stringArray[displayIndex[index - 1]];//��ȡĳһ�����ݵĶ�Ӧ�ֶε�ֵ
                            if (resString == targetString) {
                                if (infoResultNode == nullptr) {
                                    nextInfoNode = p;
                                    infoResultNode = nextInfoNode;
                                } else {
                                    nextInfoNode->next_info = p;
                                    nextInfoNode = nextInfoNode->next_info;
                                }
                            }
                            if (timesFlag == 1) {//������ǵ�һ�ν��룬�����ķ�ʽͨ��������һ�β�ѯ�Ľ������
                                p = p->next_info;
                            } else {
                                p = p->next;//����ǵ�һ�ν��룬�����ķ�ʽͨ��������
                            }
                        }
                    } else {
                        cout << "������������������\n";
                    }
                }


            } else {
                cout << "�������\n";
            }
        } else {
            cout << "�������\n";
        }

        /*�����ʾ�ﲢ�һ�ȡ�û��Ƿ�������ң�����������ң��ͼ���ѭ��������������˾�break��*/
        if (infoResultNode == NULL) {
            cout << "û�з���Ҫ��Ĳ�ѯ���\n";
            return nullptr;
        } else {
            if (timesFlag == 0) {
                timesFlag = 1;
            }
            break;
        }

    }

    /*���ˣ�infoResultNode�Ѿ����Һ���*/

    /*��ÿһ�����ҽ�����±����indexArray������Ҫ����*/
    int nodeNum = 0;
    struct Node *p2;
    p2 = infoResultNode;
    while (p2 != NULL) {
        nodeNum++;
        p2 = p2->next_info;
    }
    int *indexArray = new int[nodeNum];//�洢��indexArray
    int nodeIndex = 0;//
    p2 = infoResultNode;
    while (p2 != NULL) {
        indexArray[nodeIndex] = p2->nodeIndex;
        nodeIndex++;
        p2 = p2->next_info;
    }

    int *showArray = new int[len];
    /*��������������õĲ�ѯ��������Ҫѡ��չʾ�ֶ�*/
    if (flag == 0) {
        int breakFlag = 0;
        while (1) {

            /*�����ʾ��*/
            cout << "��ѡ��Ҫչʾ���ֶ�\n";
            cout << "���������ֶΣ�\n";
            for (int i = 0; i < len; ++i) {
                cout << i + 1 << ". " << infoSegmentName[i] << " ";
            }
            cout << endl;
            /*����չʾ���ֶ��±�*/
            while (1) {
                cout << "������Լ�������ֶεı��,����0����������-1չʾȫ���ֶ�:";
                int showIndex;
                cin >> showIndex;
                if (showIndex == 0) {
                    breakFlag = 1;
                    break;
                } else if (showIndex < -1 || showIndex > len) {
                    cout << "�����������������\n";
                    break;
                } else if (showIndex == -1) {
//                    memset(showArray, 1, table->segmentNum);
                    for (int i = 0; i < table->segmentNum; ++i) {
                        showArray[i] = 1;
                    }
                    cout << "���ȫ���ֶ�:\n";
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
        /*ѡ�����ֶ�֮��չʾ����*/
        OutputDisplay2(table->segmentName, showArray, infoResultNode, table->typeArray, table->segmentNum);
        DeleteTable(table);
        /*���ز��ҽ�����±꼯��*/
        return indexArray;
    } else {
/*�����Ѿ����ҵ��Ľ������infoResultNode�ˣ����ڽ���չʾ*/
        OutputDisplay2(table
                               ->segmentName, table->displayArray, infoResultNode, table->typeArray,
                       table->segmentNum);//չʾ���ڵĲ�ѯ������û�
/*���ز��ҽ�����±꼯��*/
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


