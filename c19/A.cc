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
#define MAXN 11234
int dfn[MAXN], low[MAXN], id[MAXN], num, st[MAXN], top, in[MAXN], tot;
vi E[MAXN], e[MAXN], ie[MAXN];
void tarjan(int now){
	in[st[top++] = now] = true;
	dfn[now] = low[now] = ++tot;
	int i;
	for (int ii = E[now].size() - 1; ii >= 0; --ii) {
		i = E[now][ii];
		if (!dfn[i]) {
			tarjan(i);
			low[now] = min(low[now], low[i]);
		} else if (in[i])
			low[now] = min(low[now], dfn[i]);
	}
	if (dfn[now] == low[now]) {
		do {
			i = st[--top];
			in[i] = false;
			id[i] = num;
		} while (i != now);
		++num;
	}
}
void Components(int N){
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(in, 0, sizeof in);
	memset(id, 0xff, sizeof id);
	for (int i=top=num=tot=0; i<N; ++i)
		if(!dfn[i])tarjan(i);
}
int cnt[MAXN];
bitset<10000> f[10000], g[10000];
int main(){
	int n, m;
	scanf("%d%d",&n,&m);
	REP(i,m){
		int x, y;
		scanf("%d%d",&x,&y);
		--x, --y;
		E[x].pb(y);
	}
	Components(n);
	REP(i,n){
		cnt[id[i]]++;
		for(auto j: E[i])if(id[i]!=id[j])e[id[i]].pb(id[j]);
	}
	REP(i,num){
		sort(e[i].begin(), e[i].end());
		e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
	}
	REP(i,num){
		f[i].reset();
		f[i][i]=1;
		for(auto j: e[i]){
			ie[j].pb(i);
			assert(j<i);
			f[i]|=f[j];
		}
	}
	int ans=0;
	for(int i=num-1; ~i; --i){
		g[i]=f[i];
		for(auto j: ie[i]){
			assert(j>i);
			g[i]|=g[j];
		}
		int tmp=0;
		REP(j,num)if(g[i][j])tmp+=cnt[j];
		ans+=tmp*cnt[i];
	}
	printf("%d\n", ans);
}
