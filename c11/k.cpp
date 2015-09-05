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
int a[1123], b[1123];
int main() {
	freopen("knockout.in", "r", stdin);
	freopen("knockout.out", "w", stdout);
	int n, m;
	scanf("%d%d",&n,&m);
	REP(i,n)scanf("%d%d",a+i,b+i);
	REP(i,m){
		int x, y, t;
		scanf("%d%d%d",&x,&y,&t);
		int ans=0;
		REP(i,n){
			int rg = (b[i]-a[i])*2;
			int tt = t % rg;
			if (tt>b[i]-a[i]) {
				tt -= b[i]-a[i];
				tt = (b[i] - a[i]) - tt;
			}
			tt = a[i]+tt;
			if (tt >= x && tt <= y) ans++;
		}
		printf("%d\n", ans);
	}
}
