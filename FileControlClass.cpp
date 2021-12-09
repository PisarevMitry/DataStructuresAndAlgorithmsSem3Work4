#include "FileControlClass.h"

FileControlClass::FileControlClass(const char *fileNameTXT) {
    numberMovies = 0;
    fileNameBIN = "data.bin";
    creatingFile(getMoviesFromTxt(fileNameTXT));
}

void FileControlClass::creatingFile(Movie *movies) {
    std::ofstream stream(fileNameBIN, std::ios::binary | std::ios::trunc);
    if (stream.is_open()) {
        for (int i = 0; i < numberMovies; i++) {
            stream.write((char *) (&movies[i]), sizeof(Movie));
        }
        stream.close();
    }
}

Movie *FileControlClass::getMoviesFromTxt(const char *fileNameTXT) {
    std::string nodeString;
    std::ifstream stream;
    Movie movie;

    getNumberMoviesFromTxt(fileNameTXT);
    auto *movies = new Movie[numberMovies];
    stream.open(fileNameTXT, std::ios::in);
    if (stream.is_open()) {
        for (int i = 0; i < numberMovies; i++) {
            getline(stream, nodeString, '\n');
            strcpy(movie.title, (nodeString.substr(0, nodeString.find(' '))).c_str());
            nodeString = nodeString.substr(nodeString.find(' ') + 1);
            movie.numberReviews = std::stoi(nodeString.substr(0, nodeString.find(' ')));
            movie.averageRating = std::stod(nodeString.substr(nodeString.find(' ') + 1));
            movies[i] = movie;
        }
        stream.close();
    }
    return movies;
}

void FileControlClass::getNumberMoviesFromTxt(const char *fileNameTXT) {
    std::ifstream stream;
    stream.open(fileNameTXT, std::ios::in);
    if (stream.is_open()) {
        while (!stream.eof()) {
            std::string str;
            getline(stream, str, '\n');
            numberMovies++;
        }
        stream.close();
    }
}

Movie FileControlClass::search(const std::string &title) {
    std::ifstream stream;
    Movie movie;

    stream.open(fileNameBIN, std::ios::binary);
    if (stream.is_open()) {
        for (int i = 0; i < numberMovies; i++) {
            stream.read((char *) &movie, sizeof(Movie));
            if (movie.title == title) {
                break;
            }
        }
        stream.close();
    }
    return movie.title == title ? movie : Movie(nullptr, 0, 0);
}

Movie FileControlClass::getMovie(int address) {
    std::ifstream stream;
    Movie movie;

    stream.open(fileNameBIN, std::ios::binary);
    if (stream.is_open() && address < numberMovies) {
        stream.seekg(address * sizeof(Movie), stream.beg);
        stream.read((char *) &movie, sizeof(Movie));
        stream.close();
    }
    return movie;
}

void FileControlClass::insert(Movie node) {
    std::ofstream stream(fileNameBIN, std::ios::binary | std::ios::app);
    if (stream.is_open()) {
        stream.write((char *) (&node), sizeof(Movie));
        numberMovies++;
        stream.close();
    }
}

void FileControlClass::output(Movie node) {
    std::cout << node << std::endl;
}

void FileControlClass::outputAll() {
    std::ifstream stream;
    Movie movie;

    stream.open(fileNameBIN, std::ios::binary);
    for (int i = 0; i < numberMovies; i++) {
        stream.read((char *) &movie, sizeof(Movie));
        output(movie);
    }
    stream.close();
}

void FileControlClass::checkedSearch(const std::string &movieKey) {
    std::cout << "Проверка " << numberMovies << " элементов в файле:" << std::endl;
    clock_t start, end;

    start = clock();

    std::ifstream stream;
    Movie movie;
    int i;
    stream.open(fileNameBIN, std::ios::binary);
    if (stream.is_open()) {
        for (i = 0; i < numberMovies; i++) {
            stream.read((char *) &movie, sizeof(Movie));
            if (movie.title == movieKey) {
                break;
            }
        }
        stream.close();
    }

    end = clock();

    std::string result;
    if (i < numberMovies / 3) {
        result = " в начале файла ";
    } else if (i > numberMovies / 3 && i < numberMovies * 2 / 3) {
        result = " в середине файла ";
    } else {
        result = " в конце файла";
    }
    std::cout << "Выполнен поиск" + result + "за ";
    printf("%.2f секунд(ы)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
}
