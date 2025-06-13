#include "header.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ListNode::ListNode(const string& w) : word(w), next(nullptr) {}

ListChain::ListChain(const vector<string>& wordList)
    : words(wordList), head(nullptr), tail(nullptr) {
    if (wordList.empty()) {
        throw invalid_argument("Ошибка: пустой список слов");
    }
    used.resize(words.size(), false);
}

ListChain::~ListChain() {
    clearList();
}

void ListChain::clearList() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

char ListChain::getLastChar(const string& word) {
    if (word.empty()) {
        throw runtime_error("Ошибка: пустое слово");
    }

    char last = word.back();
    if (last == 'ь' && word.length() > 1) {
        return word[word.length() - 2];
    }
    return last;
}

bool ListChain::findChain(int step) {
    if (step == words.size()) {
        return (head && tail) && (getLastChar(tail->word) == head->word[0]);
    }

    char neededChar = (step == 0) ? '\0' : getLastChar(tail->word);

    for (size_t i = 0; i < words.size(); ++i) {
        if (!used[i] && (step == 0 || words[i][0] == neededChar)) {
            used[i] = true;
            ListNode* newNode = new ListNode(words[i]);

            if (!head) head = tail = newNode;
            else {
                tail->next = newNode;
                tail = newNode;
            }

            if (findChain(step + 1)) return true;

            // Backtrack
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                ListNode* prev = head;
                while (prev->next != tail) prev = prev->next;
                delete tail;
                tail = prev;
                tail->next = nullptr;
            }
            used[i] = false;
        }
    }
    return false;
}

bool ListChain::buildChain() {
    clearList();
    return findChain(0);
}

void ListChain::saveResult(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл " + filename);
    }

    ListNode* current = head;
    while (current) {
        outFile << current->word;
        if (current->next) outFile << " ";
        current = current->next;
    }
    outFile << "\n ^~^  ,\n('Y') )\n/   \\/ \n(\\|||/)";
}

ListNode* ListChain::getChain() const {
    return head;
}

vector<string> split(const string& input) {
    vector<string> words;
    string word;
    for (char ch : input) {
        if (isspace(ch)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

void saveToFile(const string& filename, const string& input) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось создать файл " + filename);
    }
    outFile << input;
}