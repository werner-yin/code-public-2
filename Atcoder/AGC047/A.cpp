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
int cnt[50][60];
ll ans;
char s[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) {
		scanf("%s", s + 1);
		int t = strlen(s + 1); ll ret = 0; int pv = 9; bool fl = 0;
		rep(j, 1, t) {
			if(s[j] == '.') fl = 1;
			else ret = ret * 10 + (s[j] - '0'), pv -= fl;
		}
		while(pv--) ret *= 10;
		int cnt0 = 0; while(ret % 5 == 0) ret /= 5, cnt0++;
		int cnt1 = 0; while(ret % 2 == 0) ret /= 2, cnt1++;
		cnt[cnt0][cnt1]++;
	}
	rep(i, 0, 30) rep(j, 0, 50) if(cnt[i][j]) 
		rep(k, 0, 30) rep(d, 0, 50) if(cnt[k][d]) {
			int v = i + k, t = j + d;
			int c = min(v, t);
			if(c >= 18)
				ans += 1ll * cnt[i][j] * (cnt[k][d] - (i == k && j == d));
		}
	ans /= 2; cout << ans << endl;
	return 0;
}
