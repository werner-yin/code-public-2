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

int n;
deque < int > q[2];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(t, 0, 1) {
		vec pot; rep(i, 1, n) pot.push_back(in);
		sort(pot.begin(), pot.end());
		for(auto v : pot) q[t].push_back(v);
	}
	int cnt = 0;
	rep(_, 1, n) {
		if(q[0].front() > q[1].front()) { cnt += q[0].front() > q[1].front(), q[0].pop_front(), q[1].pop_front(); }
		else if(q[0].back() > q[1].back()) { cnt += q[0].back() > q[1].back(), q[0].pop_back(), q[1].pop_back(); }
		else {
			cnt -= q[1].back() > q[0].front();
			q[1].pop_back(); q[0].pop_front();
		}
	} printf("%d\n", cnt * 200);
	return 0;
}
