#include <ctime>
#include<math.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  unsigned t0, t1;
  vector<vector<int>> a ;
  srand(time(NULL));
  t0 = clock();
  for(int i=0;i<100;i++){
    vector<int> aux;
    for(int j=0;j<1000;j++){
      aux.push_back((rand()%999)+1);
    }
    a.push_back(aux);
  }
  vector<int> aux;
    for(int j=0;j<1000;j++){
      aux.push_back((rand()%999)+1);
    }
  int dist =0;
  
  for(int i=0;i<100;i++){
    for(int j=0;j<1000;j++){
      dist+=(a[i][j]-aux[j])*(a[i][j]-aux[j]);
    }
  }
  dist=sqrt(dist);
  t1 = clock();

  double time = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 1: " << time << endl;

  t0 = clock();
  for(int i=0;i<100;i++){
    vector<int> aux;
    for(int j=0;j<10000;j++){
      aux.push_back((rand()%999)+1);
    }
    a.push_back(aux);
  }
  vector<int> aux_2;
    for(int j=0;j<10000;j++){
      aux_2.push_back((rand()%999)+1);
    }
  int dist_2 =0;
  
  for(int i=0;i<100;i++){
    for(int j=0;j<10000;j++){
      dist_2+=(a[i][j]-aux_2[j])*(a[i][j]-aux_2[j]);
    }
  }
  dist_2=sqrt(dist);
  t1 = clock();

  double time_2 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 2: " << time_2 << endl;

  t0 = clock();
  for(int i=0;i<100;i++){
    vector<int> aux;
    for(int j=0;j<50000;j++){
      aux.push_back((rand()%999)+1);
    }
    a.push_back(aux);
  }
  vector<int> aux_3;
    for(int j=0;j<50000;j++){
      aux_3.push_back((rand()%999)+1);
    }
  int dist_3 =0;
  
  for(int i=0;i<100;i++){
    for(int j=0;j<50000;j++){
      dist_3+=(a[i][j]-aux_3[j])*(a[i][j]-aux_3[j]);
    }
  }
  dist_3=sqrt(dist);
  t1 = clock();

  double time_3 = (double(t1 - t0) / CLOCKS_PER_SEC);
  cout << "Execution Time 3: " << time_3 << endl;

}
