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

int p, fac[N], cnt, pt, a, b, tt, ind[N];
bool vis[N];
int id[N], tid[N], tot, tvis[N], vvis[N];
vec pot;

ll qp(ll x, int t, int mod) { ll ret = 1; for(; t; t >>= 1, x = x * x % mod) if(t & 1) ret = ret * x % mod; return ret; }
bool check(int x) { rep(i, 1, cnt) if(qp(x, (p - 1) / fac[i], p) == 1) return false; return true; }

void dfs(int x, int fl) {
	pot.eb(x); tvis[tid[x]] = true; vvis[x] = true;
	int t = fl ? a : p - 1 - a;
	if(!vvis[(x + t) % (p - 1)] && !tvis[tid[(x + b) % (p - 1)]]) dfs((x + b) % (p - 1), fl ^ 1);
	if(!vvis[(x + t) % (p - 1)]) dfs((x + t) % (p - 1), fl);
}

void factor(int x) {
	rep(i, 2, x) {
		if(i * i > x) break; if(x % i) continue;
		fac[++cnt] = i; while(x % i == 0) x /= i;
	} if(x > 1) fac[++cnt] = x;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	p = in, a = in, b = in; factor(p - 1);
	if(p == 2) return puts("Yes"), puts("1 1"), 0;
	rep(i, 1, p - 1) if(check(i)) { pt = i; break; } assert(pt);
	int cur = 1; while(!vis[cur]) id[cur] = tt++, ind[tt - 1] = cur, vis[cur] = true, cur = 1ll * cur * pt % p;
	//cerr << "!" << pt << " " << tt << endl;
	a = id[a], b = id[b];
	if(__gcd(__gcd(a, b), p - 1) != 1) return cout << "No" << endl, 0;
	if(a < b) swap(a, b); // assume a >= b
	rep(i, 0, p - 2) {
		int cur = i; ++tot;
		while(!tid[cur]) tid[cur] = tot, cur = (cur + a) % (p - 1);
	}
	dfs(0, 1); pot.eb(0); //assert(pot.size() == p);
	puts("Yes"); for(auto v : pot) printf("%d ", ind[v]); puts("");
	return 0;
}
