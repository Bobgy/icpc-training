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
#define EPS 2e-6
typedef long double flt;
struct rang{
	flt L, R;
	rang(flt L, flt R):L(L),R(R){}
	bool check() const {
		return L+EPS<R;
	}
	rang operator&(rang r) const {
		return rang(max(L, r.L), min(R, r.R));
	}
};
struct Rang{
	vector<rang> rg;
	void add(rang a){
		if(!a.check())return;
		rg.pb(a);
	}
	Rang operator&(Rang r) const {
		Rang res;
		for(auto u: rg)for(auto v: r.rg){
			rang t=u&v;
			if(t.check())res.add(t);
		}
		return res;
	}
	flt get() const {
		assert(rg.size());
		flt ddd=0, res=-1;
		REP(i,rg.size())if(rg[i].R-rg[i].L>ddd){
			ddd = rg[i].R-rg[i].L;
			res = (rg[i].L+rg[i].R)/2.0;
		}
		return res;
	}
	void print(const char *head) const {
		/*
		puts("=============");
		puts(head);
		REP(i,rg.size())printf("(%.8lf %.8lf)\n", rg[i].L, rg[i].R);
		puts("=============");
		*/
	}
} sol;
const flt g = 10.0;
flt L, h, l, d;
flt vx, vy, ux, uy;
flt mi, ma;
flt sqr(flt x){return x*x;}
Rang genRange(flt k, flt b, flt hh, bool LT){
	flt A = -0.5*g*(sqr(k)+1.0);
	flt B = vy+uy*k-g*k*b;
	flt C = uy*b-0.5*g*sqr(b)-hh;
	Rang res;
	flt delta = sqr(B) - 4.0*A*C;
	if (delta<0) {
		if (LT) {
			res.add(rang(-1e9, 1e9));
		}
	} else {
		flt x0, x1;
		x0 = (-B+sqrt(delta))*0.5/A;
		x1 = (-B-sqrt(delta))*0.5/A;
		if (fabs(x0) > fabs(x1)) {
			x1 = C / A / x0;
		} else {
			x0 = C / A / x1;
		}
		if(x1<x0)swap(x0,x1);
		if (LT) {
			res.add(rang(-1e9, x0));
			res.add(rang(x1, 1e9));
		} else res.add(rang(x0, x1));
	}
	return res;
}
int main(){
	cin>>L>>h>>l>>d;
	cin>>vx>>vy>>ux>>uy;
	mi = 0; ma = min(L/flt(vx), 2.0*vy/g);
	sol.add(rang(mi, ma));
	sol.print("1");
	Rang tmp;
	tmp = genRange(-vx/flt(ux), L/flt(ux), h, 0);
	sol = sol & tmp;
	sol.print("2");
	tmp = genRange(-vx/flt(ux), L/flt(ux), h+d, 1);
	sol = sol & tmp;
	sol.print("3");
	tmp = genRange(-vx/flt(ux), (L+l)/flt(ux), h, 0);
	sol = sol & tmp;
	sol.print("4");
	tmp = genRange(-vx/flt(ux), (L+l)/flt(ux), h+d, 1);
	sol = sol & tmp;
	sol.print("5");
	Rang tmp2;
	flt tt = uy*ux/g;
	flt le = (L-tt)/vx, ri = (L+l-tt)/vx;
	tmp2.add(rang(-1e9, le));
	tmp2.add(rang(ri, 1e9));
	Rang tmp3 = sol & tmp2;
	tmp3.print("5");
	//out(tmp3.rg.size());
	flt ans;
	bool found = 0;
	if (tmp3.rg.size()) { //answer found
		ans = tmp3.get();
		found = 1;
	} else {
		tmp = genRange(0, uy/g, h+d, 1);
		sol = sol & tmp;
		sol.print("6");
		if (sol.rg.size()) {
			ans = sol.get();
			found = 1;
		}
	}
	if (found) printf("%.10lf\n", (double)ans);
	else puts("-1");
}
