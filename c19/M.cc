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
struct Poly{
	LL a[8];
	int now;
	void read() {
		REP(i,8)scanf("%lld",a+i);
		now=1;
	}
	LL get() {
		LL res=0;
		REP(i,8)res=res*now+a[i];
		++now;
		return res;
	}
} p[31234];
int main(){
	int k;
	scanf("%d",&k);
	REP(i,k)p[i].read();
	int n;
	scanf("%d",&n);
	LL t;
	priority_queue<pair<LL, int> > q;
	REP(i,k)q.push(mp(-p[i].get(), i));
	while(n--){
		t=q.top().X;
		int id=q.top().Y;
		q.pop();
		q.push(mp(-p[id].get(), id));
	}
	printf("%lld\n", -t);
}
