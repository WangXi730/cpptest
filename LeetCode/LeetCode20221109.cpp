#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            while (left < right && (s[left] > '9' || s[left] < '0') && (s[left] < 'a' || s[left]>'z') && (s[left] < 'A' || s[left]>'Z')) {
                ++left;
            }
            while (left < right && (s[right] > '9' || s[right] < '0') && (s[right] < 'a' || s[right]>'z') && (s[right] < 'A' || s[right]>'Z')) {
                --right;
            }
            if (left < right) {
                if (s[left] == s[right]) {
                    ++left;
                    --right;
                    continue;
                }
                if (s[left] >= 'a' && s[left] <= 'z') {
                    s[left] = s[left] - 'a' + 'A';
                }
                else if(s[left] >= 'A' && s[left] <= 'Z') {
                    s[left] = s[left] - 'A' + 'a';
                }
                if (s[left] == s[right]) {
                    ++left;
                    --right;
                    continue;
                }
                return false;
            }
        }
        return true;
    }
public:
//超时解法
//    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//        //不会解怎么办？直接暴力淦起来！
//        //先求出所有解
//        vector<vector<string>> res;
//        vector<string> tmp{ beginWord };
//        vector<bool> tmp_bool(wordList.size(), true);
//        _findLadders(res, tmp_bool, tmp, endWord, wordList);
//        if (res.empty()) {
//            return res;
//        }
//        //找出长度最小的
//        int m = res[0].size();
//        for (int i = 0; i < res.size(); ++i) {
//            if (res[i].size() < m) {
//                m = res[i].size();
//            }
//        }
//        vector<vector<string>> result;
//        for (int i = 0; i < res.size(); ++i) {
//            if (res[i].size() == m) {
//                result.push_back(res[i]);
//            }
//        }
//        return result;
//    }
//private:
//    //res是最终的返回值
//    //tmp_bool是用来标记单词的状态，是否可使用，每一个单词最多出现一次，因为如果出现两次及以上，那么就会导致形成环，永远也走不出去
//    //tmp是本次走过的路线，tmp的最后一个元素是当下的状态：this_condition
//    //dest是destination，最终的形态，也就是endWord
//    void _findLadders(vector<vector<string>>& res, vector<bool>& tmp_bool, vector<string>& tmp, string& dest, vector<string>& wordList) {
//        //递归结束条件：this_condition == destination
//        string this_cond = tmp[tmp.size() - 1];
//        if (this_cond == dest) {
//            //tmp.push_back(dest);
//            res.push_back(tmp);
//            //tmp.pop_back();
//            return;
//        }
//        //遍历wordList
//        for (int i = 0; i < wordList.size(); ++i) {
//            //如果这个单词是可使用状态，且与当前单词的相差为1，就可以试试这个单词
//            if (tmp_bool[i] && only_dif(this_cond, wordList[i])) {
//                tmp.push_back(wordList[i]);
//                tmp_bool[i] = false;
//                _findLadders(res, tmp_bool, tmp, dest, wordList);
//                //回溯
//                tmp.pop_back();
//                tmp_bool[i] = true;
//            }
//        }
//    }
//    //计算两个单词不同的字母的个数是否是1
//    bool only_dif(string& s1, string& s2) {
//        bool count = true;
//        for (int i = 0; i < s1.size(); ++i) {
//            if (s1[i] != s2[i]) {
//                if (count) {
//                    count = false;
//                }
//                else {
//                    return count;
//                }
//            }
//        }
//        return !count;
//    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //先检查一遍，如果wordList中不存在endWord，直接返回即可
        int end_idx = -1;
        for (int i = 0; i < wordList.size(); ++i) {
            if (wordList[i] == endWord) {
                end_idx = i;
                break;
            }
        }
        if (end_idx == -1) {
            return {};
        }
        //最终结果，之所以采用这种手段，是因为数字比较相对字符串比较容易
        vector<pair<vector<string>, int>> res(1, { {beginWord },-1});
        //收录每一个阶段的单词每个单词最多被收录一次
        vector<bool> used(wordList.size(), false);
        size_t used_count = 0;
        size_t used_size = wordList.size();
        //开始收录
        int t = 0;//收录阶段
        //那么，优化以后，就只能通过手动来进行第一次的收录了
        //预先分配空间，就可以免去总是回溯的过程
        bool end = false;
        vector<pair<vector<string>, int>> tmp0(move(res));
        for (int j = 0; j < tmp0.size(); ++j) {
            tmp0[j].first.push_back("");
        }
        //遍历单词列表
        for (int i = 0; i < wordList.size(); ++i) {
            //如果这个单词在之前阶段被使用过，就意味着之后不能使用了
            if (used[i]) {
                continue;
            }
            //遍历tmp，看看哪些单词在这个行列
            for (int j = 0; j < tmp0.size(); ++j) {
                if (only_dif(tmp0[j].first[t],wordList[i])) {
                    used[i] = true;
                    tmp0[j].first[t + 1] = wordList[i];
                    tmp0[j].second = i;//代表最后一个单词下标是i
                    res.push_back(tmp0[j]);
                }
            }
        }
        //本轮结束，t自增
        ++t;
        if (res.empty()) {
            //探索失败
            return {};
        }
        vector<bool> pre_used = used;
        while (used_count < used_size) {
            if (end) {
                //到达终点
                break;
            }
            vector<pair<vector<string>, int>> tmp(move(res));
            //预先分配空间，就可以免去总是回溯的过程
            for (int j = 0; j < tmp.size(); ++j) {
                tmp[j].first.push_back("");
            }
            vector<bool> new_pre_used(used_size,false);
            //遍历单词列表
            for (int i = 0; i < wordList.size(); ++i) {
                //如果这个单词在之前阶段被使用过，就意味着之后不能使用了
                if (used[i]) {
                    continue;
                }
                //this_used里装的是pre中收录，且这次可以匹配的单词下标
                vector<bool> this_used(used_size,false);
                //遍历单词列表，查看哪个单词是这一次可以收录的
                for (int j = 0; j < wordList.size(); ++j) {
                    //如果不是上次收录的，那么就没必要判断
                    if (!pre_used[j]) {
                        continue;
                    }
                    if (only_dif(wordList[i], wordList[j])) {
                        this_used[j] = true;
                        //如果endWord被收录，那么代表最短的路径已完成收录，本轮结束就可以返回了
                        if (end_idx == i) {
                            end = true;
                        }
                        //收录成功，那么被标记点加一
                        if (!used[i]) {
                            ++used_count;
                            used[i] = true;
                        }
                    }
                }
                //遍历tmp，看看哪些单词在这个行列
                for (int j = 0; j < tmp.size(); ++j) {
                    //如果最后一个单词在收录名单，收录
                    if (this_used[tmp[j].second]) {
                        tmp[j].first[t + 1] = wordList[i];
                        res.push_back(tmp[j]);
                        res[res.size() - 1].second = i;//代表最后一个单词下标是i
                        new_pre_used[i] = true;//这一次被收录的单词
                    }
                }
            }
            //本轮结束，t自增
            ++t;
            if (res.empty()) {
                //探索失败
                return {};
            }
            pre_used.swap(new_pre_used);
        }
        //去除所有没有到达终点的路径
        vector<vector<string>> result;
        for (int i = 0; i < res.size(); ++i) {
            if (res[i].second == end_idx) {
                result.push_back(res[i].first);
            }
        }
        return result;
    }
