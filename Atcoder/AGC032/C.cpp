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

int n, m, cnt, id[N];
veg G[N];
bool vis[N];
vec pot;
bool hav[N];

void dfs(int x) {
	while(G[x].size()) {
		int y = G[x].back().fi, id = G[x].back().se;
		G[x].pop_back();
		if(!vis[id]) {
			vis[id] = true; dfs(y);
		}
	} pot.eb(x);
}

veg lG[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) { int a = in, b = in; G[a].eb(b, i), G[b].eb(a, i); }
	rep(i, 1, n) if(G[i].size() & 1) return puts("No"), 0;
	rep(i, 1, n) lG[i] = G[i];
	//rep(i, 1, n) shuffle(G[i].begin(), G[i].end(), rnd);
	auto solveonce = [&]() {
						 rep(i, 1, n) G[i] = lG[i], hav[i] = 0; pot.clear();
						 rep(i, 1, m) vis[i] = 0;
						 rep(i, 1, n) if(G[id[i]].size()) ++cnt, dfs(id[i]);
						 int vnt = 0; reverse(pot.begin(), pot.end());
						 vec cur;
						 rep(i, 0, (int)pot.size() - 1) {
							 int x = pot[i]; 
							 if(hav[x]) {
								 vnt++;
								 while(cur.back() != x) hav[cur.back()] = 0, cur.pop_back();
							 } else hav[x] = true, cur.eb(x);
						 }
						 cerr << cnt << " " << vnt << endl;
						 if(cnt <= 3 && vnt >= 3) { cout << "Yes" << endl, exit(0); }
					 };
	rep(i, 1, n) id[i] = i;
	sort(id + 1, id + n + 1, [&](int x, int y) { return G[x].size() > G[y].size(); });
	solveonce();
	rep(i, 1, n) id[i] = i;
	solveonce();
	cout << "No"  << endl;
	return 0;
}
