#include <bits/stdc++.h>
#define eb emplace_back
#define fi first
#define se second

#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using vec = vector < int >;

const int N = 110;

int bel[N], _n, siz[N], fa[N], mat[N];
bool usd[N][N];
int gf(const int &x) { return fa[x]; }
void merge(int x, int y) { x = gf(x), y = gf(y); if(x == y) return; if(siz[x] < siz[y]) swap(x, y); siz[x] += siz[y]; rep(i, 1, _n) if(fa[i] == y) fa[i] = x; }
string query(vec p) {
	cout << "test ";
	for(auto v : p) cout << v << " ";
	cout << endl; string s; cin >> s; return s;
}
void answer(string s) { cout << "answer " << s << endl; }

void solve(int n, char tp) {
	_n = n;
	rep(i, 1, n) bel[i] = i, siz[i] = 1, fa[i] = i;
	rep(i, 1, n) rep(j, 1, n) usd[i][j] = false;
	int ct = 8;
	while(ct--) {
		vector < pair < int, int > > pot;
		rep(i, 1, n) rep(j, i + 1, n) if(gf(i) != gf(j) && !usd[gf(i)][gf(j)]) pot.eb(i, j);
		sort(pot.begin(), pot.end(), [&](const auto &x, const auto &y) { return max(siz[gf(x.fi)], siz[gf(x.se)]) > max(siz[gf(y.fi)], siz[gf(y.se)]); });
		rep(i, 1, n) mat[i] = -1;
		for(const auto &v : pot) {
			int x, y; tie(x, y) = v;
			if(usd[gf(x)][gf(y)] || mat[x] != -1 || mat[y] != -1) continue;
			mat[x] = y; mat[y] = x;
		} vec res(n, 0); rep(i, 1, n) if(i < mat[i]) res[i - 1] = mat[i], res[mat[i] - 1] = i;
		string s = query(res); rep(i, 1, n) if(i < res[i - 1]) {
			if(s[mat[i] - 1] == '1' && s[i - 1] == '1') merge(i, mat[i]);
			else usd[gf(i)][gf(mat[i])] = usd[gf(mat[i])][gf(i)] = true;
		}
	} int p = -1; rep(i, 1, n) if((gf(i) == i) && (p == -1 || siz[i] > siz[p])) p = i;
	string s; rep(i, 1, n) s += (gf(i) == p) + '0'; answer(s); return;
}

int main() {
	int T; cin >> T; while(T--) { int n; cin >> n; solve(n, 'c'); } return 0;
}
