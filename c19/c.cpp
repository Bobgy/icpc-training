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
const int maxn=1000005;
bool bad[maxn];
bool ok(int x){
  if(x>1000000)return 0;
  return !bad[x];
}
int rev(int x){
  static int d[100];int c=0;
  while(x)d[c++]=x%10,x/=10;
  int y=0;
  rep(i,c)y=y*10+d[i];
  return y;
}
int main(){
  bad[0]=bad[1]=1;
  vector<int> p;
  for(int i=2;i<=1000000;++i)if(!bad[i])
  for(LL j=(LL)i*i;j<=1000000;j+=i)bad[j]=1;
  for(int i=2,j;i<=1000000;++i)if(!bad[i] && ok(j=rev(i)) && i!=j)p.push_back(i);
  int k;scanf("%d",&k);--k;
  if(k>=p.size())puts("-1");
  else printf("%d\n",p[k]);
  return 0;
}
