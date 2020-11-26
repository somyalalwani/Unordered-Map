#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template<class S,class T> 
class unordered_mapp{
    public:
    struct ll{
        S key;
        T value;
        ll * next;
    };  
    ll* arr[10000];
    unordered_mapp(){
    for(int i=0;i<10000;i++) arr[i]=NULL;   
    }
void insert(S key,T value){
    int h=hash(key);
    if(arr[h]==NULL){
        ll* p=new ll;
        p->key=key;
        p->value=value;
        p->next=NULL;
        arr[h]=p;
    }
    else{
        ll* q=new ll;
        q=arr[h];
        while(q->next!=NULL) {
            if(q->key==key) return;         
            q=q->next;
        }       
        ll* p=new ll;
        p->key=key;
        p->value=value;
        p->next=NULL;
        q->next=p;              
    }
}
void erase(S key){
    int h=hash(key);
    if(arr[h]==NULL) return;
    else if(arr[h]->key==key){
        ll* p=arr[h]->next;
        arr[h]->next=NULL;
        arr[h]=p;   
    }
    else{
        ll* p=new ll;
        p=arr[h];
        while(p->next!=NULL and p->next->key!=key) p=p->next;
        if(p->next==NULL) return;
        ll* q=p->next;      
        p->next=q->next;
        q->next=NULL;
        free(p);
    }
}

int hash(S key){
    long long int h=0;
    ostringstream os;
    os << key;  
    string key1=os.str();       
    int m=1;
    for(int i=0;i<int(key1.size());i++){
        h+=int(key1[i])*m;
        h=h%10000;
        m*=17;  
    }
    return h;   
}
bool find(S key){
    int h=hash(key);
    if(arr[h]==NULL) return false;
    ll* p=arr[h];
    while(p!=NULL){
        if(p->key==key) return true;
        p=p->next;  
    }
    return false;
}
T operator[](S key){
    int h=hash(key);
    ll* p=arr[h];
    while(p!=NULL){
        if(p->key==key) return p->value;
        p=p->next;  
    }
    }
};

int main()
{

unordered_mapp<string,int> m;
m.insert("1",3);
m.insert("2",4);

cout<<m["1"]<<endl;
cout<<m["2"]<<endl;
cout<<m["3"]<<endl;

m.erase("3");
m.erase("2");

cout<<m["2"]<<endl;

cout<<m.find("1")<<"(1=true)/(2=false)"<<endl;
cout<<m.find("2")<<"(1=true)/(2=false)"<<endl;

return 0;
}