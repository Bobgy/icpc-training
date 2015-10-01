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
using namespace std;
const int maxn=100005;
vector<pii> g[maxn];
int fa[maxn][20],gup[maxn][20],gdn[maxn][20],dep[maxn];
void dfs(int u,int f){
  fa[u][0]=f;
  REP(i,1,20){
    fa[u][i]=fa[fa[u][i-1]][i-1];
    gup[u][i]=gup[u][i-1]&&gup[fa[u][i-1]][i-1];
    gdn[u][i]=gdn[u][i-1]&&gdn[fa[u][i-1]][i-1];
  }
  for(pii e:g[u]){
    int v=e.fi,w=e.se;
    if(v==f)continue;
    dep[v]=dep[u]+1;
    if(w)gup[v][0]=0,gdn[v][0]=1;
    else gup[v][0]=1,gdn[v][0]=0;
    dfs(v,u);
  }
}
inline int lca(int u,int v){
  int d=dep[u]-dep[v],&c=d>=0?u:v;d=abs(d);
//  out(d);
  REP(i,0,20)if(d>>i&1){
    c=fa[c][i];
  }
  if(u==v)return u;
  FORD(i,19,0)if(fa[u][i]!=fa[v][i])
    u=fa[u][i],v=fa[v][i];
  return fa[u][0];
}
inline bool up(int x,int y){
  if(x==y)return 1;
  int d=dep[x]-dep[y];
  REP(i,0,20)if(d>>i&1){
    if(!gup[x][i])return 0;
    x=fa[x][i];
  }
  return 1;
}
inline bool dn(int x,int y){
  if(x==y)return 1;
  int d=dep[x]-dep[y];
//  out(d);
  REP(i,0,20)if(d>>i&1){
//    out(gdn[x][i]);
    if(!gdn[x][i])return 0;
    x=fa[x][i];
  }
  return 1;
}
int main(){
  int n;scanf("%d",&n);
  rep(i,n-1){
    int u,v;scanf("%d%d",&u,&v);
    g[u].push_back(pii(v,1));
    g[v].push_back(pii(u,0));
  }
  dfs(1,0);
  int Q;scanf("%d",&Q);
  while(Q--){
    int x,y;scanf("%d%d",&x,&y);
    int z=lca(x,y);
//    out(x);out(y);out(z);
//    out(gdn[2][0]);
//    out(dn(y,z));return 0;
    bool res=up(x,z) && dn(y,z);
    puts(res?"Yes":"No");    
  }
  return 0;
}
