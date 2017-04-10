#include <bits/stdc++.h>
#include "SL_grammer.cpp"
#include "SL_table_generator.cpp"
#include "SL_analyser.cpp"
#include "wordsSeperator.cpp"


using namespace std;

int main() {
	SL_grammer grammer;
	SLgenerator generator;
	Analyser analyser;


	grammer.init();
	grammer.read_grammer("../grammer/grammer1.txt");

	printf("read OK\n");
	grammer.show();

	printf("show OK\n");

	
	vector< vector<int> >  sltable = generator.generate(grammer);
	for (int i = 0; i < sltable.size(); i++) {
		for (int j = 0; j < sltable[0].size(); j++) {
			printf("\t%d ", sltable[i][j]);
		}
		printf("\n");
	}

	for (auto psi : grammer.id_of_symbol) {
		cout << psi.first << "---" << psi.second << endl;
	}
	cout << "!!!" << endl;

	Scanner scanner;
	cout << "begin scanner" << endl;
	scanner.init();
	scanner.scan();
	vector< pair<int,string> > tokens = scanner.scan();
	cout << "end scanner" << endl;


	vector<int> tmp;
	for (auto pis : tokens) {
		tmp.push_back(pis.first);
	}

	int out = analyser.analyse(sltable, tmp, grammer, -9999);


	printf("out = %d\n", out);

	return 0;
}

	/*
	

	string str;
	ifstream in("in.txt");
	while(in >> str) {
		vector<int> tokens;
		for (int i = 0; i < str.length(); i++) {
			string tmp = "";
			tmp.push_back(str[i]);
			cout << tmp << " : " << grammer.id_of_symbol[tmp] << endl;
			tokens.push_back(grammer.id_of_symbol[tmp]);
		}

		int out = analyser.analyse(sltable, tokens, grammer, -9999);
		printf("input:\n%s\n", str.c_str());
		printf("output:\n%d\n", out);
	}
	*/