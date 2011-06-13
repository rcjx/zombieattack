#include "SpatialHash.h"

//Hash class using a vector of int vectors
//Cuts down collision check algorithm loops from O(n^2) to O(nlogn);
SpatialHash::SpatialHash() {

  cellsize = 100;
  column = SCREEN_WIDTH / cellsize; 
  row = SCREEN_HEIGHT / cellsize;

  size = column * row;

  for(int i = 0; i < size; i++)
    bucket.push_back(std::vector<Object*>()); 
}

SpatialHash::~SpatialHash() {
  clear();
}
        
//Sets up the hash for hashing, fires on every game turn
void SpatialHash::setup(std::vector<Object*> objects) {              
  
  for(unsigned int i = 0; i < objects.size(); i++)
    add(objects[i]); //Adds position of object
                
  // std::cout << "hashtable size " << column * row << " std::vector size: " << bucket.size() << std::endl;

  /*
   for(unsigned int i = 0; i < bucket.size(); i++) {

     std::cout << "bucket " << i << ": " << bucket[i].size() <<
       " objects ( ";            
     if(bucket[i].size() > 0) {
       for(unsigned int j = 0; j < bucket[i].size(); j++)
   std::cout << bucket[i][j] << " ";
     }
     if(bucket[i].size() > 1)
       std::cout << ") collision check(s) needed";
     else
       std::cout << ")";
     std::cout << std::endl;
   }   
   */
}
        
//Adds object into the hashtable
void SpatialHash::add(Object* object) {

  std::vector<int> hash_codes = hashCodes(object);
            
  //std::cout << object << ": " << topleft << " " << topright << " AND "
  //     << bottomleft << " " << bottomright << std::endl;       

  /*
  std::cout << hash_codes.size() << std::endl;
 for(unsigned int i = 0; i < hash_codes.size(); ++i)
	  std::cout << "    " << hash_codes[i] << std::endl;
	  */

  for(unsigned int i = 0; i < hash_codes.size(); ++i)
	  bucket[hash_codes[i]].push_back(object);
}

std::vector<int> SpatialHash::hashCodes(Object* object) {

  int _x = object->getSprite().GetPosition().x;
  int _y = object->getSprite().GetPosition().y;
  int _w = object->getSprite().GetSize().x;
  int _h = object->getSprite().GetSize().y;

  //Add top left corner
  int topleft = (int) (floor(_x / cellsize) + floor(_y / cellsize) * column);
            
  //Top right
  int topright = (int) (floor((_x + _w) / cellsize) + floor((_y) / cellsize) * column);
             
  //Bottom left
  int bottomleft = (int) (floor((_x) / cellsize) + floor((_y + _h) / cellsize) * column);
    
  //Bottom right
  int bottomright = (int) (floor((_x + _w) / cellsize) + floor((_y + _h) / cellsize) * column);

  std::vector<int> hash_codes;

    hash_codes.push_back(topleft);
	if(hash_codes.back() != topright)
		hash_codes.push_back(topright);
	if(hash_codes.front() != bottomleft && hash_codes.back() != bottomleft)
		hash_codes.push_back(bottomleft);
	if(hash_codes.back() != bottomright)
		hash_codes.push_back(bottomright);
  
  return hash_codes;
}
std::vector<Object*> SpatialHash::getNearby(Object *subject) {
  
  std::vector<int> hash_codes = hashCodes(subject);
  std::vector<Object*> nearby_objects; 

  for (unsigned int i = 0; i < hash_codes.size(); ++i)
  {
    nearby_objects.insert(nearby_objects.end(), bucket[hash_codes[i]].begin(),
 			  bucket[hash_codes[i]].end());
  }

  return nearby_objects;
}

//Resets hash, hashing happens on every frame refresh
void SpatialHash::clear() {
  bucket.clear();
  for(int i = 0; i < column * row; i++)
    bucket.push_back(std::vector<Object*>()); 
}
        

