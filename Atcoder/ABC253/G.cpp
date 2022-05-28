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

int n, p[N];
ll L, R;
vec pot;
bool fl;

mt19937_64 rnd(random_device{}());

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
	n = 20; ll tt = 1ll * n * (n - 1) / 2; L = rnd() % tt + 1, R = rnd() % tt + 1; if(L > R) swap(L, R);
	L = 61, R = 190;
#else
	n = in, L = lin, R = lin;
#endif
	rep(i, 1, n) p[i] = i;
	rep(i, 1, n) {
		int tot = n - i;
		if(L > tot && tot) {
			L -= tot; R -= tot;
		} else {
			if(L == 1) {
				//cerr << "!" << L << " " << R << " " << i << " " << pot.size() << endl;
				if(R >= tot) {
					//			cerr << "OK1" << endl;
					if(!fl) { rep(j, i, n) pot.eb(p[j]); fl = 1; }
					p[i] = pot.back(), pot.pop_back();
					R -= tot;
					//cerr << "R: " << R << endl;
				} else {
					if(!fl) {
						rep(j, i + 1, n) if(R) swap(p[i], p[j]), R--;
					} else {
						rep(j, i, n) p[j] = pot[j - i]; pot.clear();
						rep(j, i + 1, n) if(R) swap(p[i], p[j]), R--;
					}
					break;
				}
			} else {
				rep(j, i + 1, n) {
					if(L == 1) { if(R) swap(p[i], p[j]), R--; }
					else L--, R--;
				} assert(L == 1);
				if(R == 0) break;
			}
		} //if(L > R) break;
	} for(auto v : pot) cerr << v << " "; assert(!pot.size()); //assert(L == 1), assert(R == 0);
#ifndef YJR_2333_TEST
	rep(i, 1, n) printf("%d ", p[i]); puts("");
#endif
	return 0;
}
