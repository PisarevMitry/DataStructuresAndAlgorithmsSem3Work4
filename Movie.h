#ifndef MOVIE_H
#define MOVIE_H

#include <cstring>
#include <string>
#include <ostream>

struct Movie {

    Movie();

    Movie(std::string title, int numberReviews, double averageRating);

    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);

    char title[20] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                      '\0', '\0', '\0', '\0'};
    int numberReviews;
    double averageRating;

};

#endif
