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

string s;
int n, K;

string rev(string s) { reverse(s.begin(), s.end()); return s; }

string get(string s) {
	string lst, ret;
	rep(i, 0, n + n - 1) {
		lst = s[i] + lst;
		if(lst.size() > n) lst.resize(n);
		if(lst.size() == n) {
			if(!ret.size()) ret = lst;
			else chkmin(ret, lst);
		}
	} return rev(ret);
}

string mxget(string s) {
	string lst, ret;
	rep(i, n - 1, n + n - 1) {
		lst = ""; rep(j, i - n + 1, i) lst += s[j];
		if(i == n - 1) ret = lst;
		else chkmin(ret, lst);
	} return ret;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in; cin >> s;
	rep(i, 1, K - 1) {
		s = get(s + rev(s));
		bool fl = 1;
		for(auto v : s) fl &= v == s[0];
		if(fl) break;
	} s = mxget(s + rev(s)); cout << s << endl;
	return 0;
}
