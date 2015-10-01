#include<bits/stdc++.h>
#define INF 10000
using namespace std;
short f[210][2][21][21][21][21];
int a[210],b[210];

inline void checkmin(short &x,short y) {
	if (y<x) x=y;
}

int main() {
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	for (int i=1;i<=n;i++) scanf("%d",b+i);
	for (int i=0;i<=n+1;i++)
		for (int k=0;k<2;k++)
			for (int a1=0;a1<=A;a1++) for (int b1=0;b1<=B;b1++)
				for (int a2=0;a2<=A;a2++) for (int b2=0;b2<=B;b2++)
					f[i][k][a1][b1][a2][b2]=INF;
	f[0][1][0][0][0][0]=0;
	for (int i=0;i<n;i++) {
		for (int a1=0;a1<=A;a1++) for (int b1=0;b1<=B;b1++)
			for (int a2=0;a2<=A;a2++) for (int b2=0;b2<=B;b2++) {
				int nb1=max(0,b1-1);
				int nb2=max(0,b2-1);
				short &t=f[i][1][a1][b1][a2][b2];
				checkmin(f[i+1][0][a1][nb1][a2][nb2],t);
				checkmin(f[i+1][0][A][B][a2][nb2],t+1);
				checkmin(f[i+1][0][a1][nb1][A][B],t+1);
				checkmin(f[i+1][0][A][B][A][B],t+2);
			}
		int u=a[i+1]+b[i+1];
		for (int a1=0;a1<=A;a1++) for (int b1=0;b1<=B;b1++)
			for (int a2=0;a2<=A;a2++) for (int b2=0;b2<=B;b2++) {
				short &t=f[i+1][0][a1][b1][a2][b2];
				if (u==0) checkmin(f[i+1][1][a1][b1][a2][b2],t);
				if (u==1) {
					if (a1>0 && b1>0) checkmin(f[i+1][1][a1-1][b1][a2][b2],t);
					if (a2>0 && b2>0) checkmin(f[i+1][1][a1][b1][a2-1][b2],t);
				}
				if (u==2) {
					if ((a1>0 && b1>0) && (a2>0 && b2>0)) checkmin(f[i+1][1][a1-1][b1][a2-1][b2],t);
				}
			}
	}
	short ans=INF;
	for (int a1=0;a1<=A;a1++) for (int b1=0;b1<=B;b1++)
		for (int a2=0;a2<=A;a2++) for (int b2=0;b2<=B;b2++)
			checkmin(ans,f[n][1][a1][b1][a2][b2]);
	printf("%d\n",(int)ans);
}
