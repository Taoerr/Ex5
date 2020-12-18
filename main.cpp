#include<iostream>
#include "TableFunctions.h"
#include "IOFunctions.h"
#include <string>
using namespace std;

// TODO: ���ʹ��string������https://blog.csdn.net/fybon/article/details/52995358

int main() {
    int flag1 = 1;
    // flag1���������ѭ����bool��һֱ��true
    // flag2�������ڲ�ѭ����bool
    cout << "��ӭʹ�����ݹ��������\n";
    DisplayTables();
    while (flag1) {
        // TODO: ���е�һ��ѡ��
        cout << "���� 0 : ��ֹ����\n"
             << "���� 1 : �������ݱ�\n"
             << "���� 2 : ɾ�����ݱ�\n"
             << "���� 3 : �޸����ݱ�\n"
             << "���� 4 : �鿴ĳ�����ݱ�\n"
             << "���� 5 : �޸����ݱ�����\n"
             << "��������Ҫ�������ֲ�����";
        int num1 = -1;
        cin >> num1;
        while (num1 < 0 || num1 > 5) {
            cout << "���벻��ȷ��������ѡ��";
            cin >> num1;
        }
        string tableName = "";
        // TODO: ���е�һ��num���ж�
        if (num1 == 0)// ֱ����ֹ����
            return 0;
        else if (num1 == 1) // ������ݱ�
            CreateTable();
        else if (num1 == 3) {
            while (1){
                cout << "��������Ҫ�������ֲ�����\n"
                     << "���� 0 : �޸ı���\n"
                     << "���� 1 : �޸��ֶ���\n"
                     << "���� 2 : ������һ��\n";
                int num = -1;
                cin >> num;
                while (num < 0 || num > 2) {
                    cout << "���벻��ȷ��������ѡ��";
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
            cout << "����������ƣ�";
            cin >> tableName;
            while (!CorrectString(tableName)) { // ���string�Ϸ���
                cout << "��������������ƣ�";
                cin >> tableName;
            }
            if (num1 == 2) DeleteTable(tableName); // ɾ�����ݱ�
            if (num1 == 4) {
                // �鿴�������ݱ�
                struct Table *table = ReadTable(tableName);
                if (table != NULL) {
                    cout << "��ȡ����ϣ�����������\n";
                    for (int i = 0; i < table->segmentNum; ++i) {
//                        cout << "+++++++" << table->segmentName[i] << "++++++\n";
                    }
                    OutputDisplay(table->segmentName, table->displayArray,
                                  table->nodeHead, table->typeArray, table->segmentNum);
                }
            }
            if (num1 == 5) {
                // �޸����ݱ�
                // TODO: ���еڶ���ѡ��
                int num2 = -1;
                struct Table *table = ReadTable(tableName);
                if (table != NULL) {
                    cout << "��ѡ��ı��ǣ�" << tableName << "�������������:" << endl;
                    OutputDisplay(table->segmentName, table->displayArray, table->nodeHead, table->typeArray, table->segmentNum);
                    DeleteTable(table);
                    cout << " ��������Ҫ�������ֲ�����\n"
                         << "���� 0 : ���ص���һ������\n"
                         << "���� 1 : ����һ������\n"
                         << "���� 2 : ɾ��һ������\n"
                         << "���� 3 : ����ָ������\n"
                         << "���� 4 : �޸�ָ������\n";
                    cin >> num2;
                    while (num2 < 0 || num2 > 4) {
                        cout << "���벻��ȷ��������ѡ��";
                        cin >> num2;
                    }
                    // TODO: ����num2���жϣ�
                    if (num2 == 1) InsertData(tableName);// ����һ������
                    else if (num2 == 2) DeleteData(tableName);// ɾ��һ������
                    else if (num2 == 3) { // ����һ������
                        struct Table *table = ReadTable(tableName);
                        InfoData(0, table);
                    } else if (num2 == 4) EditData(tableName); // �޸�����
                }
                else {
                    cout << "����Ҫ�����ı����ڣ����������롣" << endl;
                }
            }// num1 = 5
        }// �������
    }// ���ѭ��
}

