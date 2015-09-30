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
typedef double flt;
const flt PI = acos(-1.0);
int main(){
	flt x, y, theta, omega;
	scanf("%lf%lf%lf%lf",&x,&y,&theta,&omega);
	theta*=PI/180.0;
	omega*=PI/180.0;
	if(theta>PI)theta-=2*PI;
	flt ang0=atan2(y,x);
	flt ang=min(fabs(theta-ang0), 2*PI-fabs(theta-ang0));
	flt R = hypot(x, y);
	flt lo, hi;
	lo=0; hi=omega*R;
	int tt=100;
	while(tt--){
		flt mi=lo+(hi-lo)/2.0;
		flt x=R*omega/mi, y=sqrt(x*x-1);
		if(y-atan(y)<=ang)hi=mi;
		else lo=mi;
	}
	printf("%.10lf\n", lo);
}
