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
//        //dp[l][m][r]表示第m(mid)个气球被戳破的时候，左右两个气球是第l(left)个气球和第r(right)个气球
//        //当l = m 时，就是左边没有气球了，当r = m时，就是右边没有气球了
//        //但是，这样不是很方便，底层是这么存储的，但上层调用认为：dp(-1,m,?)才是左边没有气球，同理，dp(?,m,n)才是右边没有气球，但是数组没有-1的位置，于是通过一个接口进行转换：index()
//        //nums也是，固定index(nums,-1) = index(nums,n) = 1 
//
//        //初始化dp，也就是记录戳破第一个气球时的数字
//        for (int m = 0; m < n; ++m) {
//            index(dp, m - 1, m, m + 1) = index(nums, m - 1) * index(nums, m) * index(nums, m + 1);
//        }
//
//        //接下来逐个戳破气球，并记录最大值作为返回
//        for (int step = 2; step <= n; ++step) {
//            //step代表着l和r之间的气球的数量，由于初始化已经计算了一个气球的情况，所以step从2开始，最大的step是区间（-1，n），也就是n个气球全部戳破，所以step上确界是n
//            //寻找区间(l,r)
//            for (int l = -1; l + step < n; ++l) {
//                int r = l + step + 1;
//                //寻找m
//                for (int m = l + 1; m < r; ++m) {
//                    //计算当前位置的最大值
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
//        //寻找区间(-1,n)的最大值，返回即可
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
//    int lim_const = 1;//边界值，也就是-1位置和n位置的值
//};
//class Solution {
//public:
//    int maxCoins(vector<int>& nums) {
//        n = nums.size();
//        if (n == 1) {
//            return nums[0];
//        }
//        vector<vector<int>> dp(n, vector<int>(n,0));
//        //优化之后，dp[l][r]代表在区间(l,r)中，戳破所有气球最大可以获得的数字
//
//        //初始化dp，也就是记录戳破第一个气球时的数字
//        for (int m = 0; m < n; ++m) {
//            index(dp, m - 1, m + 1) = index(nums, m - 1) * index(nums, m) * index(nums, m + 1);
//        }
//
//        //接下来逐个戳破气球，并记录最大值作为返回
//        for (int step = 2; step <= n; ++step) {
//            //step代表着l和r之间的气球的数量，由于初始化已经计算了一个气球的情况，所以step从2开始，最大的step是区间（-1，n），也就是n个气球全部戳破，所以step上确界是n
//            //寻找区间(l,r)
//            for (int l = -1; l + step < n; ++l) {
//                int r = l + step + 1;
//                //寻找m
//                for (int m = l + 1; m < r; ++m) {
//                    //计算当前位置的最大值
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
//    int lim_const = 1;//边界值，也就是-1位置和n位置的值
//    int null_figure = 0;//l和r之间本就没有数字，所以应当加0
//
//};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        vector<TreeNode> bst(n);
        //构造BST，默认n-1为根结点，所以不必再插入一次，所以不必做处理
        //计划有变，bst退化成线性表了，所以根结点必须是黑色的
        bst[n - 1].color = false;
        for (int i = n - 2; i >= 0; --i) {
            //从root开始插入
            int root = n - 1;
            //寻找root
            while (bst[root].pr_node != -1) {
                root = bst[root].pr_node;
            }
            while (1) {
                if (nums[i] <= nums[root]) {
                    //插入左树
                    //插入左树，则维护这个结点的左孩子的数量
                    ++bst[root].left_children;
                    if (bst[root].left == -1) {
                        bst[root].left = i;
                        bst[i].pr_node = root;
                        //插入成功，如果root为红色，进行平衡调整
                        if (bst[root].color) {
                            balance(bst, i);
                        }
                        break;
                    }
                    root = bst[root].left;
                }
                else {
                    //插入右树
                    //插入右树说明这个结点比在这个根上挂着的左树都大，故而加上这个数量和根结点
                    res[i] += bst[root].left_children + 1;
                    if (bst[root].right == -1) {
                        bst[root].right = i;
                        bst[i].pr_node = root;
                        //插入成功，如果root为红色，进行平衡调整
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
        //找出父节点
        int father = tree[node].pr_node;
        //递归结束条件之一：调整到了根结点
        if(father == -1){
            //根结点变成黑色并结束调整
            tree[node].color = false;
            return;
        }
        //递归结束条件二：父节点为黑色
        else if (!tree[father].color) {
            return;
        }
        //插入看叔伯，分为两种情况
        //先把爷爷节点找出来(由于父节点不是黑色--不是根结点--所以爷爷结点一定是存在的)
        int grandpa = tree[father].pr_node;
        int uncle = -1;
        if (tree[grandpa].left == father) {
            uncle = tree[grandpa].right;
        }
        else {
            uncle = tree[grandpa].left;
        }
        //1、叔伯存在且为红色
        if (uncle != -1 && tree[uncle].color) {
            //直接换颜色即可
            tree[grandpa].color = true;
            tree[father].color = false;
            tree[uncle].color = false;
            //递归调用
            balance(tree, grandpa);
        }
        //2、叔伯不存在或者为黑色
        else {
            //1、父节点是左结点
            if (tree[grandpa].left == father) {
                //1、儿子是右节点
                if (tree[father].right == node) {
                    //左旋转
                    left_revolve(tree, node, father);
                    //数据以及颜色调整
                    father = node;
                    node = tree[node].left;
                }
                //2、儿子是左结点
                //右旋转
                right_revole(tree, father, grandpa);
            }
            //2、父节点是右节点
            else {
                //1、儿子是左结点
                if(tree[father].left == node){
                    //右旋转
                    right_revole(tree, node, father);
                    //数据以及颜色调整
                    father = node;
                    node = tree[node].right;
                }
                //2、儿子是右节点
                //左旋转
                left_revolve(tree, father, grandpa);
            }
            //颜色以及数据调整
            tree[father].color = false;
            tree[grandpa].color = true;
        }
    }
    //旋转函数
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
        //数据调整
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
        //数据调整
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
