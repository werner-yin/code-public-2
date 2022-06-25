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

int n, m;
char s[N], t[N];

namespace ACAM {
	int ch[N][26], fail[N], ndn = 1, len[N];
	void ins(char *s, int n) {
		int p = 1;
		rep(i, 1, n) {
			int x = s[i] - 'a';
			if(!ch[p][x]) ch[p][x] = ++ndn, len[ch[p][x]] = i;
			p = ch[p][x];
		}
	}
	void build() {
		rep(i, 0, 25) ch[0][i] = 1;
		queue < int > q; q.ep(1);
		while(q.size()) {
			int x = q.front(); q.pop(); int F = fail[x];
			rep(j, 0, 25) {
				if(!ch[x][j]) ch[x][j] = ch[F][j];
				else fail[ch[x][j]] = ch[F][j], q.ep(ch[x][j]);
			}
		}
	}
}

using namespace ACAM;

int f[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); scanf("%s", t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	ins(s, n); build(); int cur = 1;
	rep(i, 1, m) {
		cur = ch[cur][t[i] - 'a'];
		if(cur == 1) return puts("-1"), 0;
		f[i] = f[i - len[cur]] + 1;
	} cout << f[m] << endl;
	return 0;
}
