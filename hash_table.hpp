#include <bits/stdc++.h>
#include "minhash.hpp"

const long long MOD=1610612741;
const long long A=85467845;
const long long B=5432789;
const double SCALE=2;

class Vector{
private:
    Set_t *a;
    int sz, true_sz;
public:
    Vector(){
      sz=0;
      true_sz=1;
      a=new Set_t[1];
    }
    ~Vector(){
      delete [] a;
    }
    Set_t operator[](int pos){
      assert(pos<sz);
      return a[pos];
    }
    int size(){return sz;}
    void push(Set_t x){
      if(sz==true_sz){
        Set_t* tmp=a;
        true_sz=ceil(true_sz*SCALE);
        a=new Set_t[true_sz];
        for(int i=0;i<sz;i++)a[i]=tmp[i];
        delete [] tmp;
      }
      a[sz++]=x;
    }
    void remove(int pos){
      assert(pos<sz);
      Set_t* tmp=a;
      a=new Set_t[true_sz];
      int offset=0;
      for(int i=0;i<sz;i++){
        if(i!=pos)a[i-offset]=tmp[i];
        else offset=1;
      }
      sz--;
      delete [] tmp;
    }
    Set_t* begin(){
      return a;
    }
    Set_t* end(){
      return (a+sz);
    }
};
class HashTable{
private:
    Vector *v;
    int sz,true_sz;
    int hash(Set_t x){
      return (int)((((long long)(*x).toint()*A+B)%MOD))%true_sz;
    }
    int search(Set_t x){
      int h=hash(x);
      for(int i=0;i<v[h].size();i++)if(v[h][i]==x)return i;
      return -1;
    }
  public:
    HashTable(){
      sz=0;
      true_sz=1;
      v=new Vector[1];
    }
    ~HashTable(){
      delete [] v;
    }
    int size(){return sz;}
    bool count(Set_t x){return search(x)!=-1;}

    void insert(Set_t x){
      if(count(x))return;
      if(sz==true_sz){
        Vector* tmp=v;
        int new_true_sz=ceil(true_sz*SCALE);
        v=new Vector[new_true_sz];
        for(int i=0;i<true_sz;i++)
        for(int j=0;j<tmp[i].size();j++)
          v[hash(tmp[i][j])].push(tmp[i][j]);
        delete [] tmp;
        true_sz=new_true_sz;
      }
      v[hash(x)].push(x);
      sz++;
    }
    void erase(Set_t x){
      int ind=search(x);
      if(ind==-1)return;
      v[hash(x)].remove(ind);
      sz--;
    }
    Vector similars(Set_t x){
      return v[hash(x)];
    }
};
