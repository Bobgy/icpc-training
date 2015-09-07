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
vpii a, b;
int s=0;
int main(){
	int n;
	scanf("%d",&n);
	a.resize(n);
	b.resize(n);
	REP(i,n){
		scanf("%d",&a[i].X);
		a[i].Y=i+1;
		s+=a[i].X;
	}
	REP(i,n){
		scanf("%d",&b[i].X);
		b[i].Y=i+1;
		s-=b[i].X;
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	if(s>0){
		reverse(b.begin(), b.end());
	} else reverse(a.begin(), a.end());
	REP(i,n)printf("%d %d\n", a[i].Y, b[i].Y);
}
