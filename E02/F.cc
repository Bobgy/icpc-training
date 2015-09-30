#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
typedef long long LL;
const LL K = 1e18;
void gao(){
    double ma=1e10;
    int j=-1;
    for(int i=2;i<=30;++i){
        double tmp = i+log(K)/log(i);
        if(tmp<ma){
            ma=tmp;
            j=i;
        }
    }
    //                       9          18            27
    printf("%d %d %.10lf\n", j, (int)(log(K)/log(j)), ma);
}
int g[30][30];
void init(int n, int m){
    memset(g, 0, sizeof g);
    REP(i,n)REP(j,n)g[i][j]=1;
    REP(i,m-1)g[n+i][n+i+1]=1;
}
void fit(LL k){
    init(9, 19);
    int now=9;
    while(k){
        int r=k%9;
        k/=9;
        assert(now<=27);
        if(now>27)while(1)puts("sldkf");
        REP(i,r)g[i][now]=1;
        ++now;
    }
}
int main(){
    //gao();
    int T;
    scanf("%d",&T);
    while(T--){
        LL k;
        scanf("%lld",&k);
        printf("%d %d\n", 9+19, 20);
        fit(k);
        REP(i,28){
            REP(j,28)printf("%d",g[i][j]);
            putchar('\n');
        }
    }
}
