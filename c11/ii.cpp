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
  freopen("improvements.in","r",stdin);
  freopen("improvements.out","w",stdout);
  int n;scanf("%d",&n);
  static int p[200005],q[200005];
  rep(i,n){
    int x;scanf("%d",&x);--x;
    p[x]=i;
  }
  rep(i,n)q[i]=p[n-1-i];
  
  return 0;
}
