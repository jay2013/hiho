/* ******************************************************************
 * title: The Marshtomp has seen it all before 
 * url: https://hihocoder.com/problemset/problem/1082
 * date: Fri Oct 14 20:31:41 CST 2016
 * description: 字符替换
 * general idea: 简单题，却WA了两次，必须细心。
 * tags: string 
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
	string a = "marshtomp", b= "fjxmlhx";
    string s;
    while(getline(cin, s)) {
		int len = s.length();
		int alen = a.length();
		if(len < alen) {
			cout << s << endl;
		} else {
			string o;
			for(int i = 0; i < len; ++i) {
				if(i + alen <= len && (s[i] == a[0] || s[i] == a[0] - 'a' + 'A')) {
                    bool flag = true;  
                    for(int  j = 0; j < alen; ++j) {
                        if(a[j] != s[i + j] && s[i + j] != a[j] - 'a' + 'A') {
                            flag = false;
                            break;
                        }
                    }
                    if(flag == true) {
                        o += b;
                        i = i + alen - 1;
                    } else {
                        o += s[i];
                    }
                } else {
                    o += s[i];
                }				
			}
            cout << o << endl;
		}
    }
    return 0;
}
