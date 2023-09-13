#include"LeetCode_array.hpp"
#include<queue>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) {return a[1] < b[1]; });
        priority_queue<int> pq;
        int time = 0;

        for (int i = 0; i < courses.size(); ++i) {
            if (time + courses[i][0] <= courses[i][1]) {
                //¼ÓÈë
                time += courses[i][0];
                pq.push(courses[i][0]);
            }
            else if(!pq.empty() && pq.top() > courses[i][0]) {
                time = time - pq.top() + courses[i][0];
                pq.pop();
                pq.push(courses[i][0]);
            }
        }
        return pq.size();
    }
};


int main() {
    Solution test;
    vector<vector<int>> courses {{914, 9927}, { 333,712 }, { 163,5455 }, { 835,5040 }, { 905,8433 }, { 417,8249 }, { 921,9553 }, { 913,7394 }, { 303,7525 }, { 582,8658 }, { 86,957 }, { 40,9152 }, { 600,6941 }, { 466,5775 }, { 718,8485 }, { 34,3903 }, { 380,9996 }, { 316,7755 }};
    std::cout << test.scheduleCourse(courses);
    return 0;
}