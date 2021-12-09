#ifndef MOVIENODE_H
#define MOVIENODE_H

#include "Movie.h"

struct MovieNode {

    MovieNode();

    friend std::ostream &operator<<(std::ostream &os, const MovieNode &node);

    MovieNode(Movie movie, int fileIndex);

    void setKey(Movie movie);

    void setFileIndex(int index);

    int key;
    int fileIndex;

};

#endif