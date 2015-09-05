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
const int MAXN = 212345, OFFSET=5;
typedef int DATA;
struct BITree{
	DATA a[MAXN];
	void clear(){
		memset(a, 0, sizeof(a));
	}
	int lowbit(int i){
		return i&-i;
	}
	DATA sum(int i){
		DATA ret=0;
		for(i+=OFFSET; i>0; i-=lowbit(i))
			ret += a[i];
		return ret;
	}	
	void add(int i, DATA d){
		for(i+=OFFSET; i<MAXN; i+=lowbit(i))
			a[i] += d;
	}
} bt;
int x[MAXN];
int main(){
	freopen("improvements.in", "r", stdin);
	freopen("improvements.out", "w", stdout);
	int n;
	scanf("%d",&n);
	REP(i,n){
		scanf("%d",x+i);
		bt.add(x[i], 1);	
	}
	int mi=0, ma=n, ans=0;
	REP(i,n){
		bt.add(x[i], -1);
		int le = bt.sum(x[i])-bt.sum(mi);
		int ri = bt.sum(ma)-bt.sum(x[i]);
//		out(x[i]);out(le); out(ri);
		if(le>0 && ri>0){
			++ans;
		} else {
			if(le>0){
				ma = x[i]-1;
			} else {
				mi = x[i];
			}
		}
	}
	printf("%d\n", n-ans);
}
