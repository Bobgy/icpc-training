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
vector<LL> p;
LL f[31234], g[31234];
bitset<51> sqr[31234];
LL power(LL x, int n){
	LL res=1;
	for(; n; n>>=1, x*=x)
		if(n&1)res*=x;
	return res;
}
LL log2(LL x){
	LL L=1, R=1;
	for(; R*R<x; R*=2);
	while(L<R){
		LL M=(L+R+1)/2;
		if(M*M<=x)L=M;
		else R=M-1;
	}
	assert(L*L<=x && (L+1)*(L+1)>x);
	return L;
}
LL log3(LL x){
	LL L=1, R=1;
	for(; R*R*R<x; R*=2);
	while(L<R){
		LL M=(L+R+1)/2;
		if(M*M*M<=x)L=M;
		else R=M-1;
	}
	assert(L*L*L<=x && (L+1)*(L+1)*(L+1)>x);
	return L;
}
const LL INF=1e17;
void init(){
	for(int i=4;i<=50;++i){
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
	out(p.size());
	for(int i=4;i<=50;++i){
		int j=1;
		while(1){
			LL t=power(j, i);
			if(t<=INF && pow((double)j, i)<=INF*10.0){
				int id=lower_bound(p.begin(), p.end(), t)-p.begin();
				sqr[id][i]=1;
			} else break;
			++j;
		}
	}
	for(int i=0; i+1<p.size(); ++i){
		LL t0, t1;
		t0=log2(p[i]);
		t1=log2(p[i+1]-1);
		f[i]=t1-t0;
		t0=log3(p[i]);
		t1=log3(p[i+1]-1);
		g[i]=t1-t0;
		//if(i<=4)printf("i=%d, p=%lld, f=%lld, g=%lld\n", i, p[i], f[i], g[i]);
	}
	REP(i,p.size()){
		LL t=log2(p[i]);
		if(t*t==p[i])sqr[i][2]=1;
		t=log3(p[i]);
		if(t*t*t==p[i])sqr[i][3]=1;
	}
}
bitset<51> msk;
LL bin(LL L, LL R, int n){
	LL t0, t1, g0, g1;
	t0=t1=g0=g1=0;
	if(msk[2])t0 = log2(L-1);
	if(msk[3])t1 = log3(L-1);
	while(L<R){
		LL M=(L+R)/2;
		if(msk[2])g0 = log2(M);
		if(msk[3])g1 = log3(M);
		if(g0-t0+g1-t1<n)L=M+1;
		else R=M;
	}
	assert(L==R);
	return L;
}
int a[50];
int main(){
	init();
	out(p.back());
	int q;
	scanf("%d",&q);
	while(q--){
		int n, m;
		scanf("%d%d",&n,&m);
		msk.reset();
		REP(i,m){
			scanf("%d",a+i);
			msk[a[i]]=1;
		}
		if(msk[1]){
			printf("%d\n", n);
			continue;
		}
		LL ans=0;
		REP(i,p.size()){
			out(i);out(n);
			if((msk&sqr[i]).any())n--;
			out(n);
			if(n==0){
				ans=p[i];
				break;
			}
			LL tot=0;
			if(msk[2])tot+=f[i];
			if(msk[3])tot+=g[i];
			out(tot);
			if(n<=tot){
				ans=bin(p[i]+1, p[i+1]-1, n);
				break;
			} else n-=tot;
		}
		printf("%lld\n", ans);
	}
}
