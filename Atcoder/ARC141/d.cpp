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

int n, m, a[N], mx[N], mn[N];
vec pot[N];

void GG() { while(n--) puts("No"); cerr << "!" << endl; exit(0); }
void ensure(bool condi) { if(!condi) GG(); }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in, pot[a[i] >> __builtin_ctz(a[i])].eb(__builtin_ctz(a[i]));
	rep(i, 1, m << 1) if(i & 1) ensure(pot[i].size()), sort(pot[i].begin(), pot[i].end());
	rep(i, 1, m << 1) mx[i] = 0x3f3f3f3f, mn[i] = 0x80808080;
	per(i, m << 1, 1) if(i & 1) {
		for(int j = i + i; j <= m << 1; j += i) chkmax(mn[i], mn[j]);
		if(mn[i] >= pot[i].back()) GG();
		mn[i] = *upper_bound(pot[i].begin(), pot[i].end(), mn[i]);
	} rep(i, 1, m << 1) mx[i] = 0x3f3f3f3f;
	rep(i, 1, m << 1) if(i & 1) {
		if(mx[i] <= pot[i].front()) GG();
		mx[i] = *--lower_bound(pot[i].begin(), pot[i].end(), mx[i]);
		for(int j = i + i; j <= m << 1; j += i) chkmin(mx[j], mx[i]);
	}
	rep(i, 1, n) { int v = __builtin_ctz(a[i]), t = a[i] >> v; if(v >= mn[t] && v <= mx[t]) puts("Yes"); else puts("No"); }
	return 0;
}
