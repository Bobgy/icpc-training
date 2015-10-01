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

int main(){
  int n;scanf("%d",&n);
  static int c[1005];
  int s=0;
  rep(i,n){
    scanf("%d",c+i);
    s+=c[i];
  }
//  assert(s%n==0);
  s/=n;
  int res=0;
  rep(i,n)res+=c[i]>s;
  printf("%d\n",res);
  return 0;
}
