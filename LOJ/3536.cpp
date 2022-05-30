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

const int N = 2e5 + 10;
constexpr int mod = 998244353;

ll tmp[2][2];
int n, q;

struct mat {
	int a[2][2];
	mat() { memset(a, 0, sizeof a); }
	int *operator [](int x) { return a[x]; }
	const int *operator [](int x) const { return a[x]; }
	friend mat operator * (mat a, mat b) {
		rep(i, 0, 1) rep(j, 0, 1) tmp[i][j] = 0;
		rep(i, 0, 1) rep(j, 0, 1) if(a[i][j]) rep(k, 0, 1) tmp[i][k] += 1ll * a[i][j] * b[j][k];
		mat c; rep(i, 0, 1) rep(j, 0, 1) c[i][j] = tmp[i][j] % mod; return c;
	}
} a[N], tp[2];

char s[N], t[N];

char getc() { char ch = getchar(); while(!isalpha(ch)) ch = getchar(); return ch; }

namespace sub1 {
	pii calc() {
		mat ret; ret[0][0] = 1;
		per(i, n, 1) ret = ret * tp[s[i] == 'E'];
		ret = ret * a[0]; return { ret[0][0], ret[0][1] };
	}
	void solve() {
		a[0][0][0] = a[0][0][1] = a[0][1][1] = 1; auto ans = calc(); printf("%d %d\n", ans.fi, ans.se);
		while(q--) {
			scanf("%s", t + 1);
			if(t[1] == 'A') s[++n] = getc();
			else if(t[1] == 'F') { int l = in, r = in; rep(i, l, r) s[i] = 'W' ^ 'E' ^ s[i]; }
			else { int l = in, r = in; rep(i, l, r) if(i < r + l - i) swap(s[i], s[r + l - i]); else break; }
			auto ans = calc(); printf("%d %d\n", ans.fi, ans.se);
		}
	}
}

struct node {
	mat t[2][2];
	mat *operator [](int x) { return t[x]; }
} val[N], sum[N];

const int V = 1e9 + 7;

mt19937 rnd(random_device{}());
int rt, ndn, revwe[N], rev[N], ch[N][2], u, v, w, siz[N], pri[N];

void revit(int x) { if(!x) return; rev[x] ^= 1; rep(i, 0, 1) swap(sum[x][i][0], sum[x][i][1]), swap(val[x][i][0], val[x][i][1]); }
void revweit(int x) { if(!x) return; revwe[x] ^= 1; rep(i, 0, 1) swap(sum[x][0][i], sum[x][1][i]), swap(val[x][0][i], val[x][1][i]); }
void pd(int x) {
	if(rev[x]) revit(ch[x][0]), revit(ch[x][1]), rev[x] = 0;
	if(revwe[x]) revweit(ch[x][0]), revweit(ch[x][1]), revwe[x] = 0;
}
void pu(int x) {
	rep(i, 0, 1) {
		sum[x][i][0] = sum[ch[x][1]][i][0] * val[x][i][0] * sum[ch[x][0]][i][0];
		sum[x][i][1] = sum[ch[x][0]][i][1] * val[x][i][1] * sum[ch[x][1]][i][1];
	} siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
}

int nd(int op) {
	int x = ++ndn; rep(i, 0, 1) val[x][0][i] = tp[op], val[x][1][i] = tp[op ^ 1];
	pri[x] = rnd() % V; pu(x); return x;
}

void calc() { mat ret; ret[0][0] = 1; ret = ret * sum[rt][0][0] * a[0]; printf("%d %d\n", ret[0][0], ret[0][1]); }

int merge(int x, int y) {
	if(!x || !y) return x | y;
	if(pri[x] < pri[y]) return ch[x][1] = merge(ch[x][1], y), pu(x), x;
	else return ch[y][0] = merge(x, ch[y][0]), pu(y), y;
}

void split(int cur, int k, int &x, int &y) {
	if(!cur) return x = y = 0, void();
	if(siz[ch[cur][0]] + 1 <= k) x = cur, split(ch[cur][1], k - siz[ch[cur][0]] - 1, ch[x][1], y), pu(x);
	else y = cur, split(ch[cur][0], k, x, ch[y][0]), pu(y);
}

int merge(list < int > pot) { int ret = 0; for(auto v : pot) ret = merge(ret, v); return ret; }

namespace sub2 {
	void solve() {
		a[0][0][0] = a[0][0][1] = a[0][1][1] = 1; rep(i, 0, 1) rep(j, 0, 1) rep(k, 0, 1) rep(d, 0, 1) sum[0][i][j][k][d] = k == d;
		rep(i, 1, n) rt = merge(rt, nd(s[i] == 'E'));
		calc();
		while(q--) {
			scanf("%s", t + 1);
			if(t[1] == 'A') rt = merge(rt, nd(getc() == 'E'));
			else {
				int l = in, r = in; split(rt, l - 1, u, v), split(v, r - l + 1, v, w);
				if(t[1] == 'F') revweit(v); else revit(v); rt = merge({ u, v, w }); 
			}
			calc();
		}
	}
}

int main() {
	freopen("code.in", "r", stdin); freopen("code.out", "w", stdout);
	n = in, q = in; scanf("%s", s + 1);
	tp[0][0][0] = tp[0][0][1] = tp[0][1][1] = 1;
	tp[1][0][0] = 2; tp[1][0][1] = mod - 1; tp[1][1][0] = 1;
	if(n <= 2000 && q <= 2000) sub1 :: solve();
	else sub2 :: solve();
	return 0;
}
