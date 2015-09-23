#include<bits/stdc++.h>
using namespace std;

int a[110000];

int main() {
	int n,K;
	map<int,int> M;
	scanf("%d%d",&n,&K);
	for (int i=0;i<=n;i++) scanf("%d",a+i);
	int t=a[n]/K;
	for (int i=0;i<n;i++) {
		int &x=M[a[i]%t];
		x++;
		if (x==K) return puts("1"),0;
	}
	puts("0");
}
