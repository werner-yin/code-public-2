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

int K, a[N], n;
int ch[N * 32][2], ndn = 1, label[N * 32];

void ins(int x, int id) {
	int p = 1; label[p] = id;
	per(i, 30, 0) {
		int &v = ch[p][x >> i & 1];
		if(!v) v = ++ndn;
		p = v; label[p] = id;
	}
}

vec vdfs(int x, int y, int d) {
	if(!x && !y) return vec();
	if(!x) return { label[y] };
	if(!y) return { label[x] };
	if(d == -1) return { label[x], label[y] };
	if(K >> d & 1) {
		vec res1 = vdfs(ch[x][0], ch[y][1], d - 1);
		vec res2 = vdfs(ch[x][1], ch[y][0], d - 1);
		return res1.size() > res2.size() ? res1 : res2;
	} else {
		if(ch[x][0] && ch[y][1]) return { label[ch[x][0]], label[ch[y][1]] };
		if(ch[x][1] && ch[y][0]) return { label[ch[x][1]], label[ch[y][0]] };
		vec res1 = vdfs(ch[x][0], ch[y][0], d - 1);
		vec res2 = vdfs(ch[x][1], ch[y][1], d - 1);
		return res1.size() > res2.size() ? res1 : res2;
	}
}

vec solve(int x, int d) {
	if(!x || !label[x]) return vec();
	if(d == -1) return vec(1, label[x]);
	if(K >> d & 1) {
		vec res = vdfs(ch[x][0], ch[x][1], d - 1);
		return res;
	} else {
		vec a = solve(ch[x][0], d - 1), b = solve(ch[x][1], d - 1);
		for(auto v : b) a.eb(v);
		return a;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in;
	if(K == 0) {
		printf("%d\n", n);
		rep(i, 1, n) printf("%d ", i);
		puts("");
		return 0;
	}
	rep(i, 1, n) a[i] = in, ins(a[i], i);
	vec ans = solve(1, 30);
	if(ans.size() < 2) return puts("-1"), 0;
	printf("%lu\n", ans.size()); sort(ans.begin(), ans.end());
	for(auto v : ans) assert(v != 0), printf("%d ", v);
	puts("");
	return 0;
}
