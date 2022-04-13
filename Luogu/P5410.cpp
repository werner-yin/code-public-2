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

const int N = 2e7 + 10;

char s[N << 1], t[N];
int ls, lt, z[N << 1], n;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", t + 1); scanf("%s", s + 1); ls = strlen(s + 1), lt = strlen(t + 1);
	s[ls + 1] = '#'; rep(i, ls + 1, ls + lt) s[i + 1] = t[i - ls];
	int pos = 0, r = 0; n = ls + lt + 1;
	ll ans1 = 0, ans2 = 0;
	rep(i, 2, n) {
		if(i <= r) z[i] = min(r - i + 1, z[i - pos + 1]);
		while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
		if(i + z[i] - 1 >= r) r = i + z[i] - 1, pos = i;
	} 
	z[1] = ls; // notice.
	rep(i, 1, n) {
		if(i <= ls) ans1 ^= 1ll * i * (z[i] + 1);
		else if(i > ls + 1) ans2 ^= 1ll * (i - ls - 1) * (z[i] + 1);
		//cerr << z[i] << " " ;
	}
	printf("%lld\n%lld\n", ans1, ans2); return 0;
}
