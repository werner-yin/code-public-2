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

const int N = 3e5 + 10;

char s[N];
int bel[N], id[N], n, ndn, q, rt, mat[N], res[N], pres[N];

int build(int l, int r) {
	int x = ++ndn; bel[l] = x; bel[r] = x; l++; r--;
	int cid = 0;
	res[x] = 0;
	rep(i, l, r) {
		if(mat[i]) {
			int y = build(i, mat[i]);
			id[y] = ++cid; /*cerr << x << " " << y << " " << id[y] << endl;*/ i = mat[i]; res[x] += res[y]; pres[y] = res[x];
		}
	} res[x] += 1ll * cid * (cid - 1) / 2 + 1; pres[x] = res[x];
	return x;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; q = in;
	scanf("%s", s + 1);
	static int stk[N]; int top = 0;
	rep(i, 1, n) {
		if(s[i] == '(') stk[++top] = i;
		else {
			if(top) {
				int v = stk[top]; top--;
				mat[v] = i; mat[i] = v;
			}
		}
	} 
	int cid = 0; ll tot = 0;
	rep(i, 1, n) {
		if(mat[i]) {
			int y = build(i, mat[i]);
			id[y] = ++cid; i = mat[i]; pres[y] = tot + res[y]; tot = pres[y];
		}
	}
	//rep(i, 1, n) cerr << bel[i] << " ";
	//cerr << endl;
	while(q--) {
		int t = in, l = in, r = in;
		int x = bel[l], y = bel[r];
		ll ans = pres[y] - pres[x] + res[x];
		//cerr << l << " " << r << " " << x << " " << y << " " << id[x] << " " << id[y] << endl;
		ans += 1ll * (id[y] - id[x] + 1) * (id[y] - id[x]) / 2;
		printf("%lld\n", ans);
	}
	return 0;
}
