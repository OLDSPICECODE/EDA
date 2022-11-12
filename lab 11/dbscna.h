#include <cmath>
#include <iostream>
#include <vector>

#define UNCLASSIFIED -1
#define CORE_POINT 1
#define BORDER_POINT 2
#define NOISE -2
#define SUCCESS 0
#define FAILURE -3

using namespace std;

typedef struct Point_ {
  float x, y, z; // X, Y, Z position
  int clusterID; // clustered ID
} Point;

class DBSCAN {
public:
  vector<Point> m_points;
  DBSCAN(unsigned int minPts, float eps, vector<Point> &points) {
    m_minPoints = minPts;
    m_epsilon = eps;
    m_points = points;
    m_pointSize = points.size();
  }
  ~DBSCAN() {}

  int run();
  vector<int> calculateCluster(Point point);
  int expandCluster(Point point, int clusterID);
  inline double calculateDistance(const Point &pointCore,
                                  const Point &pointTarget);

  int getTotalPointSize() { return m_pointSize; }
  int getMinimumClusterSize() { return m_minPoints; }
  int getEpsilonSize() { return m_epsilon; }

private:
  unsigned int m_pointSize;
  unsigned int m_minPoints;
  float m_epsilon;
};
int DBSCAN::run() {
  int clusterID = 1;
  vector<Point>::iterator iter;
  for (iter = m_points.begin(); iter != m_points.end(); ++iter) {
    if (iter->clusterID == UNCLASSIFIED) {
      if (expandCluster(*iter, clusterID) != FAILURE) {
        clusterID += 1;
      }
    }
  }

  return 0;
}

int DBSCAN::expandCluster(Point point, int clusterID) {
  vector<int> clusterSeeds = calculateCluster(point);

  if (clusterSeeds.size() < m_minPoints) {

    point.clusterID = NOISE;
    return FAILURE;
  } else {
    int index = 0, indexCorePoint = 0;
    vector<int>::iterator iterSeeds;
    for (iterSeeds = clusterSeeds.begin(); iterSeeds != clusterSeeds.end();
         ++iterSeeds) {
      m_points.at(*iterSeeds).clusterID = clusterID;
      if (m_points.at(*iterSeeds).x == point.x &&
          m_points.at(*iterSeeds).y == point.y &&
          m_points.at(*iterSeeds).z == point.z) {
        indexCorePoint = index;
      }
      ++index;
    }
    clusterSeeds.erase(clusterSeeds.begin() + indexCorePoint);

    for (vector<int>::size_type i = 0, n = clusterSeeds.size(); i < n; ++i) {
      vector<int> clusterNeighors =
          calculateCluster(m_points.at(clusterSeeds[i]));

      if (clusterNeighors.size() >= m_minPoints) {
        vector<int>::iterator iterNeighors;
        for (iterNeighors = clusterNeighors.begin();
             iterNeighors != clusterNeighors.end(); ++iterNeighors) {
          if (m_points.at(*iterNeighors).clusterID == UNCLASSIFIED ||
              m_points.at(*iterNeighors).clusterID == NOISE) {
            if (m_points.at(*iterNeighors).clusterID == UNCLASSIFIED) {
              clusterSeeds.push_back(*iterNeighors);
              n = clusterSeeds.size();
            }
            m_points.at(*iterNeighors).clusterID = clusterID;
          }
        }
      }
    }

    return SUCCESS;
  }
}

vector<int> DBSCAN::calculateCluster(Point point) {
  int index = 0;
  vector<Point>::iterator iter;
  vector<int> clusterIndex;
  for (iter = m_points.begin(); iter != m_points.end(); ++iter) {
    if (calculateDistance(point, *iter) <= m_epsilon) {
      clusterIndex.push_back(index);
    }
    index++;
  }
  return clusterIndex;
}

inline double DBSCAN::calculateDistance(const Point &pointCore,
                                        const Point &pointTarget) {
  return pow(pointCore.x - pointTarget.x, 2) +
         pow(pointCore.y - pointTarget.y, 2) +
         pow(pointCore.z - pointTarget.z, 2);
}
