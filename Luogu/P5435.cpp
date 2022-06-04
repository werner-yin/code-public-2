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
const int B = 1000;
constexpr int mod = 998244353;

int pgcd[B + 10][B + 10];
int k[N][3], pnum, pri[N], n, a[N], b[N];
bool v[N];

void init(int l) {
	k[1][0] = k[1][1] = k[1][2] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, k[i][0] = 1, k[i][1] = 1, k[i][2] = i;
		rep(j, 1, pnum) {
			int t = pri[j] * i; if(t > l) break; v[t] = true;
			k[t][0] = k[i][0] * pri[j]; k[t][1] = k[i][1]; k[t][2] = k[i][2]; sort(k[t], k[t] + 3); if(i % pri[j] == 0) break;
		}
	}
}

int gcd(int x, int y) {
	int ans = 1;
	rep(i, 0, 2) {
		int t = 1;
		if(k[x][i] > B) {
			if(y % k[x][i] == 0) t = k[x][i];
		} else t = pgcd[k[x][i]][y % k[x][i]];
		ans *= t; y /= t;
	} return ans;
}
	
int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 0, B) pgcd[i][0] = pgcd[0][i] = i;
	rep(i, 1, B) rep(j, 1, i) pgcd[i][j] = pgcd[j][i] = pgcd[i % j][j];
	init(1000000);
	rep(i, 1, n) a[i] = in; rep(i, 1, n) b[i] = in;
	rep(i, 1, n) {
		ll ret = 1, hans = 0;
		rep(j, 1, n) {
			ret *= i; ret %= mod;
			hans += ret * gcd(a[i], b[j]); hans %= mod;
		} printf("%lld\n", hans);
	}
	return 0;
}
