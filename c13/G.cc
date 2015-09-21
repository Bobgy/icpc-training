#include <bits/stdc++.h>
using namespace std;
#define RER(i,L,R) for(int i=L;i<=int(R);++i)
#define REP(i,n) for(int i=0;i<n;++i)
typedef long long LL;
const LL MOD = 1e9+7;
LL power(LL x, LL n){
    LL res=1;
    for(; n; x=x*x%MOD, n>>=1)
        if(n&1)res=res*x%MOD;
    return res;
}
const LL i2=power(2,MOD-2);
LL calc(LL x, int i, int j){
    assert(j);
    if(j<=1)return x*power(power(i,MOD-2),2-j)%MOD;
    return x*power(i,j-2)%MOD;
}
inline void fix(LL &x){
    if(x<0)x+=MOD;
}

//f[i][j], i points, j bi-connected components
//g[i][j], i points, j connected components
LL f[51][51], g[51][51], c[51][51];
void init(){
    c[0][0]=1;
    RER(i,0,49)RER(j,0,i){
        c[i+1][j]=(c[i+1][j]+c[i][j])%MOD;
        c[i+1][j+1]=(c[i+1][j+1]+c[i][j])%MOD;
    }
    memset(f, 0, sizeof f);
    f[0][0]=1;
    g[0][0]=1;
    RER(i,1,50){
        LL sum=0, sum2=0;
        RER(j,2,i){
            f[i][j]=g[i][j]=0;
            RER(k,1,i-j+1){
                f[i][j]=(f[i][j]+k*f[i-k][j-1]%MOD*calc(f[k][1],k,1)%MOD*c[i-1][k-1])%MOD;
                g[i][j]=(g[i][j]+g[i-k][j-1]*g[k][1]%MOD*c[i-1][k-1])%MOD;
            }
            fix(f[i][j]); fix(g[i][j]);
            // if(i<=3)printf("f[%d][%d]=%lld g=%lld\n", i, j, f[i][j], g[i][j]);
            sum=(sum+calc(f[i][j], i, j))%MOD;
            sum2=(sum2+g[i][j])%MOD;
        }
        LL tot=power(2, i*(i-1)/2);
        g[i][1]=(tot-sum2)%MOD;
        f[i][1]=(tot-sum2-sum)*i%MOD;
        fix(f[i][1]); fix(g[i][1]);
        // if(i<=3)printf("f[%d][%d]=%lld g=%lld\n", i, 1, f[i][1], g[i][1]);
    }
}
int main(){
    init();
    int n, b;
    scanf("%d%d",&n,&b);
    b=min(b,n-1);
    LL ans=0;
    RER(i,1,b+1){
        ans=(ans+calc(f[n][i],n,i))%MOD;
    }
    if(ans<0)ans+=MOD;
    printf("%lld\n", ans);
}
