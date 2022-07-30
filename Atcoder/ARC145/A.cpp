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
char s[N], t[N];

bool check1() {
	rep(i, 1, n) {
		int t = n + 1 - i;
		if(s[i] == s[t]) continue;
		if(s[i] == 'A') return 0;
		s[i] = 'A'; s[i + 1] = 'B';
		if(s[i] != s[t]) return 0;
	} return 1;
}

bool check2() {
	rep(i, 1, n) {
		int t = n + 1 - i;
		if(s[i] == s[t]) continue;
		if(s[i] == 'A') return 0;
		s[t] = 'B', s[t - 1] = 'A';
		if(s[i] != s[t]) return 0;
	} return 1;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1);
	rep(i, 1, n) t[i] = s[i];
	if(check1()) return puts("Yes"), 0;
	rep(i, 1, n) s[i] = t[i];
	if(check2()) return puts("Yes"), 0;
	puts("No");
	return 0;
}
