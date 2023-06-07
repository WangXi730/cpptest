#include<iostream>
#include<string>
#include<vector>

using namespace std;
//class Solution {
//public:
    ////前缀树结点
    //struct treeNode {
    //    bool end = false;
    //    treeNode* children[26] = { 0 };
    //    bool is_layer = true;
    //    //特殊需求，需要将单词在数组中的位置保存下来
    //    int _index = 0;
    //    void set_end(int index) {
    //        end = true;
    //        _index = index;
    //    }
    //    int get_index() {
    //        return _index;
    //    }
    //    void insert(char c) {
    //        is_layer = false;
    //        if (children[c - 'a'] == nullptr)
    //            children[c - 'a'] = new treeNode();
    //    }
    //    void insert(const string word, int i, int index) {
    //        if (i >= word.size()) {
    //            set_end(index);
    //            return;
    //        }
    //        char c = word[i];
    //        insert(c);
    //        children[c - 'a']->insert(word, i + 1, index);
    //    }
    //    void r_insert(const string word, int i, int index) {
    //        if (i >= word.size()) {
    //            set_end(index);
    //            return;
    //        }
    //        char c = word[word.size() - i - 1];
    //        insert(c);
    //        children[c - 'a']->r_insert(word, i + 1, index);
    //    }
    //    ~treeNode() {
    //        clear();
    //    }
    //    void clear() {
    //        for (int i = 0; i < 26; ++i) {
    //            if (children[i] != nullptr) {
    //                delete children[i];
    //                children[i] = nullptr;
    //            }
    //        }
    //    }
    //};
    //using Tree = treeNode*;
    //vector<vector<int>> palindromePairs(vector<string>& words) {
    //    //构造两棵前缀树，一棵从前往后，一棵从后往前
    //    Tree pre = new treeNode();
    //    Tree post = new treeNode();

    //    //init tree
    //    for (int i = 0; i < words.size(); ++i) {
    //        pre->insert(words[i], 0, i);
    //        post->r_insert(words[i], 0, i);
    //    }

    //    //order tree
    //    //这里采用深度遍历的方式，当不存在相同子节点且不为word结尾的时候，就剪枝
    //    vector<vector<int>> res;
    //    dfs(res, pre, post);
    //    return res;
    //}
    ////res是返回值，pre和post是两棵前缀树
    //void dfs(vector<vector<int>>& res, Tree pre, Tree post) {
    //    //递归结束条件
    //    if (pre->end && post->end && post->get_index() != pre->get_index()) {
    //        vector<int> tmp{ pre->get_index(),post->get_index() };
    //        res.emplace_back(tmp);
    //    }
    //    if (pre->end) {
    //        vector<int> post_set;
    //        string word = " ";
    //        for (int i = 0; i < 26; ++i) {
    //            if (post->children[i] == nullptr) {
    //                continue;
    //            }
    //            word[0] = i + 'a';
    //            is_palindrome(post->children[i], word, post_set);
    //            word.resize(1);
    //        }
    //        int pre_index = pre->get_index();
    //        for (int i = 0; i < post_set.size(); ++i) {
    //            vector<int> tmp{ pre_index, post_set[i] };
    //            res.emplace_back(tmp);
    //        }
    //    }
    //    if (post->end) {
    //        vector<int> pre_set;
    //        string word = " ";
    //        for (int i = 0; i < 26; ++i) {
    //            if (pre->children[i] == nullptr) {
    //                continue;
    //            }
    //            word[0] = i + 'a';
    //            is_palindrome(pre->children[i], word, pre_set);
    //            word.resize(1);
    //        }
    //        int post_index = post->get_index();
    //        for (int i = 0; i < pre_set.size(); ++i) {
    //            vector<int> tmp{ pre_set[i], post_index };
    //            res.emplace_back(tmp);
    //        }
    //    }

    //    //递归
    //    for (int i = 0; i < 26; ++i) {
    //        if (pre->children[i] != nullptr && post->children[i] != nullptr) {
    //            dfs(res, pre->children[i], post->children[i]);
    //        }
    //    }

    //}
    //void is_palindrome(Tree tree, string& word, vector<int>& res) {
    //    if (tree->end) {
    //        int i = 0;
    //        int j = word.size() - 1;
    //        while (i < j) {
    //            if (word[i] != word[j]) {
    //                break;
    //            }
    //            ++i;
    //            --j;
    //        }
    //        if (i >= j) {
    //            res.emplace_back(tree->get_index());
    //        }
    //    }
    //    int size = word.size();
    //    word.resize(size + 1);
    //    for (int i = 0; i < 26; ++i) {
    //        if (tree->children[i] == nullptr) {
    //            continue;
    //        }
    //        word[size] = i + 'a';
    //        is_palindrome(tree->children[i], word, res);
    //        word.resize(size + 1);
    //    }
    //}
    //试试哈希表
