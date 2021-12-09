#include "MovieNode.h"

MovieNode::MovieNode() {
    key = 0;
    fileIndex = -1;
}

MovieNode::MovieNode(Movie movie, int fileIndex) {
    setKey(movie);
    setFileIndex(fileIndex);
}

void MovieNode::setKey(Movie movie) {
    key = 0;
    for (char i : movie.title) {
        if (i != '\0') { key += (int) i; }
    }
}

void MovieNode::setFileIndex(int index) {
    this->fileIndex = index;
}

std::ostream &operator<<(std::ostream &os, const MovieNode &node) {
    os << "key: " << node.key << " fileIndex: " << node.fileIndex;
    return os;
}
