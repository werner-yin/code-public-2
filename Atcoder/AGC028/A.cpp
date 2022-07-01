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

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	scanf("%s", s + 1); scanf("%s", t + 1);
	if(n % m && m % n) {
		int v1 = n / __gcd(n, m), v2 = m / __gcd(n, m), cur1 = 1, cur2 = 1;
		while(cur1 <= n && cur2 <= m) {
			if(s[cur1] != t[cur2]) return puts("-1"), 0;
			cur1 += v1, cur2 += v2;
		}
		cout << 1ll * n * m / __gcd(n, m) << endl;
	} else {
		if(n < m) swap(n, m), swap(s, t);
		int pt = n / m;
		rep(i, 1, m) {
			if(s[(i - 1) * pt + 1] != t[i]) return puts("-1"), 0;
		} cout << n << endl;
	}
	return 0;
}
