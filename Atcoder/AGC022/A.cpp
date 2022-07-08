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
char s[N];
bool vis[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1);
	if(n < 26) {
		rep(i, 1, n) vis[s[i]] = true;
		char ch = 'z';
		rep(i, 'a', 'z') {
			if(!vis[i]) { ch = i; break; }
		}
		s[++n] = ch;
		printf("%s\n", s + 1);
	} else {
		rep(i, 'a', 'z') vis[i] = true;
		per(i, n, 1) {
			vis[s[i]] = false;
			int t = -1;
			rep(j, s[i] + 1, 'z') if(!vis[j]) { t = j; break; }
			if(t == -1) continue;
			s[i] = t;
			rep(j, 1, i) putchar(s[j]); puts("");
			return 0;
		} puts("-1");
	}
	return 0;
}
