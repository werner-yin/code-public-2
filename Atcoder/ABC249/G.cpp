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

int n, K;
vec a, b;
vector < ll > t;

template < typename T, int B > int liner_base(vector < T > &t) {
	int cur = 0; 
	per(i, B - 1, 0) {
		int pos = -1;
		rep(j, cur, int(t.size()) - 1) if(t[j] >> i & 1) { pos = j; break; }
		if(pos != -1) {
			swap(t[pos], t[cur]);
			rep(j, pos + 1, int(t.size()) - 1)
				if(t[j] >> i & 1) t[j] ^= t[cur];
			cur++;
		}
	} return cur;
}

int get(vec t, int val) {
	liner_base < int, 30 > (t);
	for(auto v : t) chkmax(val, val ^ v);
	return val;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; a.resize(n), b.resize(n);
	rep(i, 0, n - 1) a[i] = in, b[i] = in, t.eb((ll)a[i] << 30 | b[i]);
	n = liner_base < ll, 60 > (t); if((t.back() >> 30) > K) return puts("-1"), 0;
	rep(i, 0, n - 1) a[i] = t[i] >> 30, b[i] = t[i] & ((1 << 30) - 1);
	int m = 0; while(m < n && a[m]) m++;
	int ans = 0, nowa = 0, nowb = 0;
	rep(i, 0, m - 1) {
		int p = 1; while(p <= a[i]) p <<= 1; p >>= 1; 
		if((nowa | (p - 1)) <= K) {
			chkmax(ans, get(vec(b.begin() + i + 1, b.end()), nowb));
			nowa ^= a[i], nowb ^= b[i];
		} else if(((nowa ^ a[i]) | (p - 1)) <= K) {
			chkmax(ans, get(vec(b.begin() + i + 1, b.end()), nowb ^ b[i]));
		} else if(nowa & p) nowa ^= a[i], nowb ^= b[i];
	} if(nowa <= K) chkmax(ans, get(vec(b.begin() + m, b.end()), nowb)); cout << ans << endl; return 0;
}
