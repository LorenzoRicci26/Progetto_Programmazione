//
// Created by Lorenzo Ricci on 10/09/2020.
//

#ifndef UNTITLED_UTILITY_H
#define UNTITLED_UTILITY_H


class Utility {
public:
    //Constructor and Destructor
    Utility(int* tiles,int width,int height);
    virtual ~Utility();

    //Getter and Setter
    int *getMap() const;
    void setMap(int *map);
    int getMHeight() const;
    void setMHeight(int mHeight);
    int getMWidth() const;
    void setMWidth(int mWidth);

    //Functions
    int GetMap (int x, int y);

private:
     int* map; //world_map
     int m_height; //x of the map
     int m_width; //y of the map
};


#endif //UNTITLED_UTILITY_H
