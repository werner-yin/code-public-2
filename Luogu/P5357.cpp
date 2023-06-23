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

int n;
int trie[N][26], tot[N], fail[N], ndn = 1;
int ed[N];
vec G[N];

char s[N];

int insert(char *s) {
	int l = strlen(s + 1), p = 1;
	rep(i, 1, l) {
		int x = s[i] - 'a';
		if(!trie[p][x]) trie[p][x] = ++ndn;
		p = trie[p][x];
	}
	return p;
}

void getfail() {
	rep(i, 0, 25) trie[0][i] = 1;
	queue < int > q; q.push(1);
	while(q.size()) {
		int x = q.front(), F = fail[x]; G[F].eb(x); q.pop();
		rep(i, 0, 25) {
			int &y = trie[x][i];
			if(!y) y = trie[F][i];
			else fail[y] = trie[F][i], q.push(y);
		}
	}
}

void query(char *s) {
	int l = strlen(s + 1), p = 1;
	rep(i, 1, l) {
		int x = s[i] - 'a';
		p = trie[p][x]; tot[p]++;
	}
}

void dfs(int x) { for(auto y : G[x]) dfs(y), tot[x] += tot[y]; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) {
		scanf("%s", s + 1);
		ed[i] = insert(s);
	}
	getfail();
	scanf("%s", s + 1);
	query(s);
	dfs(1);
	rep(i, 1, n) printf("%d\n", tot[ed[i]]);
	return 0;
}
