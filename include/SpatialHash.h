#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "Object.h"

enum hash_code {
  TOPLEFT,
  TOPRIGHT,
  BOTTOMLEFT,
  BOTTOMRIGHT
};

//Hash class using a vector of int vectors
//Cuts down collision check algorithm loops from O(n^2) to O(nlogn);
class SpatialHash {
  
 public:
  SpatialHash();
  ~SpatialHash();

          
  //Sets up the hash for hashing, fires on every game turn
  void setup(std::vector<Object*> objects);
        
  //Adds object into the hashtable
  void add(Object *object, int position);
  std::vector<int> hashCodes(Object *object);
  std::vector<int> getNearby(Object* subject);

  //Resets hash, hashing happens on every frame refresh
  void clear();
  
 private:

  int column;
  int row;
  int size;
  double cellsize;
  std::vector<std::vector<int> > bucket;
};

#endif
