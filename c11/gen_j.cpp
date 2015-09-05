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
int a[50];
int main(){
	srand(time(0));
	freopen("joke.in", "w", stdout);
	int n=50;
	REP(i,n)a[i]=i+1;
	random_shuffle(a,a+n);
	REP(i,n)printf("%d",a[i]);
	putchar('\n');
}
