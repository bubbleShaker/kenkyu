#include <iostream>
#include <bitset>

int powi(int a,int b){
  int ret=1;
  for(int i=0;i<b;i++){
    ret*=a;
  }
  return ret;
};

int calc_idx(int x,int p){
  std::bitset<7> bitset(x);
  int ret=0;
  const int BIT=7;
  for(int i=BIT-p;i<BIT;i++){
    if(bitset[i]){
      ret+=powi(2,i-(BIT-p));
    }
  }
  return ret;
}

int main(){
  int idx=calc_idx(83,3);
  std::cout<<idx<<'\n';
  return 0;
}