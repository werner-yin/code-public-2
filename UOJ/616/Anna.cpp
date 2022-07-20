#include "Anna.h"
#include <bits/stdc++.h>
#include <vector>

#define eb emplace_back

#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;

const int B = 63;
const int T = 43;

ll fib[B + 10];

void Anna(int N, std::vector<char> S) {
	fib[0] = fib[1] = 1; rep(i, 2, B) fib[i] = fib[i - 1] + fib[i - 2];
	//cerr << fib[B] << " " << (1ll << T) << endl;
	int firstx = N; rep(i, 0, N - 1) if(S[i] == 'X') { firstx = i; break; }
	rep(i, 0, 18) Send(firstx >> i & 1);
	for(int l = 0, r; l < N; l = r + 1) {
		r = min(l + B - 1, N - 1);
		vector < int > pot;
		rep(i, l, r) {
			if(S[i] == 'Z' && pot.size() && pot.back() == 1) pot.back() = 0;
			pot.eb(S[i] == 'Z');
		}
		ll ret = 0;
		rep(i, 0, (int)pot.size() - 1)
			if(pot[i]) ret += fib[i + 1];
		rep(j, 0, T) Send(ret >> j & 1ll);
	}
}
