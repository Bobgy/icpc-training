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
using node=tuple<int,int,int>;
bool ok(node a,node b){
  return get<0>(a)+get<0>(b)==1 && get<1>(a)==get<1>(b);
}
inline int id(char x){
  return islower(x)?x-'a':x-'A';
}
int main(){
  int n;scanf("%d",&n);  
  static char s[10005];scanf("%s",s);
  static int g[10005];
  stack<node> st;
  rep(i,n+n){
    auto u=node(!!isupper(s[i]),id(s[i]),i);
    if(st.empty()){
      st.push(u);
    }else{
      if(ok(st.top(),u)){
        g[i]=get<2>(st.top());
        g[get<2>(st.top())]=i;
        st.pop();
      }else st.push(u);
    }
  }
  static int ss[10005];
  ss[0]=!!islower(s[0]);
  REP(i,1,n+n)ss[i]=ss[i-1]+(islower(s[i])?1:0);
  if(!st.empty())puts("Impossible");
  else{
    int ct=0;
    rep(i,n+n)if(isupper(s[i]))printf("%d%c",ss[g[i]]," \n"[++ct==n]);
  }
  return 0;
}
