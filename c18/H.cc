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
const int MAX=1e8;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		double x;
		scanf("%lf", &x);
		int t=round(x*1e8);
		LL rem=MAX/2-t;
		if(rem==0){
			puts("-1");
			continue;
		}
		bool inf=0;
		int cnt=0;
		for(int i=5e7; i>=rem;){
			++cnt;
			if(i==rem){
				inf=1;
				break;
			}
			if(i%2!=0)rem*=2;
			else i/=2;
		}
		if(inf)puts("-1");
		else {
			printf("%d\n", cnt*4);
		}
	}
}
