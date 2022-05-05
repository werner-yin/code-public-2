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
int n, mustnot[N];

void solve() {
	scanf("%s", s + 1); n = strlen(s + 1);
	int l = 1, r = n, cnt0 = 0, cnt1 = 0;
	rep(i, 1, n) cnt0 += s[i] == '0', cnt1 += s[i] == '1';
	while(true) {
		if(cnt0 - (s[r] == '0') >= 1) {
			if(s[r] == '1') {
				assert(0);
			} else if(s[r] == '0') cnt0--;
			r--;
		} else if(cnt1 - (s[l] == '1') >= 1) {
			if(s[l] == '0') {
				assert(0);
			} else if(s[l] == '1') cnt1--;
			l++;
		} else break;
	} //cerr << r <<  " " << l << endl;
	cout << r - l + 1 << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
