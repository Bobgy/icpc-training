#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int f[10][10];
int w[1000];

void gao(int y) {
	int a,b;
	b=w[0];
	for (int i=999;i>=0;i--) if (w[i]) {
		a=w[i];
		break;
	}
	if (!f[a][b]) f[a][b]=y;
//	printf("%d %d %d\n",y,a,b);
}

void mul() {
	int g=0;
	for (int i=0;i<1000;i++) {
		w[i]=w[i]*2+g;
		g=w[i]/10;
		w[i]%=10;
	}
}

int main() {
	w[0]=1;	
	for (int i=0;i<1000;i++) {
		gao(i+1);
		mul();
	}
	int a,b;
/*	for (int a=1;a<=9;a++) {
		for (int b=0;b<=9;b++)
			printf("%d ",f[a][b]);
		puts("");
	}*/
	scanf("%d%d",&a,&b);
	printf("%d\n",f[a][b]-1);
}
