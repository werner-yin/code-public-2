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

const int N = 1510;

int n, L[N][N], R[N][N], s[N][N], w[N][N];
char t[N];
ll ans;

int top;
pii stk[N * N];

void rundfs(int x, int y) {
	top = 0; stk[++top] = { x, y };
	while(top) {
		x = stk[top].fi, y = stk[top].se; top--;
		if(!w[x][y] || w[x - 1][y] || w[x][y - 1]) continue;
		int &v = w[x][y]; rep(j, y, n) s[j][x] -= v; v = 0;
		stk[++top] = { x + 1, y }, stk[++top] = { x, y + 1 };
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("subtask01-01.txt", "r", stdin);
#endif
	n = in;
	rep(i, 1, n) {
		scanf("%s", t + 1);
		rep(j, 1, n) w[i][j] = t[j] == '#' ? 0 : t[j] - '0', L[i][j] = n + 1, s[j][i] = s[j - 1][i] + w[i][j];
	}
	per(i, n, 1) per(j, n, 1)
		if(w[i][j]) {
			int *L = ::L[j], *R = ::R[j], *TL = ::L[j + 1], *TR = ::R[j + 1];
			L[i] = R[i] = j; ll tot = 0;
			rep(k, i, n) {
				if(j < n)
					chkmin(L[k], TL[k]), chkmax(R[k], TR[k]);
				if(L[k] <= R[k]) tot += s[R[k]][k] - s[L[k] - 1][k];
				else break;
			}
			ans += (tot - w[i][j]) * w[i][j]; rundfs(i, j); 
		} else {
			int *L = ::L[j], *R = ::R[j];
			rep(k, i, n) L[k] = n + 1, R[k] = 0;
		}
	cout << ans << endl;
	return 0;
}
