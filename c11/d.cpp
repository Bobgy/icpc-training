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
#define eps 100
const double PI = acos(-1.0);
inline double sqr(double x){
	return x*x;
}
int d, l, R, t, h;
double r, dd, si, co, co_i, ta;
double radius(double y){
	if(y>=0 && y<=l)return r;
	double dh = y < 0 ? -y : (y-l);
	if (dh+dd>R) return 0;
	return sqrt(R*R-sqr(dh+dd));
}
double gao(double x, double r){
	if (x>r) return PI*sqr(r) - gao(r+r-x, r);
	double theta = acos((r-x)/r);
	return sqr(r) * (theta - sin(theta)*cos(theta));
}
double f(double y){
	//return 1.0;
	double x;
	if(l!=t){
		x = -ta*y+h*co_i;
	} else x = y < l ? 1e9 : 0;
	//out(x);out("fff");
	double rr = radius(y);
	//out(rr);
	if (rr<EPS) return 0;
	if (x>rr+r) return PI*sqr(rr);
	if (x<r-rr) return 0;
	x-=r-rr;
	return gao(x, rr);
}
double Simpson_VariStep(double xl, double xh){
	int subs=1, n=1, i;
	double result, x, p, width=(xh-xl), t1=width*(f(xl)+f(xh))/2.0, t2;
	//out(t1);
	double s1=t1, s2=s1+2.0*eps;
	int cnt=0;
	while(cnt<=20){
		++cnt;
		//out(n);
		for (p=0.0, i=0; i<=n-1; ++i) {
			x=xl+(i+0.5)*width;
			//out(x);
			//out(f(x));
			p=p+f(x);
		}
		t2=(t1+width*p)/2.0;
		s2=(t2*4-t1)/3.0;
		result=s2;
		//out(s2);
	//	subs=(fabs(s2-s1)>=eps);
		t1=t2;
		s1=s2;
		n+=n;
		//out(s2);
		width/=2.0;
	}
	return s2;
}
int main(){
	freopen("damage.in", "r", stdin);
	freopen("damage.out", "w", stdout);
	scanf("%d%d%d%d%d",&d,&l,&R,&t,&h);
	r = d/2.0;
	dd = sqrt(R*R-r*r);
	si = t/double(l);
	co = sqrt(1-si*si);
	co_i = 1.0/co;
	ta = si*co_i;
	double ans = Simpson_VariStep(-R+dd, 0)
			   + Simpson_VariStep(0, l)
			   + Simpson_VariStep(l, l+R-dd);
	ans/=1e6;
	printf("%.5lf\n", ans);
}