//    vector<vector<int>> palindromePairs(vector<string>& words) {
//        int n = words.size();
//        vector<long long> hash(n, 0);
//        vector<long long> r_hash(n, 0);
//        vector<long long> idx_27 = { 1 };
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < words[i].size(); ++j) {
//                hash[i] *= 27;
//                hash[i] += words[i][j] - 'a' + 1;
//                r_hash[i] *= 27;
//                r_hash[i] += words[i][words[i].size() - j - 1] - 'a' + 1;
//            }
//            if (idx_27.size() < words[i].size() + 1) {
//                int j = idx_27.size();
//                idx_27.resize(words.size() + 1);
//                while (j < idx_27.size()) {
//                    idx_27[j] = idx_27[j - 1] * 27;
//                    ++j;
//                }
//            }
//        }
//        vector<vector<int>> res;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (i == j) {
//                    continue;
//                }
//                else if (hash[i] * idx_27[words[j].size()] + hash[j] == r_hash[j] * idx_27[words[i].size()] + r_hash[i]) {
//                    vector<int> tmp = { i,j };
//                    res.push_back(tmp);
//                }
//            }
//        }
//        return res;
//    }
//
//};
//
//
//  // This is the interface that allows for creating nested lists.
//  // You should not implement it, or speculate about its implementation
//  class NestedInteger {
//  public:
//      // Return true if this NestedInteger holds a single integer, rather than a nested list.
//      bool isInteger() const {
//            return isint;
//      }
// 
//      // Return the single integer that this NestedInteger holds, if it holds a single integer
//      // The result is undefined if this NestedInteger holds a nested list
//      int getInteger() const {
//          return val1;
//      }
// 
//      // Return the nested list that this NestedInteger holds, if it holds a nested list
//      // The result is undefined if this NestedInteger holds a single integer
//      const vector<NestedInteger>& getList() const {
//          return val2;
//      }
//      bool isint = false;
//      int val1;
//      vector<NestedInteger> val2;
//  };
// 
//
// //多叉树遍历
//  class NestedIterator {
//  public:
//      NestedIterator(vector<NestedInteger>& nestedList) {
//          int n = nestedList.size();
//          if (n == 0) {
//              index = -1;
//              return;
//          }
//          children.resize(n);
//          for (int i = 0; i < n; ++i) {
//              children[i] = new NestedIterator(nestedList[i]);
//          }
//          for (int i = 0; i < n; ++i) {
//              if (children[i]->hasNext()) {
//                  break;
//              }
//              else {
//                  ++index;
//              }
//          }
//          if (index == n) {
//              index = -1;
//          }
//      }
//
//      NestedIterator(const NestedInteger& nested) {
//          if (nested.isInteger()) {
//              val = nested.getInteger();
//              is_int = true;
//          }
//          else {
//              const vector<NestedInteger>& nestedList = nested.getList();
//              int n = nestedList.size();
//              if (n == 0) {
//                  index = -1;
//                  return;
//              }
//              children.resize(n);
//              for (int i = 0; i < n; ++i) {
//                  children[i] = new NestedIterator(nestedList[i]);
//              }
//              for (int i = 0; i < n; ++i) {
//                  if (children[i]->hasNext()) {
//                      break;
//                  }
//                  else {
//                      ++index;
//                  }
//              }
//              if (index == n) {
//                  index = -1;
//              }
//          }
//      }
//
//      ~NestedIterator() {
//          for (int i = 0; i < children.size(); ++i) {
//              delete children[i];
//          }
//      }
//
//      int next() {
//          if (is_int) {
//              index = -1;
//              return val;
//          }
//          int res = children[index]->next();
//          while (!children[index]->hasNext()) {
//              ++index;
//              if (index == children.size()) {
//                  index = -1;
//                  return res;
//              }
//          }
//          if (index == children.size()) {
//              index = -1;
//          }
//          return res;
//      }
//
//      bool hasNext() {
//          return index != -1;
//      }
//  private:
//      vector<NestedIterator*> children;
//      int index = 0;
//      int val;
//      bool is_int = false;
//  };
//
//  class Solution2 {
//  public:
//
//      string reverseVowels(string s) {
//          bool hash[256] = { false };
//          hash['A'] = true;
//          hash['E'] = true;
//          hash['I'] = true;
//          hash['O'] = true;
//          hash['U'] = true;
//          hash['a'] = true;
//          hash['e'] = true;
//          hash['i'] = true;
//          hash['o'] = true;
//          hash['u'] = true;
//          int i = 0;
//          int j = s.size() - 1;
//          while (j > i) {
//              while (j > i && !hash[s[j]])--j;
//              while (j > i && !hash[s[i]])++i;
//              char c = s[i];
//              s[i] = s[j];
//              s[j] = c;
//              ++i;
//              --j;
//          }
//          return s;
//      }
//  };
/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
#include<map>
#include<unordered_map>
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            ++umap[nums[i]];
        }
        multimap<int, int> omap;
        for (auto& e : umap) {
            omap.insert(make_pair(e.second, e.first));
        }
        vector<int> res(k);
        auto rit = omap.rbegin();
        for (int i = 0; i < k; ++i) {
            res[i] = (*rit).second;
            ++rit;
        }
        return res;
    }
};

