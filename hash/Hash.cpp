#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

//SCREEN SIZE must be mutiples of Hash's int cellsize, 60 
const int SCREEN_WIDTH = 180;
const int SCREEN_HEIGHT = 180;

class Object
{
    public:
        Object(int X, int Y)
        {
            x = X;
            y = Y;
            rad = 40;    
        }      
        
        //Simulates how move() will be fired inside hash. Display function atm
        void move()
        {
             cout << left << setw(4) << x << setw(4) << y << setw(4) << rad << endl;
        }
      
        int x, y, rad;
};

//Hash class using a vector of int vectors
//Cuts down collision check algorithm loops from O(n^2) to O(nlogn);
class Hash
{
    public:
        Hash() {}
        ~Hash() {}
        
        //Sets up the hash for hashing, fires on every game turn
        void setup(int WIDTH, int HEIGHT, vector<Object*> list)
        {
            cellsize = 60; //60 looks like the best combination
             
            column = WIDTH / cellsize; 
            row = HEIGHT / cellsize; 
             
            for(unsigned int i = 0; i < column * row; i++)
                bucket.push_back(vector<int>()); 
            
            cout << "object size " << list.size() << endl;  
            cout << "ID x   y   radius" << endl;  
            for(unsigned int i = 0; i < list.size(); i++)
            {
                cout << i << ": ";
                list[i]->move();
            }
            
            cout << "object hash positions " << endl;
            for(unsigned int i = 0; i < list.size(); i++)
                add(i, list); //Adds position of object
                
            cout << "hashtable size " << column * row << " vector size: " << bucket.size() << endl;
            for(unsigned int i = 0; i < bucket.size(); i++)
            {
                cout << i << ": " << bucket[i].size();            
                if(bucket[i].size() > 0)
                {
                    cout << " has ";    
                    for(unsigned int j = 0; j < bucket[i].size(); j++)
                        cout << bucket[i][j] << " ";
                }
                if(bucket[i].size() > 1)
                    cout << "collision";
                cout << endl;
            }   
        }
        
        //Adds object into the hashtable
        void add(int object, vector<Object*> list)
        {
            //Add top left corner
            int topleft = (int) (floor(list[object]->x / cellsize) + floor(list[object]->y / cellsize) * column);
            
            //Top right
            int topright = (int) (floor((list[object]->x + list[object]->rad) / cellsize) + floor((list[object]->y) / cellsize) * column);
             
            //Bottom left
            int bottomleft = (int) (floor((list[object]->x) / cellsize) + floor((list[object]->y + list[object]->rad) / cellsize) * column);
    
            //Bottom right
            int bottomright = (int) (floor((list[object]->x + list[object]->rad) / cellsize) + floor((list[object]->y + list[object]->rad) / cellsize) * column);
            
            //cout << object << ": " << topleft << " " << topright << " AND "
            //     << bottomleft << " " << bottomright << endl;       
             
            if(bucket[topleft].back() != object)
                bucket[topleft].push_back(object);
            if(bucket[topright].back() != object)
                bucket[topright].push_back(object);    
            if(bucket[bottomleft].back() != object)
                bucket[bottomleft].push_back(object);
            if(bucket[bottomright].back() != object)
                bucket[bottomright].push_back(object);
        }
        
        //Resets hash, hashing happens on every frame refresh
        void clear()
        {
            bucket.clear();     
        }
        
    private:
        vector< vector<int> > bucket;
        unsigned int column, row, width, height, cellsize;
};

int main(int argc, char *argv[])
{
    vector<Object*> vec;
    
    const int size = 5;
    
    srand(time(NULL));
    for(unsigned int i = 0; i < size; i++)
    {
        int x = rand() % 140; 
        int y = rand() % 140;         
        vec.push_back(new Object(x, y));
    }
    
    Hash hash;
    
    clock_t start, end, middle;
    start = clock();
    hash.setup(SCREEN_WIDTH, SCREEN_HEIGHT, vec);
    middle = clock();
    
    hash.clear();
    end = clock();
    
    cout << (double) (middle - start) / CLOCKS_PER_SEC << " to hash " << endl;
    cout << (double) (end - start) / CLOCKS_PER_SEC << " to hash and clear" <<endl;

    system("PAUSE");
    return EXIT_SUCCESS;
}
