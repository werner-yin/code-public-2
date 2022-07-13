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
int ans[N], tg;
deque < int > pot;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin); //freopen("1.out", "w", stdout);
#endif
	n = in, K = in; scanf("%s", s + 1);
	rep(i, 1, n) 
		if(i == n || s[i] != s[i + 1]) pot.push_back(i);
	ans[0] = s[1] == 'A';
	int cnt = 0;
	while(K) {
		cnt++; K--;
		if(ans[0] != 1) {
			int lsz = pot.size(), ct = 0; tg++;
			while(pot.front() <= tg) pot.pop_front(), ct++;
			if(lsz & 1) pot.pop_back();
			pot.push_back(n + tg);
			if(!ct) ans[0] ^= 1;
		} else {
			if(pot.front() == 1 + tg) pot.pop_front();
			else pot.push_front(1 + tg);
			ans[0] ^= 1;
		}
		if(cnt >= 5 * n) K %= 2;
	} //if(K & 1) ans[0] = 1;
	while(pot.size()) { int v = pot.front() - tg; pot.pop_front(); ans[v + 1] ^= 1; }
	rep(i, 1, n) ans[i] = ans[i - 1] ^ ans[i];
	rep(i, 1, n) putchar(ans[i] ? 'A' : 'B'); puts("");
	return 0;
}
