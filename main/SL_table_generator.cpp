#include <bits/stdc++.h>
#include "SL_table_class.cpp"

using namespace std;

class SLgenerator {

public:

	void generate(SL_grammer& grammer) {
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
		deque <State> unclosure_state;

		unclosure_state.push_back(start_state);

		// first calculate all the State
		// then connect all the edges 

		while(!unclosure_state.empty()) {
			// printf("tot_state : %d\n", tot_state);
			State tmp = unclosure_state.front();
			unclosure_state.pop_front();
			vector<State> new_state = tmp.make_closure(grammer);

			if (!closure_state.count(tmp)) {
				for (int i = 0; i < new_state.size(); i++) 
					unclosure_state.push_back(new_state[i]);
				tmp.state_id = tot_state;
				closure_state[tmp] = tot_state++;
				cout << "\n++++++ new state found! ++++++" <<endl;
				tmp.show();
			}

		}


		// printf("tot_state : %d\n", tot_state);
		for (auto exp : start_state.exps) {
			exp.show();
		}
		return ;
	}
};

int main() {
	SL_grammer grammer;
	SLgenerator generator;
	grammer.init();
	grammer.read_grammer("../grammer/test_grammer_1.txt");
	printf("!!!\n");
	grammer.show();

	generator.generate(grammer);
	printf("!!!\n");
	return 0;
}
