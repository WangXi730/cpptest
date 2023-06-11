#include<iostream>
#include<map>
#include<vector>
#include<set>
using namespace std;
class Twitter {
public:
    Twitter() {

    }

    void postTweet(int userId, int tweetId) {
        tweet[userId].push_back(make_pair(tweetId, time));
        ++time;
    }

    vector<int> getNewsFeed(int userId) {
        //create map
        map<int, pair<int, int>> omap;//{time : {userID,tweetID}}
        map<int, vector<pair<int, int>>::iterator> omap2;//{userID:iterator}

        //create result
        vector<int> res(10);

        //init
        if (tweet[userId].size() != 0) {
            omap2.insert(make_pair(userId, tweet[userId].end()));
            --omap2[userId];
            omap.insert(make_pair(omap2[userId]->second, make_pair(userId, omap2[userId]->first)));
        }
        for (auto& e : followed[userId]) {
            if (tweet[e].size() != 0) {
                omap2[e] = tweet[e].end();
                --omap2[e];
                omap.insert(make_pair(omap2[e]->second, make_pair(e, omap2[e]->first)));
            }
        }

        //choose sort by map
        for (int i = 0; i < 10; ++i) {
            if (omap.empty()) {
                res.resize(i);
                return res;
            }
            //choose the biggest figure and insert into result vector
            auto it = omap.end();
            --it;
            int user = it->second.first;
            res[i] = it->second.second;
            //pop the figure and insert this user's next tweet
            omap.erase(it);
            if (omap2[user] != tweet[user].begin()) {
                --omap2[user];
                omap.insert(make_pair(omap2[user]->second, make_pair(user, omap2[user]->first)));
            }
        }

        return res;
    }

    void follow(int followerId, int followeeId) {
        followed[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        followed[followerId].erase(followeeId);
    }
private:
    //{userId : followdId_set}
    map<int, set<int>> followed;
    //{userId : {tweetId,time}}
    map<int, vector<pair<int, int>>> tweet;
    //begin at 0
    int time = 0;
};
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        vector<vector<int>> dp = matrix;
        //init
        int row = matrix.size();
        int col = matrix[0].size();
        for (int i = 1; i < col; ++i) {
            dp[0][i] += dp[0][i - 1];
        }
        for (int i = 1; i < row; ++i) {
            dp[i][0] += dp[i - 1][0];
            for (int j = 1; j < col; ++j) {
                dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            }
        }
        int res = -100000;
        //i1和j1都为0的过程
        for (int i2 = 0; i2 < row; ++i2) {
            for (int j2 = 0; j2 < col; ++j2) {
                if (matrix[i2][j2] <= k) {
                    res = max(res, matrix[i2][j2]);
                    if (res == k) {
                        return k;
                    }
                }
                if (dp[i2][j2] <= k) {
                    res = max(res, dp[i2][j2]);
                    if (res == k) {
                        return k;
                    }
                }
            }
        }
        //一个i1为0，j1不为0的过程
        for (int j1 = 1; j1 < col; ++j1) {
            for (int i2 = 0; i2 < row; ++i2) {
                for (int j2 = j1; j2 < col; ++j2) {
                    int tmp = dp[i2][j2] - dp[i2][j1 - 1];
                    if (tmp <= k) {
                        res = max(res, tmp);
                        if (res == k) {
                            return k;
                        }
                    }
                }
            }
        }
        for (int i1 = 1; i1 < row; ++i1) {
            //这里是一个j1为0的过程
            for (int i2 = i1; i2 < row; ++i2) {
                for (int j2 = 0; j2 < col; ++j2) {
                    int tmp = dp[i2][j2] - dp[i1 - 1][j2];
                    if (tmp <= k) {
                        res = max(res, tmp);
                        if (res == k) {
                            return k;
                        }
                    }
                }
            }
            for (int j1 = 1; j1 < col; ++j1) {

                if (matrix[i1][j1] <= k) {
                    res = max(res, matrix[i1][j1]);
                    if (res == k) {
                        return k;
                    }
                }
                for (int i2 = i1; i2 < row; ++i2) {
                    for (int j2 = j1; j2 < col; ++j2){
                        int tmp = dp[i2][j2] + dp[i1-1][j1-1] - dp[i1-1][j2] - dp[i2][j1-1];
                        if (tmp <= k) {
                            res = max(res, tmp);
                            if (res == k) {
                                return k;
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};
#include"LeetCode_array.hpp"
int main() {
    Solution test;
    string s = "[[5,-4,-3,4],[-3,-4,4,5],[5,1,5,-4]]";
    wx::array_to_c(s);
    cout << s;
    vector<vector<int>> m{ {5,-4,-3,4},{-3,-4,4,5},{5,1,5,-4} };
    cout << test.maxSumSubmatrix(m,8);
    return 0;
}