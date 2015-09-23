#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
#define fi first
#define se second
#define out(x) cout<<#x<<"="<<x<<endl
#define rep(i,b) for(int i=(0);i<(int)(b);++i)
#define REP(i,a,b) for(int i=(a);i<(int)(b);++i)
#define FOR(i,a,b) for(int i=(a);i<=(int)(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(int)(b);--i)
#define ALL(x) x.begin(),x.end()
int n,X[100005],Y[100005];
pii p[100005];
int gao1(int x){
  if(x<=0)return abs(x-(1-n))+1;
  else return abs(x-(n-1))+1;
}
int gao2(int x){
  if(x<=n+1)return x-1;
  return n+n+1-x;
}
int main(){
  int m;scanf("%d%d",&n,&m);
  set<int> xx,yy;
  map<int,LL> sz;
  vector<int> q[2];
  rep(i,m){
    int x,y;scanf("%d%d",&x,&y);
    X[i]=x,Y[i]=m;
    p[i]=pii(x-y,x+y);
    xx.insert(x-y),yy.insert(x+y);
    ++sz[x-y];
    q[((x-y)%2+2)%2].push_back(x+y);
  }
  sort(ALL(q[0]));q[0].erase(unique(ALL(q[0])),q[0].end());
  sort(ALL(q[1]));q[1].erase(unique(ALL(q[1])),q[1].end());
  LL res=0,cr=0;
  for(int x:xx)res+=gao1(x);
  for(int x:yy)res+=gao2(x);
  for(int x:xx){
    int lo,hi;    
    if(x<=0)lo=2-x,hi=n+n+x;
    else lo=2+x,hi=n+n-x;
    int o=(x%2+2)%2;
    auto &qq=q[o];
    cr+=upper_bound(ALL(qq),hi)-lower_bound(ALL(qq),lo);
  }
  res=(LL)n*n-res+cr;
  printf("%lld\n",res);
  return 0;
}
