#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#ifdef DEBUG
#define out(x) (cerr<<#x"="<<(x)<<endl,(x))
#define debug(args...) fprintf(stderr, args)
#else
#define out(x) (x)
#define debug(...)
#endif
#define rep(i,n) for(int i=0;i<int(n);++i)
#define rer(i,L,R) for(int i=int(L);i<=int(R);++i)
#define all(o) (o).begin(),(o).end()
#define pb push_back
#define mp make_pair
#define X first
#define Y second
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pair<int,int> > vpii;
typedef double flt;
LL sgn(LL x){
    return x>=0 ? 1 : -1;
}
int n;
template<class T>
struct Pt{
    T x, y;
    Pt(T x, T y):x(x),y(y){}
    Pt(){}
    Pt operator+(Pt r)const{return Pt(x+r.x,y+r.y);}
    Pt operator-(Pt r)const{return Pt(x-r.x,y-r.y);}
    T operator^(Pt r)const{return x*r.y-y*r.x;}
    T operator*(Pt r)const{return x*r.x+y*r.y;}
    Pt operator/(flt k)const{return Pt(x/k,y/k);}
    flt len()const{return hypot(x,y);}
    friend Pt operator*(flt k, Pt r){return Pt(k*r.x,k*r.y);}
    void print()const{
#ifdef DEBUG
        cerr<<"["<<x<<", "<<y<<"]"<<endl;
#endif
    }
};
typedef Pt<flt> PF;
typedef Pt<LL> PLL;
struct Ray{
    PF u, v;
    Ray(PF u,PF v):u(u),v(v){}
    void print(const char *s)const{
        debug(s);
        u.print();
        v.print();
    }
};
flt cmp_side(PF a, PF b){
    return a.x*b.y-a.y*b.x;
}
PF intersect(const Ray &a, const Ray &b){
    PF s=a.u-a.v,t=b.u-b.v;
    flt at=cmp_side(s,t);
    if(at==0.0){
        a.print("a\n"); b.print("b\n");
        s.print();t.print();
        assert(at);
    }
    return a.u+(((b.u-a.u)^t)/at*s);
}
PF pf[1123];
PLL p[1123];
flt v[1123];
vector<pair<int, flt>> E[1123];
struct Ang{
    LL a, b;
    int ph;
    Ang(LL a, LL b):a(a),b(b){
        if(a>=0 && b>=0)ph=0;
        else if(a<0 && b>=0)ph=1;
        else if(a<0 && b<0)ph=2;
        else ph=3;
        LL g=__gcd(a, b);
        g=abs(g);
        if(g)a/=g,b/=g;
    }
    Ang(){}
    bool operator<(Ang r)const{
        if(ph!=r.ph)return ph<r.ph;
        LL t=sgn(r.a)*sgn(a);
        return b*r.a*t<r.b*a*t;
    }
    bool operator==(Ang r)const{
        return ph==r.ph && b*r.a==r.b*a;
    }
    void print()const{
        debug("(%lld, %lld)\n", a, b);
    }
} ax(1,0), a[1123];
int nxt(int i){return i+1==n?0:i+1;}
int pre(int i){return i==0?n-1:i-1;}
Ang now;
struct Edge{
    int u, v;
    Edge(int u, int v):u(u),v(v){}
    flt dis(Ang a)const{
        if(u==v)return 0;
        PF t=intersect(Ray(PF(0,0),PF(a.a,a.b)),Ray(pf[u],pf[v]));
        return t.len();
    }
    bool operator<(Edge r)const{
        flt d0=dis(now), d1=r.dis(now);
        if(d0!=d1)return d0<d1;
        if(u!=r.u)return u<r.u;
        return v<r.v;
    }
    bool on(int x)const{
        if(u==v)return x==u || x==nxt(u) || x==pre(u);
        return u==x||v==x;
    }
};
set<Edge> s;
map<pii,set<Edge>::iterator> M;
void ins(int i, int j){
    debug("ins %d %d\n", i, j);
    auto tmp=s.insert(Edge(i,j));
    assert(tmp.Y);
    M[mp(i,j)]=tmp.X;
}
bool del(int i, int j){
    auto it=M.find(mp(i,j));
    if(it!=M.end()){
        s.erase(it->Y);
        M.erase(it);
        debug("del %d %d\n", i, j);
        return 1;
    }
    return 0;
}
bool work(int i, int j, int x){
    if(i==x||j==x)i=j=x;
    if(del(i,j)||del(j,i))return 0;
    if(i!=j && (p[i]^p[j])==0)return 0;
    ins(i, j);
    return 1;
}
void gao(int x){
    s.clear();
    M.clear();
    rep(i,n)if(i!=x){
        p[i]=p[i]-p[x];
        pf[i]=PF(p[i].x,p[i].y);
    }
    p[x]=PLL(0,0);
    rep(i,n)a[i]=Ang(p[i].x,p[i].y);
    vector<pair<pair<Ang,flt>,int>> evt;
    rep(i,n)if(i!=x)evt.pb(mp(mp(a[i],pf[i].len()),i));
    sort(all(evt));
    debug("=======\n");
    for(auto u: evt){
        u.X.X.print();
        debug("%.4lf %d\n", u.X.Y, u.Y);
    }
    debug("\n");
    now=ax;
    rep(i,n){
        int u=i, v=(u+1)%n;
        if(p[u].y<p[v].y)swap(u,v);
        if(p[u].y>=0 && p[v].y<0){
            if((p[u]^p[v])<0)ins(u,v);
        }
    }
    {
        int u=pre(x), v=nxt(x);
        if(a[u]<a[v])ins(x,x);
    }
    debug("events\n");
    bool valid=0;
    for(auto ev: evt){
        int id=ev.Y, pp=pre(id), nn=nxt(id);
        bool ok=!valid || !(a[id]==now);
        valid=1;
        now=a[id];
        now.print();
        out(s.size());
        if(ok && (s.empty() || s.begin()->dis(now)>pf[id].len() || s.begin()->on(id))){
            E[x].pb(mp(id,pf[id].len()));
        }
        debug("pp=%d id=%d nn=%d\n", pp, id, nn);
        work(pp,id,x);
        work(id,nn,x);
        debug("\n");
    }
    debug("end\n");
}
flt dp[1123];
int main(){
    int T;
    scanf("%d",&T);
    rer(cs,1,T){
        scanf("%d",&n);
        flt s=0;
        rep(i,n){
            flt x, y;
            scanf("%lf%lf%lf",&x,&y,v+i);
            p[i]=PLL(round(x*1e4),round(y*1e4));
            pf[i]=PF(p[i].x,p[i].y);
        }
        rep(i,n)s+=pf[i]^pf[(i+1)%n];
        if(s<0){
            debug("REV\n");
            reverse(p,p+n);
            reverse(pf,pf+n);
        }
        rep(i,n)gao(i);
        flt ans=0;
        rep(i,n)dp[i]=-1e10;
        dp[0]=v[0];
        rep(i,n)for(auto u: E[i])if(u.X>i){
            u.Y/=1e4;
            debug("%d %d %.4lf\n", i, u.X, u.Y);
            dp[u.X]=max(dp[u.X], dp[i]+v[u.X]-u.Y);
        }
        rep(i,n)ans=max(ans, dp[i]);
        printf("Case #%d: %.10lf\n", cs, ans);
        rep(i,n)E[i].clear();
    }
}
