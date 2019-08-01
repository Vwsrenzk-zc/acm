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
int vis[maxn];
int getpos(double x) {
    return lower_bound(sh + 1, sh + 1 + tot, x) - sh;
}

int main() {
//    freopen("in.txt", "r", stdin);
//    ios::sync_with_stdio(false);
    int n, cas = 1;
    while(~scanf("%d", &n)) {
        if(n == 0) break;
        memset(sh, 0, sizeof(sh));
        tot = 0, len = 0;
        for(int i = 0; i <= 2 * n; i++) {
            s[i] = node(0, 0, 0, 0);
            vis[i] = 0;
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
        sh[0] = 0;
        double ans = 0;
        for(int i = 1; i <= len; i++) {
            int l = getpos(s[i].y1), r = getpos(s[i].y2);
            double sum = 0;
            for(int j = 1; j <= tot; j++) {
                if(vis[j]) sum += sh[j] - sh[j - 1];
                if(j > l && j <= r) vis[j] += s[i].k;
            }
            ans += sum * (s[i].x - s[i - 1].x);
        }
        printf("Test case #%d\n", cas++);
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
