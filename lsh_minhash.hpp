#include <bits/stdc++.h>
#include "hash_table.hpp"

using namespace std;

const int BB = 1200;
const int  RR = 10; //These parameters create a (0.5,0.6,0.69,0.12)-sensitive function
const int D = 5;

class LSH{

private:
  HashTable OR[BB];
  Hash *h[BB];
  int sz;
  vector<Set> sets[BB];

public:
  LSH(){
    sz=0;
    for(int i=0;i<B;i++)h[i]=new Hash(RR);
  }
  void push(vector<int> v, int id){
      for(int i=0;i<B;i++){
        sets[i].push_back(Set(h[i],v,id));
        OR[i].insert(&sets[i].back());
      }
  }

  set<int> query(vector<int> v){
    set<int> ans;
    for(int i=0;i<B;i++){
      Set a(h[i],v);
      Vector sim=OR[i].similars(&a);
      for(Set_t i:sim)if(compare(a,*i)>=D)ans.insert((*i).identity());
    }
    return ans;
  }
};
