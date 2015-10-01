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
const int MAXN = 4123;
flt P[4123];
flt f[4123], g[4123];
void init(){
	P[0]=1.0;
	for(int i=1;i<MAXN;++i)
		P[i]=P[i-1]*flt(i);
	g[0]=0;
	for(int i=1;i<MAXN;++i){
		g[i]=g[i-1]+1.0/flt(i);
		//if(i<20)fprintf(stderr, "%d %.0lf %.0lf\n", i, P[i], P[i]*g[i]);
	}
}
int a[4123];
bool vis[4123];
int dfs(int i){
	vis[i]=1;
	if(a[i]){
		if(vis[a[i]])return a[i];
		return dfs(a[i]);
	}
	return 0;
}
int main(){
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		int n, c, tot, chain;
		flt ans;
		scanf("%d%d",&n,&c);
		tot=0;ans=0;chain=0;
		REP(i,n)scanf("%d",a+i+1),vis[i+1]=0;
		for(int i=1;i<=n;++i)if(!vis[i]){
			int t=dfs(i);
			if(t==i)ans+=1.0;
			else if(t==0){
				tot++;
				if(a[i]!=0)chain++;
			} else if(a[t]==0)chain++;
		}
		out("=========");
		out(tot); out(ans); out(chain);
		int pt = tot - chain;
		flt num, den, xx;
		num=den=0; xx=1.0;
		REP(i,pt+1){
			out(xx);
			num+=xx*(g[tot-i]+i);
			den+=xx;
			xx*=-(pt-i)/flt(i+1)/flt(tot-i);
		}
		out(num);out(den);
		ans+=num/den;
		ans*=c;
		printf("%.10lf\n", ans);
	}
}
