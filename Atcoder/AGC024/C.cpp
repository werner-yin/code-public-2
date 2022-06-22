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

int n, a[N];
ll ans;

bool solve(vec pot) {
	//for(auto v : pot) cerr << v << " "; cerr << endl;
	int lpos = pot.size();
	per(j, (int)pot.size() - 1, 0) {
		if(pot[j] > j) return 0;
		if(j + 1 < pot.size() && pot[j + 1] == pot[j] + 1) continue;
		if(j - pot[j] > lpos) return 0;
		ans += pot[j]; lpos = j - pot[j];
	} return true;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in;
	rep(i, 1, n) {
		if(a[i] != 0) return puts("-1"), 0;
		vec pot; int j = i + 1; pot.eb(0);
		while(a[j] && j <= n) pot.eb(a[j++]);
		if(!solve(pot)) return puts("-1"), 0; i = j - 1;
	} cout << ans << endl;
	return 0;
}
