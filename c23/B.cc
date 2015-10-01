#include<bits/stdc++.h>
using namespace std;

int a[300],b[300],c[300],v[300];

int main() {
	int n,A,B,ans=0;
	scanf("%d%d%d",&n,&A,&B);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	for (int i=1;i<=n;i++) scanf("%d",b+i);
	for (int i=1;i<=n;i++) c[i]=a[i]+b[i];
	while (1) {
		int flag=0,k;
		for (int i=1;i<=n;i++) if (c[i]>0) {
			k=i;
			flag=1;
			break;
		}
		if (!flag) break;
		ans++;
		c[k]--;
		int t=A-1;
		memset(v,0,sizeof(v));
		for (int i=k+1;i<k+B;i++) if (c[i]==2 && t>0) {
			c[i]--;
			t--;
			v[i]=1;
		}
		for (int i=k+1;i<k+B;i++) if (c[i]>0 && t>0 && !v[i]) {
			c[i]--;
			t--;
		}
	}
	printf("%d\n",ans);
}
