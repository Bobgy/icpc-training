#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define RER(i,L,R) for(int i=L;i<=int(R);++i)
typedef long long LL;
struct P{
    int x, y;
    P(int x, int y):x(x),y(y){}
    P(){}
    P operator-(P r) const { return P(x-r.x, y-r.y); }
    LL operator*(P r) const { return x*(LL)r.y-y*(LL)r.x; }
    void read() { scanf("%d%d",&x,&y); }
} p[112345], s[1812345];
int L[412345], R[412345], tot, n;
void build(int x, int l, int r){
    if(l==r)return;
    int i=l;
    L[x]=tot;
    s[tot++]=p[l];
    s[tot++]=p[++i];
    for(; i<=r+1; ++i){
        while(tot>l+1 && (p[i]-s[tot-1])*(s[tot-1]-s[tot-2])<0)--tot;
        s[tot++]=p[i];
    }
    R[x]=tot-1;
    int m=(l+r)/2;
    build(x*2, l, m);
    build(x*2+1, m+1, r);
}
void init(){
    tot=0;
    build(1,0,n-2);
}
int u, v;
P pp;
bool check(int l, int r){
    while(l<r){
        int m=(l+r)/2;
        if(pp*(s[m+1]-s[m])<0)r=m;
        else l=m+1;
    }
    return pp*(s[l]-p[v])>0;
}
int gao(int x, int l, int r){
    int m=(l+r)/2;
    if(l==r){
        if(pp*(p[l]-p[v])>0 || pp*(p[l+1]-p[v])>0)return l;
        return -1;
    }
    if(l>=v){
        if(!check(L[x],R[x]))return -1;
    }
    if(v<=m){
        int res = gao(x*2, l, m);
        if (~res) return res;
    }
    return gao(x*2+1, m+1, r);
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        REP(i,n)p[i].read();
        init();
        REP(i,n-1){
            u=i, v=i+1;
            pp=p[v]-p[u];
            printf("%d%c", gao(1, 0, n-2)+1, " \n"[i+2==n]);
        }
    }
}
