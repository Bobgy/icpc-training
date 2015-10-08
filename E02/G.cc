#include <bits/stdc++.h>
#define MAXN 112345
using namespace std;
#define rep(i,n) for(int i=0;i<int(n);++i)
#define rer(i,l,r) for(int i=l;i<=int(r);++i)
typedef pair<int, int> pii;
#define X first
#define Y second
struct sf {
    int l, r, par, rev, ma;
} f[MAXN];

inline bool isroot(int x) {
    return f[f[x].par].l!=x && f[f[x].par].r!=x;
}

inline void push(int x) {
    if (f[x].rev) {
        f[f[x].l].rev^=1;
        f[f[x].r].rev^=1;
        swap(f[x].l,f[x].r);
        f[x].rev=0;
    }
}

inline void update(int x) {
    f[x].ma=x;
    if(f[x].l)f[x].ma=max(f[x].ma, f[f[x].l].ma);
    if(f[x].r)f[x].ma=max(f[x].ma, f[f[x].r].ma);
}

inline void rotate(int x) {
    int y=f[x].par, z=f[y].par;
    push(y); push(x);
    if (f[y].l==x) f[f[y].l=f[x].r].par=y,f[x].r=y;
    else f[f[y].r=f[x].l].par=y,f[x].l=y;
    if (f[z].l==y) f[z].l=x;
    if (f[z].r==y) f[z].r=x;
    f[f[y].par=x].par=z;
    update(y);
}

inline void splay(int x) {
    push(x);
    for (;!isroot(x);rotate(x)) {
        int y=f[x].par, z=f[y].par;
        if (!isroot(y)) rotate(f[z].l==y^f[y].l==x?x:y);
    }
    update(x);
}

inline void access(int x) {
    for(int t=0,y=x;y;y=f[y].par) splay(y),f[y].r=t,update(t=y);
    splay(x);
}

inline void makeroot(int x) {
    access(x);f[x].rev^=1;
}

inline void link(int x, int y) {
    makeroot(x);f[x].par=y;
}

inline void cut(int x, int y) {
    makeroot(x);access(y);f[x].par=f[y].l=0;update(y);
}

inline int query(int x, int y) {
    makeroot(x);access(y);
    return f[y].ma;
}

inline bool isconnect(int x, int y) {
    makeroot(x);access(y);
    while (push(y), f[y].l) y=f[y].l;
    splay(y);
    return x==y;
}

pii e[MAXN*2];
int n, m, q;

const int OFFSET = 3;
struct BITree {
    int a[MAXN], N;
    void clear(int n){
        memset(a, 0, sizeof(int)*(n+OFFSET*2));
        N=n+OFFSET*2;
    }
    int sum(int i){
        int ret = 0;
        for(i+=OFFSET; i>0; i-=i&-i)ret+=a[i];
        return ret;
    }
    void add(int i, int d){
        for(i+=OFFSET; i<N; i+=i&-i)a[i]+=d;
    }
} bt;

inline int lch(int x){
    for(; push(x), f[x].l; x=f[x].l);
    return x;
}

void add_edge(int u, int v){
    if(u==v)return;
    if(!isconnect(u,v)){
        link(u,v);
        bt.add(max(u,v), 1);
    } else {
        int id=query(u,v);
        if(id<=max(u,v))return;
        makeroot(id);
        access(u);
        int t;
        push(id);
        if(f[id].r)t=lch(f[id].r);
        else t=f[id].par;
        cut(id, t);
        bt.add(id, -1);
        link(u,v);
        bt.add(max(u,v), 1);
    }
}
struct Qu{
    int L, R, id;
    void read(int _id) {scanf("%d%d",&L,&R);id=_id;}
    bool operator<(Qu r) const {return L>r.L;}
} Q[MAXN];
int ans[MAXN];
int main() {
    while(scanf("%d%d%d",&n,&m,&q)==3){
        memset(f, 0, sizeof(sf)*(n+2));
        rer(i,1,n)f[i].ma=i;
        rep(i,m){
            scanf("%d%d",&e[i].X,&e[i].Y);
            if(e[i].X>e[i].Y)swap(e[i].X,e[i].Y);
            e[i].X=-e[i].X;
        }
        sort(e,e+m);
        rep(i,q)Q[i].read(i);
        sort(Q,Q+q);
        int j=0;
        bt.clear(n);
        rep(i,q){
            for(;j<m && -e[j].X>=Q[i].L;++j)
                add_edge(-e[j].X, e[j].Y);
            ans[Q[i].id]=n-bt.sum(Q[i].R);
        }
        rep(i,q)printf("%d\n", ans[i]);
    }
}
