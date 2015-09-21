#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
	#define out(x)
#else
	#define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
char buf[11234];
int M;
struct Node {
	Node *pre, *nxt;
	char ch;
	Node():pre(NULL),nxt(NULL),ch(0){}
} *bg;
Node *now, *cp_pos;
bool cp, subs;
int pos, cp_int_pos, tot;
vector<char> ctmp;
void init(){
	cp=subs=pos=tot=0;
	now=bg;
	cp_pos=NULL;
	cp_int_pos=-1;
	ctmp.clear();
}
//del now->nxt
void del(Node *now){
	Node *tmp=now->nxt;
	assert(tmp);
	now->nxt=now->nxt->nxt;
	if(now->nxt)now->nxt->pre=now;
	delete tmp;
	tot--;
}
//insert after now
void insert(Node *now, char op){
	Node *tmp=now->nxt;
	now->nxt=new Node;
	now->nxt->pre=now;
	now->nxt->ch=op;
	now->nxt->nxt=tmp;
	if(tmp)tmp->pre=now->nxt;
	tot++;
}
void print(bool debug=1){
#ifdef ONLINE_JUDGE
	if(debug)return;
#endif
	int cnt=0;
	for(Node *p=bg->nxt; p; p=p->nxt)
		putchar(p->ch),++cnt;
	if(cnt==0)printf("%s", "NOTHING");
	putchar('\n');
}
void oper(char op){
	if(cp){
		if(op=='C'){
			ctmp.clear();
			Node *L=now, *R=cp_pos;
			if(cp_int_pos<pos)swap(L,R);
			if(L!=R){
				for(Node *p=L->nxt;;p=p->nxt){
					ctmp.pb(p->ch);
					if(p==R)break;
				}
				out("pastebin:");
				/*
				for(auto cc: ctmp)putchar(cc);
				putchar('\n');
				*/
			}
			cp^=1;
			cp_pos=NULL;
			cp_int_pos=-1;
			return;
		} else if(op=='D'){
			Node *L=now, *R=cp_pos;
			int len=cp_int_pos-pos;
			if(cp_int_pos<pos)swap(L,R),len=pos-cp_int_pos;
			out(len);
			out(L->ch); out(R->ch);
			while(len--){
				del(L);
				print();
			}
			cp^=1;
			cp_pos=NULL;
			cp_int_pos=-1;
			return;
		} else if(op!='L' && op!='R')cp=0;
	}
	if(op>='a' && op<='z'){
		if(subs && pos>=M)return; //exceed M
		if(!subs && tot>=M)return;
		out(subs);
		if(subs && now->nxt){
			now=now->nxt;
			now->ch=op;
			pos++;
		} else {
			insert(now, op);
			now=now->nxt;
			pos++;
		}
	} else if(op=='L'){
		if(now!=bg){
			now=now->pre;
			pos--;
		}
	} else if(op=='R'){
		if(now->nxt){
			now=now->nxt;
			pos++;
		}
	} else if(op=='S'){
		subs^=1;
	} else if(op=='D'){
		if(now->nxt){
			del(now);
		}
	} else if(op=='B'){
		if(now!=bg){
			now=now->pre;
			del(now);
			pos--;
		}
	} else if(op=='C'){
		cp^=1;
		cp_pos=now;
		cp_int_pos=pos;
	} else if(op=='V'){
		if(!subs && tot+ctmp.size()>M)return;
		if(subs && pos+ctmp.size()>M)return;
		for(char cc: ctmp){
			if(subs && now->nxt){
				now=now->nxt;
				now->ch=cc;
				pos++;
			} else {
				insert(now, cc);
				now=now->nxt;
				pos++;
			}
		}
	}
}
void release(){
	while(bg->nxt)del(bg);
	delete bg;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %s", &M, buf);
		bg = new Node;
		init();
		for(char *p=buf;*p;++p){
			oper(*p);
			out("======");
			out(pos);
			out(now->ch);
			print();
		}
		print(0);
		release();
	}
}
