//
// Created by BINOFL on 2020/12/9.
//

#include "IOFunctions.h"
#include "iostream"
#include <stdlib.h>
#include <string>
using namespace std;
#define MAX_SIZE 20000


// TODO: 检测合法性函数
/**
* @Return: -1 --string超长了 0 -- string是一个回车 1 -- 正常的string
*/
int CorrectString(string s) {
    if (s[0] == '\0') { // 这个有两种可能，一种是回车，一种是超长了
        char overSize[12] = "\0OVER_SIZE\0";
        for (int i = 0; i < 11; i++) {
            if (s[i] != overSize[i]) return 0; // string是回车
        }
        return -1; // 超长
    }
    return 1;
}

/**
* @Return:  0 -- 不是一个int 1 -- 正常的int
*/
int CorrectInt(string s) {
    if (!CorrectString(s)) return 0; // 是一个合法的string
    int num_cnt = 0; // 要保证起码得有一个数字
    int left = s[0] == '-' ? 1 : 0;
    for (int i = left; i < MAX_SIZE; i++) {
        if (s[i] == '\0') break; // 找到结尾
        if (s[i] < '0' || s[i] > '9') return 0;
        else num_cnt++;
    }
    if (num_cnt >= 1) return 1; // 是有尽头的string而且有至少一个数字
    return 0;
}

/**
* @Return:  0 -- 不是一个char 1 -- 正常的char
*/
int CorrectChar(string s) {
    if (!CorrectString(s)) return 0; // 是一个合法的string
    if (s[0] == '\0') return 0; // 一定要有，怕溢出
    if (s[1] == '\0' && s[0] != '\0') return 1;
    return 0;
}

/**
* @Return:  0 -- 不是一个double 1 -- 正常的double
*/
int CorrectDouble(string s) {
    if (!CorrectString(s)) return 0; // 是一个合法的string
    if (CorrectInt(s)) return 1; // 如果是正常的int, 那么也一定是正常的double
    int dot_cnt = 0, num_cnt = 0;
    int left = s[0] == '-' ? 1 : 0;
    for (int i = left; i < MAX_SIZE; i++) {
        if (s[i] == '\0') break; // 找到尽头了
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
            if (s[i] == '.') dot_cnt++;
            else num_cnt++;
            if (dot_cnt > 1) return 0; // 超过了一个 .
        } else return 0;
    }

    if (dot_cnt == 1 && num_cnt >= 2) return 1;
    return 0;
}

// TODO: 转换参数

/**
* @Return:  返回int
*/
int String2Int(string s) {
    int value = 0;
    int index = s[0] == '-' ? 1 : 0;
    for (; s[index] >= '0' && s[index] <= '9'; index++) {
        value = value * 10 + s[index] - '0';
    }
    if(s[0] == '-') value = -value; // 负数
    return value;
}

/**
* @Return:  返回char
*/
char String2Char(string s) {
    return s[0];
}

/**
* @Return:  返回double
*/
double String2Double(string s) {
    int intValue = 0;
    int index1 = s[0] == '-' ? 1 : 0;
    for (; index1 < MAX_SIZE && s[index1] != '.' && s[index1] != '\0'; ++index1) {
        intValue = intValue * 10 + s[index1] - '0'; // 处理整数部分
    }
//    printf("%d", s[index1]);
    double doubleValue = 0.0;
    if(s[index1] != '\0') { // 如果没有小数点
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