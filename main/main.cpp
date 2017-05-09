#include <bits/stdc++.h>
#include "SL_grammer.cpp"
#include "SL_table_generator.cpp"
#include "SL_analyser.cpp"
#include "wordsSeperator.cpp"

using namespace std;

int main() {
	freopen("out.log", "w", stdout);
  //FILE *fp = fopen("table.txt", "w");
  FILE *fin = fopen("table.txt.tmp", "r");
	SL_grammer grammer;
	SLgenerator generator;
	Analyser analyser;

	grammer.init();
	grammer.read_grammer("../grammer/grammer2.txt");

	printf("read OK\n");
	grammer.show();
	printf("show OK\n");
  
  int n, m;
  fscanf(fin, "%d%d", &n, &m);
  vector< vector<int> > sltable(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      fscanf(fin, "%d", &sltable[i][j]);
    }
  }
  /*
   * below generate sltable, pregenerate
   *
   */
  /*
	vector< vector<int> >  sltable = generator.generate(grammer);
  fprintf(fp, "%d %d\n", sltable.size(), sltable[0].size());
	for (int i = 0; i < sltable.size(); i++) {
		for (int j = 0; j < sltable[0].size(); j++) {
			fprintf(fp, "\t%d ", sltable[i][j]);
		}
		fprintf(fp, "\n");
	}
	for (auto psi : grammer.id_of_symbol) {
		cout << psi.first << "---" << psi.second << endl;
	}
	cout << "!!!" << endl;
  */

	Scanner scanner;
	cout << "begin scanner" << endl;
	scanner.init();
	scanner.scan();
	vector< pair<int,string> > tokens = scanner.scan();
	cout << "end scanner" << endl;

	vector<int> tmp;
	for (auto pis : tokens) {
		tmp.push_back(pis.first);
		fprintf(stderr, "%s ", grammer.getstr(pis.first).c_str());
	}

	fprintf(stderr, "\n");
  analyser.init();
	int out = analyser.analyse(sltable, tokens, grammer, -9999);
	cerr << "out = " << out << endl;
	return 0;
}

