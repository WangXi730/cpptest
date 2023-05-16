#include<iostream>
#include<vector>
#include"LeetCode_array.hpp"

using namespace std;

//class Solution {
//public:
//    int maxCoins(vector<int>& nums) {
//        n = nums.size();
//
//        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
//        //dp[l][m][r]��ʾ��m(mid)�����򱻴��Ƶ�ʱ���������������ǵ�l(left)������͵�r(right)������
//        //��l = m ʱ���������û�������ˣ���r = mʱ�������ұ�û��������
//        //���ǣ��������Ǻܷ��㣬�ײ�����ô�洢�ģ����ϲ������Ϊ��dp(-1,m,?)�������û������ͬ��dp(?,m,n)�����ұ�û�����򣬵�������û��-1��λ�ã�����ͨ��һ���ӿڽ���ת����index()
//        //numsҲ�ǣ��̶�index(nums,-1) = index(nums,n) = 1 
//
//        //��ʼ��dp��Ҳ���Ǽ�¼���Ƶ�һ������ʱ������
//        for (int m = 0; m < n; ++m) {
//            index(dp, m - 1, m, m + 1) = index(nums, m - 1) * index(nums, m) * index(nums, m + 1);
//        }
//
//        //����������������򣬲���¼���ֵ��Ϊ����
//        for (int step = 2; step <= n; ++step) {
//            //step������l��r֮�����������������ڳ�ʼ���Ѿ�������һ����������������step��2��ʼ������step�����䣨-1��n����Ҳ����n������ȫ�����ƣ�����step��ȷ����n
//            //Ѱ������(l,r)
//            for (int l = -1; l + step < n; ++l) {
//                int r = l + step + 1;
//                //Ѱ��m
//                for (int m = l + 1; m < r; ++m) {
//                    //���㵱ǰλ�õ����ֵ
//                    int l2m = 0;
//                    int m2r = 0;
//                    for (int i = l + 1; i < m; ++i) {
//                        l2m = max(l2m, index(dp, l, i, m));
//                    }
//                    for (int i = m + 1; i < r; ++i) {
//                        m2r = max(m2r, index(dp, m, i, r));
//                    }
//                    index(dp, l, m, r) = index(nums, l) * index(nums, m) * index(nums, r) + l2m + m2r;
//                }
//            }
//        }
//
//        //Ѱ������(-1,n)�����ֵ�����ؼ���
//        int res = 0;
//        for (int m = 0; m < n; ++m) {
//            res = max(res, index(dp, -1, m, n));
//        }
//        return res;
//    }
//private:
//    int& index(vector<vector<vector<int>>>& dp, int l, int m, int r) {
//        if (l == -1) {
//            l = m;
//        }
//        if (r == n) {
//            r = m;
//        }
//        return dp[l][m][r];
//    }
//    int& index(vector<int>& nums, int idx) {
//        if (idx == -1 || idx == n) {
//            return lim_const;
//        }
//        return nums[idx];
//    }
//private:
//    int n = 0;
//    int lim_const = 1;//�߽�ֵ��Ҳ����-1λ�ú�nλ�õ�ֵ
//};
//class Solution {
//public:
//    int maxCoins(vector<int>& nums) {
//        n = nums.size();
//        if (n == 1) {
//            return nums[0];
//        }
//        vector<vector<int>> dp(n, vector<int>(n,0));
//        //�Ż�֮��dp[l][r]����������(l,r)�У������������������Ի�õ�����
//
//        //��ʼ��dp��Ҳ���Ǽ�¼���Ƶ�һ������ʱ������
//        for (int m = 0; m < n; ++m) {
//            index(dp, m - 1, m + 1) = index(nums, m - 1) * index(nums, m) * index(nums, m + 1);
//        }
//
//        //����������������򣬲���¼���ֵ��Ϊ����
//        for (int step = 2; step <= n; ++step) {
//            //step������l��r֮�����������������ڳ�ʼ���Ѿ�������һ����������������step��2��ʼ������step�����䣨-1��n����Ҳ����n������ȫ�����ƣ�����step��ȷ����n
//            //Ѱ������(l,r)
//            for (int l = -1; l + step < n; ++l) {
//                int r = l + step + 1;
//                //Ѱ��m
//                for (int m = l + 1; m < r; ++m) {
//                    //���㵱ǰλ�õ����ֵ
//                    int tmp = index(nums, l) * index(nums, m) * index(nums, r) + index(dp,l,m) + index(dp,m,r);
//                    index(dp, l, r) = max(tmp, index(dp, l, r));
//                }
//            }
//        }
//
//        return index(dp,-1,n);
//    }
//private:
//    int& index(vector<vector<int>>& dp, int l, int r) {
//        if (l + 1 == r) {
//            return null_figure;
//        }
//        return dp[l + 1][r - 1];
//    }
//    int& index(vector<int>& nums, int idx) {
//        if (idx == -1 || idx == n) {
//            return lim_const;
//        }
//        return nums[idx];
//    }
//private:
//    int n = 0;
//    int lim_const = 1;//�߽�ֵ��Ҳ����-1λ�ú�nλ�õ�ֵ
//    int null_figure = 0;//l��r֮�䱾��û�����֣�����Ӧ����0
//
//};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        vector<TreeNode> bst(n);
        //����BST��Ĭ��n-1Ϊ����㣬���Բ����ٲ���һ�Σ����Բ���������
        //�ƻ��б䣬bst�˻������Ա��ˣ����Ը��������Ǻ�ɫ��
        bst[n - 1].color = false;
        for (int i = n - 2; i >= 0; --i) {
            //��root��ʼ����
            int root = n - 1;
            //Ѱ��root
            while (bst[root].pr_node != -1) {
                root = bst[root].pr_node;
            }
            while (1) {
                if (nums[i] <= nums[root]) {
                    //��������
                    //������������ά������������ӵ�����
                    ++bst[root].left_children;
                    if (bst[root].left == -1) {
                        bst[root].left = i;
                        bst[i].pr_node = root;
                        //����ɹ������rootΪ��ɫ������ƽ�����
                        if (bst[root].color) {
                            balance(bst, i);
                        }
                        break;
                    }
                    root = bst[root].left;
                }
                else {
                    //��������
                    //��������˵�����������������Ϲ��ŵ��������󣬹ʶ�������������͸����
                    res[i] += bst[root].left_children + 1;
                    if (bst[root].right == -1) {
                        bst[root].right = i;
                        bst[i].pr_node = root;
                        //����ɹ������rootΪ��ɫ������ƽ�����
                        if (bst[root].color) {
                            balance(bst, i);
                        }
                        break;
                    }
                    root = bst[root].right;
                }
            }
        }
        return res;
    }
