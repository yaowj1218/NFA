//
//  DFA.cpp
//  DFA
//
//  Created by 姚文杰 on 2016/12/2.
//  Copyright © 2016年 姚文杰. All rights reserved.
//

#include <iostream>
#include <string>

#define max 100

using namespace std;

int N,num;

struct edge {
	string first;
	string choice;
	string last;
};
// 判断是否为 NFA
int judge(edge *e) {
	int i, j, s = 0;
	for (i = 0; i<N; i++) {
		s = 0;
		if (e[i].choice == "&") {
			return 1;
		}
		for (j = i; j<N; j++) {
			if (e[i].first[0] == e[j].first[0] && e[j].choice == e[i].choice) {
				s++;
			}
			if (s>1) {
				return 1;
			}
		}
	}
	return 0;
}
//DFA 的确定

string closure(string a, edge *e) {
	int i, j;
	for (i = 0; i<a.length(); i++) {
		for (j = 0; j<N; j++) {
			if (e[j].first[0] == a[i] && e[j].choice == "&") {
				a = a + e[j].last[0];
			}
		}
	}
	return a;
}



string sub(string first, char ch, edge* e) {
	int i, j;
	string s = "";
	for (i = 0; i<first.length(); i++) {
		for (j = 0; j<N; j++) {
			if (first[i] == e[j].first[0] && ch == e[j].choice[0]&& ch!='&' ) {
				s = s + e[j].last[0];
			}
		}

	}
	return s;
}



string sort(string t) {
	int k, i, j;
	char tt;
	for (i = 0; i<t.length() - 1; i++) {
		k = i;
		for (j = i + 1; j<t.length(); j++) {
			if (t[j]<t[k])k = j;
		}
		tt = t[k];
		t[k] = t[i];
		t[i] = tt;
	}
	return t;
}

void move(edge* e,string choice,string* T,int& num){
    int h,j=0;
    for(int m=0;m<=num;m++){
    for(j=0;j<choice.length();j++){
        string ss="";
        ss=sub(T[m], choice[j], e);
		if (ss != "") {
			for (h = 0; h < num; h++) {
				ss = closure(ss, e);
				if (T[h] == sort(ss))break;
			}
			if (h == num)T[++num] = sort(ss);
		}
    }
    }

}

void makedfa(edge* NFA_e,edge* DFA_e,string* T, string choice,int& num) {
	int n = 0;
	int m;
	string s;
	for (int i = 0; i <= num; i++) {
		for (int j = 0; j < choice.length(); j++) {
			s = "";
			s = sub(T[i], choice[j], NFA_e);
			if (s != "") {
				s = closure(s, NFA_e);
				s = sort(s);
				DFA_e[n].first = T[i];
				DFA_e[n].choice = choice[j];
				for (m = 0; m <= num; m++) {
					if (T[m] == s) {
						DFA_e[n++].last = T[m];
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= num; j++) {
			if (DFA_e[i].first == T[j])
				cout << j << " " << DFA_e[i].choice;
		}
		for (int j = 0; j <= num; j++) {
			if (DFA_e[i].last == T[j])
				cout << " " << j <<endl;
		}
	}
}

int main() {
	string first, end;
	string choice;
	string T[max];
	int i,j,h,flag,isNFA = 0;
	edge *NFA_e = new edge[max];
	edge *DFA_e = new edge[max];
	cin >> N;
	for (int i = 0; i <N; i++) {
		cin>> NFA_e[i].first>> NFA_e[i].choice >> NFA_e[i].last;
	}
	cin >> end;

	for (int h = 0; h < N; h++) {
		flag = 0;
		 for (j = 0; j <= choice.length(); j++){
			 if (NFA_e[h].choice[0] == choice[j]) flag = 1; break;
		}
		 if (flag == 0) {
			 choice += NFA_e[h].choice;
		 }
	}

	isNFA = judge(NFA_e);
	if (isNFA) {
		cout << "是NDA" << endl;
	}
	else
		cout << "是DFA" << endl;
	//cout << isNFA;
	first = NFA_e[0].first;
	T[0]=closure(first, NFA_e);
	T[0] = sort(T[0]);
	move(NFA_e, choice, T, num);
	makedfa(NFA_e, DFA_e, T, choice,num);
	system("pause");
	return 0;

}		
























