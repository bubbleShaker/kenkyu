#include <iostream>
#include <random>

// 32bit環境の場合
uint32_t get_rand() {
    // 乱数生成器（引数にシードを指定可能）
    static std::mt19937 mt32(0);

    // [0, (2^32)-1] の一様分布整数を生成
    return mt32();
}
//参考:https://rkd3.dev/post/random-range-cpp/

int main(){
  int n=100000000; //ストリームの要素数
  std::cout<<n<<'\n';
  for(int i=0;i<n;i++){
    std::cout<<get_rand()<<' ';
  }
  return 0;
}