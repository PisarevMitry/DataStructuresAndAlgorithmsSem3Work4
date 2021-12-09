#ifndef BALANCEDSEARCHTREE_H
#define BALANCEDSEARCHTREE_H

#include "BinarySearchTree.h"

#include <fstream>
#include <iostream>
#include "Movie.h"
#include "MovieNode.h"

const int treeGrade = 2;

struct BalancedTreeNode {

    MovieNode *movieNode[2 * treeGrade];
    BalancedTreeNode *children[2 * treeGrade + 1];
    BalancedTreeNode *parent;
    int count;
    int countSons;
    bool leaf;
};

class BalancedSearchTree {
public:

    BalancedTreeNode *rootTreeNode;
    int numberMovies;
    int maxFileIndex;
    const char *fileNameBIN;
    const char *fileNameTXT;
    double averageRotation = 0;

    BalancedSearchTree();

    ~BalancedSearchTree();

    void creatingTree(Movie *movies);

    Movie *getMoviesFromTxt();

    int getNumberMoviesFromTxt();

    void insertMovie(Movie node);

    MovieNode *insertMovieToFile(Movie node);

    void insertMovieNode(MovieNode *movieNode, BalancedTreeNode *treeNode);

    void sort(BalancedTreeNode *treeNode);

    void splittingTreeNode(BalancedTreeNode *treeNode);

    void removeTreeNode(BalancedTreeNode *treeNode);

    void remove(int key, BalancedTreeNode *treeNode);

    void removeFromNode(int key, BalancedTreeNode *node);

    void removeLeaf(int key, BalancedTreeNode *node);

    void connectTreeNode(BalancedTreeNode *treeNode, BalancedTreeNode *otherTreeNode);

    void repair(BalancedTreeNode *treeNode);

    void deleteMovieNode(int key);

    void outputMovieNode(MovieNode node, const std::string &mode);

    Movie getMovieFromFile(int index);

    void outputMovie(Movie node);

    void outputTree();

    void outputTree(BalancedTreeNode *treeNode, int level, const std::string &mode);

    int searchMovie(int key);

    Movie searchMovie(const std::string &title);

    MovieNode *searchMovie(BalancedTreeNode *treeNode, int key);

    void deleteMovie(const std::string &title);

    void checkedSearch(const std::string &movieKey) const;
};

#endif
