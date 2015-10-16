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
#define EPS 1e-10
//#undef assert
//#define assert(x) while(!(x));
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
    Pt operator+(Pt r) const {return Pt(x+r.x, y+r.y);}
    Pt operator-(Pt r) const {return Pt(x-r.x, y-r.y);}
    flt operator^(Pt r) const {return x*r.y-y*r.x;}
    flt ang() const {return atan2(y, x);}
    Pt rot(flt a) const {return Pt(cos(a)*x-sin(a)*y, sin(a)*x+cos(a)*y);}
    void print() const {debug("%.4lf %.4lf\n", x, y);}
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
    void print() const {debug("%d %d\n", u, v);}
} e[MAXN*2];

int n, m, q;
vector<pair<flt, int>> E[MAXN];

vi seq;
bool vis[MAXN*2], border[MAXN*2];
//returns vector<vector<Edge ID>> polys in counter-clockwise
vector<vi> find_poly(){
    vector<vi> polys;
    fill(vis,vis+m*2,0);
    rep(i,n)for(auto u: E[i]){
        if(vis[u.Y])continue;
        int j=u.Y;
        seq.clear();
        do {
            vis[j]=1;
            seq.pb(j);
            auto &et=E[e[j^=1].u];
            j=et[(e[j].id+1)%et.size()].Y;
        } while(!vis[j]);
        flt s=0;
        bool found=0;
        polys.pb(vi());
        for(auto x: seq){
            found = found || x==j;
            if(found){
                s+=p[e[x].u]^p[e[x].v];
                polys.back().pb(x);
            }
        }
        if(s>EPS){
            for(auto x: polys.back())border[x]=1;
        } else polys.pop_back();
    }
    return polys;
}

int grp[MAXN];
void find_connected_components(){
    int cnt=0;
    rep(i,n)if(grp[i]==0){
        queue<int> Q;
        Q.push(i);
        grp[i]=++cnt;
        while(!Q.empty()){
            int x=Q.front();
            for(auto u: E[x]){
                int y=e[u.Y].v;
                if(grp[y]==0){
                    Q.push(y);
                    grp[y]=cnt;
                }
            }
            Q.pop();
        }
    }
}

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

vector<pair<flt, int>> evt;
bool ins[MAXN];

int main(){
    srand(time(0));

    scanf("%d%d%d",&n,&m,&q);
    rep(i,n)p[i].read();

    bool fail;
    flt ang;
    do {
        evt.clear();
        ang=rand()/65535.0*2.0*PI;
        rep(i,n){
            p[i]=p[i].rot(ang);
            evt.pb(mp(p[i].x, i));
        }
        sort(all(evt));
        fail=0;
        rep(i,evt.size()-1)if(fcmp(evt[i].X-evt[i+1].X)==0){
            fail=1;
            break;
        }
        if(fail)rep(i,n)p[i]=p[i].rot(-ang);
    } while(fail);

    int z=-1;
    rep(i,m){
        int u, v;
        scanf("%d%d",&u,&v);
        --u, --v;
        e[++z]=Edge(u, v);
        E[u].pb(mp(e[z].ang, z));
        e[++z]=Edge(v, u);
        E[v].pb(mp(e[z].ang, z));
    }
    ++z;

    rep(i,n){
        sort(all(E[i]));
        rep(j,E[i].size())e[E[i][j].Y].id=j;
    }

    find_poly();

    rep(i,2*m)if(border[i]&&border[i^1]){
        border[i]=border[i^1]=0;
    }

    rep(i,q){
        p[i+n].read();
        p[i+n]=p[i+n].rot(ang);
        evt.pb(mp(p[i+n].x, i+n));
    }
    sort(all(evt));

    find_connected_components();

    fill(vis, vis+2*m, 0);
    for(auto ev: evt){
        int id=ev.Y;
        now=p[id].x;
        p[n+q]=p[id]+Pt(10,0);
        e[z]=Edge(id, n+q);
        auto it = bd.lower_bound(Border(z, 0));
        bool inside;
        if (it!=bd.end()) {
            Edge &ed=e[it->id];
            inside=p[ed.u].x>p[ed.v].x;
        } else inside=0;
        if(id>=n){ //query
            ins[id-n]=inside;
        } else { //point
            bool flag=0;
            for (auto ed: E[id]) if(vis[ed.Y]||vis[ed.Y^1]) {
                flag=1;
                break;
            }
            if(flag || !inside || grp[id]==grp[e[it->id].u]){
                int k;
                for (auto ed: E[id]) {
                    if(vis[k=ed.Y]||vis[k^=1])bd.erase(e[k].it);
                }
                for (auto ed: E[id]) {
                    if (border[k=ed.Y]||border[k^=1]) {
                        if(fcmp(p[e[k].u].x-p[e[k].v].x)==0)continue;
                        if(!vis[k]){
                            auto tmp=bd.insert(Border(k, e[k].u==id ? e[k].ang : e[k^1].ang));
                            e[k].it=tmp.X;
                            assert(tmp.Y);
                            vis[k]=1;
                        }
                    }
                }
            }
        }
    }
    rep(i,q)puts(ins[i] ? "Yes" : "No");
}
