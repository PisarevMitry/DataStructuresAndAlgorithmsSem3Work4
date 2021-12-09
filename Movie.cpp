#include "Movie.h"

Movie::Movie(std::string title, int numberReviews, double averageRating) {
    strcpy(this->title, title.c_str());
    this->numberReviews = numberReviews;
    this->averageRating = averageRating;
}

Movie::Movie() {
    strcpy(this->title, "ERROR");
    this->numberReviews = -1;
    this->averageRating = -1;
}

std::ostream &operator<<(std::ostream &os, const Movie &movie) {
    os << "title: " << movie.title << " numberReviews: " << movie.numberReviews << " averageRating: "
       << movie.averageRating;
    return os;
}
