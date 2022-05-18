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

const int N = 2e6 + 10;

int n, m, tot;

map < string, int > to[N];
int fa[N], pre[N];
string pstr[N];

int gf(int x) { return x == fa[x] ? x : fa[x] = gf(fa[x]); }

int getp(const string &s) {
	int cur = 1, x = 1; string ret;
	auto getit = [&](int &p) {
		string ret = "";
		while(p < s.size() && s[p] != '/') ret += s[p++];
		return ret;
	};
	while(cur < s.size()) {
		ret = getit(cur);
		if(to[x].count(ret)) x = to[x][ret];
		else to[x][ret] = ++tot, pre[tot] = x, x = tot, pstr[tot] = ret, fa[x] = x;
		x = gf(x), cur++;
	} return x;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cin >> n >> m; tot = 1; fa[tot] = tot;
	rep(i, 1, n) {
		string s, t; cin >> s >> t;
		int x = getp(s), y = getp(t);
		fa[gf(x)] = gf(y);
	}
	rep(i, 1, m) {
		string s; cin >> s;
		int t = getp(s); vector < string > pot; 
		while(t != 1) pot.eb(pstr[t]), t = pre[t];
		reverse(pot.begin(), pot.end());
		for(auto v : pot) cout << "/" << v;
		if(pot.size() == 0) cout << "/"; cout << endl;
	}
	return 0;
}
