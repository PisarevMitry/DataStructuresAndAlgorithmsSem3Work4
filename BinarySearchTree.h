#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <fstream>
#include <iostream>
#include <ostream>
#include "Movie.h"
#include "MovieNode.h"

struct TreeNode {
    TreeNode();

    TreeNode(MovieNode *movieNode);

    TreeNode(MovieNode *movieNode, TreeNode *leftNode, TreeNode *rightNode);

    MovieNode *movieNode;
    TreeNode *leftNode;
    TreeNode *rightNode;

};

class BinarySearchTree {

private:
    TreeNode *rootTreeNode;
    int numberMovies;
    int maxFileIndex;
    const char *fileNameBIN;
    const char *fileNameTXT;
public:
    BinarySearchTree();

    void creatingTree(Movie *movies);

    Movie *getMoviesFromTxt();

    int getNumberMoviesFromTxt();

    Movie getMovieFromFile(int index);

    Movie searchMovie(std::string title);

    int searchMovie(int key);

    MovieNode *searchMovie(TreeNode *treeNode, int key);

    MovieNode *insertMovieToFile(Movie node);

    void insertMovie(Movie node);

    void outputMovieNode(MovieNode node, const std::string &mode);

    void outputMovie(Movie node);

    void outputTree();

    void outputTree(TreeNode *treeNode, int level, const std::string &mode);

    TreeNode *findMinNode(TreeNode *treeNode);

    void deleteMovie(const std::string &title);

    TreeNode *deleteMovieNode(TreeNode *treeNode, int key);

    void deleteMovieNode(int key);

    void checkedSearch(const std::string &movieKey);

};

#endif
