#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
struct point {
	double x,y;
};
point a[110];

int change(double x) {
	return int(x)+1;
}

double dis(point a,point b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int main() {
	int tt,n,m;
	scanf("%d",&tt);
	while (tt--) {
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
		int ans=-1;
		for (int i=0;i<n;i++) {
			vector<int> d;
			set<int> S;
			for (int j=0;j<n;j++) {
				d.push_back(change(dis(a[i],a[j])+eps));
				int t=(int)dis(a[i],a[j]);
				for (int k=-1;k<=1;k++) if (fabs(t+k-dis(a[i],a[j]))<eps) {
					S.insert(t+k);
			//		printf("t+k=%d\n",t+k);
				}
			}
			sort(d.begin(),d.end());
			//for (int j=0;j<n;j++) printf("%d ",d[j]);
			//puts(" ");
			int j=m-1;
			if (m>n) continue;
			if ((j==n-1 || d[j]!=d[j+1]) && S.find(d[j])==S.end()) {
				if (ans==-1 || d[j]<ans) {
					ans=d[j];
				}
			} 
		}
		printf("%d\n",ans);
	}
}
