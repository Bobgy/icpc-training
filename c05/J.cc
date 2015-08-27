#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int x, y, w;
    void read(){
        scanf("%d%d%d",&x,&y,&w);
        --x; --y;
    }
    bool operator<(Edge r) const {return w < r.w;}
} e[112345];
int a[100001][1001];
int s[1123];
int fi(int x){
    return x==s[x] ? x : (s[x]=fi(s[x]));
}
bool link(int x, int y){
    x=fi(x), y=fi(y);
    if(x==y)return false;
    s[x]=y;
}
int main(){
    int T;
    scanf("%d",&T);
    REP(tt,T){
        int n, m;
        scanf("%d%d",&n,&m);
        REP(i,m)e[i].read();
        sort(e, e+m);
        for(int bg=m-1; ~bg; --bg){
            REP(i,n)s[i]=i;
            int (&b)[1001]=a[bg];
            int &tot=b[0];
            tot=0;
            link(e[bg].x, e[bg].y);
            b[++tot]=bg;
            if(bg==m-1)continue;
            int (&c)[1001]=a[bg+1];
            for(int i=1; i<=c[0]; ++i)
                if(link(e[c[i]].x, e[c[i]].y)){
                    b[++tot]=c[i];
                } else {
                    for(++i; i<=c[0]; ++i)
                        b[++tot]=c[i];
                }
        }
        REP(bg,m){
            int (&b)[1001]=a[bg];
            REP(i,b[0]){
                b[i+1]
            }
        }
        int q, ans=0;
        scanf("%d",&q);
        while(q--){
            int l, h;
            scanf("%d%d",&l,&h);
            l+=ans; h+=ans;
            
        }
    }
}
