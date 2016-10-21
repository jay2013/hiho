/* ******************************************************************
 * title: KMP算法
 * url: https://hihocoder.com/problemset/problem/1015
 * date: Mon Oct 17 21:38:12 CST 2016
 * description: 使用KMP算法统计模式串在数据串中出现次数
 * general idea: 应用KMP算法
 * tags: kmp 
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

int main() {
    freopen("input.txt", "r", stdin);
    int N, next[10240];
    char p[10240], t[1024000];
    scanf("%d", &N);
    while(N--) {
        scanf("%s %s", p, t);
        int lenP = strlen(p);
        int lenT = strlen(t);
		// calculate the next array.
        next[0] = -1;
        int k = -1;
        for(int i = 1; i < lenP; ++i) {
            while(k >= 0 && p[k + 1] != p[i]) {
                k = next[k];
            } 
            if(p[k + 1] == p[i]) {
                k = k + 1;
            }
            next[i] = k;
        }
        for(int i = 0; i < lenP; ++i) {
            printf("%d ", next[i]);
        }
        printf("\n");
		// match string
        int q = 0; // number of characters matched.
        int ans = 0;
        for(int i = 0; i < lenT; ++i) {
            while(q > 0 && p[q] != t[i]) {
                q = next[q - 1] + 1;
            } 
            if(p[q] == t[i]) {
                q = q + 1;
            }
            if(q == lenP) {
                ans ++;
				q = next[q - 1] + 1; // look for the next match
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
