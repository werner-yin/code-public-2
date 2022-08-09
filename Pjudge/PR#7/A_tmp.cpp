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

ll calc(int d, int k) {
	__int128 ret = 0;
	auto calc = [&](__int128 v, int k) {
		__int128 tv = 1; while(k--) tv = v * tv; return tv;
	};
	rep(i, 1, 300) {
		ret = __gcd(ret, calc(i + d, k) - calc(i, k));
	} return ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	rep(d, 1, 100) rep(k, 1, 15) {
		//ll t = calc(d, k);
		d = 84623, k = 25861;
		auto tget = [&](ll k, ll d) {
			ll pv = 1; ll tk = k, hav = 0, ohv = 0;
			if(k % 2 == 0) {
				if(d % 2 == 0) {
					while(k % 2 == 0) k /= 2, pv *= 2, hav++;
				}
			}
			if(k % 5 == 0) {
				if(d % 5 == 0) {
					while(k % 5 == 0) pv *= 5, k /= 5;
					ohv = 1;
				} ohv = 1;
			}
			if(k % 3 == 0) {
				if(d % 3 == 0) {
					while(k % 3 == 0) pv *= 3, k /= 3;
				}
				ohv = 1;
			}
			if(k % 7 == 0) {
				if(d % 7 == 0) {
					while(k % 7 == 0) pv *= 7, k /= 7;
				}
				ohv = 1;
			}
			if(!hav) ohv = 0;
			ll td = 0;
			while(d % 2 == 0) d /= 2, td++, hav--; if(td > 1) hav = -1; cerr << hav << endl; if(ohv) hav++; cerr << hav << ohv << endl;
			hav = hav > 0; while(hav --> 0) pv *= 2;
			while(__gcd(k, d) > 1 && k % __gcd(k, d) == 0) pv *= __gcd(k, d), k /= __gcd(d, k); return pv;
		};
		auto get = [&](int k, int d) {
			int ld = d, ret = __gcd(k, d); //k /= ret, d /= ret;
			d /= ret;
			while(ld % 2 == 0 && k % 2 == 0) ret *= 2, k /= 2;
			while(ld % 3 == 0 && k % 3 == 0) ret *= 3, k /= 3;
			while(ld % 5 == 0 && k % 5 == 0) ret *= 5, k /= 5;
			while(ld % 7 == 0 && k % 7 == 0) ret *= 7, k /= 7;
			return ret * d;
		};
		ll vt = d * tget(k, d);
		cout << vt << endl;
		//cerr << d << " " << k << " " << t << " " << vt << endl;
		//assert(t == vt);
	}
	return 0;
}
