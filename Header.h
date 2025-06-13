#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class ListNode {
public:
    string word;
    ListNode* next;
    ListNode(const string& w);
};

class ListChain {
private:
    vector<string> words;
    vector<bool> used;
    ListNode* head;
    ListNode* tail;

    char getLastChar(const string& word);
    bool findChain(int step);
    void clearList();

public:
    ListChain(const vector<string>& wordList);
    ~ListChain();
    bool buildChain();
    void saveResult(const string& filename);
    ListNode* getChain() const;
};

vector<string> split(const string& input);
void saveToFile(const string& filename, const string& input);

#endif // HEADER_H