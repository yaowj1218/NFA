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
int N, NFA_num, DFA_num;
string part[max];//分割子集
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
			if (first[i] == e[j].first[0] && ch == e[j].choice[0] && ch != '&') {
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



void move(edge* e, string choice, string* T, int& num,string end) {
	int h, j = 0;
	for (int m = 0; m <= num; m++) {
		for (j = 0; j < choice.length(); j++) {
			string ss = "";
			ss = sub(T[m], choice[j], e);
			if (ss != "") {
				ss = closure(ss, e);
				ss = sort(ss);
				for (h = 0; h < num; h++) {
					if (T[h] == ss)break;
				}
				if (h == num)
					T[++num] = ss;
			}
		}
	}
		
	
	for (int m = 0; m <= num; m++) {
	for (int j = 0; j < T[m].length(); m++)
			if (end == T[m].substr(j, 1)) {
				end = T[m];
			}
	}
}



void makedfa(edge* NFA_e, edge* DFA_e, string* T, string choice, int& num, int &n,string end) {
	n = 0;
	int m;
	string s;
	char letter = 'A';
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
						break;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for ( int j = 0; j <= num; j++) {
			if (DFA_e[i].first == T[j]) {
				if (DFA_e[i].first == end)
					end = letter + j;
				DFA_e[i].first = letter+j;
				cout << DFA_e[i].first << " " << DFA_e[i].choice ;
			}
			
		}
		  for ( int j = 0; j <= num; j++){
			  if (DFA_e[i].last == T[j]) {
				  DFA_e[i].last = letter + j;
				  cout <<" " << DFA_e[i].last << endl;
		  }
			  
	    }
	}
}



bool isexist(string s, string d)

{

	if (d != "" && 0 <= d.find(s) && d.find(s) <= d.length() - 1)

		return 1;

	else

		return 0;

}

//int Simplify()

//分割子集法进行DFA的最小化

int divide(edge *e, string choice)

{

	int x, m, flag = 2, flag0, i, j;

	string ss, part0[max], t[max];

	flag0 = flag;

	for (x = 0; x<choice.length(); x++)  //遍历有穷字母表
	{

		for (m = 0; m<flag0; m++)       //遍历各个划分的集合

		{

			for (i = 0; i<part[m].length(); i++)

			{

				ss = sub(part[m].substr(i, 1), choice[x], e);     //一个状态可以通过choice能够到的所有状态

				for (j = 0; j<flag; j++)

				{

					if (isexist(ss, part[j]))

						part0[j] = part0[j] + part[m].substr(i, 1);

					if (ss == "")

					{

						part0[flag] = part0[flag] + part[m].substr(i, 1);

						break;

					}

				}

			}

			for (j = 0; j <= flag; j++)

			{

				if (part0[j] != ""&&part0[j] != part[m])

				{

					part[flag++] = part0[j];

					part0[j] = "";

					part[j] = "";



				}

				else

					part0[j] = "";

			}

		}

		flag0 = flag;

	}

	cout << "此DFA最小化划分的子集如下：" << endl;

	for (i = 0; i<flag; i++)

	{

		if (part[i] != "")

			cout << part[i] << endl;

	}

	cout << "用状态A,B,C···等代替子集：";

	for (i = 0; i<flag; i++)

	{

		if (part[i] != "")cout << "{" << part[i] << "},";

	}

	cout << endl << "则DFA最小化后的各边信息如下：" << endl;

	char letters[max];

	char letter = 'A';

	for (i = 0; i<flag; i++)

	{

		if (part[i] != "")

		{

			letters[i] = letter;

			++letter;

		}

	}

	for (i = 0; i<flag; i++)

		for (j = 0; j<choice.length(); j++)

		{

			ss = sub(part[i], choice[j], e);

			if (part[i] != ""&&ss != "") {



				cout << letters[i] << "  " << choice[j] << "  ";

				for (x = 0; x<flag; x++)

					if (isexist(ss.substr(0, 1), part[x]))cout << letters[x] << endl;

			}

		}



	return flag;

}



int main() {

	string first, end;

	string choice;

	string T[max];

	int i, j, h, flag, isNFA = 0;

	edge *NFA_e = new edge[max];

	edge *DFA_e = new edge[max];

	cin >> N;

	for (int i = 0; i <N; i++) {

		cin >> NFA_e[i].first >> NFA_e[i].choice >> NFA_e[i].last;

	}

	cin >> end;



	for (int h = 0; h < N; h++) {
		flag = 0;
		for (j = 0; j <= choice.length(); j++) {
			if (NFA_e[h].choice[0] == choice[j]) { flag = 1; break; }
		}
		if (flag == 0) {
			choice += NFA_e[h].choice;
		}
	}



	isNFA = judge(NFA_e);

	if (isNFA) {

		cout << "是NFA" << endl;

	}

	else

		cout << "是DFA" << endl;

	//cout << isNFA;

	first = NFA_e[0].first;
	T[0] = closure(first, NFA_e);
	T[0] = sort(T[0]);
	move(NFA_e, choice, T, NFA_num,end);
	makedfa(NFA_e, DFA_e, T, choice, NFA_num, DFA_num,end);
	part[1] = end;
	for (i = 0; i<DFA_num; i++) {
		flag = 0;
		for (int k = 0; k<part[0].length(); k++) {
			if (DFA_e[i].first == part[0].substr(k, 1)) {
				flag = 1;
			}
		}
		if (flag == 0)part[0] += DFA_e[i].first;
	}
	flag = divide(DFA_e, choice);
	system("pause");

	return 0;



}















































