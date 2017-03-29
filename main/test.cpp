#include <bits/stdc++.h>

using namespace std;


set <int> a, b;



int main() {

	a.insert(1);
	a.insert(2);
	a.insert(3);
	b.insert(1);
	
	b.insert(3);


	cout << (a == b) << endl;


	return 0;
}