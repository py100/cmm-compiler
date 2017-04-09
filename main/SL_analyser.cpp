#include <bits/stdc++.h>
#include "SL_grammer.cpp"
using namespace std;
#ifndef SL_ANALYSER_INC
#define SL_ANALYSER_INC

class Analyser {
public:
	deque< int > stack_state;
	deque< int > stack_symbol;
	int analyse(vector< vector<int> >& table, vector<int>& bf, SL_grammer& grammer, int err) {


		for (int i = 0; i < bf.size(); i++) {
			printf("%d--", bf[i]);
		}
		printf("\n");
		int END = grammer.END;
		printf("END = %d\n", END);
		stack_state.clear();
		stack_symbol.clear();
		stack_state.push_back(0);
		stack_symbol.push_back(END);

		for (int i = 0; i < bf.size(); i++) {
			int sm = stack_state.back();
			int a = bf[i];
			if (table[sm][a] == err) {
				printf("error table (%d, %d, %d)\n", i, sm, a);
				return -1;
			}
			else if (table[sm][a] > 0) {
				stack_state.push_back(table[sm][a]);
				stack_symbol.push_back(a);
			}
			else if (table[sm][a] < 0) {
				// reduce by table[sm][a];
				printf("--reduced by %d--\n", -table[sm][a]);

				int pos = -table[sm][a];
				int len = grammer.exps[pos].right.size();
				int A = grammer.exps[pos].left;

				for (int j = 0; j < len; j++) {
					stack_state.pop_back();
					stack_symbol.pop_back();
				}
				stack_symbol.push_back(A);

				int gt = table[stack_state.back()][A];
				if (gt == err) {
					printf("error goto\n");
					return -1;
				}
				else {
					stack_state.push_back(gt);
				}
				i--;
			}
			else {
				printf("Accpted!!\n");
			}
		}
		return 0;
	}
};


#endif