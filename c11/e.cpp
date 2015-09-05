#include<bits/stdc++.h>
using namespace std;

struct sa {
	int s[3];
	int c;
};

sa a[110];
sa ans[51000];
map<vector<int>,int> M;
queue<vector<int> > Q;
int tot,n;

int change(char c) {
	if (c=='R') return 0;
	if (c=='S') return 1;
	return 2;
}

char rchange(int x) {
	if (x==0) return 'R';
	if (x==1) return 'S';
	return 'P';
}

int check(vector<int> v) {
	int k=(w+2)%3;
	for (int j=0;j<=n+1;j++) {
		vector<int> x;
		for (int i=0;i<y.size();i++) if (a[y[i]].c==w) x.push_back(a[y[i]].s[k]);
		sort(x.begin(),x.end());
		x.erase(unique(x.begin(),x.end()),x.end());
		if (x.size()!=y.size()) return 1;
		y=x;
	}
	return 0;
}

int main() {
	freopen("epic.in","r",stdin);
	freopen("epic.out","w",stdout);
	scanf("%d",&n);
	vector<int> v;
	for (int i=1;i<=n;i++) {
		char tmp[10];
		scanf("%s%d%d%d",tmp,&a[i].s[0],&a[i].s[2],&a[i].s[1]);
		a[i].c=change(tmp[0]);
		v.push_back(i);
	}
	M[v]=1;
	tot=1;
	Q.push(v);
	while (!Q.empty()) {
		vector<int> v=Q.front();
		Q.pop();
		int id=M[v];
	//	printf("v.size()=%d %d\n",v.size(),v[0]);
		if (v.size()==1) {
			ans[id].c=(a[v[0]].c+2)%3;
			vector<int> y;
			y.push_back(a[v[0]].s[ans[id].c]);
			if (M.find(y)==M.end()) {
				M[y]=++tot;
				Q.push(y);
			}
			for (int k=0;k<3;k++) {
				if (k!=a[v[0]].c) ans[id].s[k]=1;
				else ans[id].s[k]=M[y];
			}
			continue;
		}
		int flag=0;
		for (int k=0;k<3;k++) {
			vector<int> y[3];
			for (int i=0;i<v.size();i++) y[a[v[i]].c].push_back(a[v[i]].s[k]);
			int ok=1;
			for (int i=0;i<3;i++) {
				sort(y[i].begin(),y[i].end());
				y[i].erase(unique(y[i].begin(),y[i].end()),y[i].end());
				if (y[i].size()==v.size()) ok=0;
			}
			if (ok) {
				flag=1;
				ans[id].c=k;
				for (int i=0;i<3;i++) {
					if (y[i].empty()) {
						ans[id].s[i]=1;
						continue;
					}
					if (M.find(y[i])==M.end()) {
						M[y[i]]=++tot;
						Q.push(y[i]);
					}
					ans[id].s[i]=M[y[i]];					
				}
				break;
			}
		}
	//	printf("flag=%d\n",flag);
		if (!flag) {
			int k=(a[v[0]].c+2)%3;
			ans[id].c=k;
			vector<int> y;
			for (int i=0;i<v.size();i++) y.push_back(a[v[i]].s[k]);
			sort(y.begin(),y.end());
			y.erase(unique(y.begin(),y.end()),y.end());
			int u;
			if (check(v)) {
				if (M.find(y)==M.end()) {
					M[y]=++tot;
					Q.push(y);
				}
				u=M[y];
			}
			else u=id;
			for (int i=0;i<3;i++) {
				if (i!=a[v[0]].c) ans[id].s[i]=1;
				else ans[id].s[i]=u;
			}
		}
	}
	printf("%d\n",tot);
	for (int i=1;i<=tot;i++) printf("%c %d %d %d\n",rchange(ans[i].c),ans[i].s[0],ans[i].s[2],ans[i].s[1]);
}
