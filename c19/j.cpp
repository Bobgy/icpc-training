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
const LL INF=100;
LL power(LL x, int n){
	LL res=1;
	for(; n; n>>=1, x*=x)
		if(n&1)res*=x;
	return res;
}
bitset<51> msk;
vector<LL> p;
void init(){
	for(int i=2;i<=50;++i){
		int j=1;
		while(1){
			LL t=power(j, i);
			if(t<=INF && pow((double)j, i)<=INF*10.0)p.pb(t);
			else break;
			++j;
		}
	}
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
}
int main(){
	FILE *fans = fopen("ans", "w");
	int q=10;
	printf("%d\n", q);
	while(q--){
		int n, m;
		for(int i=2;i<=50;++i)msk[i]=rand()&1;
		m=msk.count();
		init();
		n=rand()%p.size()+1;
		printf("%d %d\n", n, m);
		REP(i,51)if(msk[i])printf("%d ", i);
		putchar('\n');
		fprintf(fans, "%lld\n", p[n-1]);
	}
	fclose(fans);
}
