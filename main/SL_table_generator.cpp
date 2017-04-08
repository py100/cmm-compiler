#include <bits/stdc++.h>
#include "SL_table_class.cpp"

using namespace std;

class SLgenerator {

public:

	void addedge(int u, int v, int transitor, deque< triple > &vt) {
		vt.push_back({u, v, transitor});
	}

	vector< vector<int> > generate(SL_grammer& grammer) {
		const char* _location = "generate";
		int start_pos = -1;
		State start_state = State(0), tmp;
		int tot_state = 0;
		start_state.insert_exp(grammer.start_exp(), grammer.END);
		deque<State> unclosure;
		vector<State> closure;
		//cout << tmp.insert_exp(exps[start_pos], END) << endl;
		
		//start_state.make_closure(grammer);

		map <State, int> closure_state;
		deque< triple > edges;

		deque < pair<State, int> > unclosure_state;

		unclosure_state.push_back({start_state, -1});

		// first calculate all the State
		// then connect all the edges 

		while(!unclosure_state.empty()) {
			// printf("tot_state : %d\n", tot_state);
			State tmp = unclosure_state.front().first;
			int from = unclosure_state.front().second;

			unclosure_state.pop_front();
			vector<State> new_state = tmp.make_closure(grammer);

			if (!closure_state.count(tmp)) {
				addedge(from, tot_state, tmp.transitor, edges);
				for (int i = 0; i < new_state.size(); i++) 
					unclosure_state.push_back({new_state[i], tot_state});
				tmp.state_id = tot_state;
				closure_state[tmp] = tot_state++;
				cout << "\n++++++ new state found! ++++++" <<endl;
				tmp.show();
			}
			else {
				int dest = closure_state[tmp];
				addedge(from, dest, tmp.transitor, edges);
			}
		}

		// printf("tot_state : %d\n", tot_state);
		for (auto exp : start_state.exps) {
			exp.show();
		}
		printf("tot edge = %d\n", edges.size());
		for (auto tp : edges) {
			printf("%d -- %d -- %d\n", tp.a, tp.b, tp.c);
		}
		cout << closure_state.size() << endl;
		cout << grammer.tot_symbol << endl;
		vector< vector<int> > ret(closure_state.size(), vector<int>(grammer.tot_symbol, -9999));

		// principle 1 & 2
		for (int i = 1; i < edges.size(); i++) {
			if (grammer.terminals.count(edges[i].c)) {
				ret[edges[i].a][edges[i].c] = edges[i].b;
			}
			else {
				ret[edges[i].a][edges[i].c] = edges[i].b;
			}
		}

		cout << "principle 1 & 2 ok" << endl;

		// principle 3

		for (auto pstate : closure_state) {
			State state = pstate.first;
			for (auto exp : state.exps) if(exp.pos == exp.right.size()) {
				for (int i = 0; i < grammer.exps.size(); i++) {
					if (exp == grammer.exps[i]) {
						ret[state.state_id][exp.follow_terminal] = -i;
					}
				}
			}
		}

		cout << "principle 3 ok" << endl;

		return ret;
	}

};

int main() {
	SL_grammer grammer;
	SLgenerator generator;
	grammer.init();
	grammer.read_grammer("../grammer/test_grammer_1.txt");
	printf("!!!\n");
	grammer.show();
	
	vector< vector<int> >  sltable = generator.generate(grammer);	

	printf("!!!\n");

	for (int i = 0; i < sltable.size(); i++) {
		for (int j = 0; j < sltable[0].size(); j++) {
			printf("\t%d ", sltable[i][j]);
		}
		printf("\n");
	}

	return 0;
}
