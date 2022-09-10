#include <ctime>
#include<math.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  unsigned t0, t1;
  vector<int> a = {(rand()%999)+1,(rand()%999)+1,(rand()%999)+1};
  srand(time(NULL));
  t0 = clock();
  for(int i=0;i<1000;i++){
    int dist=sqrt(((((rand()%999)+1)-a[0])*(((rand()%999)+1)-a[0]))+((((rand()%999)+1)-a[1])*(((rand()%999)+1)-a[1]))+((((rand()%999)+1)-a[2])*(((rand()%999)+1)-a[2])));
  }
  t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 1: " << time << endl;

  t0 = clock();
  for(int i=0;i<10000;i++){
    int dist=sqrt(((((rand()%999)+1)-a[0])*(((rand()%999)+1)-a[0]))+((((rand()%999)+1)-a[1])*(((rand()%999)+1)-a[1]))+((((rand()%999)+1)-a[2])*(((rand()%999)+1)-a[2])));
  }
  t1 = clock();

  double time_2 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 2: " << time_2 << endl;
  
  t0 = clock();
  for(int i=0;i<50000;i++){
    int dist=sqrt(((((rand()%999)+1)-a[0])*(((rand()%999)+1)-a[0]))+((((rand()%999)+1)-a[1])*(((rand()%999)+1)-a[1]))+((((rand()%999)+1)-a[2])*(((rand()%999)+1)-a[2])));
  }
  t1 = clock();

  double time_3 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 3: " << time_3 << endl;

}
