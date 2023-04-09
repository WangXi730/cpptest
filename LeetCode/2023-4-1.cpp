#include<iostream>
#include<vector>
using namespace std;

int hIndex(vector<int>& citations) {
    int left = 0;
    int right = citations.size();
    int mid = (left + right) / 2;
    while (left < right - 1) {
        if (citations[mid] < citations.size() - mid) {
            //引用次数 < 论文数目
            left = mid;
            mid = (left + right) / 2;
        }
        else if (citations[mid] > citations.size() - mid) {
            right = mid;
            mid = (left + right) / 2;
        }
        else {
            return citations.size() - mid;
        }
    }
    return citations[mid];
}

int main() {
    vector<int>a{ 0 };
    hIndex(a);    return 0;
}