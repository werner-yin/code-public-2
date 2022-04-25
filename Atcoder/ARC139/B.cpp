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

ll n, a, b, x, y, z;
ll ans;
ll X, Y, G;

void exgcd(int a, int b) {
	if(b == 0) return G = a, X = 1, Y = 0, void();
	exgcd(b, a % b); ll tx = X; X = Y; Y = tx - a / b * Y;
}

void solve() {
	n = in, a = in, b = in, x = in, y = in, z = in;
	ans = 1ll * n * x;
	chkmin(ans, n / a * y + (n % a) * x);
	chkmin(ans, n / b * z + (n % b) * x);
	if(y * b > z * a) swap(a, b), swap(y, z);
	if(n / a <= a) 
		rep(i, 0, n / a) {
			chkmin(ans, i * y + (n - i * a) / b * z + (n - i * a) % b * x);
		}
	else
		rep(i, 0, a - 1) if(i * b <= n) {
			chkmin(ans, i * z + (n - i * b) / a * y + (n - i * b) % a * x);
		}
	cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(); return 0;
}
