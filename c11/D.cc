#include <bits/stdc++.h>
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
#define EPS 1e-9
typedef long double flt;
const flt PI = acos(-1.0);
inline flt sqr(flt x){
	return x*x;
}
int d, l, R, t, h;
flt r, dd, si, co, co_i, ta;
flt radius(flt y){
	if(y>=0 && y<=l)return r;
	flt dh = y < 0 ? -y : (y-l);
	if (dh+dd>R) return 0;
	return sqrt(R*R-sqr(dh+dd));
}
flt gao(flt x, flt r){
	if (x>r) return PI*sqr(r) - gao(r+r-x, r);
	flt theta = acos((r-x)/r);
	return sqr(r) * (theta - sin(theta)*cos(theta));
}
flt f(flt y){
	//return 1.0;
	flt x;
	if(l!=t){
		x = -ta*y+h*co_i;
	} else x = y < h ? 1e9 : 0;
	//out(x);out("fff");
	flt rr = radius(y);
	//out(rr);
	if (rr<EPS) return 0;
	if (x>rr+r) return PI*sqr(rr);
	if (x<r-rr) return 0;
	x-=r-rr;
	return gao(x, rr);
}
flt ada(flt l, flt r, flt m, flt eps, flt s, flt fl, flt fr, flt fm, int mi, int lim) {
	flt h=(r-l)/12;
	flt u=ldexp(l+m,-1), v=ldexp(m+r,-1);
	flt fu=f(u), fv=f(v);
	flt sl=(fl+fm+ldexp(fu,2))*h,
		   sr=(fm+fr+ldexp(fv,2))*h,
		   s2=sl+sr;
	if(mi<=0 && (lim<=0 || fabs(s2-s)<=eps))
		return s2+(s2-s)/15;
	eps=ldexp(eps,-1);--lim;--mi;
	return ada(l,m,u,eps,sl,fl,fm,fu,mi,lim)
		+  ada(m,r,v,eps,sr,fm,fr,fv,mi,lim);
}
flt simpson(flt l, flt r, flt eps=100, int minrec=20, int maxrec=60){
	flt m=ldexp(l+r,-1);
	flt fl=f(l),fm=f(m),fr=f(r);
	return ada(l,r,m,eps*15,(r-l)/6*(fl+fr+ldexp(fm,2)),fl,fr,fm,minrec,maxrec);
}
int main(){
	freopen("damage.in", "r", stdin);
	freopen("damage.out", "w", stdout);
	scanf("%d%d%d%d%d",&d,&l,&R,&t,&h);
	r = d/2.0;
	dd = sqrt(R*R-r*r);
	si = t/flt(l);
	co = sqrt(1-si*si);
	co_i = 1.0/co;
	ta = si*co_i;
	flt ans = simpson(-R+dd, 0)
			   + simpson(0, l)
			   + simpson(l, l+R-dd);
	ans/=1e6;
	printf("%.5lf\n", (double)ans);
}
