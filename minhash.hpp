#include <bits/stdc++.h>

const int K=322; //number of functions required by a good estimator (epsilon=0.8, delta=1e-9)
const int MAXU=1e6; //max possible number in the universe considered
const int M=1e9; //we need M>MAXU

//This class stores k hash functions and generates sketches for sets
class Sketch{
private:

  int a[K];
  int b[K];

public:
  Sketch(){
    std::random_device rd_a;
    std::mt19937 gen_a(rd_a());
    std::uniform_int_distribution<int> distr_a(1,M-1);

    std::random_device rd_b;
    std::mt19937 gen_b(rd_b());
    std::uniform_int_distribution<int> distr_b(0,M-1);
    for(int i=0;i<K;i++)a[i]=distr_a(gen_a); //Generation of a coefficients for hash functions
    for(int i=0;i<K;i++)b[i]=distr_b(gen_b); //Generation of b coefficients for hash functions
  }
  int hash(int i, int x){  //hash functions are simply h_i(x)=a_i*x+b_i mod M
    return ((long long)x*a[i]+b[i])%M;
  }
};

//Data Structure that store sketch for min hash and the set itself
//elements are integers for simplicity
class Set{

private:
  int sz;
  int sketch[K];
  Sketch *sk;

public:
  Set(Sketch *skk, std::set<int> a){
    sk=skk;  //save Sketch ptr for further operations
    sz=a.size();
    for(int i=0;i<K;i++){  //Calculate MinHash for every of the k hash functions
      int min_h=M-1;
      for(int x:a)min_h=std::min(min_h, (*sk).hash(i,x));
      sketch[i]=min_h;
    }
  }
  Set(Sketch *skk){
    sk=skk;  //save Sketch ptr for further insertions
    sz=0;
    for(int i=0;i<K;i++)sketch[i]=M-1;
  }
  void insert(int x){
    sz++;
    for(int i=0;i<K;i++)sketch[i]=std::min(sketch[i],(*sk).hash(i,x));
  }
  friend Set unite(Set a, Set b);
  friend double compare(Set a, Set b);

  bool operator==(const  Set a)const{
    if(a.sz!=sz)return false;
    return compare(*this, a)==1.0;
  }
  int size(){return sz;}
  Sketch* sketch_gen(){return sk;}
};

Set unite(Set a, Set b){ //generates AuB
  assert(a.sketch_gen()==b.sketch_gen());
  Set result(a.sketch_gen());
  for(int i=0;i<K;i++){
    result.sketch[i]=std::min(a.sketch[i],b.sketch[i]);
  }
  result.sz=a.sz+b.sz;
  return result;
}

double compare(Set a, Set b){ //Jaccard similarity generator
  double J=0;
  for(int i=0;i<K;i++)J+=(a.sketch[i]==b.sketch[i]);
  return J/K;
}
