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

int A, B, num1, ans, totvar = 3;

vector < tuple < int, int, int, int > > pot;

int comp(int x, int y) { // x < y
	totvar++; pot.eb(0, x, y, totvar); return totvar;
}

int add(int x, int y) {
	totvar++; pot.eb(1, x, y, totvar); return totvar;
}

void addto(int x, int y, int z) {
	pot.eb(1, x, y, z); 
}

int create1() {
	return comp(2, add(A, B));
}

int pw[32], bina[32], binb[32];

int getpow(int x, int t) {
	while(t--) x = add(x, x);
	return x;
}

void getbin(int A, int *bina) {
	int ret = ++totvar; 
	per(i, 30, 0) {
		int cur = ++totvar; cur = add(cur, ret);
		rep(j, 0, i - 1) cur = add(cur, pw[j]);
		bina[i] = comp(cur, A);
		ret = add(ret, getpow(bina[i], i));
	}
}

ll valpot[N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	A = 0, B = 1, ans = 2;
	pw[0] = create1();
	rep(i, 1, 30) pw[i] = add(pw[i - 1], pw[i - 1]);
	getbin(A, bina); getbin(B, binb);
	per(i, 59, 0) {
		addto(ans, ans, ans);
		rep(j, 0, 30) {
			int k = i - j;
			if(k < 0 || k > 30) continue;
			addto(ans, comp(pw[0], add(bina[j], binb[k])), ans);
		}
	}
#ifdef YJR_2333_TEST
	valpot[0] = 114514, valpot[1] = 1919810;
#endif
	printf("%lld\n", pot.size());
	for(auto v : pot) {
		int op, x, y, z; tie(op, x, y, z) = v;
#ifdef YJR_2333_TEST
		if(op == 0) valpot[z] = valpot[x] < valpot[y];
		else valpot[z] = valpot[x] + valpot[y];
#endif
		printf("%c %d %d %d\n", (op ? '+' : '<'), x, y, z);
	}
#ifdef YJR_2333_TEST
	rep(i, 0, 30) cerr << valpot[bina[i]] << " "; cerr << endl;
	
	rep(i, 0, 30) cerr << valpot[binb[i]] << " "; cerr << endl;
	cerr << valpot[2] << endl;
#endif
	return 0;
}
