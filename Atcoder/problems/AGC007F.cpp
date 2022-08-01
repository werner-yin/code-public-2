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

int n, segpos[N];
char s[N], t[N];
vec pot[30], ps;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1), scanf("%s", t + 1);
	bool fl = 1;
	rep(i, 1, n) fl &= s[i] == t[i];
	if(fl) return cout << 0 << endl, 0;
	if(s[1] != t[1]) return cout << -1 << endl, 0;
	rep(i, 1, n) pot[s[i] - 'a'].eb(i);
	rep(i, 1, n)
		if(t[i] == t[i - 1]) segpos[i] = segpos[i - 1];
		else ps.eb(i), segpos[i] = segpos[i - 1] + 1;
	int ans = 0, ret = n + 1;
	veg tpot;
	per(j, (int)ps.size() - 1, 0) {
		chkmin(ret, ps[j]); int p = ps[j];
		while(pot[t[p] - 'a'].size() && pot[t[p] - 'a'].back() > ret) pot[t[p] - 'a'].pop_back();
		if(!pot[t[p] - 'a'].size()) return puts("-1"), 0;
		//chkmax(ans, j + 1 - segpos[pot[t[p] - 'a'].back()]);
		//chkmax(ans, pot[t[p] - 'a'].back());
		tpot.eb(p, pot[t[p] - 'a'].back());
		chkmin(ret, pot[t[p] - 'a'].back());
		pot[t[p] - 'a'].pop_back();
	} reverse(tpot.begin(), tpot.end());
	rep(i, 0, tpot.size() - 1) {
		auto v = tpot[i];
		if(v.fi == v.se) continue;
		while(tpot[i - ans].fi + ans > v.se) ans++;
	}
	cout << ans + 1 << endl;
	return 0;
}
