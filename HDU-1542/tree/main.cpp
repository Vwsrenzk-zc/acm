#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3;
double sh[maxn];
int tot = 0, len = 0;
struct node {
    double x, y1, y2;
    int k;
    node(double _l = 0, double _r = 0, double _h = 0, int _f = 0): x(_l), y1(_r), y2(_h), k(_f) {};
} s[maxn];

bool cmp(node a, node b) {
    return a.x < b.x;
}
int getpos(double x) {
    return lower_bound(sh + 1, sh + 1 + tot, x) - sh;
}

struct SegmentTree {
    int l, r, add;
    double sum;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define add(x) tree[x].add
} tree[maxn * 4];

void build(int p, int l, int r) {
    sum(p) = 0; add(p) = 0;
    l(p) = l, r(p) = r;
    if(l == r) return;
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
}

void spread(int p) {
    if(add(p)) sum(p) = sh[r(p) + 1] - sh[l(p)];
    else sum(p) = sum(p * 2) + sum(p * 2 + 1);
}

void change(int p, int l, int r, int d) {
    if(l <= l(p) && r >= r(p)) {
        add(p) += d;
        spread(p);
        return;
    }
    int mid = (l(p) + r(p)) / 2;
    if(l <= mid) change(p * 2, l, r, d);
    if(r > mid) change(p * 2 + 1, l, r, d);
    spread(p);
}
int n, cas = 1;

void init() {
    tot = 0, len = 0;
    for(int i = 0; i <= 2 * n; i++) {
        s[i] = node(0, 0, 0, 0);
        sh[i] = 0;
    }
    double x1, x2, y1, y2;
    for(int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        sh[++tot] = y1;
        sh[++tot] = y2;
        s[++len] = node(x1, y1, y2, 1);
        s[++len] = node(x2, y1, y2, -1);
    }
    sort(sh + 1, sh + 1 + tot);
    tot = unique(sh + 1, sh + 1 + tot) - sh - 1;
    sort(s + 1, s + 1 + len, cmp);
    build(1, 1, tot - 1);
    for(int i = 0; i < 5 * tot; i++) sum(i) = 0;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    ios::sync_with_stdio(false);
    while(~scanf("%d", &n)) {
        if(n == 0) break;
        init(); double ans = 0;
        for(int i = 1; i < len; i++) {
            int l = getpos(s[i].y1), r = getpos(s[i].y2) - 1;
            change(1, l, r, s[i].k);
            ans += sum(1) * (s[i + 1].x - s[i].x);
        }
        printf("Test case #%d\n", cas++);
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
