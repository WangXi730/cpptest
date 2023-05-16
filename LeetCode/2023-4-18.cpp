#include<iostream>
#include<list>
#include<vector>
#include<sstream>
using namespace std;
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        //�����ֵ��λ��
        int max_idx = 0;
        //��������
        list<int> nums_l;
        nums_l.push_back(0);
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[max_idx]) {
                max_idx = i;
            }
            nums_l.push_back(i);
        }
        //���Ҹߵ�
        list<int>::iterator left = nums_l.begin();
        list<int>::reverse_iterator right = nums_l.rbegin();
        int res = 0;
        //��ߵ�Ѱ�ң���ɾ�������λ��֮�������Ͽ��
        while (*left < max_idx) {
            //��ߵ�Ѱ��
            while (*left < max_idx) {
                if (nums[*(left++)] < nums[*left]);
                else {
                    --left;
                    break;
                }
            }
            if (*left == max_idx) {
                //���ڣ�left������߾��Եĸߵ�
                break;
            }
            //Ͽ��Ѱ�Ҳ�����
            list<int>::iterator cliff = left;
            while (nums[*left] >= nums[*cliff]) {
                //Ѱ�ҵ͹�
                while (1) {
                    if (nums[*(cliff++)] > nums[*cliff]);
                    else {
                        break;
                    }
                }
                //ɾ���͹�
                list<int>::iterator it = cliff;
                --it;
                while (it != left && nums[*it] < nums[*cliff]) {
                    list<int>::iterator tmp = it;
                    res += nums[*(it--)] * nums[*cliff] * nums[*it];
                    nums_l.erase(tmp);
                }
            }
        }
        //�Ҹߵ�Ѱ�ң���ɾ�������λ��֮�������Ͽ��
        while (*right > max_idx) {
            //��ߵ�Ѱ��
            while (*right > max_idx) {
                if (nums[*(right++)] < nums[*right]);
                else {
                    ++right;
                    break;
                }
            }
            if(*right == max_idx){
                //���ڣ�right�����ұ߾��Եĸߵ�
                break;
            }
            //Ͽ��Ѱ�Ҳ�����
            list<int>::reverse_iterator cliff = right;
            while (nums[*right] >= nums[*cliff]) {
                //Ѱ�ҵ͹�
                while (1) {
                    if (nums[*(cliff--)] > nums[*cliff]);
                    else {
                        break;
                    }
                }
                //ɾ���͹�
                list<int>::reverse_iterator it = cliff;
                ++it;
                while (it != right && nums[*it] < nums[*cliff]) {
                    list<int>::reverse_iterator tmp = it;
                    res += nums[*(it++)] * nums[*cliff] * nums[*it];
                    nums_l.erase(tmp.base());
                }
            }
        }
        //����ֻ��Ҫ�����еĽ�㣬����ɾ������
        vector<int> l2v(nums_l.begin(), nums_l.end());
        int idx = 0;
        for (int i = 0; i < l2v.size(); ++i) {
            if (l2v[i] == max_idx) {
                idx = i;
                break;
            }
        }
        for (int i = idx + 1; i < l2v.size() - 1; ++i) {
            res += nums[max_idx] * nums[l2v[i]] * nums[l2v[i + 1]];
        }
        if(idx != l2v.size() - 1){
            res += nums[max_idx] * nums[l2v[l2v.size() - 1]];
        }
        for (int i = idx - 1; i > 0; --i) {
            res += nums[max_idx] * nums[l2v[i]] * nums[l2v[i - 1]];
        }
        if (idx != 0) {
            res += nums[max_idx] * nums[l2v[0]];
        }
        res += nums[max_idx];
        return res;
    }
};
template<class T>
class A {
public:
    //A(vector<T> cp){}
    A(initializer_list<T> cp) {}
};
#include<bitset>
int main() {

    return 0;
}