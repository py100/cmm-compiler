#include <bits/stdc++.h>
#include "SL_table.h"

using namespace std;
#ifndef SL_GRAMMER_CLASS_INCLUDE
#define SL_GRAMMER_CLASS_INCLUDE

struct Exp{
	Exp(){}
	int left, pos, follow_terminal;
	vector<int> right;
	Exp(int _left, vector<int> _right) {
		left = _left;
		right = _right;
		pos = 0;
		follow_terminal = -1;
	}
	void adjust(int p, int ft) {
		this->pos = p;
		this->follow_terminal = ft;
	}

	friend bool operator < (const Exp& a, const Exp& b) {
		if (a.left == b.left) {
			if (a.pos == b.pos) {
					if (a.follow_terminal == b.follow_terminal)
						return a.right < b.right;
					return a.follow_terminal < b.follow_terminal;
			}
			return a.pos < b.pos;
		}
		else
			return a.left < b.left;
	}

	friend bool operator == (const Exp&a, const Exp& b) {
		return a.left == b.left && a.right == b.right;
	}

	void show() {
		printf("\n%d => ", left);
		for (int i = 0; i < right.size(); i++) {
			printf("%d ", right[i]);
		}
		printf("\n %d--%d", pos, follow_terminal);
		printf("\n======================\n");
	}
};

class SL_grammer {
public:
	int num_terminal, num_nonterminal, startid, tot_symbol, END;
	map<int, string> str_of_nonterminal, str_of_terminal;
	map<string, int> id_of_symbol;
	set<int> nonterminals, terminals;
	vector < Exp >  exps;
	

	void init() {
		num_nonterminal = num_terminal =  tot_symbol = 0;
		startid = -1;
		str_of_nonterminal.clear();
		str_of_terminal.clear();
		id_of_symbol.clear();
		END = -1;
	}

	void g_first(set< int >& firstset, int id) {
		if (terminals.count(id)) {
			firstset.insert(id);
			return;
		}
		else {
			for (int i = 0; i < exps.size(); i++) {
				if (exps[i].left == id) {
					g_first(firstset, exps[i].right[0]);
				}
			}
		}
	}

	void show() {
		printf("non_terminals: %d\nterminals: %d\nstart id: %d\nEND : %d\n", num_nonterminal, num_terminal, startid, END);
		printf("\n\n");
		for (auto pis : str_of_nonterminal) {
			printf("%d -- %s\n", pis.first, pis.second.c_str());
			set <int> tmp;
			g_first(tmp, pis.first);


			for (auto tt : tmp) {
				printf("%d, ", tt);
			}
			printf("\n");
		}
		printf("\n\n");
		for (auto pis : str_of_terminal) {
			printf("%d -- %s\n", pis.first, pis.second.c_str());
			set <int> tmp;
			g_first(tmp, pis.first);
			for (auto tt : tmp) {
				printf("%d, ", tt);
			}
			printf("\n");
		}
		printf("\n\n");
		for (int i = 0; i < exps.size(); i++) {
			exps[i].show();
		}
	}

	void read_grammer(const char *file) {
		printf("%s\n", file);
		ifstream in(file);
		//freopen(file, "r", stdin);
		int label_id = -1;
		string in_str;
		while(in >> in_str) {
			printf("instr = {%s}\n", in_str.c_str());
			if (in_str[0] == '[') {
				string lable_str = in_str.substr(1,in_str.length()-2);
				label_id = -1;
				cout << lable_str << endl;
				for (int i = 0; i < NUM_LABLE; i++) {
					if (strcmp(label_list[i], lable_str.c_str()) == 0) {
						label_id = i;
					}
				}
				if (label_id == -1) {
					_ERROR("in read_grammer -- invalid label");
				}
			}
			else {
				switch(label_id) {
					case 0:
						num_nonterminal++;
						id_of_symbol[in_str] = tot_symbol;
						str_of_nonterminal[tot_symbol] = in_str;
						nonterminals.insert(tot_symbol);
						tot_symbol++;
						break;

					case 1:
						num_terminal++;
						id_of_symbol[in_str] = tot_symbol;
						str_of_terminal[tot_symbol] = in_str;
						if (in_str == "#") {
							END = tot_symbol;
						}
						terminals.insert(tot_symbol);
						tot_symbol++;
						break;

					case 2:
						startid = id_of_symbol[in_str];
						break;

					case 3: {
						int left = id_of_symbol[in_str];
						in >> in_str;
						in >> in_str;
						vector < int > tmp;
						while (true) {
							if (in_str == ";") {
								exps.push_back(Exp(left, tmp));
								tmp.clear();
								break;
							}
							else if (in_str == "|") {
								exps.push_back(Exp(left, tmp));
								tmp.clear();
							}
							else {
								tmp.push_back(id_of_symbol[in_str]);
							}
							in >> in_str;
						}
						break;
					}

					default:
						_ERROR("in read_grammer -- swich -- invalid case");
						break;
				}
			}
		}
	}

	Exp start_exp() {
		for (int i = 0; i < exps.size(); i++) {
			if (exps[i].left == startid)
				return exps[i];
		}
	}

};


#endif