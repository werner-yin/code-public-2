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

char s[N];
int ans = 1e9, n;

int get(char gl) {
	bool fl = 0;
	rep(i, 1, n) fl |= s[i] == gl;
	if(!fl) return 1e9;
	int cur = 0, lef = 0;
	rep(i, 1, n) {
		if(s[i] == gl) chkmax(lef, cur), cur = 0;
		else cur++;
	} chkmax(lef, cur); return lef;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1);
	rep(i, 'a', 'z') chkmin(ans, get(i));
	cout << ans << endl;
	return 0;
}
