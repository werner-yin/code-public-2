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

int n, id[N];
ll ret[N];
vec tpot[N];

int main() {
#ifdef YJR_2333_TEST
	//freopen("1.in", "r", stdin);
#endif
	cin >> n; vec pot; rep(i, 1, 1 << 13) if(__builtin_popcount(i) == 6) pot.eb(i);
	rep(i, 1, n) {
		id[i] = pot.back(), pot.pop_back();
		rep(j, 0, 12) if(id[i] >> j & 1) tpot[j].eb(i);
	}
	rep(j, 0, 12) {
		if(!tpot[j].size()) continue; cout << "? " << tpot[j].size();
		for(auto v : tpot[j]) cout << " " << v; cout << endl;
		cin >> ret[j];
	}
	cout << "!";
	rep(i, 1, n) {
		ll ans = 0;
		rep(j, 0, 12) if(~id[i] >> j & 1) ans |= ret[j];
		cout << " " <<ans;
	} cout << endl;
	return 0;
}
