#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
#define fi first
#define se second
#define rep(i,b) for(int i=(0);i<(int)(b);++i)
#define REP(i,a,b) for(int i=(a);i<(int)(b);++i)
#define FOR(i,a,b) for(int i=(a);i<=(int)(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(int)(b);--i)
#define ALL(x) x.begin(),x.end()

int main(){
  freopen("alter.in","r",stdin);
  freopen("alter.out","w",stdout);
  int n,m;scanf("%d%d",&n,&m);
  printf("%d\n",n/2+m/2);
  for(int j=2;j<=m;j+=2)printf("%d %d %d %d\n",1,j,n,j);
  for(int i=2;i<=n;i+=2)printf("%d %d %d %d\n",i,1,i,m);
  return 0;
}
