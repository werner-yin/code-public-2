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

const int N = 3010;

char s[N << 1];
int n, id[N << 1], posa[N], posb[N], nxtpos[N << 1], ca, cb;
string f[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; scanf("%s", s + 1);
	rep(i, 1, n + n) {
		if(s[i] == 'a') posa[id[i] = ++ca] = i;
		else posb[id[i] = ++cb] = i;
	}
	id[n + n + 1] = n + 1; posa[n + 1] = posb[n + 1] = n + n + 1;
	int tpos = 1;
	rep(i, 1, n + 1)
		while(tpos < min(posa[i], posb[i])) nxtpos[tpos++] = i;
	per(i, n, 1) {
		if(posa[i] < posb[i]) f[i] = "ab" + f[nxtpos[posb[i]]];
		else {
			int j = posb[i];
			while(posa[id[j]] > posb[id[j]] && (id[j] <= i || posb[id[j]] <= posa[id[j] - 1])) {
				if(id[j] >= i) f[i] += s[j];
				j++;
			} f[i] += f[id[j]];
		} chkmax(f[i], f[i + 1]);
	}
	cout << f[1] << endl;
	return 0;
}
