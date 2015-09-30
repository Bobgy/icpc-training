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
const int mod=(int)1e9+9;
int n,fa[3000005],sz[3000005];
const int maxn=3000005;
int fac[maxn],invf[maxn],g[maxn];
inline int add(int x,int y){
  x+=y;if(x>=mod)x-=mod;
  return x;
}
inline int sub(int x,int y){
  x-=y;if(x<0)x+=mod;
  return x;
}
inline int mul(int x,int y){
  return (LL)x*y%mod;
}
inline int gg(int x){
  assert(x%3==0);
  x/=3;
  int t=g[x];
  return t;
}
inline int C(int a,int b){
  int t=mul(fac[a],invf[b]);
  t=mul(t,invf[a-b]);
  return t;
}
int find(int x){
  return fa[x]==-1?x:fa[x]=find(fa[x]);
}
inline int gao(vector<pii> &p){
  vector<int> q;
  for(pii o:p)q.push_back(o.fi),q.push_back(o.se);
  sort(ALL(q));q.erase(unique(ALL(q)),q.end());
  for(int x:q)fa[x]=-1,sz[x]=1;
  for(pii e:p){
    int u=e.fi,v=e.se;
    u=find(u),v=find(v);
    if(u!=v){
      fa[u]=v,sz[v]+=sz[u];
    }
  }
  int a=0,m=3*n;
  for(int x:q)if(fa[x]==-1){
    if(sz[x]>3){
      return 0;
    }
    assert(sz[x]>1);    
    if(sz[x]==2)++a;
    m-=sz[x];
  }
  int res=1;
//  out(C(5,2));
  FOR(i,1,a){
    res=mul(res,C(m,1));
    --m;
  }
  res=mul(res,gg(m));
  res=mul(res,invf[m/3]);
  return res;
}
inline int pw(int a,int p){
  int r=1;
  for(;p;p>>=1,a=mul(a,a))if(p&1)r=mul(r,a);
  return r;
}
void init(){
  int n=::n*3;
  fac[0]=invf[0]=1;
  FOR(i,1,n){
    fac[i]=mul(i,fac[i-1]);
  }
  invf[n]=pw(fac[n],mod-2);
  FORD(i,n-1,1){
    invf[i]=mul(i+1,invf[i+1]);
  }
  g[0]=1;
  FOR(i,1,n/3){
    g[i]=mul(C(3*i,3),g[i-1]);
  }
}
int main(){
  int m;
  scanf("%d%d",&n,&m);
  init();
  vector<pii> p1,p2;
  rep(i,m){
    int u,v,c;scanf("%d%d%d",&u,&v,&c);
    if(c)p2.push_back(pii(u,v));
    else p1.push_back(pii(u,v));
  }
  int all=gao(p1),cr=0;
//  out(all);
  int c=SIZE(p2);
  REP(msk,1,1<<c){
    vector<pii> q=p1;
    int cc=0;
    rep(i,c)if(msk>>i&1){
      ++cc;
      q.push_back(p2[i]);
    }
    if(cc&1)cr=add(cr,gao(q));
    else cr=sub(cr,gao(q));
  }
  int res=sub(all,cr);
  printf("%d\n",res);
  return 0;
}
