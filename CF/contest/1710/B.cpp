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

int n, m, a[N], siz, x[N], p[N], b[N];
veg pot[N];
ll tot[N];
bool ok[N];

void solve() {
	n = in, m = in;
	rep(i, 1, n) {
		x[i] = in, p[i] = in; b[i] = x[i];
		//pot[x[i]].eb(p[i], i);
	}
	sort(b + 1, b + n + 1);
	siz = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) x[i] = lower_bound(b + 1, b + siz + 1, x[i]) - b;
	rep(i, 1, n) pot[x[i]].eb(p[i], i);
	multiset < ll > all; ll ad = 0; ll sum = 0, cnt = 0;
	rep(i, 1, siz) {
		while(all.size() && *all.begin() <= ad + (b[i] - b[i - 1])) cnt--, sum -= *all.begin() - ad, all.erase(all.begin());
		ad += b[i] - b[i - 1], sum -= (b[i] - b[i - 1]) * cnt;
		for(auto v : pot[i]) all.insert(v.fi + ad), sum += v.fi, cnt++;
		tot[i] = sum;
	}
	all.clear(); ad = sum = cnt = 0;
	b[siz + 1] = b[siz];
	per(i, siz, 1) {
		while(all.size() && *all.begin() <= ad + (b[i + 1] - b[i])) cnt--, sum -= *all.begin() - ad, all.erase(all.begin());
		ad += b[i + 1] - b[i], sum -= (b[i + 1] - b[i]) * cnt;
		tot[i] += sum;
		//cerr << i << " " << sum << " " << cnt << endl;
		for(auto v : pot[i]) all.insert(v.fi + ad), sum += v.fi, cnt++;
	}
	//rep(i, 1, siz) cerr << tot[i] << " "; cerr << endl;
	rep(i, 1, n) ok[i] = true;
	ll mx = -1e18;
	rep(i, 1, siz) {
		mx += b[i] - b[i - 1]; if(tot[i] > m) chkmax(mx, tot[i] - m);
		for(auto v : pot[i]) ok[v.se] &= v.fi >= mx;
	}
	mx = -1e18;
	b[siz + 1] = b[siz];
	per(i, siz, 1) {
		mx += b[i + 1] - b[i]; if(tot[i] > m) chkmax(mx, tot[i] - m);
		for(auto v : pot[i]) ok[v.se] &= v.fi >= mx;
	}
	rep(i, 1, n) if(ok[i]) putchar('1'); else putchar('0'); puts("");
	rep(i, 1, n) pot[i].clear();
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
