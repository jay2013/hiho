/* ******************************************************************
 * title: 最近公共祖先·一
 * url: http://hihocoder.com/problemset/problem/1062 
 * date: Fri Oct 21 13:17:29 CST 2016
 * description: 给若干家谱中的部分人的父子关系，询问两个人的祖先中
 * 辈份最小的那一位姓名。
 * general idea: 使用tarjan离线算法预处理出任意两个人的lca，对每个询问，O(1)
 * 给出答案。
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
    int lca[LEN];
    TreeNode() {
        name = "";
        indegree = 0;
        childs.clear();
        memset(lca, -1, sizeof(lca));
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
        cout << "lca: ";
        for(int i = 0; i < LEN; ++i) {
            cout << lca[i] << " ";
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
    for(size_t i = 0; i < LEN; ++i) {
        if(visit[i]) {
            nodes[root]->lca[i] = ase[find(i)];
            nodes[i]->lca[root] = nodes[root]->lca[i];
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
        if(nodes[i]->indegree == 0) {
            root->childs.insert(nodes[i]);
        }
    }
    // use tarjan calc lca
    init();
    lca(0);
    for(int i = 0; i <= cnt; ++i) {
        cout << "ID:" << i << endl;
        nodes[i]->dump();
    }
    // record the query
    cin >> M;
    for(int i = 0; i < M; ++i) {
        cin >> strA >> strB;
        if(strA == strB) {
            cout << strA << "\n";
            continue;
        }
        if(sm.find(strA) == sm.end() || sm.find(strB) == sm.end()) {
            cout << "-1\n";
            continue;
        }
        posA = sm.find(strA)->second;
        posB = sm.find(strB)->second;
        assert(nodes[posA]->lca[posB] == nodes[posB]->lca[posA]);
        int tmp = nodes[posA]->lca[posB];
        if(tmp == 0) {
            cout << "-1\n";
        } else {
            cout << nodes[tmp]->name << "\n";
        } 
    }
    delete root;
    return 0;
}
