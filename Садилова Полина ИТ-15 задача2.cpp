#include "header.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    setlocale(LC_ALL, ("ru"));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Добро пожаловать в игру 'Цепочка слов'!" << endl;
    cout << "Правила игры: очередное слово должно заканчиваться той буквой,";
    cout << "на которую закончилось предыдущее\n";
    cout << "Введите слова, которые использовались в этой игре (через пробел): ";

    string input;
    getline(cin, input);

    // Сохраняем введённые слова в файл
    saveToFile("a.txt", input);

    try {
        vector<string> wordList = split(input);
        ListChain chain(wordList);

        if (chain.buildChain()) {
            cout << "Цепочка слов построена успешно!\n";
            chain.saveResult("b.txt");
            cout << "Результат сохранён в b.txt\n";
            cout << "\n ^~^  ,\n('Y') )\n/   \\/ \n(\\|||/)";
        }
        else {
            cout << "Не удалось построить цепочку.\n";
            ofstream outFile("b.txt");
            outFile << "Не удалось построить цепочку из введённых слов.\n";
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}