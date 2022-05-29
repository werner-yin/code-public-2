#include <bits/stdc++.h>

#define left _RUG_LEFT
#define right _RUG_RIGHT

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

int p[N], q[N], n;
bool right[N], left[N];
int stk[N], top;

#define GG { puts("-1"); exit(0); }

bool sureright(int x) {
#ifdef YJR_2333_TEST
	cerr << "RIGHT: " << x << endl;
#endif
	if(left[x]) GG; right[x] = true; return true;
}
bool sureleft(int x) {
#ifdef YJR_2333_TEST
	cerr << "LEFT: " << x << endl;
#endif
	if(right[x]) GG; left[x] = true; return true;
}
void sureit(bool cd) { if(!cd) GG; }

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in;
	rep(i, 1, n << 1) p[i] = in; rep(i, 1, n << 1) q[i] = in;
	int cur = 1; queue < int > tq;
	rep(i, 1, n << 1) {
		if(i != p[cur]) sureright(i), tq.ep(i);
		else {
			if(tq.size()) sureleft(i), (cur && sureright(p[cur - 1])), sureit(tq.front() == p[cur + 1]), tq.pop(), cur++;
			cur++;
		} 
	}
	//cerr << "---" << endl;
	cur = 1; while(tq.size()) tq.pop();
	per(i, n << 1, 1) {
		if(i != q[cur]) sureright(i), tq.ep(i);
		else {
			if(tq.size()) sureleft(i), (cur && sureright(q[cur - 1])), sureit(tq.front() == q[cur + 1]), tq.pop(), cur++;
			cur++;
		}
	}
	//cerr << "---" << endl;
	sureleft(p[1]), sureleft(q[1]); sureright(p[n << 1]); sureright(q[n << 1]);
	//rep(i, 1, top) sureleft(stk[i]), sureright(stk[i + 1]), i++;
	int cnt = 0; rep(i, 1, n << 1) if(left[i]) cnt++; else cnt--; sureit(cnt == 0);
	rep(i, 1, n << 1) if(left[i]) putchar('('); else putchar(')'); puts("");
	return 0;
}
