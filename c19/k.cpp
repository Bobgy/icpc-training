#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct point {
	ll x,y;
};

ll f[3100][5100];
ll s[5100];
ll g[5100];
ll a[5100];
point q[5100];
int n,m;

inline ll cha(point a,point b,point c) {
	return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}

inline ll cal(ll k,point t) {
	return k*t.x+t.y;
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%lld",a+i);
		s[i]=s[i-1]+a[i]*i;
		g[i]=g[i-1]+a[i];
		f[1][i]=s[i];
	}
	for (int i=2;i<=m;i++) {
		int l,r;
		l=1;
		r=1;
		q[l].x=0;
		q[r].y=0;
		for (int j=1;j<=n;j++) {
			/*f[i][j]=100000000;
			for (int k=0;k<j;k++)
				f[i][j]=min(f[i][j],s[j]+f[i-1][k]-s[k]+g[k]*k-g[j]*k);*/
			while (l<r && cal(-g[j],q[l])>=cal(-g[j],q[l+1])) l++;
			point t;
			f[i][j]=cal(-g[j],q[l])+s[j];
			t.x=j;
			t.y=f[i-1][j]-s[j]+g[j]*j;
			while (l<r && cha(t,q[r],q[r-1])>=0) r--;
			q[++r]=t;
		//	printf("i=%d j=%d %lld\n",i,j,f[i][j]);
		}
	}
	printf("%lld\n",f[m][n]);
}
