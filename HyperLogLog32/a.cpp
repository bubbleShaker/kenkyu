#include <iostream>
#include <bitset>

int powi(int a,int b){
  int ret=1;
  for(int i=0;i<b;i++){
    ret*=a;
  }
  return ret;
};

unsigned int calc_idx(int p){
  std::bitset<10> bitset("1010111111");
  unsigned int ret=0;
  const int BIT=10;
  for(int i=BIT-p;i<BIT;i++){
    if(bitset[i]){
      ret+=powi(2,i-(BIT-p));
    }
  }
  return ret;
}

unsigned int calc_w(int p){
  std::bitset<10> bitset("1010111111");
  unsigned int ret=0;
  const int BIT=10;
  for(int i=0;i<BIT-p;i++){
    if(bitset[i]){
      ret+=powi(2,i);
    }
  }
  return ret;
}

int rho(){
  std::bitset<10> bitset("0000000000");
  int ret=1;
  for(int i=9;i>=0;i--){
    if(bitset[i]){
      break;
    }else{
      ret++;
    }
  }
  return ret;
}

int main(){
  std::cout<<calc_idx(5)<<'\n';
  std::cout<<calc_w(5)<<'\n';
  std::cout<<rho()<<'\n';
  return 0;
}