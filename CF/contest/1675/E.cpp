#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using db = double;
using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n, K;
char s[N];

void solve() {
	n = in, K = in;
	scanf("%s", s + 1);
	int mx = 'a';
	rep(i, 1, n) {
		if(s[i] > mx) {
			int ned = s[i] - mx;
			if(K >= ned) K -= ned, mx = s[i];
			else {
				char goal = s[i] - K, tg = s[i];
				rep(j, 1, n)
					if(s[j] <= mx) s[j] = 'a';
					else if(s[j] >= goal && s[j] <= tg) s[j] = goal;
				printf("%s\n", s + 1);
				return;
			}
		}
	}
	rep(i, 1, n) s[i] = 'a';
	printf("%s\n", s + 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
