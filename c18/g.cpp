#include<bits/stdc++.h>
using namespace std;

int d[10][1000000];
int h[10];
int a[10];
int w[10][10];

int main() {
	for (int n=1;n<8;n++) {
		w[n][0]=1;
		for (int i=1;i<n;i++) w[n][i]=w[n][i-1]*n;
		int st=0;
		for (int i=0;i<n;i++) st+=i*w[n][i];
		queue<int> Q;
		Q.push(st);
		d[n][st]=1;
		while (!Q.empty()) {
			int x=Q.front();
			Q.pop();
		//	if (n==2) printf("n=%d x=%d d[n][x]=%d\n",n,x,d[n][x]);
			for (int i=0;i<n;i++) h[i]=100;
			int t=x;
			for (int i=0;i<n;i++) {
				a[i]=x%n;
				h[a[i]]=min(h[a[i]],i);
				x/=n;
			}
			x=t;
			for (int i=0;i<n;i++)
				for (int j=-1;j<=1;j++) if (j!=0 && a[i]+j>=0 && a[i]+j<n && h[a[i]+j]>i && h[a[i]]==i) {
					int y=x+j*w[n][i];
					if (d[n][y]==0) {
						d[n][y]=d[n][x]+1;
						Q.push(y);
					}
				}
		}
	}
	int tt;
	scanf("%d",&tt);
	while (tt--) {
		int n;
		scanf("%d",&n);
		vector<int> v;
		for (int i=0;i<n;i++) {
			scanf("%d",a+i);
			v.push_back(a[i]);
		}
		sort(v.begin(),v.end());
		int st=0;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++) if (v[i]==a[j]) {
				st+=j*w[n][i];
				break;
			}
		printf("%d\n",d[n][st]-1);
	}
}
