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

int n, a[N], b[N], cnt[N];
vec pot[N];

int ask(int x, int y) {
	cout << "? " << x << " " << y << endl;
	int ans; cin >> ans; return ans;
}

int main() {
	cin >> n;
	rep(i, 3, n) a[i] = ask(1, i), b[i] = ask(2, i);
	if(n == 4) {
		if(a[3] == 1 && b[3] == 2 && a[4] == 2 && b[4] == 1) {
			int t = ask(3, 4);
			if(t == 1) cout << "! " << 3 << endl;
			else cout << "! " << 1 << endl;
			return 0;
		} else if(a[3] == 2 && b[3] == 1 && a[4] == 1 && b[4] == 2) {
			int t = ask(3, 4);
			if(t == 1) cout << "! " << 3 << endl;
			else cout << "! " << 1 << endl;
			return 0 ;
		}
	}
	rep(ans, 1, n - 1) {
		rep(i, 1, n) pot[i].clear();
		bool fl = 0;
		rep(i, 3, n) {
			if(a[i] - b[i] == ans || b[i] - a[i] == ans) continue;
			if((a[i] + b[i] - ans) & 1) fl = true;
			int t = (a[i] + b[i] - ans) / 2;
			if(t >= a[i] || t >= b[i]) fl = true;
			if(a[i] - t >= ans) fl = true;
			if(fl) break;
			pot[a[i] - t].eb(t);
		}
		rep(i, 1, ans - 1) {
			sort(pot[i].begin(), pot[i].end());
			rep(j, 0, n) cnt[j] = 0;
			for(auto v : pot[i]) cnt[v]++;
			if(cnt[0] != 1) fl = true; if(fl) break;
			pot[i].resize(unique(pot[i].begin(), pot[i].end()) - pot[i].begin());
			rep(j, 0, (int)pot[i].size() - 1) {
				if(j != pot[i][j]) fl = true;
			}
			if(fl) break;
		}
		if(!fl) return cout << "! " << ans << endl, 0;
	} assert(0); cout << "what" << endl;
	return 0;
}
