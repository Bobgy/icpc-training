#include <bits/stdc++.h>
using namespace std;
#define ONLINE_JUDGE
#define REP(i,n) for(int i=0;i<int(n);++i)
#ifdef ONLINE_JUDGE
    #define out(x)
#else
    #define out(x) cerr<<#x"="<<x<<endl
#endif
#define EPS 1e-8
typedef double flt;
inline flt sqr(flt x) { return x*x; }
inline int fcmp(flt x, flt y) {
    flt t = x - y;
    return fabs(t)<=EPS ? 0 : (t<0 ? -1 : 1);
}
int n;
struct Point{
    flt x, y;
    Point(flt x, flt y):x(x),y(y){}
    Point(){}
    void read(){
        scanf("%lf%lf",&x,&y);
    }
    Point operator+(Point b) const { return Point(x+b.x, y+b.y); }
    Point operator-(Point b) const { return Point(x-b.x, y-b.y); }
    flt operator*(Point b) const { return x*b.x+y*b.y; }
    friend Point operator*(flt k, Point b) { return Point(k*b.x, k*b.y); }
    flt operator!() const { return hypot(x, y); }
    flt sqr() const { return x*x+y*y; }
    flt operator^(Point b) const { return x*b.y-y*b.x; }
    Point uni() const { return (1.0/!*this) * *this; }
    void print() const {
        #ifndef ONLINE_JUDGE
            printf("(%.10lf %.10lf)\n", x, y);
        #endif
    }
} pt[1123], o;
typedef Point Vec;
flt r;
void fix_dir(){
    flt s=0;
    REP(i,n)s+=pt[i]^pt[(i+1)%n];
    if(s<0){
        reverse(pt, pt+n);
    }
}
flt ans;
vector<pair<flt,bool> > ang;
void init(){
    ans=0;
    ang.clear();
}
flt k0, k1;
// k*v+(1-k)*u==p
int intersect(Point u, Point v, Point o, flt r){
    swap(u, v);
    flt A = (u-v).sqr();
    flt B = (u-v)*(v-o);
    flt C = (v-o).sqr()-r*r;
    flt D = B*B-A*C;
    if(fcmp(D,0)<0)return 0;
    else {
        D=max(D,0.0);
        k0 = (-B-sqrt(D)) / A;
        k1 = (-B+sqrt(D)) / A;
        if(k0>k1)swap(k0,k1);
        return 1;
    }
}
const flt PI = acos(-1.0);
void add_pt(Point p, bool goInside){
    Point t = p-o;
    flt a = atan2(t.y, t.x);
    ang.push_back(make_pair(a, goInside));
}
void calc_seg(){
    REP(i,n){
        Vec &u=pt[i], &v=pt[(i+1)%n];
        assert(fcmp(!(u-v), 0.0)>0);
        flt r0=!(u-o), r1=!(v-o);
        if (fcmp(r0,r)<=0 && fcmp(r1,r)<=0) {
            ans+=!(u-v);
        } else {
            if (intersect(u, v, o, r)) {
                flt L = max(k0, 0.0);
                flt R = min(k1, 1.0);
                out(k0); out(k1);
                if (L < R) {
                    out(L); out(R);
                    Vec p0 = L*v+(1-L)*u, p1 = R*v+(1-R)*u;
                    p0.print();
                    p1.print();
                    ans += !(p0-p1);
                }
                if (fcmp(k0, 0)>0 && fcmp(k0, 1)<=0) {
                    add_pt(k0*v+(1-k0)*u, true);
                }
                if (fcmp(k1, 0)>=0 && fcmp(k1, 1)<0) {
                    add_pt(k1*v+(1-k1)*u, false);
                }
            }
        }
    }
}
flt rg(flt a0, flt a1){
    if(a0<=a1)return a1-a0;
    else return a1-a0+2*PI;
}
void calc_arc(){
    out(ans);
    sort(ang.begin(), ang.end(), [](pair<flt, bool> a, pair<flt, bool> b){
        int res = fcmp(a.first, b.first);
        if (res) return res < 0;
        return a.second > b.second;
    });
    REP(i,ang.size()){
        out(ang[i].first); out(ang[i].second);
        int j = (i+1) % ang.size();
        assert(ang[i].second ^ ang[j].second);
        if(!ang[i].second && ang[j].second)ans+=rg(ang[i].first, ang[j].first)*r;
    }
    out(ans);
}
int main(){
    while(scanf("%d",&n)==1 && n){
        init();
        REP(i,n)pt[i].read();
        o.read();
        scanf("%lf",&r);
        fix_dir();
        calc_seg();
        calc_arc();
        #ifdef ONLINE_JUDGE
            printf("%.0lf\n", ans+EPS);
        #else
            printf("%.10lf\n", ans);
        #endif
    }
}
