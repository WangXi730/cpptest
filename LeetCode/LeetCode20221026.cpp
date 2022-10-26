#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        //需要尾插、尾删、从头开始顺序遍历，所以使用vector
        vector<string> path_v;
        int begin = 0;
        for (int i = 1; i < path.size(); ++i) {
            if (path[i] == '/') {
                if (i == begin + 1) {
                    begin = i;
                    continue;
                }
                string pwd(path.begin() + begin, path.begin() + i);
                begin = i;
                if (pwd == "/.") {
                    continue;
                }
                else if (pwd == "/..") {
                    if(!path_v.empty())
                        path_v.pop_back();
                    continue;
                }
                path_v.push_back(pwd);
            }
        }
        if (path[path.size() - 1] != '/') {
            string s(path.begin() + begin, path.end());
            if (s == "/.") {
                
            }
            else if (s == "/..") {
                if (!path_v.empty())
                    path_v.pop_back();
            }
            else {
                path_v.push_back(s);
            }
        }
        stringstream res;
        for (int i = 0; i < path_v.size(); ++i) {
            res << path_v[i];
        }
        if (res.str() == "") {
            res << "/";
        }
        return res.str();
    }
};



int main() {
    Solution test;
    test.simplifyPath("/a//b////c/d//././/..");
    return 0;
}