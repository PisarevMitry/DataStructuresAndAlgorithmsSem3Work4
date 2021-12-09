#ifndef FILECONTROLCLASS_H
#define FILECONTROLCLASS_H

#include "iostream"
#include <fstream>
#include <cstring>
#include "Movie.h"

class FileControlClass {
private:
    int numberMovies;
    const char *fileNameBIN;
public:
    FileControlClass(const char *fileNameTXT);

    void creatingFile(Movie *movies);

    Movie *getMoviesFromTxt(const char *fileNameTXT);

    void getNumberMoviesFromTxt(const char *fileNameTXT);

    Movie search(const std::string &title);

    Movie getMovie(int address);

    static void output(Movie node);

    void insert(Movie node);

    void outputAll();

    void checkedSearch(const std::string &movieKey);
};

#endif
