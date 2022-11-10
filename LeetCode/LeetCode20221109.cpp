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
//��ʱ�ⷨ
//    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//        //�������ô�죿ֱ�ӱ�����������
//        //��������н�
//        vector<vector<string>> res;
//        vector<string> tmp{ beginWord };
//        vector<bool> tmp_bool(wordList.size(), true);
//        _findLadders(res, tmp_bool, tmp, endWord, wordList);
//        if (res.empty()) {
//            return res;
//        }
//        //�ҳ�������С��
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
//    //res�����յķ���ֵ
//    //tmp_bool��������ǵ��ʵ�״̬���Ƿ��ʹ�ã�ÿһ������������һ�Σ���Ϊ����������μ����ϣ���ô�ͻᵼ���γɻ�����ԶҲ�߲���ȥ
//    //tmp�Ǳ����߹���·�ߣ�tmp�����һ��Ԫ���ǵ��µ�״̬��this_condition
//    //dest��destination�����յ���̬��Ҳ����endWord
//    void _findLadders(vector<vector<string>>& res, vector<bool>& tmp_bool, vector<string>& tmp, string& dest, vector<string>& wordList) {
//        //�ݹ����������this_condition == destination
//        string this_cond = tmp[tmp.size() - 1];
//        if (this_cond == dest) {
//            //tmp.push_back(dest);
//            res.push_back(tmp);
//            //tmp.pop_back();
//            return;
//        }
//        //����wordList
//        for (int i = 0; i < wordList.size(); ++i) {
//            //�����������ǿ�ʹ��״̬�����뵱ǰ���ʵ����Ϊ1���Ϳ��������������
//            if (tmp_bool[i] && only_dif(this_cond, wordList[i])) {
//                tmp.push_back(wordList[i]);
//                tmp_bool[i] = false;
//                _findLadders(res, tmp_bool, tmp, dest, wordList);
//                //����
//                tmp.pop_back();
//                tmp_bool[i] = true;
//            }
//        }
//    }
//    //�����������ʲ�ͬ����ĸ�ĸ����Ƿ���1
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
        //�ȼ��һ�飬���wordList�в�����endWord��ֱ�ӷ��ؼ���
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
        //���ս����֮���Բ��������ֶΣ�����Ϊ���ֱȽ�����ַ����Ƚ�����
        vector<pair<vector<string>, int>> res(1, { {beginWord },-1});
        //��¼ÿһ���׶εĵ���ÿ��������౻��¼һ��
        vector<bool> used(wordList.size(), false);
        size_t used_count = 0;
        size_t used_size = wordList.size();
        //��ʼ��¼
        int t = 0;//��¼�׶�
        //��ô���Ż��Ժ󣬾�ֻ��ͨ���ֶ������е�һ�ε���¼��
        //Ԥ�ȷ���ռ䣬�Ϳ�����ȥ���ǻ��ݵĹ���
        bool end = false;
        vector<pair<vector<string>, int>> tmp0(move(res));
        for (int j = 0; j < tmp0.size(); ++j) {
            tmp0[j].first.push_back("");
        }
        //���������б�
        for (int i = 0; i < wordList.size(); ++i) {
            //������������֮ǰ�׶α�ʹ�ù�������ζ��֮����ʹ����
            if (used[i]) {
                continue;
            }
            //����tmp��������Щ�������������
            for (int j = 0; j < tmp0.size(); ++j) {
                if (only_dif(tmp0[j].first[t],wordList[i])) {
                    used[i] = true;
                    tmp0[j].first[t + 1] = wordList[i];
                    tmp0[j].second = i;//�������һ�������±���i
                    res.push_back(tmp0[j]);
                }
            }
        }
        //���ֽ�����t����
        ++t;
        if (res.empty()) {
            //̽��ʧ��
            return {};
        }
        vector<bool> pre_used = used;
        while (used_count < used_size) {
            if (end) {
                //�����յ�
                break;
            }
            vector<pair<vector<string>, int>> tmp(move(res));
            //Ԥ�ȷ���ռ䣬�Ϳ�����ȥ���ǻ��ݵĹ���
            for (int j = 0; j < tmp.size(); ++j) {
                tmp[j].first.push_back("");
            }
            vector<bool> new_pre_used(used_size,false);
            //���������б�
            for (int i = 0; i < wordList.size(); ++i) {
                //������������֮ǰ�׶α�ʹ�ù�������ζ��֮����ʹ����
                if (used[i]) {
                    continue;
                }
                //this_used��װ����pre����¼������ο���ƥ��ĵ����±�
                vector<bool> this_used(used_size,false);
                //���������б��鿴�ĸ���������һ�ο�����¼��
                for (int j = 0; j < wordList.size(); ++j) {
                    //��������ϴ���¼�ģ���ô��û��Ҫ�ж�
                    if (!pre_used[j]) {
                        continue;
                    }
                    if (only_dif(wordList[i], wordList[j])) {
                        this_used[j] = true;
                        //���endWord����¼����ô������̵�·���������¼�����ֽ����Ϳ��Է�����
                        if (end_idx == i) {
                            end = true;
                        }
                        //��¼�ɹ�����ô����ǵ��һ
                        if (!used[i]) {
                            ++used_count;
                            used[i] = true;
                        }
                    }
                }
                //����tmp��������Щ�������������
                for (int j = 0; j < tmp.size(); ++j) {
                    //������һ����������¼��������¼
                    if (this_used[tmp[j].second]) {
                        tmp[j].first[t + 1] = wordList[i];
                        res.push_back(tmp[j]);
                        res[res.size() - 1].second = i;//�������һ�������±���i
                        new_pre_used[i] = true;//��һ�α���¼�ĵ���
                    }
                }
            }
            //���ֽ�����t����
            ++t;
            if (res.empty()) {
                //̽��ʧ��
                return {};
            }
            pre_used.swap(new_pre_used);
        }
        //ȥ������û�е����յ��·��
        vector<vector<string>> result;
        for (int i = 0; i < res.size(); ++i) {
            if (res[i].second == end_idx) {
                result.push_back(res[i].first);
            }
        }
        return result;
    }
private:
    //�����������ʲ�ͬ����ĸ�ĸ����Ƿ���1
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