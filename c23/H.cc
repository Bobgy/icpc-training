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
const int MAXN = 4123;
flt P[4123];
flt f[4123], g[4123], h[4123];
void init(){
	P[0]=1.0;
	for(int i=1;i<MAXN;++i)
		P[i]=P[i-1]*flt(i);
	f[0]=1;g[0]=0;h[0]=0;
	//f[1]=0;g[1]=0;h[1]=0;
	f[1]=1;g[1]=1;h[1]=1;
	for(int i=2;i<MAXN;++i){
		f[i]=g[i]=0;
		for(int j=1;j<=i;++j){
			f[i]+=f[i-j];
			g[i]+=f[i-j]+g[i-j];
		}
		//fprintf(stderr, "f[%d]=%.10lf g[%d]=%.10lf\n", i, f[i], i, g[i]);
		//if(f[i]!=f[i])break;
		//REP(j,i+1)g[j]/=f[i],f[j]/=f[i];
		h[i]=g[i]/f[i];
		if(i<=20){
			//fprintf(stderr, "h[%d]=%.10lf\n", i, h[i]);
			LL gg=g[i], ff=f[i];
			LL tt=__gcd(gg,ff);
			gg/=tt; ff/=tt;
			fprintf(stderr, "h[%d]=%.0lf/%.0lf\n", i, g[i], f[i]);
			//fprintf(stderr, "h[%d]=%lld/%lld\n", i, gg, ff);
			//out(h[i]);
		}
		REP(j,i)g[j]*=i,f[j]*=i;
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
		int n, c, tot;
		flt ans;
		scanf("%d%d",&n,&c);
		tot=0;ans=0;
		REP(i,n)scanf("%d",a+i+1),vis[i+1]=0;
		for(int i=1;i<=n;++i)if(!vis[i]){
			int t=dfs(i);
			if(t==i)ans+=1.0;
			else if(t==0)tot++;
		}
		//out(tot); out(ans);
		ans+=h[tot];
		ans*=c;
		printf("%.10lf\n", ans);
	}
}
