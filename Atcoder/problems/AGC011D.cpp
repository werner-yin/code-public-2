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
char s[N];
int ans[N];
vec pot;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin); //freopen("1.out", "w", stdout);
#endif
	n = in, K = in; scanf("%s", s + 1);
	rep(i, 1, n) 
		if(i == n || s[i] != s[i + 1]) pot.eb(i);
	if(s[1] == 'A') {
		K--;
		if(pot.front() == 1) pot.erase(pot.begin());
		else pot.insert(pot.begin(), 1);
	}
	/*
	int t = K + 1 >> 1;
	chkmin(t, n + 10);
	rep(i, 1, t) pot.eb(n + i);
	vec tpot;
	for(auto v : pot)
		if(v - t > 0) tpot.eb(v - t);
	pot = tpot;
	for(auto v : pot) cerr << v << " "; cerr << endl;
	if(~K & 1 && K) {
		if(pot[0] != 1) pot.erase(pot.begin());
		else pot.insert(pot.begin(), 1);
	}
	if(K & 1) ans[0] ^= 1;
	*/ // fast
	//for(auto v : pot) cerr << v << " "; cerr << endl;
	rep(i, 1, K) {
		if(ans[0] != 1) {
			vec tpot;
			for(auto v : pot) if(v > 1) tpot.eb(v - 1);
			tpot.eb(n);
			if(pot[0] != 1) ans[0] ^= 1;
			pot = tpot;
		} else {
			if(pot.front() == 1) pot.erase(pot.begin());
			else pot.insert(pot.begin(), 1);
			ans[0] ^= 1;
		} //if(i % 100 == 0) cerr << "!" << i << endl;
		//for(auto v : pot) cerr << v << " "; cerr << endl;
	} //if(K & 1) ans[0] = 1;
	for(auto v : pot) ans[v + 1] ^= 1;
	rep(i, 1, n) ans[i] = ans[i - 1] ^ ans[i];
	rep(i, 1, n) putchar(ans[i] ? 'A' : 'B'); puts("");
	return 0;
}
