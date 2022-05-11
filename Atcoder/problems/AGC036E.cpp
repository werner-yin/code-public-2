#include <bits/stdc++.h>

#define rep(i, x, y) for(int i = (x); i <= (y); i++)

using namespace std;

const int N = 1e6 + 10;

list < char > s;
char S[N], A, B, C;
int n, id[5], cnt[5];

bool candel(list < char > :: iterator it) {
	if(it == s.begin()) return true;
	if(next(it) == s.end()) return true;
	if(*prev(it) == *next(it)) return false;
	return true;
}

bool check(char x, char y, char a, char b) {
	if(x == a && y == b) return true;
	if(x == b && y == a) return true;
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	scanf("%s", S + 1); n = strlen(S + 1); rep(i, 1, n) if(S[i] != S[i - 1]) s.push_back(S[i]), ++cnt[S[i] - 'A'];
	id[0] = 0, id[1] = 1, id[2] = 2; sort(id, id + 3, [&](int x, int y) { return cnt[x] < cnt[y]; });
	A = id[0] + 'A', B = id[1] + 'A', C = id[2] + 'A'; sort(cnt, cnt + 3);
	for(auto it = s.begin(); it != s.end() && cnt[2] > cnt[1]; ) if(*it == C && candel(it)) cnt[2]--, s.erase(it++); else it++;
	for(auto it = s.begin(); it != s.end() && cnt[2] > cnt[1]; )
		if(next(it) != s.end() && check(*it, *next(it), A, C) && (it == s.begin() || next(next(it)) == s.end() || *prev(it) != *next(next(it))))
			s.erase(it++), s.erase(it++), cnt[2]--, cnt[0]--;
		else it++;
	//cerr << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
	assert(cnt[2] == cnt[1]);
	for(auto it = s.begin(); it != s.end() && cnt[2] > cnt[0]; )
		if(next(it) != s.end() && check(*it, *next(it), B, C) && (it == s.begin() || next(next(it)) == s.end() || *prev(it) != *next(next(it))))
			s.erase(it++), s.erase(it++), cnt[2]--, cnt[1]--;
		else it++;
	for(auto it = s.begin(); it != s.end() && cnt[2] > cnt[0] || cnt[1] > cnt[0]; )
		if(*it == B && candel(it)) cnt[1]--, s.erase(it++);
		else if(*it == C && candel(it)) cnt[2]--, s.erase(it++);
		else it++;
	for(auto v : s) putchar(v); puts(""); return 0;
}
