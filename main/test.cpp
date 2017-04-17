#include <bits/stdc++.h>
#include "SL_grammer.cpp"
#include "SL_table_generator.cpp"
#include "SL_analyser.cpp"
#include "wordsSeperator.cpp"


using namespace std;

int main() {

	//freopen("out.log", "w", stdout);

	SLgenerator generator;
	Analyser analyser;

	Scanner scanner;
	cout << "begin scanner" << endl;
	scanner.init();
	scanner.scan();
	vector< pair<int,string> > tokens = scanner.scan();
	cout << "end scanner" << endl;


	return 0;
}
