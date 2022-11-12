#include "dbscna.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;
/*
struct Point {
  double x{0}, y{0}, z{0};
};
*/

double square(double value) { return value * value; }

double squared_l2_distance(Point first, Point second) {
  return square(first.x - second.x) + square(first.y - second.y) +
         square(first.z - second.z);
}

std::vector<Point> k_means(const std::vector<Point> &data, size_t k,
                           size_t number_of_iterations) {
  static std::random_device seed;
  static std::mt19937 random_number_generator(seed());
  std::uniform_int_distribution<size_t> indices(0, data.size() - 1);

  // Pick centroids as random points from the dataset.
  std::vector<Point> means(k);
  for (auto &cluster : means) {
    cluster = data[indices(random_number_generator)];
  }

  std::vector<size_t> assignments(data.size());
  for (size_t iteration = 0; iteration < number_of_iterations; ++iteration) {
    // Find assignments.
    for (size_t point = 0; point < data.size(); ++point) {
      double best_distance = std::numeric_limits<double>::max();
      size_t best_cluster = 0;
      for (size_t cluster = 0; cluster < k; ++cluster) {
        const double distance =
            squared_l2_distance(data[point], means[cluster]);
        if (distance < best_distance) {
          best_distance = distance;
          best_cluster = cluster;
        }
      }
      assignments[point] = best_cluster;
    }

    // Sum up and count points for each cluster.
    std::vector<Point> new_means(k);
    std::vector<size_t> counts(k, 0);
    for (size_t point = 0; point < data.size(); ++point) {
      const auto cluster = assignments[point];
      new_means[cluster].x += data[point].x;
      new_means[cluster].y += data[point].y;
      new_means[cluster].z += data[point].z;
      counts[cluster] += 1;
    }

    // Divide sums by counts to get new centroids.
    for (size_t cluster = 0; cluster < k; ++cluster) {
      // Turn 0/0 into 0/1 to avoid zero division.
      const auto count = std::max<size_t>(1, counts[cluster]);
      means[cluster].x = new_means[cluster].x / count;
      means[cluster].y = new_means[cluster].y / count;
      means[cluster].z = new_means[cluster].z / count;
    }
  }

  return means;
}

void printResults(vector<Point>& points, int num_points)
{
    int i = 0;
    printf("Number of points: %u\n"
        " x     y     z     cluster_id\n"
        "-----------------------------\n"
        , num_points);
    while (i < num_points)
    {
          printf("%5.2lf %5.2lf %5.2lf: %d\n",
                 points[i].x,
                 points[i].y, points[i].z,
                 points[i].clusterID);
          ++i;
    }
}

int main() {
  std::vector<Point> a;
  srand(time(NULL));
  for (int i = 0; i < 10000; i++) {
    Point aux;
    aux.x = float(rand() % 1000)/1000;
    aux.y =float(rand() % 1000)/1000;
    aux.z = float(rand() % 1000)/1000;
    aux.clusterID =-1;
    a.push_back(aux);
  }
  vector<Point> b = k_means(a, 6, 5);

  for (int i = 0; i < b.size(); i++) {
    std::cout << b[i].x << " " << b[i].y << " " << b[i].z << endl;
  }
  cout << endl;
  DBSCAN scn(4, 0.001, a);
  scn.run();
  //printResults(scn.m_points, scn.getTotalPointSize());   
  ofstream cluster;
  int id = 1;

  cluster.open("clusters.txt");
  if (cluster.is_open()) {
    for (int j = 0; j < 6; j++) {
      for (int i = 0; i < 10000; i++) {
        if (scn.m_points[i].clusterID == id) {
          cluster << scn.m_points[i].x << " " << scn.m_points[i].y << " " << scn.m_points[i].z
                  << " cluster ID: " << scn.m_points[i].clusterID << endl;
        }
      }
      id += 1;
    }
  }
  cluster.close();
}