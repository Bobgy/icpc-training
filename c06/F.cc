#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define out(x) cerr<<#x"="<<x<<endl
typedef long long LL;
char s[112345];
int pre[112345];
int main(){
    int T;
    scanf("%d",&T);
    REP(tt,T){
        scanf("%s", s);
        int L=strlen(s);
        for(char *p=s; *p; ++p)
            *p=*p=='a'?-1:1;
        pre[0]=1;
        REP(i,L)pre[i+1]=pre[i]+s[i];
        int ans=abs(pre[L]);
        if(pre[L]>0){
            REP(i,L)pre[i+1]-=pre[L];
        }
        //REP(i,L+1)printf("%d%c",pre[i]," \n"[i==L]);
        int ma=0, ma2=0;
        REP(i,L)if(pre[i+1]>0 && s[i]==1){
            int x=pre[i+1];
            if(x>ma)ma2=ma,ma=x;
            else if(x>ma2)ma2=x;
        }
        ans+=(ma-ma2)+ma2*2;
        printf("Case %d: %d\n", tt+1, ans);
    }
}
