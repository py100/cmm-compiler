#include <bits/stdc++.h>

#include "SL_grammer.cpp"

using namespace std;
#ifndef SL_TABLE_CLASS_INCLUDE
#define SL_TABLE_CLASS_INCLUDE

struct triple {
	int a, b, c;
	triple(int a, int b, int c):a(a),b(b), c(c){}
	friend bool operator < (const triple& ta, const triple& tb) {
		if (ta.a == tb.a) {
			if (ta.b == tb.b) {
				return ta.c < tb.c;
			}
			return ta.b < tb.b;
		}
		return ta.a < tb.b;
	}
};

struct State{
	int state_id;
	int transitor;
	set< Exp > exps;
	vector<int> edges;
	State(){}
	State(int id){
		state_id = id;
		exps.clear();
		edges.clear();
	}

	void show() {
		printf("\n**** State [%d] ****\n", state_id);

		for (auto exp : exps) {
			exp.show();
		}

		printf("\n*******************\n");
	}

	friend bool operator < (const State&a, const State& b) {
		return a.exps < b.exps;
	}

	void insert_edge(int v) {
		edges.push_back(v);
	}

	bool insert_exp(Exp exp, int x) {
		exp.follow_terminal = x;
		if (exps.count(exp)) return false;
		exps.insert(exp);
		return true;
	}

	vector<State> make_closure(SL_grammer& grammer) {

		/*
		printf("\n<<<<<< begin state >>>>>>>\n");
		show();
		printf("\n<<<<<< <<<<< >>>>> >>>>>>>\n");
		*/

		vector<Exp> &allexps = grammer.exps;
		set<int> &terminals = grammer.terminals;
		set<int> &nonterminals = grammer.nonterminals;

		vector<State> ret;

		int precount = 0;
		vector<Exp> tmpexps;

		//cout << exps.size() << endl;

		while(exps.size() != precount) {

			//cout << "pre_count : " << precount << endl;
			//cout << "now_count : " << exps.size() << endl;

			precount = exps.size();
			vector< Exp > tmp;
			for (auto exp : exps) {

				// cout << "=========now exp=========" << endl;
				// exp.show();

				int A = exp.left;
				if (exp.pos >= exp.right.size()) continue;
				int B = exp.right[exp.pos];
				int a = exp.follow_terminal;
				int beta;

				if (terminals.count(B)) {
					continue;
				}

				if (exp.pos+1 < exp.right.size())
					beta = exp.right[exp.pos+1];
				else 
					beta = -1;

				// printf("A:%d\nbeta:%d\nB:%d\na:%d\n", A,beta, B, a);

				set<int> fset;
				vector<int> vis(grammer.tot_symbol+1, 0);
				if (beta == -1) {
					grammer.g_first(fset, a, vis);
				}
				else
					grammer.g_first(fset, beta, vis);
				/*
				for (auto ttt : fset) {
					printf("%d, ", ttt);
				}
				printf("\n");
				*/
				for (auto b: fset) {
					for (auto new_exp : allexps) {
						if (new_exp.left == B) {
							new_exp.adjust(0, b);
							tmp.push_back(new_exp);
						}
					}
				}
			}
			for (auto new_exp : tmp) if(!exps.count(new_exp)) {
				// cout << "new exp" << endl;
				// new_exp.show();
				exps.insert(new_exp);
			}
			tmp.clear();
		}

		/*
		printf("\n>>>>>> closure state <<<<<<\n");
		show();
		printf("\n>>>>>> >>>>> <<<<< <<<<<<<<n");
		*/

		// printf("\n#### return state ####\n");

		for (auto symbol : nonterminals) {
			State tmp_state;
			for (auto exp : exps) {
				if (exp.right.size() > exp.pos && exp.right[exp.pos] == symbol) {
					exp.adjust(exp.pos+1, exp.follow_terminal);
					tmp_state.insert_exp(exp, exp.follow_terminal);
				}
			}
			if (tmp_state.exps.size()) {
				// tmp_state.show();
				tmp_state.transitor = symbol;
				ret.push_back(tmp_state);
			}
		}

		for (auto symbol : terminals) {
			State tmp_state;
			for (auto exp : exps) {
				if (exp.right.size() > exp.pos && exp.right[exp.pos] == symbol) {
					exp.adjust(exp.pos+1, exp.follow_terminal);
					tmp_state.insert_exp(exp, exp.follow_terminal);
				}
			}
			if (tmp_state.exps.size()) {
				// tmp_state.show();
				tmp_state.transitor = symbol;
				ret.push_back(tmp_state);
			}
		}

		// printf("\n#### ########### ####\n");

		return ret;
	}
};




#endif