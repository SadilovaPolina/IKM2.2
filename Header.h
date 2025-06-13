#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

// Узел односвязного списка
class ListNode {
public:
    string word; // Слово, хранящееся в узле
    ListNode* next;
    ListNode(const string& w); // Конструктор, принимающий слово
};

// Класс для построения цепочки слов
class ListChain {
private:
    vector<string> words; // Вектор всех слов для построения цепочки
    vector<bool> used;
    ListNode* head;
    ListNode* tail;

    char getLastChar(const string& word);  // Получить последний символ слова
    bool findChain(int step);               // Рекурсивный метод для поиска цепочки
    void clearList();                       // Очистка связного списка

public:
    ListChain(const vector<string>& wordList); // Конструктор, принимающий список слов для построения цепочки
    ~ListChain();
    bool buildChain(); // Построение цепочки слов
    void saveResult(const string& filename); // Сохрание результата в файл
    ListNode* getChain() const;
};

vector<string> split(const string& input); // Разделение строки на слова
void saveToFile(const string& filename, const string& input); // Сохрание строки в файл
