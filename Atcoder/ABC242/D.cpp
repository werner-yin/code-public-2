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

char s[N];
int Q, n;
ll t, k;

char get(char cur, ll lef, ll ldep) {
	assert(lef > 0);
	if(ldep == 0) return assert(lef == 1), cur;
	string t;
	if(cur == 'A') t = "BC";
	else if(cur == 'B') t = "CA";
	else t = "AB";
	assert(lef <= (1ll << ldep) && lef > 0);
	for(auto c : t)
		if(c != cur) {
			if(lef <= (1ll << ldep - 1)) return get(c, lef, ldep - 1);
			else lef -= 1ll << (ldep - 1);
		}
	return 'd';
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); Q = in;
	while(Q--) {
		t = lin, k = lin; int p = 1;
		ll dt = max(0ll, t - 61) % 3; t = min(t, 61ll);
		p = (k - 1) / (1ll << t) + 1, k -= (p - 1) * (1ll << t);
		//	cerr << p << " " << k << endl;
		printf("%c\n", get((s[p] - 'A'+ dt) % 3 + 'A', k, t));
	}
	return 0;
}
