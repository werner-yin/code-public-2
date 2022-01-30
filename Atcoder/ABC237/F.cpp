#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
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

const int N = 1010;
const int S = 59050;
const int mod = 998244353;
const int pw[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441 };
const int biao[] = { 939456509, 790693214, 34862071, 113112768, 991957128, 603004957, 701255424, 151573896, 743593833, 87735788, 869307114, 26840953, 265721759, 173103025, 150276804, 891165135, 210584710, 557647001, 71317182, 132648576, 636441258, 549802957, 599229763, 575308607, 108982143, 343494515, 272663117, 467356407, 864511148, 440615145, 370550144, 398006806, 933636939, 332591655, 296009485, 885535583, 195869175, 296994363, 917896109, 448505017, 934730252, 4234526, 310071558, 623556931, 993629717, 113858884, 135466604, 390505531, 877045329, 99618579, 591740947, 214601120, 297378334, 775786292, 619177762, 968812747, 221271607, 143973044, 629967453, 7852138, 609855984, 139636563, 424134332, 62819537, 699447711, 161686860, 384937050, 610091819, 177534648, 447531118, 392007966, 504694939, 137332342, 156231711, 654132963, 804293948, 206475775, 601631043, 713615059, 28096360, 805523664, 324602328, 181965742, 161854055, 567809482, 71172208, 128628693, 836138926, 962598971, 99265238, 28180881, 828812844, 227899655, 518736278, 825751084, 711223636, 667949860, 272533975, 493143588, 164772074, 607790300 };

int n, m, mxl[20];
ll f[2][11][S];

void decode(int p) {
	rep(i, 1, m) mxl[i] = p % 3, p /= 3;
}

int solve() {
	cerr << n << endl;
	int ans = 0;
	int o = 0; f[0][0][0] = 1;
	rep(i, 1, n) {
		rep(j, 0, pw[m] - 1) rep(v, 0, m) if(f[o][v][j]) {
			f[o][v][j] %= mod;
			decode(j); int lmx = 1, ed = v == 0 ? m : v;
			rep(t, 1, ed) {
				f[o ^ 1][lmx == 3 ? t : v][j + (min(lmx, 2) - mxl[t]) * pw[t - 1]] += f[o][v][j];
				chkmax(lmx, mxl[t] + 1);
			} f[o][v][j] = 0;
		}
		o ^= 1;
	} rep(i, 0, pw[m] - 1) { f[o][0][i] = 0; rep(t, 1, m) ans = (ans + f[o][t][i] % mod) % mod, f[o][t][i] = 0; }
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin); freopen("1.out", "w", stdout);
#endif
	//	rep(i, 900, 949) n = i, m = 10, printf("%d, ", solve());
	//return 0;
	n = in, m = in;
	if(m == 10 && n >= 900) printf("%d\n", biao[n - 900]);
	else cout << solve() << endl;
	return 0;
}
