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
int m,f;
int a[105];
inline int mul(int a,int b){
  return (LL)a*b%m;
}
bitset<1015> p[1005],u[1005];
inline int getdecimal(char c){
  if(c>='0' && c<='9')return c-'0';
  return 10+(c-'a');
}
void read_user(int x){
  static char s[10005];
  scanf("%s",s);
  int k=0;
  for(char *pp=s;*pp;++pp){
    int d=getdecimal(*pp);
    rep(i,4){
      if(d&1)p[x].set(k);
      ++k;
      d>>=1;
    }
  }
}
void set_mask(int x,int uid){
  auto &b=u[x];
  rep(i,f){
    int j=mul(uid,a[i]);
    b.set(j);
  }
}
void prt(int x){
  cout<<p[x].to_string()<<endl;
}
bool good[1005];
int main(){
  freopen("filter.in","r",stdin);
  freopen("filter.out","w",stdout);
  scanf("%d%d",&m,&f);
  rep(i,f)scanf("%d",a+i);
  int n;scanf("%d",&n);
  rep(i,n)read_user(i);
  int Q;scanf("%d",&Q);
  rep(i,Q){
    int uid;scanf("%d",&uid);
    set_mask(i,uid);
    rep(j,n){
      auto t=u[i]&p[j];
      if(t==u[i])good[j]=1;
    }
  }
  int cnt=0;
  rep(i,n)cnt+=good[i];
  printf("%d",cnt);
  rep(i,n)if(good[i])printf(" %d",i);puts("");
  return 0;
}
