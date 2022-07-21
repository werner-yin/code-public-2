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
const int L = 128;

char vch(int id) {
	if(id < 26) return id + 'a';
	if(id < 52) return id - 26 + 'A';
	return id - 52 + '0';
}

int cnt[N], tot;
string ret[100];

int ask(string s) {
	cout << "? " << s << endl;
	int x; cin >> x; return x;
}

string getall(int id, int cnt) { cerr << "!" << vch(id) << endl; return string(cnt, vch(id)); }

int main() {
#ifdef YJR_2333_TEST
	//freopen("1.in", "r", stdin);
#endif
	rep(i, 0, 61) cnt[i] = L - ask(getall(i, L));
	//cnt[0] = 2, cnt[1] = 1, cnt[2] = 1, cnt[3] = 1;
	//cnt[26] = 1;
	rep(i, 0, 61) tot += cnt[i];
	priority_queue < pii, vector < pii >, greater<> > q; rep(i, 0, 61) if(cnt[i]) q.ep(cnt[i], i), ret[i] = getall(i, cnt[i]);
	while(q.size() > 1) {
		int x = q.top().se; q.pop();
		int y = q.top().se; q.pop();
		int px = 0, py = 0; int lst = tot - ret[x].size();
		//cerr << "! MRG: " << ret[x] << " " << ret[y] << endl;
		while(px < ret[x].size() && py < ret[y].size()) {
			string t = ret[x];
			ret[x].insert(ret[x].begin() + px, ret[y][py]);
			if(ask(ret[x]) < lst) lst--, py++;
			else ret[x] = t; px++;
		} while(py < ret[y].size()) ret[x].insert(ret[x].begin() + px, ret[y][py]), px++, py++;
		cnt[x] += cnt[y]; q.ep(cnt[x], x);
	} int t = q.top().se; cout << "! " << ret[t] << endl;
	return 0;
}
