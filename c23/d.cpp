#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int MAXN=510000;

PII f[4*MAXN];
char s[MAXN];
int cnt[MAXN],tr[2][MAXN],ts[MAXN];
int sa[MAXN],rk[MAXN],len;
PII ans;

void construct(const char *s,int n,int m=256) {
	int i,j,k,*x=tr[0],*y=tr[1];
	memset(cnt,0,sizeof(cnt[0])*m);
	for (i=0;i<n;++i) cnt[s[i]]++;
	partial_sum(cnt,cnt+m,cnt);
	for (i=0;i<n;++i) rk[i]=cnt[s[i]]-1;
	for (k=1;k<=n;k<<=1) {
		for (i=0;i<n;++i) x[i]=rk[i],y[i]=i+k<n?rk[i+k]+1:0;
		fill(cnt,cnt+n+1,0);
		for (i=0;i<n;++i) cnt[y[i]]++;
		partial_sum(cnt,cnt+n+1,cnt);
		for (i=n-1;i>=0;--i) ts[--cnt[y[i]]]=i;
		fill(cnt,cnt+n+1,0);
		for (i=0;i<n;++i) cnt[x[i]]++;
		partial_sum(cnt,cnt+n+1,cnt);
		for (i=n-1;i>=0;--i) sa[--cnt[x[ts[i]]]]=ts[i];
		for (i=rk[sa[0]]=0;i+1<n;++i) rk[sa[i+1]]=rk[sa[i]]+(x[sa[i]]!=x[sa[i+1]]||y[sa[i]]!=y[sa[i+1]]);
	}
}

void ins(int p,int l,int r,int b,PII u) {
	if (l==r) {
		f[p]=u;
		return;
	}
	int mid=(l+r)/2;
	if (b<=mid) ins(p*2,l,mid,b,u);
	else ins(p*2+1,mid+1,r,b,u);
	f[p]=max(f[p*2],f[p*2+1]);
}

void count(int p,int l,int r,int b,int e) {
	if (e<l || b>r) return;
	if (b<=l && r<=e) {
		ans=max(ans,f[p]);
		return;
	}
	int mid=(l+r)/2;
	count(p*2,l,mid,b,e);
	count(p*2+1,mid+1,r,b,e);
}

int main() {
	int n,q;
	scanf("%s",s);
	n=strlen(s);
	construct(s,n);
	for (int i=1;i<=n;i++) ins(1,1,n,i,PII(rk[i-1],i));
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		ans=PII(0,0);
		count(1,1,n,l,r);
		printf("%d\n",ans.second);
	}
}
