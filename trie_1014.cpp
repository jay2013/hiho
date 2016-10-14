/* ******************************************************************
 * title: Trie树
 * url: https://hihocoder.com/problemset/problem/1014#
 * date: Fri Oct 14 16:46:03 CST 2016
 * description: 统计词典中以某个字符为前缀的单词个数，自己是自己的前缀，空是任何字符的前缀。
 * general idea: 构建一个字典树，每个节点记录从root到自己构成的串是多少单词的前缀。
 * tags: trie tree
 *******************************************************************/
#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <string>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define LEN 26
class TrieNode {
public:
    TrieNode * childs[LEN];
    int cnt;
    TrieNode() {
        for(int i = 0; i < LEN; ++i) childs[i] = NULL;
        cnt = 0;
    }
    ~TrieNode() {
        for(int i = 0; i < LEN; ++i) {
            if(childs[i] != NULL) delete childs[i];
        }
    }
};

class TrieTree {
    TrieNode * root;
public: 
    TrieTree() {
        root = new TrieNode();
    }
    ~TrieTree() {
        delete root;
    }
    void addWord(char * s) {
        int len = strlen(s);
        if(len <= 0) return;
        TrieNode * currNode = root;
        for(int i = 0; i < len; ++i) {
            if(currNode->childs[s[i] - 'a'] == NULL) {
                currNode->childs[s[i] - 'a'] = new TrieNode();
            }
            currNode->childs[s[i] - 'a']->cnt ++;
            currNode = currNode->childs[s[i] - 'a'];
        }
    }
    int cntWords(char * prefix) {
        int rtn = 0;
        int len = strlen(prefix);
        TrieNode * currNode = root;
        for(int i = 0; i < len; ++i) {
            if(currNode->childs[prefix[i] - 'a'] == NULL) {
                return rtn;
            }
            currNode = currNode->childs[prefix[i] - 'a'];
        }
        return currNode->cnt;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    char s[11];
    TrieTree tr;
    scanf("%d", &n);
    while(n--) {
        scanf("%s", s);
        tr.addWord(s);
    }
    scanf("%d", &m);
    while(m--) {
        scanf("%s", s);
        printf("%d\n", tr.cntWords(s));
    }
    return 0;
}
