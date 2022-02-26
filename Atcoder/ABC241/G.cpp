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

const int N = 50 + 10;

int u[N * N], v[N * N], win[N];
bool hav[N][N];
int n, m;
veg pot;
int twin[N];

mt19937 rnd(time(NULL));

bool check(int x) {
	rep(i, 1, n) twin[i] = win[i];
	veg tp;
	for(auto v : pot) {
		if(v.fi == x || v.se == x) twin[x]++;
		else tp.eb(v);
	} shuffle(tp.begin(), tp.end(), default_random_engine(rnd()));
	while(tp.size()) {
		pii mx = tp.front();
		for(auto &v : tp)
			if(max(twin[v.fi], twin[v.se]) > max(twin[mx.fi], twin[mx.se])) mx = v;
		if(twin[mx.fi] <= twin[mx.se]) twin[mx.fi]++;
		else twin[mx.se]++;
		auto it = tp.begin();
		while(it != tp.end()) {
			if(*it == mx) { tp.erase(it); break; }
			it++;
		}
	} rep(i, 1, n) if(twin[i] >= twin[x] && i != x) return 0;
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, m) u[i] = in, v[i] = in, hav[u[i]][v[i]] = hav[v[i]][u[i]] = true, win[u[i]]++;
	rep(i, 1, n) rep(j, i + 1, n) if(!hav[i][j]) pot.eb(i, j);
	rep(i, 1, n) if(check(i)) printf("%d ", i); puts("");
	return 0;
}
