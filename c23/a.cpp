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
unordered_map<int,vector<int> >p[1<<10];
int M[10005],X[10005];
int main(){
  int n,m;scanf("%d%d",&n,&m);
  rep(i,n){
    int x;scanf("%d",&x);x=-x;
    int t;scanf("%d",&t);
    int msk=0;
    while(t--){
      int y;scanf("%d",&y);--y;
      msk|=1<<y;
    }
    rep(j,1<<10)p[j][msk&j].push_back(x);
    M[i]=msk;X[i]=x;
  }
  rep(i,1<<10)
  for(auto &qq:p[i]){  
    auto &q=qq.se;
    sort(ALL(q));
//    q.erase(unique(ALL(q)),q.end());
  }
  int Q;scanf("%d",&Q);
  while(Q--){
    int x;scanf("%d",&x);--x;
    int t;scanf("%d",&t);
    int msk=0;
    while(t--){
      int y;scanf("%d",&y);--y;
      msk|=1<<y;
//      out(y);
//      out(msk);
    }
//    out(msk);
    int mm=msk;
    msk=msk&M[x];
    int res=(int)(lower_bound(ALL(p[mm][msk]),X[x])-p[mm][msk].begin())+1;
    printf("%d\n",res);
  }
  return 0;
}
