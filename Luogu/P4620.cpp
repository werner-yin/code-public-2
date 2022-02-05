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

const int N = 1e7 + 10;

unsigned int SA, SB, SC; int p, A, B;
int n, k, m, a[N], b[N], dep[N];
ll f[2050][210], g[2050][210], s1[2050][210], s2[2050], s3[N];

unsigned int rng61(){
    SA ^= SA << 16, SA ^= SA >> 5, SA ^= SA << 1;
    unsigned int t = SA; SA = SB; SB = SC; SC ^= t ^ SA;
    return SC;
}
void gen(){
    scanf("%d%d%d%d%u%u%u%d%d", &n, &k, &m, &p, &SA, &SB, &SC, &A, &B);
    for(int i = 1; i <= p; i++)scanf("%d%d", &a[i], &b[i]), a[i] %= m;
    for(int i = p + 1; i <= n; i++){
        a[i] = rng61() % A + 1; a[i] %= m;
        b[i] = rng61() % B + 1;
    }
}

int getpos(int x) {
	while(dep[x] > k + 1) x /= 1 << (k + 1); 
	return x;
}

void solve() {
	gen(); rep(i, 1, n) dep[i] = dep[i >> 1] + 1;
	rep(i, 1, 1 << (k + 1)) {
		rep(j, 0, m) s1[i][j] = s2[i] = s3[i] = 0, f[i][j] = g[i][j] = 1e18;
	}
	rep(i, 1, n) {
		int v = getpos(i);
		if(a[i]) s1[v][a[i] - 1] += 1ll * m * b[i];
		s2[v] += b[i]; s3[v] += 1ll * a[i] * b[i];
	}
	rep(i, 1, (1 << k + 1) - 1) {
		per(j, m - 1, 0) {
			s1[i][j] += s1[i][j + 1];
			f[i][j] = -s3[i] + 1ll * s2[i] * j + s1[i][j];
		}
	}
	rep(i, (1 << k), (1 << k + 1) - 1) 
		rep(j, 0, m - 1) g[i][j] = f[i][j];
	per(i, (1 << k) - 1, 1) 
		rep(j, 0, m - 1) {
			g[i][j] = 1e18;
			rep(k, 0, m - 1) 
				chkmin(g[i][j], g[i << 1][(j - k + m) % m] + g[i << 1 | 1][(j - k + m) % m] + f[i][k]); 
		}
	printf("%lld\n", g[1][0]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
