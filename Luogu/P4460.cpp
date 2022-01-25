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

const int N = 1 << 20;
const int mod = 1e8 + 7;

int n, g[25][25], f[N][25];

struct node {
    int x, y;
    node(int _x = 0, int _y = 0) : x(_x), y(_y) { }
    friend node operator - (node a, node b) { return node(a.x - b.x, a.y - b.y); }
    friend ll operator ^ (node a, node b) {
        return 1ll * a.x * b.y - 1ll * a.y * b.x;
    }
} a[30];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
    n = in; rep(i, 0, n - 1) a[i].x = in, a[i].y = in;
    sort(a, a + n, [](auto a, auto b) { return a.x ^ b.x ? a.x < b.x : a.y < b.y; });
    rep(i, 0, n - 1)
        rep(j, i + 1, n - 1)
            if(i ^ j) { 
                rep(k, j + 1, n - 1) if(k ^ i && k ^ j) {
                    if(((a[i] - a[j]) ^ (a[i] - a[k])) == 0) {
                        g[i][k] |= 1 << j;
                    }
                }
            }
    rep(i, 0, n - 1) f[1 << i][i] = 1;
    int U = 1 << n;
    rep(s, 1, U) {
        rep(i, 0, n - 1) if(s >> i & 1) if(f[s][i]) { // lst 
            rep(j, 0, n - 1) if(~s >> j & 1 && (g[min(i, j)][max(i, j)] & ~s) == 0) { //nxt
                (f[s | 1 << j][j] += f[s][i]) %= mod;
            }
        }
    } int ans = 0; rep(s, 1, U) if(__builtin_popcount(s) >= 4) rep(j, 0, n - 1) if(s >> j & 1) (ans += f[s][j]) %= mod;
    printf("%d\n", ans);
	return 0;
}