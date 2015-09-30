#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
#define fi first
#define se second
#pragma comment(linker, "/STACK:1024000000,1024000000") 
#define out(x) cout<<#x<<"="<<x<<endl
#define rep(i,b) for(int i=(0);i<(int)(b);++i)
#define REP(i,a,b) for(int i=(a);i<(int)(b);++i)
#define FOR(i,a,b) for(int i=(a);i<=(int)(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(int)(b);--i)
#define ALL(x) x.begin(),x.end()
#define SIZE(x) (int)(x).size()
using namespace std;
const int maxn=2005;
vector<pii> g[maxn];
vector<LL> C;
int n,s[maxn];
LL dp[maxn],curw;
void dfs1(int u,int f){
  dp[u]=0;
  for(pii e:g[u])if(e.fi!=f){
    int v=e.fi,w=e.se;
    dfs1(v,u);
    dp[v]+=w;
    dp[u]=max(dp[u],dp[v]);
  }
}
void dfs2(int u,int f,int cw){
  bool fd=0;
  while(1){
    int maxc=-1;LL sc=0;
    for(pii e:g[u]){
      int v=e.fi;
      if(v==f)continue;
      if(maxc==-1 || dp[v]>dp[maxc])maxc=v,sc=dp[v];
    }
    if(!fd){
      fd=1;
      LL tp=(LL)curw*(cw+sc);
      C.push_back(tp);
    }
    if(maxc==-1)break;
    for(pii e:g[u]){
      int v=e.fi,w=e.se;
      if(v==f || v==maxc)continue;
      dfs2(v,u,w);
    }
    f=u,u=maxc;
  }
}
void gao(int x){
  dfs1(x,-1);
  curw=s[x];
  dfs2(x,-1,0);
}
int main(){
  int m;scanf("%d%d",&n,&m);
  rep(i,n-1){
    int u,v,w;scanf("%d%d%d",&u,&v,&w);
    g[u].push_back(pii(v,w));
    g[v].push_back(pii(u,w));
  }
  FOR(i,1,n)scanf("%d",s+i);
  FOR(i,1,n)gao(i);
  sort(ALL(C));reverse(ALL(C));
  m=min(m,SIZE(C));
  LL res=0;
  rep(i,m)res+=C[i];
  printf("%lld\n",res);
  return 0;
}
