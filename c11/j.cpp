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
char s[112];
bool f[112][1<<9];
int L, n;
LL vis;
int a[51], tot=0;
bool dfs(int i){
	if(i>=L)return true;
	if(i<L-1){
		int xx=s[i]*10+s[i+1];
		if(xx<=n && !((vis>>xx)&1)){
			vis|=1LL<<xx;
			a[tot++]=xx;
			if(dfs(i+2))return true;
			--tot;
			vis^=1LL<<xx;
		}
	}
	if(!((vis>>s[i])&1)){
		vis|=1LL<<s[i];
		a[tot++]=s[i];
		if(dfs(i+1))return true;
		--tot;
		vis^=1LL<<s[i];
	}
	return false;
}
int main(){
	freopen("joke.in", "r", stdin);
	freopen("joke.out", "w", stdout);
	gets(s);
	L = strlen(s);
	REP(i,L)s[i]-='0';
	bool ok=0;
	for(n=1;n<=50;++n){
		int cnt=0;
		if(n<=9)cnt=n;
		else cnt=9+(n-9)*2;
		if(cnt==L){
			ok=1;
			break;
		}
	}
	assert(ok);
	vis=0;
	dfs(0);
	REP(i,n)printf("%d%c",a[i]," \n"[i+1==n]);
}
