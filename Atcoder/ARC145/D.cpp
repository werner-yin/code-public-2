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

const int L = 0000;
const int R = 10005;

int n;
ll m;

mt19937 rnd(random_device{}());

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = lin;
	if(n == 1) return cout << m << endl, 0;
	vec pot;
	/*
	rep(i, 1, n) {
		if(i & 1) pot.eb(R);
		else pot.eb(R - (rnd() % R));
	}
	*/
	int cur = -1e7;
	unordered_map < int, bool > ban;
	rep(i, 1, n) {
		while(ban[cur]) cur++;
		for(auto v : pot) ban[cur * 2 - v] = true;
		pot.eb(cur); cur++;
		//cerr << i << " " << cur << endl;
	}
	/*
	//rep(i, 1, n) pot.eb(rnd() % R + 1);
	rep(i, 0, pot.size() - 1) {
		ll tot1 = 0;
		rep(j, i, pot.size() - 1) {
			tot1 += pot[j]; ll tot2 = 0;
			rep(k, j + 1, pot.size() - 1) {
				tot2 += pot[k];
				if(tot1 == tot2) cerr << "!" << " " << tot1 << " " << tot2 << endl;
			} 
		}
	}
	*/
	ll ret = 0;
	for(auto v : pot) ret += v;
	cerr << ret << endl;
	ret = m - ret;
	ll dt = ret / n, vret = ret % n + ret / n;
	ll dback = min(10000000ll - pot.back(), ret) + pot.back();
	while((ret - dback + pot.back()) % (n - 1) != 0) dback--;
	dt = (ret - dback + pot.back()) / (n - 1);
	for(auto &v : pot) v += dt;
	pot.back() = dback;
	for(auto v : pot) printf("%d ", v); puts("");
	ret = 0; for(auto v : pot) ret += v; cerr << ret << " " << m << endl;
	assert(ret == m);
	return 0;
}
