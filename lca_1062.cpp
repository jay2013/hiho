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
class TreeNode {
public:
    string name;
    int indegree;
    set<TreeNode *> childs;
    vector<int> querys; // record the nodes that need to calc the lca.
    int ans[LEN]; // lca pos of this node and the node in the smae position in querys array
    TreeNode() {
        name = "";
        indegree = 0;
        childs.clear();
        querys.clear();
        memset(ans, 0, sizeof(ans));
    }
    TreeNode(string nm): name(nm) {
        indegree = 0;
        childs.clear();
        querys.clear();
        memset(ans, 0, sizeof(ans));
    }
    ~TreeNode() {
        for(set<TreeNode *>::iterator it = childs.begin(), 
                ie = childs.end(); it != ie; ++it) {
            TreeNode * tnPtr = *it;
            if(tnPtr != NULL) {
                delete tnPtr;
            }
        }
    }
	void dump() {
		cout << "name:" << name << endl;
		for(size_t i = 0; i < querys.size(); ++i) {
			cout << ans[querys[i]] << endl;
		}
	}
};

class QueryNode {
public:
    string name1, name2;
    QueryNode(string n1, string n2):name1(n1),name2(n2) {
    }
    ~QueryNode() {}
}; 

vector<TreeNode * > peoples;
vector<QueryNode *> querys;
TreeNode * root;
map<string, int> sm;
int visit[LEN], sp[LEN], ansestor[LEN];

void init() {
    for(int i = 0; i < LEN; ++i) {
        visit[i] = 0; // default not visit;
        sp[i] = i; // initially, node i is a set of himself
        ansestor[i] = 0;
    }
}

int find(int x) {
    if(sp[x] != x) sp[x] = find(sp[x]);
    return sp[x];
}

void merge(int x, int y) {
    int xs = find(x);
    int ys = find(y);
    sp[ys] = xs;
}

void lca(int root) {
    ansestor[root] = root;
    for(set<TreeNode *>::iterator it = peoples[root]->childs.begin(), 
            ie = peoples[root]->childs.end(); it != ie; ++it) {
        TreeNode * tnPtr = *it;
        int cpos = sm.find(tnPtr->name)->second;
        lca(cpos);
        merge(root, cpos);
        ansestor[find(cpos)] = root;
    }
    visit[root] = 1;
    for(size_t i = 0; i < peoples[root]->querys.size(); ++i) {
        int tmp = peoples[root]->querys[i];
        if (visit[tmp]) {
            peoples[root]->ans[tmp] = ansestor[find(tmp)];
            peoples[tmp]->ans[root] = peoples[root]->ans[tmp];
			// cout << peoples[root]->name << " and " << peoples[tmp]->name << "'s lca is " <<peoples[peoples[tmp]->ans[root]]->name << endl;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    root = new TreeNode();
    peoples.push_back(root);
    int N, M;
    string strP, strC;
    cin >> N;
    map<string, int>::iterator it;
    while(N--) {
        cin >> strP >> strC;
        int posP = -1, posC = -1;
        it = sm.find(strP);
        if(it != sm.end()) {
            posP = it->second; 
        } else {
            TreeNode * newNode = new TreeNode(strP);
            peoples.push_back(newNode);
            posP = (int)peoples.size() - 1;
            sm.insert(std::make_pair(strP, posP));
        }
        it = sm.find(strC);
        if(it != sm.end()) {
            posC = it->second;
        } else {
            TreeNode * newNode = new TreeNode(strC);
            peoples.push_back(newNode);
            posC = (int) peoples.size() - 1;
            sm.insert(make_pair(strC, posC));
        }
        peoples[posC]->indegree ++;
        if(peoples[posP]->childs.find(peoples[posC]) == peoples[posP]->childs.end()) {
            peoples[posP]->childs.insert(peoples[posC]);
        }
    }
	// cout << "root for each tree:" << endl;
    for(size_t i = 1; i < peoples.size(); ++i) {
        if(peoples[i]->indegree == 0) {
            // cout << peoples[i]->name << endl;
            peoples[0]->childs.insert(peoples[i]);
        }
    }
	// cout << "######################" << endl;
    cin >> M;
    string qs1, qs2;
    int pos1, pos2;
    for(int i = 0; i < M; ++i) {
        cin >> qs1 >> qs2;
        QueryNode * qNode = new QueryNode(qs1, qs2);
        querys.push_back(qNode);
        if(sm.find(qs1) != sm.end() && sm.find(qs2) != sm.end()) {
            pos1 = sm.find(qs1)->second;
            pos2 = sm.find(qs2)->second;
            peoples[pos1]->querys.push_back(pos2);
            peoples[pos2]->querys.push_back(pos1);
        }
    }
	init();
	lca(0);
    for(size_t i = 0; i < querys.size(); ++i) {
        qs1 = querys[i]->name1;
        qs2 = querys[i]->name2;
        if(sm.find(qs1) == sm.end() || sm.find(qs2) == sm.end()) {
            if(qs1 == qs2) {
                cout << qs1 << endl;
            } else {
                cout << -1 << endl;
            }
        } else {
            pos1 = sm.find(qs1)->second;
            pos2 = sm.find(qs2)->second;
            if (peoples[pos1]->ans[pos2] == 0 ) { 
                cout << -1 << endl;
            } else {
                cout << peoples[peoples[pos1]->ans[pos2]]->name << endl;
            }
        }
    }
    delete root;
    return 0;
}
