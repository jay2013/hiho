/* ******************************************************************
 * title: 最近公共祖先·一
 * url: http://hihocoder.com/problemset/problem/1062 
 * date: Fri Oct 21 13:17:29 CST 2016
 * description: 给若干家谱中的部分人的父子关系，询问两个人的祖先中
 * 辈份最小的那一位姓名。
 * general idea: 使用tarjan离线算法预处理出所有询问的结果，按顺序输出。
 * tags: tarjan-lca 
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
#define LEN 233

struct TreeNode{
    string name;
    int indegree;
    set<TreeNode *> childs;
    vector<int> qur;
    int lca[LEN];
    TreeNode() {
        name = "";
        indegree = 0;
        childs.clear();
        qur.clear();
        memset(lca, 0, sizeof(lca));
    }
    ~TreeNode() {
        for(set<TreeNode *>::iterator  it = childs.begin(), ie = childs.end(); it != ie; ++it) {
            if(*it != NULL) delete *it;
        }
    }
    void dump() {
        cout << "name:" << name << endl;
        for(set<TreeNode * >::iterator it = childs.begin(), ie = childs.end(); it != ie; ++it) {
            cout << (*it)->name << " ";
        }
        cout << endl;
    }
};

std::pair<string, string> qpairs[LEN];
map<string, int> sm;
TreeNode * nodes[LEN];
TreeNode * root;
int visit[LEN], par[LEN], ase[LEN];

void init() {
    for(int i = 0; i < LEN; ++i) {
        visit[i] = 0;
        par[i] = i;
        ase[i] = i;
    }
}

// find-union-set

int find(int x) {
    if(par[x] != x) {
        par[x] = find(par[x]);
    }
    return par[x];
}
void merge(int x, int y) {
    int xf = find(x);
    int yf = find(y);
    par[yf] = xf; 
}

// tarjan alg for off-line lca

void lca(int root) {
    ase[root] = root;
    for(set<TreeNode *>::iterator it = nodes[root]->childs.begin(), ie = nodes[root]->childs.end();
            it != ie; it++) {
        int pos = sm.find((*it)->name)->second;
        lca(pos);
        merge(root, pos);
        ase[find(pos)] = root;
    }
    visit[root] = 1;
    for(size_t i = 0; i < nodes[root]->qur.size(); ++i) {
        int tmp = nodes[root]->qur[i];
        if(visit[tmp]) {
            nodes[root]->lca[tmp] = ase[find(tmp)];
            nodes[tmp]->lca[root] = nodes[root]->lca[tmp];
        }
    }
} 

int main() {
    freopen("input.txt", "r", stdin);
    int N, M, cnt = 0;
    string strA, strB;
    int posA, posB;
    root = new TreeNode();
    nodes[0] = root;
    // build the tree 
    cin >> N;
    while(N--) {
        cin >> strA >> strB;
        if(sm.find(strA) == sm.end()) {
            nodes[++cnt] = new TreeNode(); 
            nodes[cnt]->name = strA;
            posA = cnt;
            sm[strA] = posA;
        } else {
            posA = sm.find(strA)->second;
        }

        if(sm.find(strB) == sm.end()) {
            nodes[++cnt] = new TreeNode(); 
            nodes[cnt]->name = strB;
            posB = cnt;
            sm[strB] = posB;
        } else {
            posB = sm.find(strB)->second;
        }

        nodes[posB]->indegree ++;
        if (nodes[posA]->childs.find(nodes[posB]) == nodes[posA]->childs.end()) {
            nodes[posA]->childs.insert(nodes[posB]); 
        }
    }
    for(int i = 1; i <= cnt; ++i) {
        // nodes[i]->dump();
        if(nodes[i]->indegree == 0) {
            root->childs.insert(nodes[i]);
        }
    }
    // record the query
    cin >> M;
    for(int i = 0; i < M; ++i) {
        cin >> strA >> strB;
        qpairs[i] = std::make_pair(strA, strB);
        if(sm.find(strA) == sm.end() || sm.find(strB) == sm.end()) continue;
        posA = sm.find(strA)->second;
        posB = sm.find(strB)->second;
        nodes[posA]->qur.push_back(posB);
        nodes[posB]->qur.push_back(posA);
    }
    // use tarjan calc lca
    init();
    lca(0);
    // give the output
    for(int i = 0; i < M; ++i) {
        strA = qpairs[i].first;
        strB = qpairs[i].second;
        if(strA == strB) {
            cout << strA << endl;
            continue;
        }
        if(sm.find(strA) == sm.end() || sm.find(strB) == sm.end()) {
            cout << "-1" << endl;
            continue;
        }
        posA = sm.find(strA)->second;
        posB = sm.find(strB)->second;
        assert(nodes[posA]->lca[posB] == nodes[posB]->lca[posA]);
        int tmp = nodes[posA]->lca[posB];
        if(tmp == 0) {
            cout << "-1" << endl;
        } else {
            cout << nodes[tmp]->name << endl;
        } 
    }
    delete root;
    return 0;
}
