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

int A, B, C, D, K;
int a, b;

void solve() {
	A = in, B = in, C = in, D = in, K = (max(A, B) + min(A, B)) / (min(A, B) + 1);
	auto get = [&](int cnt) {
		a = A - cnt / (K + 1) * K - cnt % (K + 1);
		b = B - cnt / (K + 1);
	};
	int l = 0, r = A + B;
	while(l <= r) {
		int mid = l + r >> 1;
		get(mid);
		if(b > 1ll * K * a) r = mid - 1;
		else l = mid + 1;
	}
	get(l); r = b - a * K + l;
	rep(i, C, D) {
		if(i <= l)
			putchar(i % (K + 1) == 0 ? 'B' : 'A');
		else 
			putchar((i - r) % (K + 1) == 1 ? 'A' : 'B');
	} puts("");
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
