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

string s;
int n;

void out(int p) {
	int res = s[p] - '0' + s[p + 1] - '0';
	string t = "";
	rep(i, 0, p - 1) t += s[i];
	if(res >= 10) t += '1', res %= 10;
	t += (res + '0');
	rep(i, p + 2, n - 1) t += s[i];
	cout << t << endl;
}

void solve() {
	cin >> s;n = s.size();
	int pos1 = -1, pos2 = -1, pos3 = -1;
	rep(i, 0, n - 2) {
		if(s[i] - '0' + s[i + 1] - '0' >= 10) {
			pos3 = i;
		} else {
			if(s[i] - '0' + s[i + 1] - '0' >= s[i] - '0') {
				if(!~pos2) pos2 = i;
			} else pos1 = i;
		}
	}
	if(~pos3) out(pos3); else if(~pos2) out(pos2); else out(pos1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
