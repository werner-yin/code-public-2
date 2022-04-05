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

veg tg[N];
int a[N], b[N], n, K;
set < tuple < int, int, int > > s;

void ins(int xl, int xr, int id) {
	auto it = s.lower_bound({ xl, 0, 0 });
	if(it != s.begin()) {
		it--; auto v = *it;
		if(get<1>(v) > xl) {
			s.ep(get<0>(v), xl, get<2>(v)); s.ep(xl, get<1>(v), get<2>(v));
			s.erase(it);
		}
	}
	it = s.lower_bound({ xr, 0, 0 });
	if(it != s.begin()) {
		it--; auto v = *it;
		if(get<1>(v) > xr) {
			s.ep(get<0>(v), xr, get<2>(v)); s.ep(xr, get<1>(v), get<2>(v));
			s.erase(it);
		}
	}
	it = s.lower_bound({ xl, 0, 0 }); int lst = xl;
	while(it != s.end() && get<1>(*it) <= xr) {
		auto v = *it;
		if(get<0>(v) != lst) tg[id].eb(1, get<0>(v) - lst);
		tg[id].eb(get<2>(v) + 1, get<1>(v) - get<0>(v));
		lst = get<1>(v); s.erase(it++);
	} if(lst != xr) tg[id].eb(1, xr - lst); s.ep(xl, xr, id);
	return;
	for(auto v : tg[id]) cerr << v.fi << " " << v.se << endl;
	cerr << endl;
	for(auto v : s) {
		cerr << get<0>(v) << " " << get<1>(v) << " " << get<2>(v) << endl;
	} cerr << endl;
}

int val[N];

ll calc(int lim, int op = 0) {
	int top = 1; ll tot = 0;
	rep(i, 0, n) val[i] = 0;
	rep(i, 1, n) {
		for(auto v : tg[i]) {
			if(op && v.fi < top) tot += 1ll * v.se * (top - v.fi) * (n - i + 1);
			chkmax(v.fi, top);
			val[v.fi] += v.se; val[i + 1] -= v.se;
		}
		while(top <= i && val[top] >= lim) val[top + 1] += val[top], (op && (tot += 1ll * val[top] * (n - i + 1))), top++;
		if(!op) tot += top - 1;
		//if(lim == 5) cerr << lim << " " << i << " " << top << " " << tot << endl;
	} return tot;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 1, n) a[i] = in, b[i] = in, ins(a[i], b[i], i);
	int l = 0, r = 1e9;
	while(l <= r) {
		int mid = l + r >> 1;
		if(calc(mid) > K) l = mid + 1;
		else r = mid - 1;
	} ll ans = calc(r + 1, 1) + 1ll * r * (K - calc(r + 1)); printf("%lld\n", ans);
	return 0;
}
