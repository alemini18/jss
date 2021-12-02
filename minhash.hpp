#include <bits/stdc++.h>

const int K=70; //Number of functions required by a good estimator (epsilon=0.3, delta=1e-6)
const int MAXU=1e6; //Max possible number in the universe considered
const int M=1e9+7; //We need M>MAXU and M must be prime to guarantee collision-free propriety to hash functions

//This class stores k hash functions for sketches
class Hash{
private:
  int a[K];
  int b[K];

public:
  Hash(){
    std::random_device rd_a;
    std::mt19937 gen_a(rd_a());
    std::uniform_int_distribution<int> distr_a(1,M-1); //coefficients must be uniformly distributed

    std::random_device rd_b;
    std::mt19937 gen_b(rd_b());
    std::uniform_int_distribution<int> distr_b(0,M-1); //coefficients must be uniformly distributed

    for(int i=0;i<K;i++)a[i]=distr_a(gen_a); //Generate a_i coefficients for hash functions
    for(int i=0;i<K;i++)b[i]=distr_b(gen_b); //Generate b_i coefficients for hash functions
  }
  int hash(int i, int x){  //hash functions are simply h_i(x)=a_i*x+b_i mod M
    return ((long long)(x+1)*a[i]+b[i])%M; //x+1 allows to have an hash function with domain [1,MAXU]
  }
};

//Data Structure that store sketch for min hash (it can also contain the set itself)
//elements are integers for simplicity
class Set{

private:
  int sz;
  int sketch[K]; //It's safer keep sketch private to avoid user changes
  Hash *h;

public:
  Set(Hash *h, std::set<int> a){
    for(int x:a)assert(x>=0&&x<MAXU);
    this->h=h;  //save Hash ptr for further operations
    sz=a.size();
    for(int i=0;i<K;i++){  //Calculate MinHash for every of the k hash functions
      int min_h=M-1;
      for(int x:a)min_h=std::min(min_h, (*h).hash(i,x));

      sketch[i]=min_h;
    }
  }
  Set(Hash *h){  //creates an empty set
    this->h=h;  //save Hash ptr for further operations
    sz=0;
    for(int i=0;i<K;i++)sketch[i]=M-1;
  }
  void insert(int x){
    assert(x>=0&&x<MAXU);
    sz++;
    for(int i=0;i<K;i++)sketch[i]=std::min(sketch[i],(*h).hash(i,x));
  }
  friend Set unite(Set a, Set b);  //We need to access Set sketches
  friend int compare(Set a, Set b);  //We need to access Set sketches

  bool operator==(const Set a)const{
    if(a.sz!=sz)return false;  //increases accuracy
    return compare(*this, a)==K;
  }
  int size(){return sz;}
  Hash* hash_gen(){return h;}
};

Set unite(Set a, Set b){ //generates Set S=AuB
  assert(a.hash_gen()==b.hash_gen());
  Set result(a.hash_gen());
  for(int i=0;i<K;i++){
    result.sketch[i]=std::min(a.sketch[i],b.sketch[i]);  //min function has the associative propriety
  }
  result.sz=a.sz+b.sz;
  return result;
}

int compare(Set a, Set b){ //Jaccard similarity calculation (this value is multiplied by K to avoid floating-point problems)
  assert(a.hash_gen()==b.hash_gen());
  int J=0;
  for(int i=0;i<K;i++)J+=(a.sketch[i]==b.sketch[i]);
  return J;
}
