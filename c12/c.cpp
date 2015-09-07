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
int n;
using Date=tuple<int,int,int,int>;
struct Rec{
  Date d;
  int x,id,did;
  void read(int ii){
    id=ii;
    static char s[100];scanf("%s",s);
    x=atoi(s+1);
    x=s[0]=='-'?-x:x;
    int day,mon;
    int hr,mm;
    scanf("%d.%d",&day,&mon);
    scanf("%d:%d",&hr,&mm);
    d=Date(mon,day,hr,mm);
  }
  bool operator<(const Rec &o){
    return d<o.d;
  }
  void prt(){
    printf("%d %d\n",x,did);
  }
}P[100005];
struct Node{
  int l,r;
  LL sum,x;
}v[100005<<2];
void build(int l,int r,int x){
  v[x].l=l,v[x].r=r,v[x].sum=v[x].x=0;
  if(l==r)return;
  int m=l+r>>1;
  build(l,m,x<<1),build(m+1,r,x<<1|1);
}
void up(int x){
  auto &ls=v[x<<1];
  auto &rs=v[x<<1|1];
  v[x].sum=ls.sum+rs.sum;
  v[x].x=min(ls.x,ls.sum+rs.x);
}
void modify(int pos,int y,int x){
  if(v[x].l==v[x].r){
    v[x].sum=y;v[x].x=y;
    return;
  }
  int m=v[x].l+v[x].r>>1;
  if(pos<=m)modify(pos,y,x<<1);
  else modify(pos,y,x<<1|1);
  up(x);
}
int main(){
  scanf("%d",&n);
  vector<Date> iv;
  rep(i,n)P[i].read(i),iv.push_back(P[i].d);
  sort(ALL(iv));iv.erase(unique(ALL(iv)),iv.end());
  rep(i,n){
    P[i].did=(int)(lower_bound(ALL(iv),P[i].d)-iv.begin())+1;
  }
  build(1,n,1);
  int maxd=-1;
  rep(i,n){
    int x=P[i].x,d=P[i].did;
    modify(d,x,1);    
    LL ans=v[1].x;
    printf("%lld\n",min(ans,0LL));
  }
  return 0;
}
