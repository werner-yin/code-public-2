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

const int N = 2e6 + 10;

int n, m, K, len, a[N], b[N];
int stk[N], top;
char s[N], t[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, K = in; len = max(n, m) + K + 1;
	scanf("%s", s + 1); scanf("%s", t + 1);
	rep(i, 1, n) a[n - i + 1] = s[i] - '0';
	rep(i, 1, m) b[m - i + 1] = t[i] - '0';
	stk[++top] = len;
	per(i, len, 1) if(a[i] || b[i]) {
		int ret = K, cur = i; vec pot;
		while(true) {
			while(stk[top] <= cur) top--;
			pot.eb(cur);
			if(a[cur] == 1 && b[cur] == 1 && ret) {
				int nxt = stk[top];
				if(nxt - cur <= ret) ret -= nxt - cur;
				else nxt = cur + ret, ret = 0;
				a[nxt]++, b[nxt]++; a[cur] = b[cur] = 0; cur = nxt;
			} else if(a[cur] == 2 || b[cur] == 2) {
				a[cur + 1] += a[cur] >> 1; a[cur] &= 1;
				b[cur + 1] += b[cur] >> 1; b[cur] &= 1;
				cur++;
			} else break;
		} reverse(pot.begin(), pot.end());
		for(auto v : pot) if(a[v] || b[v]) stk[++top] = v;
	} n = m = len; while(n && a[n] == 0) n--; while(m && b[m] == 0) m--;
	per(i, n, 1) printf("%d", a[i]); puts("");
	per(i, m, 1) printf("%d", b[i]); puts("");
	return 0;
}
