#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        vector<int> exits(n, 0);
        vector<int> hash(26, 1);
        for (int i = 0; i < 26; ++i) {
            hash[i] <<= i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                exits[i] = exits[i] | hash[words[i][j] - 'a'];
            }
        }
        int res = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (exits[i] + exits[j] == (exits[i] ^ exits[j])) {
                    res = max((size_t)res, words[i].size() * words[j].size());
                }
            }
        }
        return res;
    }
};


int main() {
    Solution test;
    vector<string> words{  "abcw","baz","foo","bar","xtfn","abcdef" };
    test.maxProduct(words);
    return 0;
}