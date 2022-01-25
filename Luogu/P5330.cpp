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

int P, Q, n, m, id[N], A[N], B[N], tot, bel[N];
bool vis[N], inB[N];
vec s[N];
ll T;

int nxtpos(int x) { return (x + P) % Q; }

ll calc(const vec &t, int id, ll len) {
    if(len == 0) return 0; 
    ll res = 0; 
    auto presum = [&](const int &x) { return x == 0 ? 0 : t[x - 1]; };
    if(len + id - 1 >= t.size()) res = t.back() - presum(id) + t[len + id - 1 - t.size()];
    else res = t[len + id - 1] - presum(id);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	P = in, Q = in, n = in, m = in, T = lin - 1;
    rep(i, 1, n) A[i] = in; rep(i, 1, m) B[i] = in, inB[B[i]] = true;
    rep(i, 0, Q - 1) if(!vis[i]) {
        int x = i; tot++;
        while(!vis[x]) vis[x] = true, bel[x] = tot, id[x] = s[tot].size(), s[tot].eb(inB[x]), x = nxtpos(x);
        int res = 0; for(auto &v : s[tot]) res += v, v = res;
    } ll ans = 0;
    rep(i, 1, n) if(A[i] <= T) {
        int a = A[i] % Q; ll len = (T - A[i]) / P + 1;
        ans += len / s[bel[a]].size() * s[bel[a]].back();
        ans += calc(s[bel[a]], id[a], len % s[bel[a]].size());
    } printf("%lld\n", ans);
	return 0;
}
