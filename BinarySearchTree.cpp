#include "BinarySearchTree.h"

//Функция создания бинарного дерева поиска по данным из текстового файла
BinarySearchTree::BinarySearchTree() {
    numberMovies = 0;
    maxFileIndex = 0;
    rootTreeNode = nullptr;
    fileNameBIN = "data.bin";
    fileNameTXT = "data.txt";
    creatingTree(getMoviesFromTxt());
}

//Функция создания бинарного дерева поиска из массива структур
void BinarySearchTree::creatingTree(Movie *movies) {
    auto numberMoviesLocal = getNumberMoviesFromTxt();
    std::ofstream stream(fileNameBIN, std::ios::binary | std::ios::trunc);
    if (stream.is_open()) {
        for (int i = 0; i < numberMoviesLocal; i++) {
            insertMovie(movies[i]);
        }
        stream.close();
    }
}

//Функция получения массива структур из текстового файла
Movie *BinarySearchTree::getMoviesFromTxt() {
    std::string nodeString;
    std::ifstream stream;
    Movie movie;

    int numberMoviesLocal = getNumberMoviesFromTxt();
    auto *movies = new Movie[numberMoviesLocal];
    stream.open(fileNameTXT, std::ios::in);
    if (stream.is_open()) {
        for (int i = 0; i < numberMoviesLocal; i++) {
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

//Функция подсчета количество структур в текстовом файле
int BinarySearchTree::getNumberMoviesFromTxt() {
    int numberMoviesLocal = 0;
    std::ifstream stream;
    stream.open(fileNameTXT, std::ios::in);
    if (stream.is_open()) {
        while (!stream.eof()) {
            std::string str;
            getline(stream, str, '\n');
            numberMoviesLocal++;
        }
        stream.close();
    }
    return numberMoviesLocal;
}

//Функция чтения структуры по определенному адресу в бинарном файле
Movie BinarySearchTree::getMovieFromFile(int index) {
    std::ifstream stream;
    Movie movie;

    stream.open(fileNameBIN, std::ios::binary);
    if (stream.is_open() && index < numberMovies && index >= 0) {
        stream.seekg(index * sizeof(Movie), stream.beg);
        stream.read((char *) &movie, sizeof(Movie));
        stream.close();
    }
    return movie;
}

//Функция поиска узла в дереве по текстовому ключу, которая возращает данные о фильме
Movie BinarySearchTree::searchMovie(std::string title) {
    int key = 0;
    for (char i: title) {
        if (i != '\0') { key += (int) i; }
    }
    int fileIndex = searchMovie(key);
    return fileIndex >= 0 ? getMovieFromFile(fileIndex) : Movie();
}

//Функция поиска адрес фильма в файле по бинарному дереву поиска
int BinarySearchTree::searchMovie(int key) {
    auto movieNode = searchMovie(rootTreeNode, key);
    return movieNode ? movieNode->fileIndex : -1;
}

//Функция поиска узла в дереве по ключу
MovieNode *BinarySearchTree::searchMovie(TreeNode *treeNode, int key) {
    if (treeNode) {
        if (treeNode->movieNode->key == key) {
            return treeNode->movieNode;
        } else if (treeNode->movieNode->key < key) {
            return searchMovie(treeNode->rightNode, key);
        } else {
            return searchMovie(treeNode->leftNode, key);
        }
    } else {
        return nullptr;
    }
}

//Функция создания узла и записи структуры в файл
MovieNode *BinarySearchTree::insertMovieToFile(Movie node) {
    std::ofstream stream(fileNameBIN, std::ios::binary | std::ios::app);
    if (stream.is_open()) {
        stream.write((char *) (&node), sizeof(Movie));
        maxFileIndex++;
        numberMovies++;
        stream.close();
    }
    auto *movieNode = new MovieNode(node, numberMovies - 1);
    return movieNode;
}

//Функция вставки узла в бинарное дерево поиска
void BinarySearchTree::insertMovie(Movie node) {
    MovieNode *movieNode = insertMovieToFile(node);
    if (rootTreeNode == nullptr) {
        rootTreeNode = new TreeNode(movieNode);
    } else {
        TreeNode **cur = &rootTreeNode;
        while (*cur) {
            TreeNode &tree = **cur;
            if (movieNode->key <= tree.movieNode->key) {
                cur = &tree.leftNode;
            } else if (movieNode->key > tree.movieNode->key) {
                cur = &tree.rightNode;
            } else {
                return;
            }
        }
        *cur = new TreeNode(movieNode);
    }
}

//Удаление всей информации из файла об определенном фильме
void BinarySearchTree::deleteMovie(const std::string &title) {
    int key = 0;
    for (char i: title) {
        if (i != '\0') { key += (int) i; }
    }
    int fileIndex = searchMovie(key);
    deleteMovieNode(key);
    numberMovies--;
}

//Функция удаления записи по ключу
void BinarySearchTree::deleteMovieNode(int key) {
    deleteMovieNode(rootTreeNode, key);
}

//Функция удаления узла в дереве по ключу
TreeNode *BinarySearchTree::deleteMovieNode(TreeNode *treeNode, int key) {
    if (treeNode == nullptr) { return nullptr; }
    else if (key < treeNode->movieNode->key) { treeNode->leftNode = deleteMovieNode(treeNode->leftNode, key); }
    else if (key > treeNode->movieNode->key) { treeNode->rightNode = deleteMovieNode(treeNode->rightNode, key); }
    else {
        if (treeNode->leftNode == nullptr && treeNode->rightNode == nullptr) {
            delete treeNode;
            treeNode = nullptr;
        } else if (treeNode->leftNode == nullptr) {
            TreeNode *temp = treeNode;
            treeNode = treeNode->rightNode;
            delete temp;
        } else if (treeNode->rightNode == nullptr) {
            TreeNode *temp = treeNode;
            treeNode = treeNode->leftNode;
            delete temp;
        } else {
            TreeNode *temp = findMinNode(treeNode->rightNode);
            treeNode->movieNode = temp->movieNode;
            treeNode->rightNode = deleteMovieNode(treeNode->rightNode, temp->movieNode->key);
        }
    }
    return treeNode;
}

//Функция поиска узла с минимальным ключом
TreeNode *BinarySearchTree::findMinNode(TreeNode *treeNode) {
    while (treeNode->leftNode) {
        treeNode = treeNode->leftNode;
    }
    return treeNode;
}

//Функция вывода узла бинарного дерева поиска
void BinarySearchTree::outputMovieNode(MovieNode node, const std::string &mode) {
    auto movie = getMovieFromFile(node.fileIndex);
    if (mode == "FULL_NODE") {
        outputMovie(movie);
    } else if (mode == "ONLY_STRING_KEY") {
        std::cout << movie.title << std::endl;
    } else if (mode == "ONLY_INT_KEY") {
        auto title = movie.title;
        int key = 0;
        for (int i = 0; i < 20; i++) {
            if (title[i] != '\0') { key += (int) title[i]; }
        }
        std::cout << key << std::endl;
    }
}

//Функция вывода структуры фильма
void BinarySearchTree::outputMovie(Movie node) {
    if (node.title != "ERROR" && node.numberReviews >= 0 && node.averageRating >= 0) {
        std::cout << node << std::endl;
    } else {
        std::cout << "ERROR" << std::endl;
    }
}

//Функция вывода всего бинарного дерева поиска
void BinarySearchTree::outputTree() {
    outputTree(rootTreeNode, 0, "STRING");
}

//Функция вывода части бинарного дерева поиска
void BinarySearchTree::outputTree(TreeNode *treeNode, int level, const std::string &mode) {
    if (treeNode) {
        outputTree(treeNode->rightNode, level + 1, mode);
        if (mode == "STRING") {
            for (int i = 0; i < level; i++) { std::cout << "        "; }
            outputMovieNode(*(treeNode->movieNode), "ONLY_STRING_KEY");
        } else if (mode == "INT") {
            for (int i = 0; i < level; i++) { std::cout << "             "; }
            outputMovieNode(*(treeNode->movieNode), "ONLY_INT_KEY");
        }
        outputTree(treeNode->leftNode, level + 1, mode);
    }
}

void BinarySearchTree::checkedSearch(const std::string &movieKey) {
    std::cout << "Проверка " << numberMovies << " элементов в файле:" << std::endl;
    clock_t start, end;

    start = clock();
    searchMovie(movieKey);
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
        result = " в конце файла ";
    }
    std::cout << "Выполнен поиск" + result + "за ";
    printf("%.2f секунд(ы)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));
}

TreeNode::TreeNode() {
    this->movieNode = nullptr;
    this->leftNode = nullptr;
    this->rightNode = nullptr;
}

TreeNode::TreeNode(MovieNode *movieNode) : movieNode(movieNode) {
    this->leftNode = nullptr;
    this->rightNode = nullptr;
}

TreeNode::TreeNode(MovieNode *movieNode, TreeNode *leftNode, TreeNode *rightNode) : movieNode(movieNode),
                                                                                    leftNode(leftNode),
                                                                                    rightNode(rightNode) {}


