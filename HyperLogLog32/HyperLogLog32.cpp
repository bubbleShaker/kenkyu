#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <set>
#include <limits>
#include <iomanip>
#include "MurmurHash3.h"

int n;
std::vector<unsigned int> S;

void input();
double HyperLogLog();
int true_count(std::vector<unsigned int> S);
unsigned int h(unsigned int x);
unsigned int powi(unsigned int a,int b);
unsigned int calc_idx(unsigned int x,int p);
unsigned int calc_w(unsigned int x,int p);
int rho(unsigned int w);
double LINEARCOUNTING(int m,int V);

int main(){
  double E=HyperLogLog();
  std::cout<<std::fixed<<std::setprecision(2);
  std::cout<<"推定カーディナリティ数:";
  std::cout<<E<<'\n';
  std::cout<<"実際の値:";
  std::cout<<true_count(S)<<'\n';
  return 0;
}

void input(){
  std::cin>>n;
  S.resize(n);
  for(int i=0;i<n;i++){ // ストリームの要素数をn,配列Sに格納するとしている
    std::cin>>S[i];
  }
  return;
}

double HyperLogLog(){
  //Require:
  int p=14;
  double m=std::pow(2,p);
  //Phase0: Initialization.
  double a_16=0.673;
  double a_32=0.697;
  double a_64=0.709;
  double a_m=0.7213/(1+1.079/m); // for m>=128
  std::vector<int> M(m); //Initialize m registers M[0] to M[m-1] to 0
  //Phase1: Aggregation
  input(); //データの受け取り
  unsigned int seed=12345;
  for(unsigned int v:S){ // for all v ∊ S do
    unsigned int x;
    MurmurHash3_x86_32(&v,4,seed,&x);
    unsigned int idx=calc_idx(x,p);
    unsigned int w=calc_w(x,p);
    M[idx]=std::max(M[idx],rho(w));
  }
  //Phase2: Result computation.
  double ret=0;
  for(int i=0;i<m;i++){
    ret+=1/std::pow(2,M[i]);
  }
  ret=1/ret;
  double E;
  if(m>=128){
    E=a_m*m*m*ret;
  }else{
    E=a_16*m*m*ret;
  }
  // return E;//補正なしで返してみる
  
  if(E<=(5*m)/(double)2){
    int V=0; // Let V be the number of register equal to 0.
    for(int i=0;i<m;i++){
      if(M[i]==0){
        V++;
      }
    }
    if(V!=0){
      E=LINEARCOUNTING(m,V);
    }else{
      E=E;
    }
  }else if(E<=std::pow(2,32)/30){
    E=E;
  }else{
    if(1-E/std::pow(2,32)>0){
      std::cout<<"test"<<'\n';
      E=-pow(2,32)*std::log2(1-E/std::pow(2,32));
    }else{
      E=-1;
    }
  }
  return E;
}

int true_count(std::vector<unsigned int> S){
  std::set<int> set;
  for(int v:S){
    set.insert(v);
  }
  return set.size();
}

unsigned int h(unsigned int x){
  // 固定シードとして使用する大きな素数
  const unsigned int seed=0x9e3779b9;
  // x にシードを掛け合わせる
  x^=seed;
  // xorshift アルゴリズム
  x^=x >> 17;
  x*=0xed5ad4bb;
  x^=x >> 11;
  x*=0xac4c1b51;
  x^=x >> 15;
  x*=0x31848bab;
  x^=x >> 14;
  return x;
}

unsigned int powi(unsigned int a,int b){
  unsigned int ret=1;
  for(int i=0;i<b;i++){
    ret*=a;
  }
  return ret;
};

unsigned int calc_idx(unsigned int x,int p){
  std::bitset<32> bitset(x);
  unsigned int ret=0;
  const int BIT=32;
  for(int i=BIT-p;i<BIT;i++){
    if(bitset[i]){
      ret+=powi(2,i-(BIT-p));
    }
  }
  return ret;
}

unsigned int calc_w(unsigned int x,int p){
  std::bitset<32> bitset(x);
  unsigned int ret=0;
  const int BIT=32;
  for(int i=0;i<BIT-p;i++){
    if(bitset[i]){
      ret+=powi(2,i);
    }
  }
  return ret;
}

int rho(unsigned int w){
  std::bitset<18> bitset(w);//p=14のため、wのビット長は18
  int ret=1;
  for(int i=17;i>=0;i--){
    if(bitset[i]){
      break;
    }else{
      ret++;
    }
  }
  return ret;
}

double LINEARCOUNTING(int m,int V){
  return m*log2(m/(double)V);
}