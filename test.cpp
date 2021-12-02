
#include <bits/stdc++.h>
#include "minhash.hpp"
using namespace std;

int main(){
  srand(time(0));
  Hash h;
  Set a(&h);
  Set b(&h);
  set<int> aa,bb;
  for(int i=0;i<100;i++){
    int p=rand()%50;
    aa.insert(p);
    a.insert(p);
  }
  for(int i=0;i<100;i++){
    int p=rand()%50;
    bb.insert(p);
    b.insert(p);
  }
  cout<<(double)compare(a,b)/(double)K<<endl;
  int cnt=0;
  for(int x:aa)cnt+=bb.count(x);
  cout<<cnt/(double)aa.size()<<endl;

}
