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

const int N = 1e5 + 10;
const ll base = 1e17;

struct bigint {
    vector < ll > arr;
    bigint(int x = 0) { arr.resize(0); arr.eb(x); }
    void shift() { // *2
        ll res = 0;
        for(auto &v : arr) {
            v = v * 2 + res;
            res = v / base; v %= base;
        } if(res) arr.eb(res);
    }
    void add1() {
        ll res = 1;
        for(auto &v : arr) {
            v += res; res = v / base; v %= base; 
            if(res == 0) break;
        } if(res) arr.eb(res);
    }
    void output() {
        int l = arr.size(); printf("%lld", arr[l - 1]);
        per(i, l - 2, 0) printf("%017lld", arr[i]);
        puts("");
    }
};

void solve(int l) {
    bigint cur(1);
    rep(i, 2, l) {
        cur.shift(); if(i & 1) cur.add1();
    } //cerr << f[l].arr.size() << endl;
    cur.output();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
    int T = in;
    while(T--) {
        int n = in;
        solve(n);
    }
	return 0;
}