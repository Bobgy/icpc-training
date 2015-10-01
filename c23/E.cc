#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
	#define out(x)
#else
	#define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<double, int> pii;
typedef vector<pii> vpii;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define EPS 1e-9
double a[11234];
vector<pii> pos, neg;
int main(){
	int n;
	scanf("%d",&n);
	REP(i,n){
		scanf("%lf",a+i);
		if(a[i]>=-0.0){
			pos.pb(pii(a[i],i));
		} else {
			neg.pb(pii(fabs(a[i]),i));
		}
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
	reverse(pos.begin(), pos.end());
	reverse(neg.begin(), neg.end());
	double ans=1.0;
	vector<int> id;
	REP(i,pos.size())if(pos[i].X>1.0){
		id.pb(pos[i].Y);
		ans*=pos[i].X;
	}
	for(int i=0;i+1<neg.size();i+=2){
		double t=neg[i].X*neg[i+1].X;
		if(t>1.0+EPS){
			id.pb(neg[i].Y);
			id.pb(neg[i+1].Y);
			ans*=t;
		}
	}
	if(id.empty()){
		ans=0;
		if(!pos.empty()){
			ans=pos[0].X;
			id=vi(1,pos[0].Y);
		}
		if(neg.size()>=2){
			double tmp=neg[0].X*neg[1].X;
			if(tmp>ans+EPS){
				ans=tmp;
				id=vi(1,neg[0].Y);
				id.pb(neg[1].Y);
			}
		}
	}
	sort(id.begin(), id.end());
	printf("%d\n", (int)id.size());
	REP(i,id.size())printf("%d%c",id[i]+1," \n"[i+1==id.size()]);
}
