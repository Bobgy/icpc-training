#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
	#define out(x)
#else
	#define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
typedef double flt;
const flt PI = acos(-1.0);
const flt EPS = 1e-7, EPS2 = 1e-4;
int fcmp(flt x, flt y, flt EPS=EPS){
	return fabs(x-y)<EPS ? 0 : (x>y ? 1 : -1);
}
struct Pt{
	flt x, y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	Pt(flt x, flt y):x(x),y(y){}
	Pt(){}
	Pt operator+(Pt r) const {return Pt(x+r.x,y+r.y);}
	Pt operator-(Pt r) const {return Pt(x-r.x,y-r.y);}
	flt operator*(Pt r) const {return x*r.x+y*r.y;}
	flt operator^(Pt r) const {return x*r.y-y*r.x;}
	flt operator!() const {return hypot(x,y);}
	flt sqr() const {return x*x+y*y;}
	friend Pt operator*(flt k, Pt r) {return Pt(r.x*k,r.y*k);}
	void print() const {
#ifndef ONLINE_JUDGE
		printf("(%.5lf, %.5lf)\n", x, y);
#endif
	}
} o;
struct Cir{
	Pt o;
	flt r;
	Cir(Pt o, flt r):o(o),r(r){}
	Cir(){}
	void read(){
		o.read();
		scanf("%lf",&r);
	}
	flt len() const {return 2.0*(PI*r);}
};
struct Seg{
	Pt u, v;
	Seg(Pt u, Pt v):u(u),v(v){}
	flt len() const {return !(u-v);}
};

flt k0, k1;
// k*v+(1-k)*u==p
int intersect(Seg s, Cir c){
	Pt u=s.u, v=s.v, o=c.o;
	flt r=c.r;
	flt A, B, C, D;
	A = (v-u).sqr();
	B = (v-u)*(u-o);
	C = (u-o).sqr()-r*r;
	D = B*B-A*C;
	if(fcmp(B*B,A*C)<0)return 0;
	else {
		D=max(D,0.0);
		k0=(-B-sqrt(D))/A;
		k1=(-B+sqrt(D))/A;
		if(k0>k1)swap(k0,k1);
		return 1;
	}
}

int intersectCC(Pt c1, flt r1, Pt c2, flt r2, Pt &p1, Pt &p2){
	Pt u, v;
	flt t = (1+(r1*r1-r2*r2)/(c1-c2).sqr())/2;
	u = c1 + t*(c2-c1);
	v = Pt(u.x+c1.y-c2.y, u.y-c1.x+c2.x);
	if(intersect(Seg(u,v),Cir(c1,r1))==0)return 0;
	p1 = k0*v+(1-k0)*u;
	p2 = k1*v+(1-k1)*u;
	return 1;
}

vector<Cir> c;
vector<Seg> s;
char buf[1123];
flt calc(flt r, bool eq=true){
	Cir C;
	C.r=r;
	C.o=o;
	flt res=0;
	for(auto cc: c){
		if(fcmp(!(cc.o-o),0.0) == 0){
			int sg = fcmp(r,cc.r);
			if(sg>0 || (eq && sg==0)){
				res += cc.len();
			}
		} else if(fcmp(!(cc.o-o)+cc.r,r) <= 0){
			res += cc.len();
		} else if(fcmp(!(cc.o-o),cc.r+r) >= 0){
			//nothing
		} else if(fcmp(!(cc.o-o)+r,cc.r) <= 0){
			//nothing
		} else {
			Pt p1, p2;
			assert(intersectCC(cc.o, cc.r, C.o, C.r, p1, p2));
			Pt u=C.o-cc.o, v=p1-cc.o;
			res+=2*acos(u*v/!u/!v)*cc.r;
		}
	}
	for(auto ss: s){
		if(intersect(ss, C)){
			flt L=max(k0, 0.0);
			flt R=min(k1, 1.0);
			if(L<R){
				Pt p0=L*ss.v+(1-L)*ss.u, p1=R*ss.v+(1-R)*ss.u;
				res+=!(p0-p1);
			}
		}
	}
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	REP(tt,T){
		c.clear();
		s.clear();
		int n;
		flt m;
		scanf("%d%lf",&n,&m);
		REP(i,n){
			scanf("%s",buf);
			if(buf[0]=='C'){
				Cir cc;
				cc.read();
				c.pb(cc);
			} else {
				assert(buf[0]=='P');
				int nn;
				scanf("%d",&nn);
				assert(nn>=3);
				Pt fi, now;
				fi.read();
				now=fi;
				while(--nn){
					Pt tmp;
					tmp.read();
					s.pb(Seg(now,tmp));
					now=tmp;
				}
				s.pb(Seg(now,fi));
			}
		}
		o.read();
		flt tot=0;
		for(auto cc: c)tot+=cc.len();
		for(auto ss: s)tot+=ss.len();
		printf("Case #%d: ", tt+1);
		if(fcmp(tot,m)==0){
			puts("inestimable");
			continue;
		}
		if(fcmp(tot,m)<0){
			puts("impossible");
			continue;
		}
		flt L=0.0, R=0.0;
		for(auto cc: c)R=max(R, !(cc.o-o)+cc.r);
		for(auto ss: s)R=max(R, !(ss.u-o)), R=max(R, !(ss.v-o));
		int ttt=100;
		while(ttt--){
			flt M=L+(R-L)/2.0;
			flt sum=calc(M);
			if(fcmp(sum,m)>0)R=M;
			else L=M;
		}
		flt M=L+(R-L)/2.0;
		flt s0=calc(M,true), s1=calc(M,false);
		if(fcmp(s0,m,EPS2) && fcmp(s1,m,EPS2))puts("impossible");
		else printf("%.2lf\n", M+EPS);
	}
}
