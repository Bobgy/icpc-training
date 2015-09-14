#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define out(x) cerr<<#x"="<<x<<endl
/*
#undef out
#define out(x)
*/
#define pb push_back
#undef assert
#define assert(x) while(!(x));
typedef vector<int> vi;
typedef double flt;
typedef long long LL;
vi E[51234];
int n;
LL F[16][51234], G[16][51234];
int fa[16][51234];
int h[51234];
LL (&f)[51234]=F[0], (&g)[51234]=G[0];
void dfs(int x, int pre, int H=0){
    fa[0][x]=~pre ? pre : x;
    h[x]=H;
    for(auto u: E[x])if(u!=pre)dfs(u, x, H+1);
    if(pre!=-1){
        f[x]=E[x].size();
        for(auto u: E[x])if(u!=pre)
            f[x]+=f[u];
    }
}
void dfs2(int x, int pre){
    LL sum=E[x].size();
    for(auto u: E[x])if(u!=pre)
        sum+=f[u];
    if(~pre)sum+=g[x];
    for(auto u: E[x])if(u!=pre){
        g[u]=sum-f[u];
        dfs2(u, x);
    }
}
void init(){
    REP(i,n)f[i]=g[i]=0.0;
    dfs(0, -1);
    dfs2(0, -1);
    //REP(i,n)printf("i=%d f=%lld g=%lld\n", i, f[i], g[i]);
    for(int dep=1;dep<16;++dep){
        REP(i,n){
            int fat=fa[dep-1][i];
            fa[dep][i]=fa[dep-1][fat];
            F[dep][i]=F[dep-1][i]+F[dep-1][fat];
            G[dep][i]=G[dep-1][i]+G[dep-1][fat];
        }
    }
}
LL len(int u, int v){
    LL res=0;
    LL (*ff)[51234]=F, (*gg)[51234]=G;
    if(h[u]<h[v])swap(u,v),swap(ff,gg);
    int log=15;
    for (int i=log;u!=v && i>=0;--i)
        if (h[u]-(1<<i)>=h[v]) {
            res+=ff[i][u];
            u=fa[i][u];
        }
    if(u==v)return res;
    for (int i=log; u!=v && i>=0; --i)
        if (fa[i][u]!=fa[i][v]) {
            res+=ff[i][u]+gg[i][v];
            u=fa[i][u];
            v=fa[i][v];
        }
    assert(fa[0][u]==fa[0][v] && u!=v);
    return res+ff[0][u]+gg[0][v];
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        REP(i,n-1){
            int u, v;
            scanf("%d%d",&u,&v);
            E[u].pb(v);
            E[v].pb(u);
        }
        init();
        int q;
        scanf("%d",&q);
        while(q--){
            int p;
            scanf("%d",&p);
            int v0, v1;
            scanf("%d",&v0);
            LL ans=0;
            while(p--){
                scanf("%d",&v1);
                ans+=len(v0, v1);
                v0=v1;
            }
            printf("%lld.0000\n", ans);
        }
        if(T)puts("");
        REP(i,n)E[i].clear();
    }
}
