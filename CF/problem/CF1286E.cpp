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
const int MASK = (1 << 30) - 1;
 
int n, nxt[N], lstpos[N], w[N];
char s[N];
__int128 ans;
ll tot;
 
vec stk;
map < int, int > cnt;
 
char gc() { char ch = getchar(); while(!isalpha(ch)) ch = getchar(); return ch; }
 
int get(int pos) { return w[*lower_bound(stk.begin(), stk.end(), pos)]; }
 
int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; s[1] = gc(); w[1] = in; ans = tot = w[1]; cout << w[1] << endl; cnt[w[1]]++;// stk.eb(1);
	function < void(__int128) > write = [&](__int128 x) {
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	};
	auto twrite = [&](auto x) { if(x == 0) putchar('0'); write(x); };
	rep(i, 2, n) {
		char ch = (gc() - 'a' + ans % 26) % 26 + 'a';
		s[i] = ch; w[i] = in ^ (ans & MASK);
		//cerr << "!" << ch << " " << w[i] << endl;
		lstpos[i - 1] = s[nxt[i - 1] + 1] == s[i] ? lstpos[nxt[i - 1]] : nxt[i - 1];
		int j = nxt[i - 1];
		while(j && s[j + 1] != s[i]) j = nxt[j];
		nxt[i] = j + (s[j + 1] == s[i]);
		//cerr << nxt[i] << " " << j << endl; 
		j = nxt[i - 1];
		while(j) {
			if(s[j + 1] == s[i]) j = lstpos[j];
			else {
				int v = get(i - j); tot -= v; cnt[v]--; if(cnt[v] == 0) cnt.erase(v);
				//cerr << "!" << v << endl;
				j = nxt[j];
			}
		}
		while(stk.size() && w[stk.back()] >= w[i]) stk.pop_back();
		stk.eb(i);
		if(s[i] == s[1]) { cnt[w[i]]++; tot += w[i]; }
		auto it = cnt.upper_bound(w[i]);
		while(it != cnt.end()) {
			tot -= 1ll * (it->fi - w[i]) * it->se;
			cnt[w[i]] += it->se; cnt.erase(it++);
		} ans += tot; twrite(ans); puts("");
	}
	return 0;
}
