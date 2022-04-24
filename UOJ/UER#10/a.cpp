#include <bits/stdc++.h>

using namespace std;

long double t1, t2, a;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%Lf", &a); a /= 1000000;
		t1 += 1. * (1 - a) / (n - a);
		t2 += 1. * (n - 1) / n / (n - a);
	} printf("%.14Lf\n", t2 / (1 - t1));
}
