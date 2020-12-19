#include<iostream>
#include "TableFunctions.h"
#include "IOFunctions.h"
#include <string>
using namespace std;

// TODO: 如何使用string函数：https://blog.csdn.net/fybon/article/details/52995358

int main() {
    int flag1 = 1;
    // flag1是设置外层循环的bool，一直是true
    // flag2是设置内层循环的bool
    cout << "欢迎使用数据管理软件！\n";
    DisplayTables();
    while (flag1) {
        // TODO: 进行第一次选择
        cout << "输入 0 : 终止程序\n"
             << "输入 1 : 创建数据表\n"
             << "输入 2 : 删除数据表\n"
             << "输入 3 : 修改数据表\n"
             << "输入 4 : 查看某张数据表\n"
             << "输入 5 : 修改数据表内容\n"
             << "请输入需要进行哪种操作：";
        int num1 = -1;
        cin >> num1;
        while (num1 < 0 || num1 > 5) {
            cout << "输入不正确，请重新选择：";
            cin >> num1;
        }
        string tableName = "";
        // TODO: 进行第一次num的判断
        if (num1 == 0)// 直接终止程序：
            return 0;
        else if (num1 == 1) // 添加数据表
            CreateTable();
        else if (num1 == 3) {
            while (1){
                cout << "请输入需要进行哪种操作：\n"
                     << "输入 0 : 修改表名\n"
                     << "输入 1 : 修改字段名\n"
                     << "输入 2 : 返回上一级\n";
                int num = -1;
                cin >> num;
                while (num < 0 || num > 2) {
                    cout << "输入不正确，请重新选择：";
                    cin >> num;
                }

                if (num != 2){
                    ChangeTable(num);
                }
                else{
                    break;
                }
            }
        }
        else {
            cout << "请输入表名称：";
            cin >> tableName;
            while (!CorrectString(tableName)) { // 检查string合法性
                cout << "请重新输入表名称：";
                cin >> tableName;
            }
            if (num1 == 2) DeleteTable(tableName); // 删除数据表
            if (num1 == 4) {
                // 查看整张数据表
                struct Table *table = ReadTable(tableName);
                if (table != NULL) {
                    cout << "读取表完毕，表内容如下\n";
                    for (int i = 0; i < table->segmentNum; ++i) {
//                        cout << "+++++++" << table->segmentName[i] << "++++++\n";
                    }
                    OutputDisplay(table->segmentName, table->displayArray,
                                  table->nodeHead, table->typeArray, table->segmentNum);
                }
            }
            if (num1 == 5) {
                // 修改数据表
                // TODO: 进行第二次选择：
                int num2 = -1;
                struct Table *table = ReadTable(tableName);
                if (table != NULL) {
                    cout << "您选择的表是：" << tableName << "，表的内容如下:" << endl;
                    OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray, table->segmentNum);
                    DeleteTable(table);
                    cout << " 请输入需要进行哪种操作：\n"
                         << "输入 0 : 返回到上一级操作\n"
                         << "输入 1 : 增加一行数据\n"
                         << "输入 2 : 删除一行数据\n"
                         << "输入 3 : 查找指定数据\n"
                         << "输入 4 : 修改指定数据\n";
                    cin >> num2;
                    while (num2 < 0 || num2 > 4) {
                        cout << "输入不正确，请重新选择：";
                        cin >> num2;
                    }
                    // TODO: 进行num2的判断：
                    if (num2 == 1) InsertData(tableName);// 增加一行数据
                    else if (num2 == 2) DeleteData(tableName);// 删除一行数据
                    else if (num2 == 3) { // 查找一行数据
                        struct Table *table = ReadTable(tableName);
                        InfoData(0, table);
                    } else if (num2 == 4) EditData(tableName); // 修改数据
                }
                else {
                    cout << "您想要操作的表不存在，请重新输入。" << endl;
                }
            }// num1 = 5
        }// 输入表名
    }// 外层循环
}

