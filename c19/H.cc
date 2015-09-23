#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
	#define out(x) (x)
#else
	#define out(x) ((cerr<<#x"="<<(x)<<endl),x)
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
flt p[21];
vi E[21];
const flt eps=1e-9;
const int MAXN=22, MAXM=22;
flt e[MAXN][MAXM], x[MAXM];
struct Gauss {
	int pos[MAXM];
	void print(int n, int m){
		#ifndef ONLINE_JUDGE
		out("=========");
		REP(i,n)REP(j,m+1)printf("%4.4lf%c", e[i][j], " \n"[j==m]);
		#endif
	}
	int solve(int n, int m){
		int r=0;
		for(int c=0,i,j,k;c<=m&&r<n;++c){
			for(i=k=r;i<n;++i)
				if(fabs(e[i][c])>fabs(e[k][c]))k=i;
			if(k!=r)for(j=c;j<=m;++j)swap(e[k][j],e[r][j]);
			if(fabs(e[r][c])<eps)continue;
			pos[r]=c;
			for(i=r+1;i<n;++i){
				flt t=-e[i][c]/e[r][c];
				for(int j=c;j<=m;++j)e[i][j]+=t*e[r][j];
			}
			++r;
		}
		if(r>0 && pos[r-1]==m)return -1;
		for(int i=0;i<m;++i)x[i]=0;
		for(int i=r-1;i>=0;--i){
			int c=pos[i];
			x[c]=e[i][m]/e[i][c];
			for(int j=0;j<i;++j)e[j][m]-=e[j][c]*x[c];
		}
		return r;
	}
} gauss;
int n;
map<vi, vector<flt>> M[21];
void dfs(vi a){
	map<vi, vector<flt>> &mm=M[a.size()];
	if(mm.find(a)==mm.end()){
		mm[a].resize(n);
		REP(i,a.size())REP(j,i){
			vi t=a;
			t[j]+=t[i];
			t.erase(t.begin()+i);
			sort(t.begin(), t.end());
			dfs(t);
		}
	}
}
void gao(){
	for(int i=1; i<=n; ++i){
		for(auto &u: M[i]){
			vi a=u.X;
			vector<flt> &ans=u.Y;
			if(i==1){
				REP(i,n)ans[i]=0.0;
				continue;
			}
			memset(e, 0, sizeof e);
			REP(j,n){
				e[j][j]=1.0;
				e[j][n]=1.0;
			}
			int tot=0;
			REP(i,a.size())tot+=a[i]*(a[i]-1)/2;
			int total=n*(n-1)/2;
			REP(j,n){
				for(auto k: E[j]){
					e[j][k]-=out(tot*1.0/total/E[j].size()*p[j]);
					e[j][k]-=out((1.0-p[j])/E[j].size());
				}
			}
			REP(i,a.size())REP(j,i){
				vi t=a;
				int tmp=t[i]*t[j];
				t[j]+=t[i];
				t.erase(t.begin()+i);
				sort(t.begin(), t.end());
				vector<flt> &ttt=M[t.size()][t];
				// REP(i,t.size())printf("%d%c",t[i]," \n"[i+1==t.size()]);
				// out(ttt.size());
				REP(j,n){
					for(auto k: E[j]){
						e[j][n]+=out(ttt[k]*tmp/total/E[j].size()*p[j]);
					}
				}
			}
			gauss.print(n, n);
			assert(~gauss.solve(n, n));
			gauss.print(n, n);
			REP(i,n)ans[i]=x[i];
			out(a.size());
			#ifndef ONLINE_JUDGE
			REP(i,a.size())printf("%d%c",a[i]," \n"[i+1==a.size()]);
			REP(i,n)printf("%.10lf%c",ans[i]," \n"[i+1==n]);
			#endif
		}
	}
}
int main(){
	scanf("%d",&n);
	REP(i,n)scanf("%lf",p+i);
	REP(i,n){
		int nn;
		scanf("%d",&nn);
		while(nn--){
			int x;
			scanf("%d",&x);
			--x;
			E[i].pb(x);
		}
	}
	dfs(vi(n,1));
	gao();
	printf("%.10lf\n", M[n][vi(n,1)][0]);
}
