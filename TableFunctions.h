//
// Created by BINOFL on 2020/12/5.
//

#ifndef DATABASE_TABLEFUNCTIONS_H
#define DATABASE_TABLEFUNCTIONS_H

#endif //DATABASE_TABLEFUNCTIONS_H
#include <string>
using namespace std;

typedef struct Node {
    int num_int, num_double, num_string;
    int nodeIndex;
    int* intArray;
    double* doubleArray;
    string* stringArray;
    struct Node* next;
    struct Node* next_info;//用于指向下一个查询结果的指针
} DataRow;

struct Table{
    string tableName; //表的名字
    int segmentNum; // 字段个数

    string *segmentType; // 字段类型
    int* typeArray;  // (int: 0, double: 1, string: 2)
    string *segmentName; // 字段名字
    struct Node *nodeHead;  // 数据头节点
    int* displayArray; // 展示的字段筛选（0标识不展示，1表示展示）
};

// TODO: 非模块函数
//static int CorrectString(string s);

// TODO: 输入输出模块

 void OutputDisplay(string* segmentName,
                          int* display,
                          struct Node* dataHead,
                          int* typeArray,
                          int totalLength);

 void OutputDisplay2(string* segmentName,
                          int* display,
                          struct Node* dataHead,
                          int* typeArray,
                          int totalLength);

// TODO: 表模块
 int DisplayTables();

 struct Table* ReadTable(string tableName);

 int StoreTable(struct Table* table);

 int CreateTable();

 int ChangeTable(int num);


 int DeleteTable(string tableName);

// TODO: 数据模块

 void InsertData(string tableName);

 void EditData(string tableName);

 void DeleteData(string tableName);

 int * InfoData(int flag, struct Table* table);

 void DeleteNode(Node* node);

 void DeleteTable(Table* table);