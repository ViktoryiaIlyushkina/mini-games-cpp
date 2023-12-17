#pragma once
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;

struct player {
    string Name;
    int score;

    friend ostream& operator << (ostream&, const player&);
    friend ofstream& operator << (ofstream&, const player&);
    friend ifstream& operator >> (ifstream&, player&);
};
void HighlightCell(char** BigMap, int x, int y, char symb) {

    for (int i = x; i < (x + 3); i++)
        for (int j = y; j < (y + 3); j++) {
            BigMap[i][j] = symb;
        }
}
void HighlightCell_1(string** BigMap, int x, int y, char symb) {

    for (int i = (x-1); i < x; i++)
        for (int j = (y-1); j < (y + 2); j++) {
            BigMap[i][j] = symb;
        }
    for (int i = (x + 1); i < (x + 2); i++)
        for (int j = (y - 1); j < (y + 2); j++) {
            BigMap[i][j] = symb;
        }
}
string EnterName(string name) {
    cout << "\nEnter Player Name: ";
    cin >> name;

    return name;
}
int Up_moving(int**& SmallMap, int string_index, int column_index, int MoveTo, int MoveFrom) {
    SmallMap[string_index][column_index] = MoveFrom;
    int ex_number = SmallMap[string_index - 1][column_index];
    SmallMap[string_index - 1][column_index] = MoveTo;

    return ex_number;
}
int Down_moving(int**& SmallMap, int string_index, int column_index, int MoveTo, int MoveFrom) {
    SmallMap[string_index][column_index] = MoveFrom;
    int ex_number = SmallMap[string_index + 1][column_index];
    SmallMap[string_index + 1][column_index] = MoveTo;

    return ex_number;
}
int Right_moving(int**& SmallMap, int string_index, int column_index, int MoveTo, int MoveFrom) {
    SmallMap[string_index][column_index] = MoveFrom;
    int ex_number = SmallMap[string_index][column_index + 1];
    SmallMap[string_index][column_index + 1] = MoveTo;

    return ex_number;
}
int Left_moving(int**& SmallMap, int string_index, int column_index, int MoveTo, int MoveFrom) {
    SmallMap[string_index][column_index] = MoveFrom;
    int ex_number = SmallMap[string_index][column_index - 1];
    SmallMap[string_index][column_index - 1] = MoveTo;

    return ex_number;
}
ostream& operator << (ostream& out, const player& player) {

    out << player.Name;

    int spaces = 30 - player.Name.length();
    for (int i = 0; i < spaces; i++)
        cout << ' ';

    out << player.score << endl;

    return out;
}
ifstream& operator >> (ifstream& in, player& player) {

    in >> player.Name;
    in >> player.score;

    in.ignore();

    return in;
}
ofstream& operator << (ofstream& out, player& player) {

    out << player.Name << endl;
    out << player.score << endl;


    return out;
}
void Get_Rank(player* rank, int rank_places, ifstream& in) {

    for (int i = 0; i < rank_places; i++)
        rank[i].score = 0;

    for (int i = 0; i < rank_places; i++)
        in >> rank[i];

    in.close();
}

void Update_Rank(player*& rank, player*& rank_New, player current, int rank_places, bool insert) {

    for (int i = 0, j = 0; i < rank_places; i++, j++) {
        // в обновленный массив рейтинга заносятся записи игроков с рейтингом больше, чем у текущего игрока
        if ((rank[i].score != 0) && (rank[j].score > current.score))
            rank_New[i] = rank[j];
        // в обновленный массив рейтинга заносится текуший игрок, если записей игроков с большим рейтингом больше нет
        else if ((rank[j].score != 0) && (rank[j].score <= current.score) && (insert == 1)) {
            rank_New[i] = current;
            j--;
            insert = 0;
        }
        // в обновленный массив рейтинга заносятся записи игроков с рейтингом меньше, чем у текущего игрока
        else if ((rank[j].score != 0) && (rank[j].score <= current.score) && (insert == 0))
            rank_New[i] = rank[j];
        // в обновленный массив рейтинга заносится текуший игрок, если еще не был занесен
        else if ((rank[j].score == 0) && (insert == 1)) {
            rank_New[i] = current;
            insert = 0;
        }
        // в обновленный массив рейтинга заносятся нули, если записей больше нет
        else if (rank[j].score == 0)
            rank_New[i].score = 0;
    }
    delete[] rank;
}

void Show_Rank(player* rank_New, int rank_places) {

    cout << "\t Wall of glory" << endl << endl;

    for (int i = 0; i < rank_places; i++)
        if (rank_New[i].score != 0)
            cout << rank_New[i] << endl;
}
void Save_Rank(player*& rank_New, int rank_places, ofstream& outfile) {

    for (int i = 0; i < rank_places; i++)
        outfile << rank_New[i];

    outfile.close();
    delete[] rank_New;
}
int UserChoose_range(int Choise, int range_start, int range_end) {
    bool Check_gamechoise = 1;
    while (Check_gamechoise) {
        cin >> Choise;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }

        if (Choise >= range_start || Choise <= range_end)
            Check_gamechoise = 0;

        cout << "\x1B[2J\x1B[H";
    }
    return Choise;
}
int Enter_UserResult(int& user_res) {
    bool checkRes = 1;
    while (checkRes) {
        cin >> user_res;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }

        if (user_res >= 0 && user_res < 1000000)
            checkRes = 0;
    }
    return user_res;
}
void UserChoose_continue(bool& play) {
    int play1 = 3;
    bool Check_play = 1;
    while (Check_play) {
        cout << "Want to continue? \n 0. No \n 1. Yes." << endl << endl;
        cin >> play1;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }

        if ((play1 == 0) || (play1 == 1)) {
            play = play1;
            Check_play = 0;
        }
    }
    cout << "\x1B[2J\x1B[H";
}

