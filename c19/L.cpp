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
int co[350],n,m,C;
struct Point{
  int x,y;
  void read(){
    scanf("%d%d",&x,&y);
  }
  Point(){}
  Point(int x,int y):x(x),y(y){}
  friend Point operator-(Point a,Point b){
    return Point(a.x-b.x,a.y-b.y);
  }
  void prt(){
    printf("[%d %d]\n",x,y);
  }
}A[350],P[50];
inline int crs(Point a,Point b){
  return a.x*b.y-a.y*b.x;
}
inline int dot(Point a,Point b){
  return a.x*b.x+a.y*b.y;
}
double dp[50][50][1<<6];
bool inq[50][50][1<<6];
const double inf=1e20;
const double eps=1e-8;
int M[50][50][50];
inline int dcmp(double x){
  return fabs(x)<eps?0:x>0?1:-1;
}
inline double gdis(int a,int b){
  return hypot(P[a].x-P[b].x,P[a].y-P[b].y);
}
inline bool intri(Point o,Point a,Point b,Point c){
  int d1=crs(b-a,o-a)>0;
  int d2=crs(c-b,o-b)>0;
  int d3=crs(a-c,o-c)>0;
/*  
  o.prt();a.prt();b.prt();c.prt();
  (c-b).prt();
  (o-b).prt();
  out(d1);
  out(d2);
  out(d3);
*/
  return d1+d2+d3==0 || d1+d2+d3==3;
}
int main(){
  scanf("%d%d%d",&n,&m,&C);
  rep(i,n)A[i].read();
  rep(i,n)scanf("%d",co+i),--co[i];
  rep(i,m)P[i].read();  
  using state=tuple<int,int,int>;
  rep(i,m)
  rep(j,m)
  rep(k,1<<C)dp[i][j][k]=inf;
  queue<state> q;
  auto upd=[&](int i,int j,int k,double du){
    double &r=dp[i][j][k];
    if(dcmp(r-du)>0){
      r=du;
      if(!inq[i][j][k])q.push(state(i,j,k)),inq[i][j][k]=1;
    }     
  };
  rep(i,m)
  rep(j,m)if(j!=i)
  rep(k,m)if(k!=j && k!=i){
    int msk=0;
    rep(o,n)if(intri(A[o],P[i],P[j],P[k]))msk|=1<<co[o];
    M[i][j][k]=msk;
    double pd=gdis(i,j)+gdis(j,k)+gdis(k,i);
    upd(i,j,msk,pd);
    upd(j,k,msk,pd);
    upd(k,i,msk,pd);
  }
  while(!q.empty()){
    state cst=q.front();q.pop();
    int i,j,msk;tie(i,j,msk)=cst;
    double du=dp[i][j][msk];
//    printf("at [%d %d %d] %.6f\n",i,j,msk,du);    
    inq[i][j][msk]=0;
    rep(k,m)if(k!=i && k!=j){
      int inner_msk=M[i][j][k];
      int nmsk=inner_msk|msk;
      double pd=gdis(i,k)+gdis(j,k)-gdis(i,j);
      upd(i,k,nmsk,du+pd);
      upd(k,i,nmsk,du+pd);
      upd(k,j,nmsk,du+pd);
      upd(j,k,nmsk,du+pd);
    }
  }
  double res=inf;
  rep(i,m)
  rep(j,m){
    double r=dp[i][j][(1<<C)-1];
    if(dcmp(r-res)<0)res=r;
  }
  if(dcmp(res-inf)==0)puts("-1");
  else printf("%.12f\n",res);
  return 0;
}
