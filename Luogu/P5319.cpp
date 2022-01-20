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

const int N = 1510;
const db inf = 1e9;
const db eps = 1e-7;

int ch[N][12], ndn = 1, n, m, cnt[N], fail[N];
db v[N];
char s[N], t[N];
db al;

void insert() {
	int ls = strlen(s + 1); int p = 1;
	rep(i, 1, ls) {
		int &v = ch[p][s[i] - '0']; if(!v) v = ++ndn;
		p = v;
	} db t = log(in); v[p] += t; chkmax(al, t); cnt[p]++; 
}

void build() {
	queue < int > q; rep(i, 0, 9) ch[0][i] = 1; q.ep(1);
	while(q.size()) {
		int x = q.front(), F = fail[x]; q.pop();
		v[x] += v[F]; cnt[x] += cnt[F];
		rep(i, 0, 9) {
			int &y = ch[x][i];
			if(!y) y = ch[F][i];
			else fail[y] = ch[F][i], q.ep(y);
		}
	}
}

db f[N][N];
int pre1[N][N], pre2[N][N];

void upd(db &x, int &p1, int &p2, db y, int j, int k) { if(x < y) x = y, p1 = j, p2 = k; }

bool check(db mid) {
	rep(i, 1, ndn) f[0][i] = -inf;
	f[0][1] = 0;
	rep(i, 1, n) {
		rep(j, 1, ndn) f[i][j] = -inf, pre1[i][j] = pre2[i][j] = -1;
		rep(j, 1, ndn) if(f[i - 1][j] > -inf) {
			int dn = t[i] == '.' ? 0 : t[i] - '0';
			int up = t[i] == '.' ? 9 : t[i] - '0';
			rep(k, dn, up)
				upd(f[i][ch[j][k]], pre1[i][ch[j][k]], pre2[i][ch[j][k]], f[i - 1][j] + v[ch[j][k]] - cnt[ch[j][k]] * mid, j, k);
		}
	} rep(i, 1, ndn) if(f[n][i] > eps) return true;
	return false;
}

void out() {
	int p = 0;
	rep(i, 1, ndn) if(f[n][i] > eps) p = i;
	//cerr << f[n][p] << endl;
	per(i, n, 1) t[i] = pre2[i][p] + '0', p = pre1[i][p];
	rep(i, 1, n) putchar(t[i]); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; scanf("%s", t + 1); 
	rep(i, 1, m) scanf("%s", s + 1), insert();
	build();
	db L = 0, R = al, res = 0;
	rep(i, 0, 32) {
		db mid = (L + R) / 2;
		if(check(mid)) res = mid, L = mid;
		else R = mid;
	} check(res); out();
	return 0;
}
