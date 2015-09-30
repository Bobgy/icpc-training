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
char s[maxn];
vector<int> g[maxn];
LL Res;
inline int gg(char c){
  return c=='('?1:-1;
}
namespace TreeDiv{
    bool isct[maxn];
    int sz[maxn],dep[maxn],root,minsz,total;
    void getSz(int u,int f){
        sz[u]=1;
        for(size_t i=0;i<g[u].size();++i){
            int v=g[u][i];
            if(v==f || isct[v]) continue;
            getSz(v,u),sz[u]+=sz[v];
        }
    }
    void getCenterDfs(int u,int f){
        int m=0;
        for(size_t i=0;i<g[u].size();++i){
            int v=g[u][i];
            if(v==f || isct[v]) continue;
            getCenterDfs(v,u),m=max(m,sz[v]);
        }
        m=max(m,total-sz[u]);
        if(m<minsz) minsz=m,root=u;
    }
    inline int getCenter(int u){
        getSz(u,-1);
        minsz=(int)1e9; total=sz[u];        
        getCenterDfs(u,-1);
        return root;
    }
    int mp1[maxn],mp2[maxn];
    int pc[maxn<<1],pcl;
    int sc;
    void dfs1(int u,int fa,int h1,int mn1,int h2,int mn2){
      //right
      int t1=gg(s[u]);
      h1+=t1;
      if(max(t1,t1+mn1)<=0){        
//        out(u);out(mp1[abs(h1)]);
        Res+=mp1[abs(h1)];
      }
      //left
      int t2=gg(s[u]);
      h2+=t2;
//      out(u);out(t2);out(mn2+t2);
      if(min(t2,mn2+t2)>=0){
//        out(u);out(mp2[abs(h2)]);
        Res+=mp2[abs(h2)];       
      }
      for(int v:g[u])if(v!=fa && !isct[v]){
        dfs1(v,u,h1,max(t1,t1+mn1),h2,min(t2,mn2+t2));
      }
    }
    void dfs2(int u,int fa,int h1,int mn1,int h2,int mn2){
      int t1=gg(s[u]);
      h1+=t1;
      if(max(t1,t1+mn1)<=0){
        ++mp2[abs(h1)];
        pc[pcl++]=abs(h1);
      }
      int t2=gg(s[u]);
      h2+=t2;
      if(min(t2,mn2+t2)>=0){
        ++mp1[abs(h2)];
        pc[pcl++]=abs(h2);
      }
      for(int v:g[u])if(v!=fa && !isct[v]){
        dfs2(v,u,h1,max(t1,t1+mn1),h2,min(t2,mn2+t2));
      }
    }
    void divide(int u){
        u=getCenter(u);isct[u]=1;
//        mp1.clear(),mp2.clear();
        ++mp1[0],++mp2[0];sc=0;
        pcl=0;
        int ctr=u;
//        out(ctr);
        for(int k=0;k<g[u].size();++k){
            int v=g[u][k];
            if(isct[v]) continue;
            dfs1(v,u,gg(s[u]),gg(s[u]),gg(s[u]),gg(s[u]));
            dfs2(v,u,0,0,0,0);
        }
        mp1[0]=mp2[0]=0;
        rep(i,pcl){
          int x=pc[i];
          mp1[x]=mp2[x]=0;
        }
        for(int k=0;k<g[u].size();++k){
            int v=g[u][k];
            if(isct[v]) continue;
            divide(v);
        }
    }    
    void build(int rt,int n){  
        for(int i=0;i<=n;++i)isct[i]=0;
        divide(rt);
    }
}
int main(){
  int n;scanf("%d",&n);
  scanf("%s",s+1);
  rep(i,n-1){
    int u,v;scanf("%d%d",&u,&v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  TreeDiv::build(1,n);
  printf("%lld\n",Res);
  return 0;
}
