#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#ifdef DEBUG
#define out(x) (cerr<<#x"="<<x<<endl,(x))
#define debug(args...) fprintf(stderr, args)
#else
#define out(x) (x)
#define debug(...)
#endif
#define rep(i,n) for(int i=0;i<int(n);++i)
#define rer(i,L,R) for(int i=int(L);i<=int(R);++i)
#define all(o) (o).begin(),(o).end()
#define pb push_back
#define X first
#define Y second
#define mp make_pair
#define EPS 1e-8
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pair<int,int> > vpii;
typedef double flt;
const int MAXN = 112345;
const flt PI = acos(-1.0);
int fcmp(flt x){return fabs(x)<EPS ? 0 : (x<0 ? -1 : 1);}
struct Pt{
    flt x, y;
    Pt(flt x, flt y):x(x), y(y){}
    Pt(){}
    void read() {scanf("%lf%lf",&x,&y);}
    Pt operator-(Pt r) const {return Pt(x-r.x, y-r.y);}
    flt ang() const {return atan2(y, x);}
    flt operator^(Pt r) const {return x*r.y-y*r.x;}
} p[MAXN*2];
struct Border;
struct Edge{
    int u, v, id;
    flt ang;
    set<Border>::iterator it;
    flt init() const {return (p[v]-p[u]).ang();}
    Edge(int u, int v):u(u),v(v){ang=init();}
    Edge(){}
    bool operator<(Edge r) const {return ang<r.ang;}
    void print() const {
        debug("%d %d\n", u, v);
    }
} e[MAXN*2];
vector<pair<flt, int>> E[MAXN];
bool vis[MAXN*2], border[MAXN*2];
int n, m, q;
inline int nxt(int x, int n){
    return ++x==n ? 0 : x;
}
vi seq;
void find_poly(){
    rep(i,n)for(auto u: E[i]){
        if(vis[u.Y])continue;
        debug("begin\n");
        int j=u.Y;
        e[j].print();
        seq.clear();
        do {
            vis[j]=1;
            seq.pb(j);
            j^=1;
            auto &ee=E[e[j].u];
            j=ee[nxt(e[j].id,ee.size())].Y;
            e[j].print();
        } while(!vis[j]);
        flt s=0;
        bool found=0;
        for(auto x: seq){
            if(!found)found=x==j;
            if(found)s+=p[e[x].u]^p[e[x].v];
        }
        debug("end %.10lf\n", s);
        if(s>EPS){
            found=0;
            for(auto x: seq){
                if(!found)found=x==j;
                if(found)border[x]=1;
            }
        }
    }
}
vector<pair<flt, int>> evt;
flt now;
struct Border{
    int id;
    flt ang;
    flt y() const {
        Pt &a=p[e[id].u], &b=p[e[id].v];
        //k*a.x+(1-k)*b.x==now
        //k*(a.x-b.x)==now-b.x
        flt k=(now-b.x)/(a.x-b.x);
        return k*a.y+(1-k)*b.y;
    }
    bool operator<(Border r)const{
        int sg=fcmp(y()-r.y());
        if(sg)return sg<0;
        return ang<r.ang;
    }
    Border(int id, flt ang):id(id),ang(ang){}
};
set<Border> bd;
bool ins[MAXN];
int main(){
    scanf("%d%d%d",&n,&m,&q);
    rep(i,n){
        p[i].read();
        evt.pb(mp(p[i].x, i));
    }
    int j=-1;
    rep(i,m){
        int u, v;
        scanf("%d%d",&u,&v);
        --u, --v;
        e[++j]=Edge(u, v);
        E[u].pb(mp(e[j].ang, j));
        e[++j]=Edge(v, u);
        E[v].pb(mp(e[j].ang, j));
    }
    ++j;
    rep(i,n){
        sort(all(E[i]));
        rep(j,E[i].size())e[E[i][j].Y].id=j;
        out(i);
        rep(j,E[i].size()){
            debug("%.4lf ", E[i][j].X);
            e[E[i][j].Y].print();
        }
    }
    find_poly();
    rep(i,2*m)if(border[i]){
        e[i].print();
    }
    rep(i,q){
        p[i+n].read();
        evt.pb(mp(p[i+n].x, i+n));
    }
    sort(all(evt));
    memset(vis, 0, sizeof vis);
    for(auto ev: evt){
        int id=ev.Y;
        now=p[id].x;
        p[n+q]=p[id];
        p[n+q].x+=10;
        e[j]=Edge(id, n+q);
        auto it = bd.lower_bound(Border(j, 0));
        debug("found ");
        bool inside;
        if (it!=bd.end()) {
            Edge &ed=e[it->id];
            ed.print();
            inside=p[ed.u].x>p[ed.v].x;
        } else {
            debug("no\n");
            inside=0;
        }
        if(id>=n){ //query
            ins[id-n]=inside;
        } else { //point
            bool flag=0;
            for (auto ed: E[id]) if(vis[ed.Y]||vis[ed.Y^1]) {
                flag=1;
                break;
            }
            if(flag || !inside) {
                for (auto ed: E[id]) {
                    if (border[ed.Y^1]^border[ed.Y]) {
                        int k=border[ed.Y] ? ed.Y : ed.Y^1;
                        if(vis[k])bd.erase(e[k].it);
                    }
                }
                for (auto ed: E[id]) {
                    if (border[ed.Y^1]^border[ed.Y]) {
                        int k=border[ed.Y] ? ed.Y : ed.Y^1;
                        if(fcmp(p[e[k].u].x-p[e[k].v].x)==0)continue;
                        debug("processing ");
                        e[k].print();
                        out("gao");
                        if(!vis[k]){
                            debug("insert %d\n", k);
                            auto tmp=bd.insert(Border(k, e[k].u==id ? e[k].ang : e[k^1].ang));
                            e[k].it=tmp.X;
                            assert(tmp.Y);
                            vis[k]=1;
                        }
                        out("gao2");
                    }
                }
            }
        }
    }
    rep(i,q)puts(ins[i] ? "Yes" : "No");
}
