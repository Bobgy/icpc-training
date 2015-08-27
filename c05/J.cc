#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define out(x) cerr<<#x"="<<x<<endl
struct Edge{
    int x, y, w;
    void read(){
        scanf("%d%d%d",&x,&y,&w);
        --x; --y;
    }
    void print(int id){
        printf("%d %d %d %d\n", id, w, x, y);
    }
    bool operator<(Edge r) const {return w < r.w;}
    Edge(int x, int y, int w):x(x), y(y), w(w){}
    Edge(){}
} e[112345];
int num[100001];
int a[100001][1001];
int s[1123];
int fi(int x){
    return x==s[x] ? x : (s[x]=fi(s[x]));
}
bool link(int x, int y){
    x=fi(x), y=fi(y);
    if(x==y)return false;
    s[x]=y;
    return true;
}
int main(){
    int T;
    scanf("%d",&T);
    REP(tt,T){
        int n, m;
        scanf("%d%d",&n,&m);
        REP(i,m)e[i].read();
        sort(e, e+m);
        //REP(i,m)e[i].print(i);
        for(int bg=m-1; ~bg; --bg){
            REP(i,n)s[i]=i;
            int (&b)[1001]=a[bg];
            int &tot=num[bg];
            tot=0;
            link(e[bg].x, e[bg].y);
            b[++tot]=bg;
            if(bg==m-1)continue;
            int (&c)[1001]=a[bg+1];
            for(int i=1; i<=num[bg+1]; ++i){
                if(link(e[c[i]].x, e[c[i]].y)){
                    b[++tot]=c[i];
                } else {
                    for(++i; i<=num[bg+1]; ++i)
                        b[++tot]=c[i];
                }
            }
            //printf("%d\n", tot);for(int i=1;i<=tot;++i)printf("%d%c",b[i]," \n"[i==tot]);
        }
        REP(bg,m){
            int (&b)[1001]=a[bg];
            REP(i,num[bg])
                b[i+1] = e[b[i+1]].w + b[i];
        }
        int q, ans=0;
        scanf("%d",&q);
        while(q--){
            int l, h;
            scanf("%d%d",&l,&h);
            l-=ans; h-=ans;
            //out(l); out(h);
            int id=lower_bound(e, e+m, Edge(0, 0, l))-e;
            if(id==m){
                puts("0");
                continue;
            }
            //out(id);out(num[id]);
            int (&b)[1001]=a[id];
            //REP(i,num[id]+1)printf("%d%c",b[i]," \n"[i==num[id]]);
            int L=0, R=num[id];
            while(L<R){
                int M=L+(R-L)/2;
                if(b[M+1]-b[M]>h)R=M;
                else L=M+1;
            }
            ans=b[L];
            printf("%d\n", ans);
        }
    }
}
