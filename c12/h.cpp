#include<bits/stdc++.h>
using namespace std;

vector<int> f[11000];
int now[11000];
int g[11000];
char s[11000];

int main() {
	int n,cnt=0;
	scanf("%d",&n);
	n*=2;
	scanf("%s",s);
	f[0].resize(26);
	map<vector<int>,int> M;
	M[f[0]]=0;
	for (int i=1;i<=n;i++) {
		f[i]=f[i-1];
		if (s[i-1]>='a' && s[i-1]<='z') f[i][s[i-1]-'a']--;
		else f[i][s[i-1]-'A']++;
		if (M.find(f[i])!=M.end()) {
			g[i]=M[f[i]]+1;
			g[M[f[i]]+1]=i;
			M.erase(f[i]);
			cnt++;
		}
		else {
			M[f[i]]=i;
		}
	}
	if (cnt*2!=n) {
		puts("Impossible");
		return 0;
	}
	for (int i=1;i<=n;i++) now[i]=now[i-1]+((s[i-1]>='a' && s[i-1]<='z')?1:0);
	int u=0;
	for (int i=1;i<=n;i++) if (s[i-1]>='A' && s[i-1]<='Z') {
		u++;
//		printf("g[i]=%d now[i]=%d\n",g[i]);
		printf("%d%c",now[g[i]],u*2==n?'\n':' ');
	}
}