private:
    struct TreeNode {
        int left = -1;
        int right = -1;
        int left_children = 0;
        //rb
        bool color = true;
        int pr_node = -1;
    };
    void balance(vector<TreeNode>& tree, int node) {
        //�ҳ����ڵ�
        int father = tree[node].pr_node;
        //�ݹ��������֮һ���������˸����
        if(father == -1){
            //������ɺ�ɫ����������
            tree[node].color = false;
            return;
        }
        //�ݹ���������������ڵ�Ϊ��ɫ
        else if (!tree[father].color) {
            return;
        }
        //���뿴�岮����Ϊ�������
        //�Ȱ�үү�ڵ��ҳ���(���ڸ��ڵ㲻�Ǻ�ɫ--���Ǹ����--����үү���һ���Ǵ��ڵ�)
        int grandpa = tree[father].pr_node;
        int uncle = -1;
        if (tree[grandpa].left == father) {
            uncle = tree[grandpa].right;
        }
        else {
            uncle = tree[grandpa].left;
        }
        //1���岮������Ϊ��ɫ
        if (uncle != -1 && tree[uncle].color) {
            //ֱ�ӻ���ɫ����
            tree[grandpa].color = true;
            tree[father].color = false;
            tree[uncle].color = false;
            //�ݹ����
            balance(tree, grandpa);
        }
        //2���岮�����ڻ���Ϊ��ɫ
        else {
            //1�����ڵ�������
            if (tree[grandpa].left == father) {
                //1���������ҽڵ�
                if (tree[father].right == node) {
                    //����ת
                    left_revolve(tree, node, father);
                    //�����Լ���ɫ����
                    father = node;
                    node = tree[node].left;
                }
                //2������������
                //����ת
                right_revole(tree, father, grandpa);
            }
            //2�����ڵ����ҽڵ�
            else {
                //1������������
                if(tree[father].left == node){
                    //����ת
                    right_revole(tree, node, father);
                    //�����Լ���ɫ����
                    father = node;
                    node = tree[node].right;
                }
                //2���������ҽڵ�
                //����ת
                left_revolve(tree, father, grandpa);
            }
            //��ɫ�Լ����ݵ���
            tree[father].color = false;
            tree[grandpa].color = true;
        }
    }
    //��ת����
    void left_revolve(vector<TreeNode>& tree, int node, int father) {
        tree[father].right = tree[node].left;
        if (tree[father].right != -1) {
            tree[tree[father].right].pr_node = father;
        }
        tree[node].pr_node = tree[father].pr_node;
        if (tree[father].pr_node != -1) {
            if (tree[tree[father].pr_node].left == father) {
                tree[tree[father].pr_node].left = node;
            }
            else {
                tree[tree[father].pr_node].right = node;
            }
        }
        tree[node].left = father;
        tree[father].pr_node = node;
        //���ݵ���
        tree[node].left_children += tree[father].left_children + 1;
    }
    void right_revole(vector<TreeNode>& tree, int node, int father) {
        tree[father].left = tree[node].right;
        if (tree[father].left != -1) {
            tree[tree[father].left].pr_node = father;
        }
        tree[node].pr_node = tree[father].pr_node;
        if (tree[father].pr_node != -1) {
            if (tree[tree[father].pr_node].left == father) {
                tree[tree[father].pr_node].left = node;
            }
            else {
                tree[tree[father].pr_node].right = node;
            }
        }
        tree[father].pr_node = node;
        tree[node].right = father;
        //���ݵ���
        tree[father].left_children -= tree[node].left_children + 1;
    }
};




int main() {
    std::vector<int> nums{ 26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41 };
    Solution test;
    vector<int> res = test.countSmaller(nums);
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << std::endl;
    }
    return 0;
}
