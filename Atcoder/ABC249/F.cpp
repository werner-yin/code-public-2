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

int n, K, t[N], y[N];
ll cur, ans;

priority_queue < int > q;
priority_queue < int, vector < int >, greater < int > > tq;

void undo() {
	if(q.size()) {
		int x = q.top(); q.pop();
		cur += x; tq.ep(x); K++;
	} else printf("%lld\n", ans), exit(0);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; rep(i, 1, n) t[i] = in, y[i] = in;
	ll ret = 0;
	rep(i, 1, n)
		if(t[i] == 1) ret = y[i];
		else ret += y[i];
	ans = ret;
	per(i, n, 1) {
		if(t[i] == 1) {
			chkmax(ans, y[i] + cur);
			K--; if(K < 0) undo();
		} else {
			if(y[i] >= 0) cur += y[i];
			else {
				q.ep(y[i]); K--;
				if(K < 0) undo();
			}
		}
		while(q.size() && tq.size() && q.top() > tq.top()) {
			int x = q.top(), y = tq.top(); q.pop(), tq.pop();
			cur += x, cur -= y; q.ep(y), tq.ep(x);
		}
	} chkmax(ans, cur); printf("%lld\n", ans);
	return 0;
}
