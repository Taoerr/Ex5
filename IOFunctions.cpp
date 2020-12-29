//
// Created by BINOFL on 2020/12/9.
//

#include "IOFunctions.h"
#include "iostream"
#include <stdlib.h>
#include <string>
using namespace std;
#define MAX_SIZE 20000


// TODO: ���Ϸ��Ժ���
/**
* @Return: -1 --string������ 0 -- string��һ���س� 1 -- ������string
*/
int CorrectString(string s) {
    if (s[0] == '\0') { // ��������ֿ��ܣ�һ���ǻس���һ���ǳ�����
        char overSize[12] = "\0OVER_SIZE\0";
        for (int i = 0; i < 11; i++) {
            if (s[i] != overSize[i]) return 0; // string�ǻس�
        }
        return -1; // ����
    }
    return 1;
}

/**
* @Return:  0 -- ����һ��int 1 -- ������int
*/
int CorrectInt(string s) {
    if (!CorrectString(s)) return 0; // ��һ���Ϸ���string
    int num_cnt = 0; // Ҫ��֤�������һ������
    int left = s[0] == '-' ? 1 : 0;
    for (int i = left; i < MAX_SIZE; i++) {
        if (s[i] == '\0') break; // �ҵ���β
        if (s[i] < '0' || s[i] > '9') return 0;
        else num_cnt++;
    }
    if (num_cnt >= 1) return 1; // ���о�ͷ��string����������һ������
    return 0;
}

/**
* @Return:  0 -- ����һ��char 1 -- ������char
*/
int CorrectChar(string s) {
    if (!CorrectString(s)) return 0; // ��һ���Ϸ���string
    if (s[0] == '\0') return 0; // һ��Ҫ�У������
    if (s[1] == '\0' && s[0] != '\0') return 1;
    return 0;
}

/**
* @Return:  0 -- ����һ��double 1 -- ������double
*/
int CorrectDouble(string s) {
    if (!CorrectString(s)) return 0; // ��һ���Ϸ���string
    if (CorrectInt(s)) return 1; // �����������int, ��ôҲһ����������double
    int dot_cnt = 0, num_cnt = 0;
    int left = s[0] == '-' ? 1 : 0;
    for (int i = left; i < MAX_SIZE; i++) {
        if (s[i] == '\0') break; // �ҵ���ͷ��
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
            if (s[i] == '.') dot_cnt++;
            else num_cnt++;
            if (dot_cnt > 1) return 0; // ������һ�� .
        } else return 0;
    }

    if (dot_cnt == 1 && num_cnt >= 2) return 1;
    return 0;
}

// TODO: ת������

/**
* @Return:  ����int
*/
int String2Int(string s) {
    int value = 0;
    int index = s[0] == '-' ? 1 : 0;
    for (; s[index] >= '0' && s[index] <= '9'; index++) {
        value = value * 10 + s[index] - '0';
    }
    if(s[0] == '-') value = -value; // ����
    return value;
}

/**
* @Return:  ����char
*/
char String2Char(string s) {
    return s[0];
}

/**
* @Return:  ����double
*/
double String2Double(string s) {
    int intValue = 0;
    int index1 = s[0] == '-' ? 1 : 0;
    for (; index1 < MAX_SIZE && s[index1] != '.' && s[index1] != '\0'; ++index1) {
        intValue = intValue * 10 + s[index1] - '0'; // ������������
    }
//    printf("%d", s[index1]);
    double doubleValue = 0.0;
    if(s[index1] != '\0') { // ���û��С����
        int index2 = index1 + 1;
        for (; index2 < MAX_SIZE && s[index2] != '\0'; ++index2) {
            doubleValue = doubleValue * 10.0 + s[index2] - '0';
        }
        for (int i = 0; i < index2 - index1 - 1; ++i) {
            doubleValue /= 10.0;
        }
    }
    doubleValue += intValue;
    if(s[0] == '-') doubleValue = -doubleValue;
    return doubleValue;
}