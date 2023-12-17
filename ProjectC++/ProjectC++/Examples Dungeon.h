#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;

int* GenerateNum(int* numbers) { // в функцию передается массив для хранения чисел.
    numbers[0] = 2 + rand() % (4 - 2 + 1); //делитель однозначный для 2 уровня
    numbers[1] = numbers[0] * (2 + rand() % ((6 - numbers[0]) - 2 + 1)); //делимое однозначное для 2 уровня
    numbers[2] = 2 + rand() % (10 - 2 + 1); //делитель однозначный для 4 уровня
    numbers[3] = numbers[2] * (2 + rand() % (10 - 2 + 1)); //делимое двухзначное для 4 уровня
    numbers[4] = 11 + rand() % (100 - 11 + 1); //делитель двузначный для 6 уровня
    numbers[5] = numbers[4] * (2 + rand() % (10 - 2 + 1)); //делимое трехзначное для 6 уровня
    numbers[6] = 2 + rand() % (9 - 2 + 1); //однозначное число
    numbers[7] = 11 + rand() % (99 - 11 + 1); // двузначное число
    numbers[8] = 100 + rand() % (999 - 100 + 1); // трехзначное число 

    return numbers;
}
void ShowEx_Case0(int* numbers, int lv) {// вывод в консоль примера структуры case 0.
    if (lv == 1)
        cout << numbers[1] << " + " << numbers[6] << " = ";
    else if (lv == 2)
        cout << numbers[1] << " * " << numbers[6] << " = ";
    else if (lv == 3)
        cout << numbers[3] << " + " << numbers[7] << " = ";
    else if (lv == 4)
        cout << numbers[3] << " * " << numbers[7] << " = ";
    else if (lv == 5)
        cout << numbers[5] << " + " << numbers[8] << " = ";
    else if (lv == 6)
        cout << numbers[5] << " * " << numbers[8] << " = ";
}
void ShowEx_Case1(int* numbers, int lv) {// вывод в консоль примера структуры case 1.
    if (lv == 1)
        cout << numbers[1] << " - " << numbers[6] << " = ";
    else if (lv == 2)
        cout << numbers[1] << " : " << numbers[0] << " = ";
    else if (lv == 3)
        cout << numbers[3] << " - " << numbers[7] << " = ";
    else if (lv == 4)
        cout << numbers[3] << " : " << numbers[2] << " = ";
    else if (lv == 5)
        cout << numbers[5] << " - " << numbers[8] << " = ";
    else if (lv == 6)
        cout << numbers[5] << " : " << numbers[4] << " = ";
}
void ShowEx_Case2(int* numbers, int lv) {// вывод в консоль примера структуры case 2.
    if (lv == 7)
        cout << numbers[7] << " + " << numbers[1] << " : " << numbers[0] << " = ";
    else if (lv == 8)
        cout << numbers[8] << " + " << numbers[3] << " : " << numbers[2] << " = ";
}
void ShowEx_Case3(int* numbers, int lv) {// вывод в консоль примера структуры case 3.
    if (lv == 7)
        cout << numbers[7] << " + " << numbers[1] << " * " << numbers[0] << " = ";
    else if (lv == 8)
        cout << numbers[8] << " + " << numbers[3] << " * " << numbers[2] << " = ";
}
void ShowEx_Case4(int* numbers, int lv) {// вывод в консоль примера структуры case 4.
    if (lv == 7)
        cout << numbers[7] << " - " << numbers[1] << " : " << numbers[0] << " = ";
    else if (lv == 8)
        cout << numbers[8] << " - " << numbers[3] << " : " << numbers[2] << " = ";
}
void ShowEx_Case5(int* numbers, int lv) {// вывод в консоль примера структуры case 5.
    if (lv == 7)
        cout << numbers[7] << " - " << numbers[1] << " * " << numbers[0] << " = ";
    else if (lv == 8)
        cout << numbers[8] << " - " << numbers[3] << " * " << numbers[2] << " = ";
}
void ShowEx_Lv_1to6(int* num, int random_operations, int lv) {
    if (random_operations == 0)
        ShowEx_Case0(num, lv);
    else if (random_operations == 1)
        ShowEx_Case1(num, lv);
}
void ShowEx_Lv_7to8(int* num, int random_operations, int lv) {
    if (random_operations == 2)
        ShowEx_Case2(num, lv);
    else if (random_operations == 3)
        ShowEx_Case3(num, lv);
    else if (random_operations == 4)
        ShowEx_Case4(num, lv);
    else if (random_operations == 5)
        ShowEx_Case5(num, lv);
}
void CalcResult_Case0(int* numbers, int& result, int lv) { // решение примера структуры case 0.
    if (lv == 1)
        result = numbers[1] + numbers[6];
    else if (lv == 2)
        result = numbers[1] * numbers[6];
    else if (lv == 3)
        result = numbers[3] + numbers[7];
    else if (lv == 4)
        result = numbers[3] * numbers[7];
    else if (lv == 5)
        result = numbers[5] + numbers[8];
    else if (lv == 6)
        result = numbers[5] * numbers[8];
}
void CalcResult_Case1(int* numbers, int& result, int lv) { // решение примера структуры case 1.
    if (lv == 1)
        result = numbers[1] - numbers[6];
    else if (lv == 2)
        result = numbers[1] / numbers[0];
    else if (lv == 3)
        result = numbers[3] - numbers[7];
    else if (lv == 4)
        result = numbers[3] / numbers[2];
    else if (lv == 5)
        result = numbers[5] - numbers[8];
    else if (lv == 6)
        result = numbers[5] / numbers[4];
}
void CalcResult_Case2(int* numbers, int& result, int lv) { // решение примера структуры case 2.
    if (lv == 7)
        result = numbers[7] + numbers[1] / numbers[0];
    else if (lv == 8)
        result = numbers[8] + numbers[3] / numbers[2];
}
void CalcResult_Case3(int* numbers, int& result, int lv) { // решение примера структуры case 3.
    if (lv == 7)
        result = numbers[7] + numbers[1] * numbers[0];
    else if (lv == 8)
        result = numbers[8] + numbers[3] * numbers[2];
}
void CalcResult_Case4(int* numbers, int& result, int lv) { // решение примера структуры case 4.
    if (lv == 7)
        result = numbers[7] - numbers[1] / numbers[0];
    else if (lv == 8)
        result = numbers[8] - numbers[3] / numbers[2];
}
void CalcResult_Case5(int* numbers, int& result, int lv) { // решение примера структуры case 5.
    if (lv == 7)
        result = numbers[7] - numbers[1] * numbers[0];
    else if (lv == 8)
        result = numbers[8] - numbers[3] * numbers[2];
}
void Generate_Example_Lv_1to6(int* num, int& result, int lv) {
    int random_operations; 
    bool check = 1;

    while (check == 1) {
        random_operations = rand() % 2; // рандом номера структуры примера
        switch (random_operations) { //решение примера в зависимости от структуры
        case 0:
            num = GenerateNum(num);
            CalcResult_Case0(num, result, lv);
            break;
        case 1:
            num = GenerateNum(num);
            CalcResult_Case1(num, result, lv);
            break;
      
        }
        if (result >= 0) // Проверка, чтобы результат не был отрицательным
            check = 0;
    }
    //cout << result << endl; // чит-код для тестирования !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ShowEx_Lv_1to6(num, random_operations, lv);
}
void Generate_Example_Lv_7to8(int* num, int& result, int lv) {
    int random_operations; 
    bool check = 1;

    while (check == 1) {
        random_operations = 2 + rand() % (5 - 2 + 1); // рандом номера структуры примера
        switch (random_operations) { //решение примера в зависимости от структуры
        case 2:
            num = GenerateNum(num);
            CalcResult_Case2(num, result, lv);
            break;
        case 3:
            num = GenerateNum(num);
            CalcResult_Case3(num, result, lv);
            break;
        case 4:
            num = GenerateNum(num);
            CalcResult_Case4(num, result, lv);
            break;
        case 5:
            num = GenerateNum(num);
            CalcResult_Case5(num, result, lv);
            break;
        }
        if (result >= 0) // Проверка, чтобы результат не был отрицательным
            check = 0;
    }
    //cout << result << endl; // чит-код для тестирования !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ShowEx_Lv_7to8(num, random_operations, lv);
}
