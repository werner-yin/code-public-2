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
using pii = pair < ll, ll >;
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

ll B, K, sx, sy, gx, gy;

ll dis(pii a, pii b) { return abs(a.fi - b.fi) + abs(a.se - b.se); }

void solve() {
	B = in, K = in;
	sx = in, sy = in, gx = in, gy = in;
	vector < tuple < ll, ll, ll > > pot, gpot;
	rep(i, 0, 1)
		rep(j, 0, 1) {
		ll tx = sx / B + i, ty = sy / B + j, ret = 0;
		tx *= B, ty *= B;
		ret = dis({ tx, ty }, { sx, sy }) * K;
		chkmin(ret, dis({ tx, ty }, { sx, ty }) + dis({ sx, sy }, { sx, ty }) * K);
		chkmin(ret, dis({ tx, ty }, { tx, sy }) + dis({ sx, sy }, { tx, sy }) * K);
		//if(i == 2) tx = sx; if(j == 2) ty = sy;
		//if(i == 2 && j == 2) continue;
		//		cerr << tx << " " << ty << endl;
		pot.eb(tx, ty, ret);
	}
	rep(i, 0, 1)
		rep(j, 0, 1) {
		ll tx = gx / B + i, ty = gy / B + j, ret = 0;
		tx *= B, ty *= B;
		ret = dis({ tx, ty }, { gx, gy }) * K;
		chkmin(ret, dis({ tx, ty }, { gx, ty }) + dis({ gx, gy }, { gx, ty }) * K);
		chkmin(ret, dis({ tx, ty }, { tx, gy }) + dis({ gx, gy }, { tx, gy }) * K);
		//if(i == 2) tx = gx; if(j == 2) ty = gy;
		//if(i == 2 && j == 2) continue;
		//		cerr << "!" << tx << " " << ty << endl;
		gpot.eb(tx, ty, ret);
	}
	ll ans = 1e18;
	for(auto x : pot)
		for(auto y : gpot)
			chkmin(ans, dis({ get<0>(x), get<1>(x) }, { get<0>(y), get<1>(y) }) + get<2>(x) + get<2>(y));
	chkmin(ans, dis({ sx, sy }, { gx, gy }) * K);
	pot.clear(), gpot.clear();
	rep(i, 0, 2)
		rep(j, 0, 2) {
		ll tx = sx / B + i, ty = sy / B + j;
		tx *= B, ty *= B;
		if(i == 2) tx = sx; if(j == 2) ty = sy;
		if(i == 2 && j == 2) continue;
		//		cerr << tx << " " << ty << endl;
		pot.eb(tx, ty, dis({ tx, ty }, { sx, sy }) * K);
	}
	rep(i, 0, 2)
		rep(j, 0, 2) {
		ll tx = gx / B + i, ty = gy / B + j;
		tx *= B, ty *= B;
		if(i == 2) tx = gx; if(j == 2) ty = gy;
		if(i == 2 && j == 2) continue;
		//		cerr << "!" << tx << " " << ty << endl;
		gpot.eb(tx, ty, dis({ tx, ty }, { gx, gy }) * K);
	}
	for(auto x : pot)
		for(auto y : gpot)
			if((get<0>(x) % B == 0 && get<0>(x) == get<0>(y)) || (get<1>(x) % B == 0 && get<1>(x) == get<1>(y)))
				chkmin(ans, dis({ get<0>(x), get<1>(x) }, { get<0>(y), get<1>(y) }) + get<2>(x) + get<2>(y));
	printf("%lld\n", ans);
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
