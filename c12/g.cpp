#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;

int f[51000][2];

int main() {
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	f[0][0]=f[0][1]=1;
	for (int i=0;i<=n;i++) {
		for (int j=1;j<=a && i-j>=0;j++) f[i][0]=(f[i][0]+f[i-j][1])%mod;
		for (int j=1;j<=b && i-j>=0;j++) f[i][1]=(f[i][1]+f[i-j][0])%mod;
	}
	printf("%d\n",(f[n][0]+f[n][1])%mod);
}