private:
    //计算两个单词不同的字母的个数是否是1
    bool only_dif(string& s1, string& s2) {
        bool count = true;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                if (count) {
                    count = false;
                }
                else {
                    return count;
                }
            }
        }
        return !count;
    }
};

int main() {
    //string s = "A man, a plan, a canal: Panama";
    Solution test;
    //test.isPalindrome("0P");
    vector<string> v{ "aaaaa","caaaa","cbaaa","daaaa","dbaaa","eaaaa","ebaaa","faaaa","fbaaa","gaaaa","gbaaa","haaaa","hbaaa","iaaaa","ibaaa","jaaaa","jbaaa","kaaaa","kbaaa","laaaa","lbaaa","maaaa","mbaaa","naaaa","nbaaa","oaaaa","obaaa","paaaa","pbaaa","bbaaa","bbcaa","bbcba","bbdaa","bbdba","bbeaa","bbeba","bbfaa","bbfba","bbgaa","bbgba","bbhaa","bbhba","bbiaa","bbiba","bbjaa","bbjba","bbkaa","bbkba","bblaa","bblba","bbmaa","bbmba","bbnaa","bbnba","bboaa","bboba","bbpaa","bbpba","bbbba","abbba","acbba","dbbba","dcbba","ebbba","ecbba","fbbba","fcbba","gbbba","gcbba","hbbba","hcbba","ibbba","icbba","jbbba","jcbba","kbbba","kcbba","lbbba","lcbba","mbbba","mcbba","nbbba","ncbba","obbba","ocbba","pbbba","pcbba","ccbba","ccaba","ccaca","ccdba","ccdca","cceba","cceca","ccfba","ccfca","ccgba","ccgca","cchba","cchca","cciba","ccica","ccjba","ccjca","cckba","cckca","cclba","cclca","ccmba","ccmca","ccnba","ccnca","ccoba","ccoca","ccpba","ccpca","cccca","accca","adcca","bccca","bdcca","eccca","edcca","fccca","fdcca","gccca","gdcca","hccca","hdcca","iccca","idcca","jccca","jdcca","kccca","kdcca","lccca","ldcca","mccca","mdcca","nccca","ndcca","occca","odcca","pccca","pdcca","ddcca","ddaca","ddada","ddbca","ddbda","ddeca","ddeda","ddfca","ddfda","ddgca","ddgda","ddhca","ddhda","ddica","ddida","ddjca","ddjda","ddkca","ddkda","ddlca","ddlda","ddmca","ddmda","ddnca","ddnda","ddoca","ddoda","ddpca","ddpda","dddda","addda","aedda","bddda","bedda","cddda","cedda","fddda","fedda","gddda","gedda","hddda","hedda","iddda","iedda","jddda","jedda","kddda","kedda","lddda","ledda","mddda","medda","nddda","nedda","oddda","oedda","pddda","pedda","eedda","eeada","eeaea","eebda","eebea","eecda","eecea","eefda","eefea","eegda","eegea","eehda","eehea","eeida","eeiea","eejda","eejea","eekda","eekea","eelda","eelea","eemda","eemea","eenda","eenea","eeoda","eeoea","eepda","eepea","eeeea","ggggg","agggg","ahggg","bgggg","bhggg","cgggg","chggg","dgggg","dhggg","egggg","ehggg","fgggg","fhggg","igggg","ihggg","jgggg","jhggg","kgggg","khggg","lgggg","lhggg","mgggg","mhggg","ngggg","nhggg","ogggg","ohggg","pgggg","phggg","hhggg","hhagg","hhahg","hhbgg","hhbhg","hhcgg","hhchg","hhdgg","hhdhg","hhegg","hhehg","hhfgg","hhfhg","hhigg","hhihg","hhjgg","hhjhg","hhkgg","hhkhg","hhlgg","hhlhg","hhmgg","hhmhg","hhngg","hhnhg","hhogg","hhohg","hhpgg","hhphg","hhhhg","ahhhg","aihhg","bhhhg","bihhg","chhhg","cihhg","dhhhg","dihhg","ehhhg","eihhg","fhhhg","fihhg","ghhhg","gihhg","jhhhg","jihhg","khhhg","kihhg","lhhhg","lihhg","mhhhg","mihhg","nhhhg","nihhg","ohhhg","oihhg","phhhg","pihhg","iihhg","iiahg","iiaig","iibhg","iibig","iichg","iicig","iidhg","iidig","iiehg","iieig","iifhg","iifig","iighg","iigig","iijhg","iijig","iikhg","iikig","iilhg","iilig","iimhg","iimig","iinhg","iinig","iiohg","iioig","iiphg","iipig","iiiig","aiiig","ajiig","biiig","bjiig","ciiig","cjiig","diiig","djiig","eiiig","ejiig","fiiig","fjiig","giiig","gjiig","hiiig","hjiig","kiiig","kjiig","liiig","ljiig","miiig","mjiig","niiig","njiig","oiiig","ojiig","piiig","pjiig","jjiig","jjaig","jjajg","jjbig","jjbjg","jjcig","jjcjg","jjdig","jjdjg","jjeig","jjejg","jjfig","jjfjg","jjgig","jjgjg","jjhig","jjhjg","jjkig","jjkjg","jjlig","jjljg","jjmig","jjmjg","jjnig","jjnjg","jjoig","jjojg","jjpig","jjpjg","jjjjg","ajjjg","akjjg","bjjjg","bkjjg","cjjjg","ckjjg","djjjg","dkjjg","ejjjg","ekjjg","fjjjg","fkjjg","gjjjg","gkjjg","hjjjg","hkjjg","ijjjg","ikjjg","ljjjg","lkjjg","mjjjg","mkjjg","njjjg","nkjjg","ojjjg","okjjg","pjjjg","pkjjg","kkjjg","kkajg","kkakg","kkbjg","kkbkg","kkcjg","kkckg","kkdjg","kkdkg","kkejg","kkekg","kkfjg","kkfkg","kkgjg","kkgkg","kkhjg","kkhkg","kkijg","kkikg","kkljg","kklkg","kkmjg","kkmkg","kknjg","kknkg","kkojg","kkokg","kkpjg","kkpkg","kkkkg","ggggx","gggxx","ggxxx","gxxxx","xxxxx","xxxxy","xxxyy","xxyyy","xyyyy","yyyyy","yyyyw","yyyww","yywww","ywwww","wwwww","wwvww","wvvww","vvvww","vvvwz","avvwz","aavwz","aaawz","aaaaz" };
    vector<string> v1{ "hot","dot","dog","lot","log","cog" };
    test.findLadders("aaaaa",
        "ggggg", v);
    return 0;
}