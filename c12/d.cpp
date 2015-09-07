#include<bits/stdc++.h>
using namespace std;

int a[300],m[300];
int n,q;

int main() {
	int M,A1,A2;
	scanf("%d%d%d",&M,&A1,&A2);
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",m+i,a+i);
	int ans1=-1,ans2=0,ans3=0;
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		int num,money,advan;
		scanf("%d%d%d",&num,&money,&advan);
		if (M>=money) {
			int cost;
			if (num==1) cost=A1;
			else cost=A2;
			if (cost+advan>ans1) {
				ans1=cost+advan;
				ans2=0;
				ans3=i+1;
			}
		}
		if (num==2)
		for (int j=0;j<n;j++) if (M*2>=money && m[j]*2>=money) {
			if (advan+a[j]>ans1) {
				ans1=advan+a[j];
				ans2=j+1;
				ans3=i+1;
			}
		}
	}
	if (ans1==-1) printf("Forget about apartments. Live in the dormitory.\n"); 
	else if (ans2) printf("You should rent the apartment #%d with the friend #%d.\n",ans3,ans2);
	else printf("You should rent the apartment #%d alone.\n",ans3);
}
