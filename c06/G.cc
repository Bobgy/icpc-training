#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define out(x) cerr<<#x"="<<x<<endl
const int MAXN = 2001;
const int MOD = 1e9 + 7;
typedef long long LL;
int f[4][2011][2015][4];
int C[2011][2015];
int b[2123], P[2123];
inline void gao(int &x, int y){
    if(y)x=(x+y)%MOD;
}
void init(){
    P[0]=1;
    REP(i,MAXN)P[i+1]=(i+1)*LL(P[i])%MOD;
    C[0][0]=1;
    REP(i,MAXN)REP(j,i+1){
        gao(C[i+1][j], C[i][j]);
        gao(C[i+1][j+1], C[i][j]);
    }
    REP(st,4){
        int (&g)[2011][2015][4]=f[st];
        g[0][0][st]=1;
        REP(i,MAXN)REP(j,i+1){
            gao(g[i+1][j+1][0], g[i][j][0]);
            gao(g[i+1][j+1][1], g[i][j][0]);
            gao(g[i+1][j+1][2], g[i][j][0]);
            gao(g[i+1][j+1][2], g[i][j][1]);
            gao(g[i+1][j+1][3], g[i][j][1]);
            gao(g[i+1][j+1][1], g[i][j][2]);
            gao(g[i+1][j+1][2], g[i][j][2]);
            gao(g[i+1][j+1][3], g[i][j][3]);
            gao(g[i+1][j][0], g[i][j][0]);
            gao(g[i+1][j][2], g[i][j][1]);
            gao(g[i+1][j][0], g[i][j][2]);
            gao(g[i+1][j][2], g[i][j][3]);
        }
    }
}
int a[10], n, k;
inline int nxt(int id){return id==n-1 ? 0 : id+1;}
inline int pre(int id){return id==0 ? n-1 : id-1;}
int main(){
    init();
    int T;
    scanf("%d",&T);
    REP(tt,T){
    //for(n=3; n<=10; ++n)for(k=0; k<=n; ++k){
        scanf("%d%d",&n,&k);
        int ans=0;
        if(n<4){
            ans = P[n];
        } else {
            REP(i,n+1)b[i]=0;
            int p[2][4]={{-1, n-1, 0, 1}, {-1, n-2, n-1, 0}};
            REP(i,4){
                int p0=p[0][i];
                REP(j,4){
                    int pn=p[1][j];
                    if(~p0 && p0==pn)continue;
                    int bg=0, ed=0;
                    if(~p0){
                        if(p0<2)bg|=1<<(1-p0);
                        else ed|=1<<(n-1-p0);
                    }
                    if(~pn){
                        if(pn<1)bg|=1<<(1-pn);
                        else ed|=1<<(n-1-pn);
                    }
                    int dk=bool(~p0)+bool(~pn);
                    for(int kk=0; kk<=n-2; ++kk){
                        int tmp=0;
                        REP(i,4)if((i&ed)==0){
                            gao(tmp, f[bg][n-2][kk][i]);
                        }
                        gao(b[kk+dk], tmp*LL(P[n-kk-dk])%MOD);
                    }
                }
            }
            //REP(i,n+1)printf("%d%c",b[i]," \n"[i==n]);
            for(int i=n; i>=k; --i){
                for(int j=k; j<i; ++j){
                    b[j]-=b[i]*LL(C[i][j])%MOD;
                    if(b[j]<0)b[j]+=MOD;
                }
            }
            //REP(i,n+1)printf("%d%c",b[i]," \n"[i==n]);
            for(int i=k; i<=n; ++i)gao(ans, b[i]);
        }
        printf("Case %d: %d\n", tt+1, ans);
        /*
        int ver=0;
        REP(i,n)a[i]=i;
        do{
            int cnt=0;
            REP(i,n)cnt+=(a[i]==nxt(i) || a[i]==i || a[i]==pre(i));
            ver+=cnt>=k;
        }while(next_permutation(a, a+n));
        assert(ver==ans);
        */
    }
}
