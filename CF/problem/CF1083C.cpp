#include <bits/stdc++.h>

#define eb emplace_back
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using vec = vector < int >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

const int N = 1e6 + 10;
const int K = 20;

int n, Q, p[N], ip[N], dep[N];
vec G[N];

namespace T {
    int dfn[N], pot[N], top, mn[K + 1][N], lg[N], pw[N], R[N];
    bool intree(int x, int y) { return dfn[y] >= dfn[x] && dfn[y] <= R[x]; }
    void dfs(int x) {
        pot[dfn[x] = ++top] = x;
        for(auto y : G[x]) dep[y] = dep[x] + 1, dfs(y), pot[++top] = x;
        R[x] = top;
    }
    int tmn(int x, int y) { return dep[x] < dep[y] ? x : y; }
    int LCA(int x, int y) {
        if(x == 0) return y; if(y == 0) return x;
        x = dfn[x], y = dfn[y]; if(x > y) swap(x, y);
        int k = lg[y - x + 1];
        return tmn(mn[k][x], mn[k][y - pw[k] + 1]);
    }
    void init() {
        dep[1] = 0; dfs(1); rep(i, 2, top) lg[i] = lg[i >> 1] + 1;
        pw[0] = 1; rep(i, 1, lg[top]) pw[i] = pw[i - 1] << 1;
        rep(i, 1, top) mn[0][i] = pot[i];
        rep(k, 1, lg[top])
            rep(i, 1, top - pw[k] + 1)
                mn[k][i] = tmn(mn[k - 1][i], mn[k - 1][i + pw[k - 1]]);
    }
}
using T :: intree;

struct node {
    int x, y; bool fl;
    void out() { cerr << x << " " << y << " " << fl << endl; }
} val[N << 1];
node operator + (node a, node b) {
    node c; c.fl = a.fl & b.fl; c.x = a.x; c.y = a.y;
    for(auto v : { b.x, b.y }) if(v) {
        if(!c.fl) break;
        if(c.x == v || c.y == v) continue;
        if(!c.x) { c.x = v; continue; }
        if(!c.y) { c.y = v; continue; }
        if(dep[c.x] < dep[c.y]) swap(c.x, c.y);
        int L = T :: LCA(v, c.x), R = T :: LCA(v, c.y), RL = T :: LCA(c.x, c.y);
        if(c.y == RL) { // x -> y is a chain.
            if(intree(c.x, v)) c.x = v;
            else if(intree(c.y, v)) {
                if(L == R) c.y = v;
                else if(v != L) c.fl = false;
            } else c.y = v;
        } else {
            if(intree(c.x, v)) c.x = v;
            else if(intree(c.y, v)) c.y = v;
            else if(v != RL && L == R && L == RL) c.fl = false;
            else if(dep[L] < dep[RL] || dep[R] < dep[RL]) c.fl = false;
            else if(L != v && L != RL) c.fl = false;
            else if(R != v && R != RL) c.fl = false;
        }
    }
    if(dep[c.x] < dep[c.y]) swap(c.x, c.y);
    return c;
}

int ch[N << 1][2], L[N << 1], R[N << 1], md[N << 1], ndn, rt;

void build(int &o, int l = 0, int r = n - 1) {
    o = ++ndn; L[o] = l; R[o] = r; if(l == r) return val[o] = (node) { ip[l], 0, 1 }, void(); md[o] = l + r >> 1;
    build(ch[o][0], l, md[o]); build(ch[o][1], md[o] + 1, r); 
    val[o] = val[ch[o][0]] + val[ch[o][1]];
}

void upd(int p, int o) {
    if(L[o] == R[o]) return val[o] = (node) { ip[L[o]], 0, 1 }, void(); 
    if(p <= md[o]) upd(p, ch[o][0]); else upd(p, ch[o][1]);
    val[o] = val[ch[o][0]] + val[ch[o][1]];
}

void query(int o, int &pos, node &cur) {
    if(L[o] == R[o]) {
        node t = cur + val[o]; 
        if(!t.fl) return;
        cur = t; pos = L[o]; return; 
    } node t = cur + val[ch[o][0]];
    if(!t.fl) return query(ch[o][0], pos, cur);
    else return cur = t, pos = md[o], query(ch[o][1], pos, cur);
}

int main() {
	n = in; rep(i, 1, n) p[i] = in, ip[p[i]] = i; rep(i, 2, n) G[in].eb(i);
    T :: init(); build(rt);
    Q = in;
    while(Q--) {
        int op = in;
        if(op == 1) {
            int x = in, y = in;
            swap(p[x], p[y]); swap(ip[p[x]], ip[p[y]]); upd(p[x], rt); upd(p[y], rt);
        } else {
            int pos = 0; node res = { 0, 0, 1 };
            query(rt, pos, res); printf("%d\n", pos + 1);
        }
    }
	return 0;
}