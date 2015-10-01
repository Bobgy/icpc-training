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
int a[1123];
int main(){
	int n;
	scanf("%d",&n);
	LL sum=0;
	REP(i,n){
		scanf("%d",a+i);
		sum+=a[i];
	}
	int ans=0;
	REP(i,n)if(a[i]*(LL)n>sum)ans++;
	printf("%d\n", ans);
}
