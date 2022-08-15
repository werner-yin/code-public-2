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

int n, p[N], a[N];

bool check(int pos, int val) {
	if(pos & 1) return pos == 1 || a[pos - 1] > val;
	else return a[pos - 1] < val;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n << 1) p[i] = in;
	set < int > s; rep(i, 1, n << 1) s.insert(p[i]);
	list < int > t; rep(i, 1, n << 1) t.eb(p[i]);
	vec pot;
	rep(i, 1, n << 1) {
		int ban = -1;
		if(i & 1) ban = *s.rbegin();
		else ban = *s.begin();
		if(i == (n << 1)) ban = -1;
		int ct = 0;
		for(auto it = t.begin(); it != t.end(); it++, ct++)
			if(*it != ban && check(i, *it)) {
				per(j, ct, 1) pot.eb(j + i - 1); a[i] = *it; s.erase(*it); t.erase(it); break;
			}
		if(a[i] == 0) assert(0);
	}
	printf("%lu\n", pot.size());
	for(auto v : pot) printf("%d ", v); puts("");
	return 0;
}
