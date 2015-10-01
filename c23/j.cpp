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
void gao(vector<int> &a){
  int n=a.size();
  if(n==1)return;
  vector<int> a1,a2;
  rep(i,n/2)a1.push_back(a[i]);
  REP(i,n/2,n)a2.push_back(a[i]);
  gao(a1);gao(a2);
  vector<int> b;
/*  
  puts("a1");
  for(int x:a1)printf("%d ",x);puts("");
  puts("a2");
  for(int x:a2)printf("%d ",x);puts("");  
*/  
  int i=0,j=0;
  while(i<a1.size() || j<a2.size()){
    if(i==a1.size())b.push_back(a2[j++]);
    else if(j==a2.size())b.push_back(a1[i++]);
    else{
//      out(i);out(j);
      printf("1 %d %d\n",a1[i],a2[j]);
      fflush(stdout);
      static char s[1000];scanf("%s",s);
      if(s[0]=='Y')b.push_back(a1[i++]);
      else b.push_back(a2[j++]);
    }
  }
  a=b;
}
int main(){
  int n;scanf("%d",&n);
  vector<int> a(n);
  rep(i,n)a[i]=i+1;
//  rep(i,n)out(a[i]);
  gao(a);
  printf("0");
  for(int x:a)printf(" %d",x);puts("");fflush(stdout);
  return 0;
}
