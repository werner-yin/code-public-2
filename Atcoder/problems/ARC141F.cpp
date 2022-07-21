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

int n, pos[N];
vector < char > ts[N];
vec ps[N];
char s[N << 1];

namespace ACAM {
	const int N = 2e6 + 10;
	int ch[N][4], ndn = 1, ed[N], fail[N], sz[N], dfn[N], R[N], tim, tpos[N], dep[N];
	vec G[N];
	void insert(char *s, int l, int id) {
		int p = 1;
		rep(i, 1, l) {
			int x = s[i] - 'A'; if(!ch[p][x]) ch[p][x] = ++ndn, dep[ch[p][x]] = dep[p] + 1;
			p = ch[p][x]; ps[id].eb(p);
		} ed[p] = id, pos[id] = p;
	}
	void build() {
		rep(i, 0, 3) ch[0][i] = 1; queue < int > q; q.ep(1);
		while(q.size()) {
			int x = q.front(), F = fail[x]; q.pop(); G[F].eb(x); if(!ed[x]) ed[x] = ed[F];
			rep(j, 0, 3)
				if(!ch[x][j]) ch[x][j] = ch[F][j];
				else fail[ch[x][j]] = ch[F][j], q.ep(ch[x][j]);
		}
	}
	bool intree(int x, int y) { return dfn[x] <= dfn[y] && dfn[y] <= R[x]; }
	void dfs(int x) {
		dfn[x] = ++tim;
		for(auto y : G[x]) dfs(y);
		R[x] = tim;
	}
}

int stk[N << 1], top;
bool ban[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) {
		scanf("%s", s + 1); int l = strlen(s + 1);
		rep(j, 1, l) ts[i].eb(s[j]); ACAM :: insert(s, l, i);
	} ACAM :: build();
	rep(i, 1, n) {
		stk[top = 0] = 1; int len = 0;
		for(auto v : ts[i]) {
			int ret = ACAM :: ch[stk[top]][v - 'A']; stk[++top] = ret;
			if(ACAM :: ed[ret] && ACAM :: ed[ret] != i) len += ts[ACAM :: ed[ret]].size(), top -= ts[ACAM :: ed[ret]].size();
		}
		if(len == 0) {
			for(auto v : ps[i]) ACAM :: tpos[v] = pos[i], ACAM :: sz[v]++;
		} else if(len == ts[i].size()) ban[i] = true;
		else return puts("Yes"), 0;
		//cerr << "!" << ban[i] << " " << len << endl;
	}
	ACAM :: dfs(1);
	rep(i, 1, n) if(!ban[i]) {
		//cerr << "!" << i << " " << pos[i] << endl;
		int cur = ACAM :: fail[pos[i]];
		while(cur != 1) {
			//cerr << "T!" << cur << " " << ACAM :: sz[cur] << " " << ACAM :: tpos[cur] << " " << ACAM :: dep[cur] << " " << ACAM :: dep[ACAM :: tpos[cur]] << " " << ACAM :: dep[pos[i]] << " " << ps[i][ps[i].size() - ACAM :: dep[cur] - 1] << " " << ACAM :: tpos[cur] << endl;
			if(ACAM :: sz[cur] > 1) return puts("Yes"), 0;
			if(ACAM :: sz[cur] == 1) {
				if(ACAM :: dep[ACAM :: tpos[cur]] != ACAM :: dep[pos[i]] ||
				   !ACAM :: intree(ps[i][ps[i].size() - ACAM :: dep[cur] - 1], ACAM :: tpos[cur]))
					return puts("Yes"), 0;
			} cur = ACAM :: fail[cur];
		}
	} puts("No"); return 0;
}
