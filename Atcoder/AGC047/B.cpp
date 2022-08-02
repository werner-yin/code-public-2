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

int n;
string s[N];
bool hav[N][26];

int ch[N][26], cnt[N][26], ndn = 1;

void ins(string &s) {
	rep(j, 0, 25) hav[0][j] = 0;
	rep(i, 1, s.size()) {
		rep(j, 0, 25) hav[i][j] = hav[i - 1][j];
		hav[i][s[i - 1] - 'a'] = true;
	}
	int p = 1; rep(j, 0, 25) cnt[p][j] += hav[s.size()][j];
	per(i, s.size() - 1, 0) {
		int x = s[i] - 'a'; if(!ch[p][x]) ch[p][x] = ++ndn;
		p = ch[p][x]; rep(j, 0, 25) cnt[p][j] += hav[i][j];
	}
}

int query(string &s) {
	int p = 1;
	per(i, s.size() - 1, 1) {
		int x = s[i] - 'a'; p = ch[p][x];
	} //cerr << p << endl; rep(j, 0, 25) cerr << cnt[p][j] << " "; cerr << endl;
	return cnt[p][s.front() - 'a'];
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) cin >> s[i];
	rep(i, 1, n) ins(s[i]);
	ll ans = 0;
	rep(i, 1, n) ans += query(s[i]) - 1;
	cout << ans << endl;
	return 0;
}
