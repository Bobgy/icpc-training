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
char buf[1123];
vi see[412];
string pos[412];
vi E[412];
bool vis[412];
vi part[2];
vi criminal;
void dfs(int x, int id){
	vis[x]=1;
	part[id].push_back(x);
	for(auto u: E[x]){
		if(!vis[u])dfs(u, id^1);
	}
}
int main(){
	int n;
	scanf("%d ",&n);
	REP(i,n){
		int nn;
		scanf("%s%d ",buf,&nn);
		pos[i]=buf;
		while(nn--){
			int x;
			scanf("%d",&x);
			--x;
			see[i].push_back(x);
		}
		sort(see[i].begin(), see[i].end());
	}
	REP(i,n)REP(j,i)if(pos[i]!=pos[j]){
		for(auto u: see[i]){
			int id = lower_bound(see[j].begin(), see[j].end(), u)-see[j].begin();
			if(id<see[j].size() && see[j][id]==u){
				E[i].pb(j);
				E[j].pb(i);
				break;
			}
		}
	}
	REP(i,n){
		for(auto u: see[i]){
			if(pos[u]!=pos[i]){
				E[u].pb(i);
				E[i].pb(u);
			}
		}
	}
	REP(i,n)if(!vis[i]){
		part[0].clear();
		part[1].clear();
		dfs(i, 0);
		int jj=part[0].size()<part[1].size() ? 0 : 1;
		for(auto u: part[jj])criminal.push_back(u);
	}
	if(criminal.empty())criminal.push_back(0);
	printf("%d\n", (int)criminal.size());
	REP(i,criminal.size())printf("%d%c",criminal[i]+1," \n"[i+1==criminal.size()]);
}
