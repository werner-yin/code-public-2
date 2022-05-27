#include <bits/stdc++.h>

#ifndef YJR_2333_TEST
#include "kth.h"
#else
#include <stdio.h>
#include <assert.h>

int get_a(int p);
int get_b(int p);
int get_c(int p);
int query_kth(int n_a, int n_b, int n_c, int k);

#define MaxN 100000
#define INF 2147483647

static int a_n, b_n, c_n;
static int a[MaxN];
static int b[MaxN];
static int c[MaxN];

static int tot_get;

int get_a(int p)
{
	tot_get++;
	if (0 <= p && p < a_n)
		return a[p];
	return INF;
}
int get_b(int p)
{
	tot_get++;
	if (0 <= p && p < b_n)
		return b[p];
	return INF;
}
int get_c(int p)
{
	tot_get++;
	if (0 <= p && p < c_n)
		return c[p];
	return INF;
}

int main()
{
#ifdef YJR_2333_TEST
	freopen("ex_kth1.in", "r", stdin);
#endif
	int i;
	int res, k;

	assert(scanf("%d %d %d %d", &a_n, &b_n, &c_n, &k) == 4);
	for (i = 0; i < a_n; i++)
		assert(scanf("%d", &a[i]) == 1);
	for (i = 0; i < b_n; i++)
		assert(scanf("%d", &b[i]) == 1);
	for (i = 0; i < c_n; i++)
		assert(scanf("%d", &c[i]) == 1);

	tot_get = 0;
	res = query_kth(a_n, b_n, c_n, k);
	printf("%d %d\n", res, tot_get);

	return 0;
}
#endif

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

int query_kth(int na, int nb, int nc, int k) {
	int la = 0, lb = 0, lc = 0;
	while(k > 2) {
		int ta = get_a(k / 3 + la - 1), tb = get_b(k / 3 + lb - 1), tc = get_c(k / 3 + lc - 1);
		if(ta <= tb && ta <= tc) la += k / 3, k -= k / 3;
		else if(tb <= ta && tb <= tc) lb += k / 3, k -= k / 3;
		else lc += k / 3, k -= k / 3;
	}
	vec pot = { get_a(la), get_a(la + 1), get_b(lb), get_b(lb + 1), get_c(lc), get_c(lc + 1) };
	sort(pot.begin(), pot.end()); return pot[k - 1];
}
