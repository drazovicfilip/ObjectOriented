#include <array>
#include <vector>
#include <iostream>

int sum(std::vector<int> a) {
  int result=0;
  for(int i=0;i<10;i++){
    result+=a.at(i);
  }
  return result;
}

int main()
{  std::vector<int> a{1,2,3,4};
   std::cout << sum(a) << std::endl;
}
