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
const ll inf = 1e18;

ll n, p[N], K;
int m;

void solve() {
	n = lin, m = in, K = lin; rep(i, 1, m) p[i] = lin; p[++m] = n; K += m;
	per(i, m, 1) p[i] -= p[i - 1];
	auto calclower = [](ll x) { ll res = 0; rep(i, 1, m) res += p[i] / x; return res; };
	auto calcupper = [](ll x) { ll res = 0; rep(i, 1, m) res += (p[i] + x - 1) / x; return res; };
	ll l = 1, r = n, L0, R0, mid;
	while(l <= r) {
		mid = l + r >> 1;
		if(calclower(mid) >= K) l = mid + 1;
		else r = mid - 1;
	} L0 = r; //assert(calclower(L0 + 1) <= K); assert(calclower(L0) >= K); //cerr << l << " " << calclower(L0) << " " <<calclower(L0 + 1) << " " << K << endl;
	l = 1, r = n;
	while(l <= r) {
		mid = l + r >> 1;
		if(calcupper(mid) <= K) r = mid - 1;
		else l = mid + 1;
	} R0 = l; //assert(calcupper(R0) <= K); //cerr << l << " " << calcupper(R0) << " " << calcupper(R0 - 1) << " " <<  K << endl;
	if(L0 >= R0) return puts("0"), void();
	vector < pair < ll, ll > > pot;
	rep(i, 1, m) {
		ll a = (p[i] + R0 - 1) / R0, b = p[i] / L0;
		if(a <= b) continue; pot.eb(p[i] / a, b ? (p[i] + b - 1) / b : inf);
	} pot.eb(L0, inf); pot.eb(-inf, R0); sort(pot.begin(), pot.end());
	ll pmx = -inf, ans = -inf; rep(i, 0, pot.size() - 2) chkmax(pmx, pot[i].se), chkmax(ans, pot[i + 1].fi - pmx);
	printf("%lld\n", -ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
