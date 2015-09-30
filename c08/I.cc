#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define RER(i,L,R) for(int i=0;i<=int(R);++i)
#define out(x) (cerr<<#x"="<<(x)<<endl,(x))
typedef long long LL;
LL r[151], a, b;
int s[151], n, ps[151], sum;
LL f[151][151];
bool init[151];
const LL INF = 1e16;
int dfs(int i, LL nu);
bool ok(int i, LL M, int ans){
    if(s[i]+ps[i+1]-dfs(i+1, -M-r[i])>=ans)return true;
    if(M>0 && dfs(i+1, M-r[i]-1)>=ans)return true;
    return false;
}
int dfs(int i, LL nu){
    if(i>=n)return 0;
    LL (&g)[151] = f[i];
    if(init[i])return upper_bound(g, g+sum+1, nu)-g-1;
    g[0]=-INF;
    LL L=-INF, R;
    RER(ans,1,sum){
        R=INF;
        while(L<=R){
            LL M=(L+R)/2;
            if(ok(i,M,ans))R=M-1;
            else L=M+1;
        }
        g[ans]=R+1;
    }
    init[i]=1;
    return dfs(i, nu);
}
int main(){
    cin>>n>>a>>b;
    sum=0;
    REP(i,n)cin>>r[i]>>s[i],sum+=s[i];
    ps[n]=0;
    for(int i=n-1;i>=0;--i)ps[i]=ps[i+1]+s[i];
    int sa = dfs(0, a-b), sb = ps[0]-sa;
    printf("%d %d\n", sa, sb);
}
