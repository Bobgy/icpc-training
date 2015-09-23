#include<bits/stdc++.h>
#define INF 1000000000
using namespace std;

struct sa {
	int a,c,s;
	friend bool operator < (sa a,sa b) {
		return a.c<b.c || a.c==b.c && a.a<b.a;
	}
};
sa a[110000];

int change(int x) {
	if (x==1) return 3;
	if (x==2) return 1;
	return 2;
}

int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&a[i].a,&a[i].c,&a[i].s);
		a[i].a=change(a[i].a);
	}
	sort(a,a+n);
	vector<vector<vector<int>>> f(n+1,vector<vector<int>>(m+1,vector<int>(m+1)));
	for (int j=0;j<=m;j++)
		for (int k=0;k<=m;k++)
			f[0][j][k]=INF;
	f[0][0][0]=0;
	for (int i=0;i<n;i++) {
		for (int j=0;j<=m;j++)
			for (int k=0;k<=m;k++)
				f[i+1][j][k]=f[i][j][k];
		for (int j=0;j<=m;j++)
			for (int k=0;k<=m;k++) {
			//	if (f[i][j][k]<INF) printf("%d %d %d\n",i,j,k);
				if ((a[i].a==1 || a[i].a==2) && k<m)
					f[i+1][j][k+1]=min(f[i+1][j][k+1],f[i][j][k]+a[i].s);
				if ((a[i].a==2 || a[i].a==3) && j<m && k>0)
					f[i+1][j+1][k-1]=min(f[i+1][j+1][k-1],f[i][j][k]+a[i].s);
			}
	}
	printf("%d\n",f[n][m][0]);
}
