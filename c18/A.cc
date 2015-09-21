#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
struct point {
	double x,y;
};
point a[110];

double dis(point a,point b) {
	return hypot(a.x-b.x, a.y-b.y);
}

int main() {
	int tt,n,m;
	scanf("%d",&tt);
	while (tt--) {
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
		if(n<m){
			puts("-1");
			continue;
		}
		int ans=-1;
		for (int i=0;i<n;i++) {
			vector<double> d;
			for (int j=0;j<n;j++) d.push_back(dis(a[i],a[j]));
			sort(d.begin(),d.end());
			int t=ceil(d[m-1]+eps);
			assert(d[m-1]<t-eps);
			if((m>=n || t+eps<d[m])){
				if(ans==-1 || t<ans)ans=t;
			}
		}
		printf("%d\n",ans);
	}
}
