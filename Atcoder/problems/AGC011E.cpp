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
int n;

int check(int ret) {
	int v = ret / 10, pr = ret;
	per(i, n - 1, 1) {
		if((ret + v) % 10 != s[i] - '0') {
			int dt = (ret + v) % 10 - (s[i] - '0');
			if(dt < 0) dt += 10;
			ret -= dt;
		} if(ret < 0) return -1;
		assert((ret + v) % 10 == s[i] - '0'); v = (ret + v) / 10;
		//if(pr == 273) cerr << i << " " << ret << " " << v << endl;
	} return v == 0 ? 0 : 1;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", s + 1); n = strlen(s + 1);
	/*
	rep(t, 0, n) {
		if(check(t * 10 + s[n] - '0') == 0) return cout << ceil(t * 10 / 9) + 1 << endl, 0;
	}
	*/
	int l = 0, r = n * 10;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid * 10 + s[n] - '0') < 0) l = mid + 1;
		else r = mid - 1;
	} //cerr << l << endl;
	//cerr << check(l * 10 + s[n] - '0') << endl;
	cout << ceil((l * 10 + s[n] - '0') / 9.) << endl;
	return 0;
}
