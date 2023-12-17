#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// � ������� ���������� ������ ��� �������� ����� � ������� �����, ������� �������� �������, ���������, ����������� � ���������� ������.
int* GenerateNumbers(int* num, int after_div, int before_div, int before_mul, int after_mul, int left_num) {
    num[after_div] = 2 + rand() % (10 - 2 + 1); //��������
    num[before_div] = num[after_div] * (2 + rand() % (10 - 2 + 1)); //�������
    num[before_mul] = 2 + rand() % (9 - 2 + 1); //����������� ���������
    num[after_mul] = 11 + rand() % (99 - 11 + 1); // ���������� ���������
    num[left_num] = rand() % 100; // ���������� ����� 
    return num;
}
void ShowExample_Case0(int* num, int lv) {// ����� � ������� ������� ��������� case 0.
    if ((lv == 3) || (lv == 4))
        cout << num[0] << " : " << num[1] << " + " << num[2] << " * " << num[3] << " - " << num[4] << " = ";
    else if (lv == 2)
        cout << num[0] << " : " << num[1] << " + " << num[2] << " * " << num[3] << " = ";
    else if (lv == 1)
        cout << num[0] << " : " << num[1] << " + " << num[2] << " = ";
    else if (lv == 0)
        cout << num[0] << " - " << num[1] << " + " << num[2] << " = ";
}
void ShowExample_Case1(int* num, int lv) {// ����� � ������� ������� ��������� case 1.
    if ((lv == 3) || (lv == 4))
        cout << num[0] << " * " << num[1] << " - " << num[2] << " : " << num[3] << " + " << num[4] << " = ";
    else if (lv == 2)
        cout << num[0] << " * " << num[1] << " - " << num[2] << " : " << num[3] << " = ";
    else if (lv == 1)
        cout << num[0] << " * " << num[1] << " - " << num[2] << " = ";
    else if (lv == 0)
        cout << num[0] << " + " << num[1] << " - " << num[2] << " = ";
}
void ShowExample_Case2(int* num, int lv) {// ����� � ������� ������� ��������� case 2.
    if ((lv == 3) || (lv == 4))
        cout << num[0] << " - " << num[1] << " : " << num[2] << " + " << num[3] << " * " << num[4] << " = ";
    else if (lv == 2)
        cout << num[0] << " - " << num[1] << " : " << num[2] << " + " << num[3] << " = ";
    else if (lv == 1)
        cout << num[0] << " - " << num[1] << " : " << num[2] << " = ";
    else if (lv == 0)
        cout << num[0] << " + " << num[1] << " - " << num[2] << " = ";
}
void ShowExample_Case3(int* num, int lv) {// ����� � ������� ������� ��������� case 3.
    if ((lv == 3) || (lv == 4))
        cout << num[0] << " + " << num[1] << " * " << num[2] << " - " << num[3] << " : " << num[4] << " = ";
    else if (lv == 2)
        cout << num[0] << " + " << num[1] << " * " << num[2] << " - " << num[3] << " = ";
    else if (lv == 1)
        cout << num[0] << " + " << num[1] << " * " << num[2] << " = ";
    else if (lv == 0)
        cout << num[3] << " - " << num[4] << " + " << num[2] << " = ";
}
void ShowExample(int* num, int random_operations, int lv) {
    if (random_operations == 0)
        ShowExample_Case0(num, lv);
    else if (random_operations == 1)
        ShowExample_Case1(num, lv);
    else if (random_operations == 2)
        ShowExample_Case2(num, lv);
    else
        ShowExample_Case3(num, lv);
}
void CalculateResult_Case0(int* num, int& result, int lv) { // ������� ������� ��������� case 0.
    if ((lv == 3) || (lv == 4))
        result = num[0] / num[1] + num[2] * num[3] - num[4];
    else if (lv == 2)
        result = num[0] / num[1] + num[2] * num[3];
    else if (lv == 1)
        result = num[0] / num[1] + num[2];
    else if (lv == 0)
        result = num[0] - num[1] + num[2];
}
void CalculateResult_Case1(int* num, int& result, int lv) { // ������� ������� ��������� case 1.
    if ((lv == 3) || (lv == 4))
        result = num[0] * num[1] - num[2] / num[3] + num[4];
    else if (lv == 2)
        result = num[0] * num[1] - num[2] / num[3];
    else if (lv == 1)
        result = num[0] * num[1] - num[2];
    else if (lv == 0)
        result = num[0] + num[1] - num[2];
}
void CalculateResult_Case2(int* num, int& result, int lv) { // ������� ������� ��������� case 2.
    if ((lv == 3) || (lv == 4))
        result = num[0] - num[1] / num[2] + num[3] * num[4];
    else if (lv == 2)
        result = num[0] - num[1] / num[2] + num[3];
    else if (lv == 1)
        result = num[0] - num[1] / num[2];
    else if (lv == 0)
        result = num[0] + num[1] - num[2];
}
void CalculateResult_Case3(int* num, int& result, int lv) { // ������� ������� ��������� case 3.
    if ((lv == 3) || (lv == 4))
        result = num[0] + num[1] * num[2] - num[3] / num[4];
    else if (lv == 2)
        result = num[0] + num[1] * num[2] - num[3];
    else if (lv == 1)
        result = num[0] + num[1] * num[2];
    else if (lv == 0)
        result = num[3] - num[4] + num[2];
}

void GenerateExample(int* num, int& result, int lv) {
    int random_operations; // ���������� ��� ������� ��������� (case) �������.
    bool check = 1;

    while (check == 1) {
        random_operations = rand() % 4; // ������ ������ ��������� �������
        switch (random_operations) { //������� ������� � ����������� �� ���������
        case 0:
            num = GenerateNumbers(num, 1, 0, 2, 3, 4);
            CalculateResult_Case0(num, result, lv);
            break;
        case 1:
            num = GenerateNumbers(num, 3, 2, 0, 1, 4);
            CalculateResult_Case1(num, result, lv);
            break;
        case 2:
            num = GenerateNumbers(num, 2, 1, 3, 4, 0);
            CalculateResult_Case2(num, result, lv);
            break;
        case 3:
            num = GenerateNumbers(num, 4, 3, 1, 2, 0);
            CalculateResult_Case3(num, result, lv);
            break;
        }
        if (result >= 0) // ��������, ����� ��������� �� ��� �������������
            check = 0;
    }
    //cout << result << endl; // ���-��� ��� ������������ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ShowExample(num, random_operations, lv);
}
