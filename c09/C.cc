#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); ++i)
#define out(x) cerr<<#x"="<<x<<endl
char str[31234];
struct Node {
    char comb;
    Node *sibling, *child;
    Node():comb(0),sibling(0),child(0){}
};
Node *root;
const char *s;
Node *build(){
    Node *p;
    switch(*s){
        case 'B':
        case 'C':
        case 'K':
        case 'I':
            p = new Node;
            p->comb = *(s++);
            p->sibling = build();
            return p;
        case '(':
            p = new Node;
            p->comb = *(s++);
            p->child = build();
            assert(*s==')');
            ++s;
            p->sibling = build();
            return p;
        case ')':
            return NULL;
        default:
            assert(*s=='\0');
            return NULL;
    }
}
void print(Node *p){
    if(p->comb != '(')putchar(p->comb);
    else {
        assert(p->child);
        putchar('(');
        print(p->child);
        putchar(')');
    }
    if(p->sibling)print(p->sibling);
}
int ans;
void dfs(Node *p){
    if(p==NULL)return;
    while(1){
        bool fail = 0;
        switch(p->comb){
            case '(': {
                assert(p->child);
                Node *tail = p->child;
                for(; tail->sibling; tail=tail->sibling);
                tail->sibling = p->sibling;
                Node *tmp = p;
                p = p->child;
                delete tmp;
                break;
            }
            case 'B': {
                Node *x, *y, *z;
                if((x=p->sibling) && (y=x->sibling) && (z=y->sibling)){
                    ++ans;
                    Node *tail = z->sibling;
                    delete p;
                    p = x;
                    Node *pack = new Node;
                    pack->comb = '(';
                    pack->child = y;
                    pack->sibling = tail;
                    x->sibling = pack;
                    y->sibling = z;
                    z->sibling = NULL;
                } else fail = 1;
                break;
            }
            case 'C': {
                Node *x, *y, *z;
                if((x=p->sibling) && (y=x->sibling) && (z=y->sibling)){
                    ++ans;
                    Node *tail = z->sibling;
                    delete p;
                    p = x;
                    x->sibling = z;
                    z->sibling = y;
                    y->sibling = tail;
                } else fail = 1;
                break;
            }
            case 'K': {
                Node *x, *y;
                if((x=p->sibling) && (y=x->sibling)){
                    ++ans;
                    Node *tail = y->sibling;
                    delete p;
                    delete y;
                    p = x;
                    x->sibling = tail;
                } else fail = 1;
                break;
            }
            case 'I': {
                Node *x;
                if(x=p->sibling){
                    ++ans;
                    Node *tail = x->sibling;
                    delete p;
                    p = x;
                } else fail = 1;
                break;
            }
            default: assert(0);
        }
        if (fail) {
            for (Node *u = p->sibling; u; u=u->sibling)
                if (u->comb == '(') dfs(u->child);
            break;
        }
    }
}
int main(){
    freopen("combinator.in", "r", stdin);
    freopen("combinator.out", "w", stdout);
    gets(str);
    s = str;
    root = build();
    //print(root);
    ans=0;
    dfs(root);
    printf("%d\n", ans);
}
