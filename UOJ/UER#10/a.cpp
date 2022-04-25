#include <bits/stdc++.h>

using namespace std;

double t1, t2, a, tot;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lf", &a); a /= 1000000;
		tot += a / (n - a);
	} tot = 1. / n + 1 / tot; printf("%.14lf\n", tot);
}
