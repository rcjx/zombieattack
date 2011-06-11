#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

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
        
        void move()
        {
             cout << left << setw(4) << x << setw(4) << y << setw(4) << rad << endl;
        }
      
        int x, y, rad;
};

class Hash
{
    public:
        Hash() {}
        ~Hash() {}
        
        void setup(int WIDTH, int HEIGHT, vector<Object*> list)
        {
            cellsize = 60; //60 looks like the best combination
             
            column = WIDTH / cellsize; 
            row = HEIGHT / cellsize; 
             
            bucket.resize(column * row);
             
            cout << "object size " << list.size() << endl;  
            cout << "ID x   y   radius" << endl;  
            for(unsigned int i = 0; i < list.size(); i++)
            {
                cout << i << ": ";
                list[i]->move();
            }
            
            //cout << "object hash positions " << endl;
            for(unsigned int i = 0; i < list.size(); i++)
                add(i, list); //Adds position of object
                
            cout << "hash size " << column * row << " vector size: " << bucket.size() << endl;
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
             
            /*
            //Add top left corner
            bucket[(int) (floor(list[object]->x / cellsize) + floor(list[object]->y / cellsize) * column)].push_back(object); 
             
            //Top right
            bucket[(int) (floor((list[object]->x + list[object]->rad) / cellsize) + floor((list[object]->y) / cellsize) * column)].push_back(object); 
             
            //Bottom left
            bucket[(int) (floor((list[object]->x) / cellsize) + floor((list[object]->y + list[object]->rad) / cellsize) * column)].push_back(object); 
    
            //Bottom right
            bucket[(int) (floor((list[object]->x + list[object]->rad) / cellsize) + floor((list[object]->y + list[object]->rad) / cellsize) * column)].push_back(object); 
            */
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
    hash.setup(SCREEN_WIDTH, SCREEN_HEIGHT, vec);


    system("PAUSE");
    return EXIT_SUCCESS;
}
