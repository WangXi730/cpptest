#include<iostream>
#include<string>
#include<vector>

using namespace std;


struct TrieTreeNode {
    TrieTreeNode(const string& word, int idx) :children(26, nullptr) {
        if (idx == word.size()) {
            end = true;
        }
        else {
            children[word[idx]-'a'] = new TrieTreeNode(word, idx + 1);
        }
    }
    ~TrieTreeNode() {
        for (int i = 0; i < 26; ++i) {
            if (children[i] != nullptr)
                delete children[i];
        }
    }
    void insert(const string& word, int idx) {
        if (idx == word.size()) {
            end = true;
        }
        else {
            if (children[word[idx]-'a'] == nullptr) {
                children[word[idx]-'a'] = new TrieTreeNode(word, idx + 1);
            }
            else {
                children[word[idx]-'a']->insert(word, idx + 1);
            }
        }
    }
    bool search(const string& word, int idx, bool findpre = false) {
        if (idx == word.size()) {
            if (findpre || end) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (children[word[idx] - 'a'] == nullptr) {
            return false;
        }
        return children[word[idx] - 'a']->search(word, idx + 1, findpre);
    }
    bool end = false;
    vector<TrieTreeNode*> children;
};
class Trie {
public:
    Trie() :children(26, nullptr) {

    }
    ~Trie() {
        for (int i = 0; i < 26; ++i) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }
    }

    void insert(string word) {
        if (word.size() == 0) {
            end = true;
            return;
        }
        if (children[word[0]-'a'] != nullptr) {
            children[word[0]-'a']->insert(word, 1);
        }
        else {
            children[word[0]-'a'] = new TrieTreeNode(word, 1);
        }
    }

    bool search(string word) {
        if (word == "") {
            return end;
        }
        if (children[word[0]-'a'] != nullptr) {
            return children[word[0]-'a']->search(word, 1);
        }
        else {
            return false;
        }
    }

    bool startsWith(string prefix) {
        if (prefix == "") {
            return true;
        }
        if (children[prefix[0]-'a'] != nullptr) {
            return children[prefix[0]-'a']->search(prefix, 1, true);
        }
        else {
            return false;
        }
    }
private:
    bool end = false;
    vector<TrieTreeNode*> children;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
#include<unordered_set>
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<unordered_set<int>> pmap(numCourses);
        int size = 0;
        vector<int> res(numCourses);
        for (int i = 0; i < prerequisites.size(); ++i) {
            if (prerequisites[i][0] == prerequisites[i][1]) {
                return {};
            }
            pmap[prerequisites[i][0]].insert(prerequisites[i][1]);
        }
        int presize = 0;
        while (size < numCourses) {
            int tmp = size;
             for (int j = 0; j < pmap.size(); ++j) {
                if (size >= numCourses) {
                    return res;
                }
                for (int i = presize; i < size; ++i) {
                    pmap[j].erase(res[i]);
                }
                if (pmap[j].empty()) {
                    res[size] = j;
                    ++size;
                }
            }
            if (size == presize) {
                return {};
            }
            presize = tmp;
        }
        return res;
    }
};

int main() {/*
    Trie trie;
    trie.insert("apple");
    std::cout << trie.search("apple") << std::endl;
    std::cout << trie.search("app") << std::endl;
    std::cout << trie.startsWith("app") << std::endl;
    trie.insert("app");
    std::cout << trie.search("app") << std::endl;*/
    Solution test;
    vector<vector<int>> pre = { {0,1} };
    test.findOrder(2,pre);
    return 0;
}