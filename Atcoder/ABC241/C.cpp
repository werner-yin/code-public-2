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

const int N = 1e3 + 10;

int n;
char s[N][N];

bool ip(int x, int y) { return x > 0 && y > 0 && x <= n && y <= n; }

#define OK return puts("Yes"), 0

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) scanf("%s", s[i] + 1);
	rep(i, 1, n)
		rep(j, 1, n) {
		int ct = 0;
		rep(t, 0, 5) {
			if(!ip(i, j + t)) { ct = 10; break; }
			if(s[i][j + t] == '.') ct++;
		} if(ct <= 2) OK;
		ct = 0;
		rep(t, 0, 5) {
			if(!ip(i + t, j)) { ct = 10; break; }
			if(s[i + t][j] == '.') ct++;
		} if(ct <= 2) OK;
		ct = 0;
		rep(t, 0, 5) {
			if(!ip(i + t, j + t)) { ct = 10; break; }
			if(s[i + t][j + t] == '.') ct++;
		} if(ct <= 2) OK;
		ct = 0;
		rep(t, 0, 5) {
			if(!ip(i + t, j - t)) { ct = 10; break; }
			if(s[i + t][j - t] == '.') ct++;
		} if(ct <= 2) OK;
	} puts("No");
	return 0;
}
