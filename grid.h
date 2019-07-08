#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include <vector>
#include "position.h"
#include <memory>

class Tile;
class TextDisplay;
class Object;

class Grid {
    std::vector<std::vector<std::shared_ptr<Tile>>> theGrid;
    int rows, cols;
    std::shared_ptr<TextDisplay> td;

public:
    Grid(int rows = 25, int cols = 79);
    ~Grid();

    std::shared_ptr<TextDisplay> getDisplay();

    void setTile(int row, int col, char symbol);
    bool isStair(int row, int col) const;

    // returns true if tile is a floor tile and is assigned to a chamber, or 
    //   if the tile is not a floor tile
    bool isAssigned(int row, int col) const;

    // set tile as assigned
    void setAssigned(int row, int col) const; 

    // returns next unassigned floor tile, starting from the position given.
    //   returns a position of (-1,-1) if all floor tiles have been assigned
    Position nextUassignedFloorTile(int row = 0, int col = 0) const; 

    // Returns the object that occupies this space.
    //   Returns nullptr if this space is something that cannot be occupied 
    //   (eg. wall, empty space)
    std::shared_ptr<Object> occupant(int row, int col) const;

    // obj tries to occupy the space located at row,col. 
    //   Return true if success
    bool occupySpace(int row, int col, std::shared_ptr<Object> obj) const;

    // make this the space at row,col unoccpied
    void unoccupy(int row, int col) const;

    bool canBeOccupied(int row, int col, std::shared_ptr<Object> obj) const;

    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