class SummaryRanges {
public:
    SummaryRanges() {

    }

    void addNum(int value) {
        intervals[value] = value;
        auto it = intervals.find(value);
        if (it != intervals.begin() && (++it)-- != intervals.end()) {
            --it;
            int ll = it->first;
            int lr = it->second;
            ++it;
            ++it;
            int rl = it->first;
            int rr = it->second;
            --it;
            if (lr == rl - 2) {
                intervals.erase(it);
                intervals.erase(intervals.find(rl));
                intervals[ll] = rr;
            }
            else if (lr == value - 1) {
                intervals.erase(it);
                intervals[ll] = value;
            }
            else if (rl == value + 1) {
                intervals.erase(intervals.find(rl));
                intervals[value] = rr;
            }
        }
        else if (it == intervals.begin()) {
            ++it;
            int rl = it->first;
            int rr = it->second;
            if (rl == value + 1) {
                intervals.erase(it);
                intervals[value] = rr;
            }
        }
        else {
            --it;
            int ll = it->first;
            int lr = it->second;
            ++it;
            if (lr == value - 1) {
                intervals.erase(it);
                intervals[ll] = value;
            }
        }

    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        int i = 0;
        for (auto& e : intervals) {
            vector<int> tmp{ e.first,e.second };
            res.push_back(tmp);
        }
        return res;
    }
private:
    map<int, int> intervals;
};
#include<algorithm>
static bool smaller(vector<int>& a, vector<int>& b) {
    return a[0] < b[0];
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(), smaller);
    int n = envelopes.size();
    if (n == 1) {
        return 1;
    }
    //这里可以做一个处理：把相同的数字分离
    for (int i = 0; i < n - 1; ++i) {
        if (envelopes[i][0] == envelopes[i + 1][0]) {
            //从i开始数字相同，开始做分离处理
            int j = 0;
            for (j = i + 1; j < n && envelopes[j][0] == envelopes[j - 1][0]; ++j);
            vector<vector<int>> v(n - j + 1 + i);
            for (int k = 0; k < n; ++k) {
                if (k <= i) {
                    v[k] = envelopes[k];
                }
                else if (k >= j) {
                    v[k - j + i + 1] = envelopes[k];
                }
            }
            int res = maxEnvelopes(v);
            for (int k = 1; k < j - i; ++k) {
                v[i] = envelopes[i + k];
                res = max(res, maxEnvelopes(v));
            }
            return res;
        }
    }
    vector<int> arr(n);
    arr[0] = envelopes[0][1];
    int maxL = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0;
        int r = maxL;
        while (l < r) {
            int mid = (l + r) / 2;
            if (arr[mid] < envelopes[i][1]) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }
        arr[l] = envelopes[i][1];
        if (l == maxL) {
            maxL += 1;
        }
    }
    return maxL;
}
int main() {
    vector<vector<int>> t{ {5,4},{6,4} ,{6,7},{2,3} };//{ {4,5},{4,6 },{6,7},{2,3},{1,1} };//{ {30,50},{12,2},{3,4},{12,15} }; //{ {1,1},{1,1},{1,1} };
    maxEnvelopes(t);
    vector<int[10]> arr;
    return 0;
}