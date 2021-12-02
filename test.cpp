
#include <bits/stdc++.h>
#include "minhash.hpp"
using namespace std;





int main(){

  Sketch sk;
  Set a(&sk);
  Set b(&sk);
  for(int i=0;i<100;i++)a.insert(i);
  for(int i=0;i<50;i++)b.insert(i);
  cout<<compare(a,b)<<endl;

}
