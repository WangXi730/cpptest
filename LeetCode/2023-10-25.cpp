#include"LeetCodeTools.hpp"
leetcode


class Solution {
public:
    Solution() :dp{0} {}
    int punishmentNumber(int n) {
        int i = dp.size();
        while (n >= i) {
            dp.push_back(*dp.rbegin());
            if (dfs(i, i * i, 0)) {
                dp[i] += i * i;
            }
            ++i;
        }
        return dp[n];
    }
private:
    //t是原本的值，post是去掉末尾剩下的值，tmp是当前加起来的值
    bool dfs(int t, int post, int tmp) {
        //判断post是否可以满足
        if (post + tmp == t) {
            return true;
        }
        int n = 10;
        while (post / n) {
            if (dfs(t, post / n, tmp + post % n)) {
                return true;
            }
            n *= 10;
        }
        return false;
    }
    vector<int> dp;


public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<int> sorted(n);
        for (int i = 0; i < n; ++i) {
            sorted[i] = i;
        }
        sort(sorted.begin(), sorted.end(), [&](int a, int b) {
            return growTime[a] > growTime[b];
            });
        vector<int> sorted_plantTime(n);
        vector<int> sorted_growTime(n);
        for (int i = 0; i < n; ++i) {
            sorted_growTime[i] = growTime[sorted[i]];
            sorted_plantTime[i] = plantTime[sorted[i]];
        }
        int res = sorted_growTime[0] + sorted_plantTime[0];
        for (int i = 1; i < n; ++i) {
            sorted_plantTime[i] += sorted_plantTime[i - 1];
            res = max(res, sorted_plantTime[i] + sorted_growTime[i]);
        }
        return res;
    }
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for (int i = 0; i < flowerbed.size(); ++i) {
            bool can = true;
            if (i > 0 && flowerbed[i - 1] > 0)can = false;
            if (i < flowerbed.size() - 1 && flowerbed[i + 1]>0)can = false;
            if (flowerbed[i] > 0)can = false;
            if (can) {
                --n;
                flowerbed[i] = 1;
            }
        }
        return n <= 0;
    }

public:
    //vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
    //    vector<int> res(people.size(), 0);
    //    sort(flowers.begin(), flowers.end(), [](vector<int>& a, vector<int>& b) {
    //        return a[0] < b[0];
    //        });
    //    for (int i = 0; i < res.size(); ++i) {
    //        int j = 0;
    //        while (j < flowers.size() && flowers[j][0] <= people[i]) {
    //            if (flowers[j][1] >= people[i]) {
    //                ++res[i];
    //            }
    //            ++j;
    //        }
    //    }
    //    return res;
    //}
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<int> res(people.size(), 0);
        vector<pair<int,char>> change_time;
        vector<int> people_map(people.size());
        for (int i = 0; i < people.size(); ++i) {
            people_map[i] = i;
        }
        for (int i = 0; i < flowers.size(); ++i) {
            change_time.emplace_back(flowers[i][0], 'b');
            change_time.emplace_back(flowers[i][1] + 1, 'e');
        }
        sort(change_time.begin(), change_time.end(), [](pair<int, char>& a, pair<int, char>& b) {
            return a.first < b.first;
            });
        sort(people_map.begin(), people_map.end(), [&](int a, int b) {
            return people[a] < people[b];
            });
        int i = 0;
        int j = 0;
        int c = 0;//在花期的花的数量
        while (i < people.size() && j < change_time.size()) {
            while (i < people.size() && people[people_map[i]] < change_time[j].first) {
                res[people_map[i]] = c;
                ++i;
            }
            if (i >= people.size()) {
                break;
            }
            while (j < change_time.size() && people[people_map[i]] >= change_time[j].first) {
                if (change_time[j].second == 'b') {
                    ++c;
                }
                else {
                    --c;
                }
                ++j;
            }
        }
        return res;
    }
};
class StockPrice {
public:
    StockPrice() {

    }
    
    void update(int timestamp, int price) {
        if(day_price.find(timestamp) != day_price.end()){
            --price_count[day_price[timestamp]];
        }
        day_price[timestamp] = price;
        ++price_count[price];
    }
    
    int current() {
        return day_price.rbegin()->second;
    }
    
    int maximum() {
        while(price_count.rbegin()->second == 0){
            price_count.erase(--price_count.end());
        }
        return price_count.rbegin()->first;
    }
    
    int minimum() {
        while(price_count.begin()->second == 0){
            price_count.erase(price_count.begin());
        }
        return price_count.begin()->first;    
    }
private:
    map<int,int> price_count;
    map<int,int> day_price;
};


int main() {
    Solution test;
    //cout << test.punishmentNumber(37);
    //StockPrice t2;
    //t2.update(1, 10);
    //t2.update(2, 5);
    //cout << t2.current() << endl;
    //cout << t2.maximum() << endl;
    //t2.update(1, 3);
    //cout << t2.maximum() << endl;
    //t2.update(4, 2);
    //cout << t2.minimum() << endl;
    vector<int> v1{ 1,4,3 };
    vector<int> v2{ 2,3,1 };
    //cout << test.earliestFullBloom(v1,v2);
    //vector<int> flowerbed{ 1,0,0,0,1 };

    //test.canPlaceFlowers(flowerbed, 2);
    vector<vector<int>> flowerbed;
    wx::create("[[1,10],[3,3]]", flowerbed);
    vector<int> people;
    wx::create("[3,3,2]", people);
    test.fullBloomFlowers(flowerbed,people);
    return 0;
}


