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
int W, L, w, l, n, m, a, b, ans;
bool ok=0;
int gao(int n, int b, int l){
	if(b==0)return 0;
	out(L);
	out(b);
	int t=l/b;
	out(t);
	int num=(n+t-1)/t;
	out(num);
	if(num*t>n)ok=1;
	return num;
}
int main(){
	scanf("%d%d%d%d",&W,&L,&w,&l);
	n=W/w, m=L/l;
	a=W%w, b=L%l;
	ans=n*m;
	out(ans);
	ans+=gao(m,a,w);
	out(ans);
	ans+=gao(n,b,l);
	if(!ok && a>0 && b>0)ans++;
	printf("%d\n", ans);
}
