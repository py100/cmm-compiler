int min(int x, int y) {
	if (x < y) return x;
	else return y;
}

int main() {
	int a[5], i, j, ret, tmp;

	a[0] = 2;
	a[1] = 4;
	a[2] = 3;
	a[3] = 0;
	a[4] = 1;

	char str[10] = "12345";

	ret = min(a[0], a[1]);

	for (i = 0; i < 5; i++) {
		for (j = i + 1; j < 5; j++) {
			if (a[i] > a[j]) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

	return 0;
}