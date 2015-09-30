#include<bits/stdc++.h>
using namespace std;

int f[20][20][20][20];
int v[20][20][20][20];
bool g[20][20][20][20][410];
char a[30][30];

int gao(int x1,int x2,int y1,int y2) {
	if (x1>x2 || y1>y2) return 0;
	if (v[x1][x2][y1][y2]) return f[x1][x2][y1][y2];
	v[x1][x2][y1][y2]=1;
	int &ret=f[x1][x2][y1][y2];
	for (int i=x1;i<=x2;i++)
		for (int j=y1;j<=y2;j++) if (a[i][j]!='X') {
			g[x1][x2][y1][y2][gao(x1,i-1,y1,j-1)^gao(x1,i-1,j+1,y2)^gao(i+1,x2,y1,j-1)^gao(i+1,x2,j+1,y2)]=true;
		}
	for (int i=0;i<410;i++) if (!g[x1][x2][y1][y2][i]) {
		ret=i;
		return ret;
	}
}

int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",a[i]);
	puts(gao(0,n-1,0,m-1)?"First":"Second");
}
