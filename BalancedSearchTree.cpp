#include "BalancedSearchTree.h"

//Конструктор класса
BalancedSearchTree::BalancedSearchTree() {
    numberMovies = 0;
    maxFileIndex = 0;
    rootTreeNode = nullptr;
    fileNameBIN = "data.bin";
    fileNameTXT = "data.txt";
    creatingTree(getMoviesFromTxt());
}

//Деструктор класса
BalancedSearchTree::~BalancedSearchTree() {
    if (rootTreeNode != nullptr) removeTreeNode(rootTreeNode);
}

//Функция создания бинарного дерева поиска из массива структур
void BalancedSearchTree::creatingTree(Movie *movies) {
    auto numberMoviesLocal = getNumberMoviesFromTxt();
    std::ofstream stream(fileNameBIN, std::ios::binary | std::ios::trunc);
    if (stream.is_open()) {
        for (int i = 0; i < numberMoviesLocal; i++) {
            insertMovie(movies[i]);
        }
        stream.close();
    }
}

//Функция чтения структуры по определенному адресу в бинарном файле
Movie BalancedSearchTree::getMovieFromFile(int index) {
    std::ifstream stream;
    Movie movie;

    stream.open(fileNameBIN, std::ios::binary);
    if (stream.is_open() && index < numberMovies && index >= 0) {
        stream.seekg(index * sizeof(Movie), std::ifstream::beg);
        stream.read((char *) &movie, sizeof(Movie));
        stream.close();
    }
    return movie;
}

//Функция получения массива структур из текстового файла
Movie *BalancedSearchTree::getMoviesFromTxt() {
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
int BalancedSearchTree::getNumberMoviesFromTxt() {
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

//Функция сортировки структур внутри узла дерева
void BalancedSearchTree::sort(BalancedTreeNode *treeNode) {
    for (int i = 0; i < (2 * treeGrade - 1); i++) {
        for (int j = i + 1; j <= (2 * treeGrade - 1); j++) {
            if (treeNode->movieNode[i] != nullptr && treeNode->movieNode[j] != nullptr) {
                if (treeNode->movieNode[i]->key > treeNode->movieNode[j]->key) {
                    std::swap(*treeNode->movieNode[i], *treeNode->movieNode[j]);
                }
            } else { break; }
        }
    }
}

//Функция разделения узла дерева на 2
void BalancedSearchTree::splittingTreeNode(BalancedTreeNode *treeNode) {
    averageRotation++;
    if (treeNode->count >= (2 * treeGrade - 1)) {
        auto *childrenTreeNode0 = new BalancedTreeNode;
        for (int j = 0; j <= treeGrade - 2; j++) {
            childrenTreeNode0->movieNode[j] = treeNode->movieNode[j];
        }
        for (int j = treeGrade - 1; j <= (2 * treeGrade - 1); j++) {
            childrenTreeNode0->movieNode[j] = nullptr;
        }
        childrenTreeNode0->count = treeGrade - 1;
        if (treeNode->countSons != 0) {
            for (int i = 0; i <= (treeGrade - 1); i++) {
                childrenTreeNode0->children[i] = treeNode->children[i];
                childrenTreeNode0->children[i]->parent = childrenTreeNode0;
            }
            for (int i = treeGrade; i <= (2 * treeGrade); i++) childrenTreeNode0->children[i] = nullptr;
            childrenTreeNode0->leaf = false;
            childrenTreeNode0->countSons = treeGrade - 1;
        } else {
            childrenTreeNode0->leaf = true;
            childrenTreeNode0->countSons = 0;
            for (int i = 0; i <= (2 * treeGrade); i++) childrenTreeNode0->children[i] = nullptr;
        }

        auto *childrenTreeNode1 = new BalancedTreeNode;
        for (int j = 0; j <= (treeGrade - 1); j++) {
            childrenTreeNode1->movieNode[j] = treeNode->movieNode[j + treeGrade];
        }
        for (int j = treeGrade; j <= (2 * treeGrade - 1); j++) {
            childrenTreeNode1->movieNode[j] = nullptr;
        }
        childrenTreeNode1->count = treeGrade;
        if (treeNode->countSons != 0) {
            for (int i = 0; i <= (treeGrade); i++) {
                childrenTreeNode1->children[i] = treeNode->children[i + treeGrade];
                childrenTreeNode1->children[i]->parent = childrenTreeNode1;
            }
            for (int i = treeGrade + 1; i <= (2 * treeGrade); i++) childrenTreeNode1->children[i] = nullptr;
            childrenTreeNode1->leaf = false;
            childrenTreeNode1->countSons = treeGrade;
        } else {
            childrenTreeNode1->leaf = true;
            childrenTreeNode1->countSons = 0;
            for (int i = 0; i <= (2 * treeGrade); i++) childrenTreeNode1->children[i] = nullptr;
        }

        if (treeNode->parent == nullptr) {
            treeNode->movieNode[0] = treeNode->movieNode[treeGrade - 1];
            for (int j = 1; j <= (2 * treeGrade - 1); j++) {
                treeNode->movieNode[j] = nullptr;
            }
            treeNode->children[0] = childrenTreeNode0;
            treeNode->children[1] = childrenTreeNode1;
            for (int i = 2; i <= (2 * treeGrade); i++) treeNode->children[i] = nullptr;
            treeNode->parent = nullptr;
            treeNode->leaf = false;
            treeNode->count = 1;
            treeNode->countSons = 2;
            childrenTreeNode0->parent = treeNode;
            childrenTreeNode1->parent = treeNode;
        } else {
            insertMovieNode(treeNode->movieNode[treeGrade - 1], treeNode->parent);
            for (int i = 0; i <= (2 * treeGrade); i++) {
                if (treeNode->parent->children[i] == treeNode) {
                    treeNode->parent->children[i] = nullptr;
                }
            }
            for (int i = 0; i <= (2 * treeGrade); i++) {
                if (treeNode->parent->children[i] == nullptr) {
                    for (int j = (2 * treeGrade); j > (i + 1); j--) {
                        treeNode->parent->children[j] = treeNode->parent->children[j - 1];
                    }
                    treeNode->parent->children[i + 1] = childrenTreeNode1;
                    treeNode->parent->children[i] = childrenTreeNode0;
                    treeNode->parent->countSons++;
                    break;
                }
            }
            childrenTreeNode0->parent = treeNode->parent;
            childrenTreeNode1->parent = treeNode->parent;
            treeNode->parent->leaf = false;
            delete treeNode;
        }
    }
}

//Функция обратная функции splittingTreeNode
void BalancedSearchTree::connectTreeNode(BalancedTreeNode *treeNode, BalancedTreeNode *otherTreeNode) {
    averageRotation++;
    if (treeNode == nullptr) return;
    for (int i = 0; i <= (otherTreeNode->count - 1); i++) {
        treeNode->movieNode[treeNode->count] = otherTreeNode->movieNode[i];
        treeNode->children[treeNode->count] = otherTreeNode->children[i];
        treeNode->count = treeNode->count + 1;
    }
    treeNode->children[treeNode->count] = otherTreeNode->children[otherTreeNode->count];
    for (int j = 0; j <= treeNode->count; j++) {
        if (treeNode->children[j] == nullptr) break;
        treeNode->children[j]->parent = treeNode;
    }
    delete otherTreeNode;
}

//Функция восстановления узлов после удаления структуры
void BalancedSearchTree::repair(BalancedTreeNode *treeNode) {
    if (treeNode == rootTreeNode && treeNode->count == 0) {
        if (rootTreeNode->children[0] != nullptr) {
            rootTreeNode->children[0]->parent = nullptr;
            rootTreeNode = rootTreeNode->children[0];
        } else {
            delete rootTreeNode;
        }
        return;
    }
    BalancedTreeNode *pTreeNode = treeNode;
    int positionSon;
    BalancedTreeNode *parent = pTreeNode->parent;
    for (int j = 0; j <= parent->count; j++) {
        if (parent->children[j] == pTreeNode) {
            positionSon = j;
            break;
        }
    }
    if (positionSon == 0) {
        insertMovieNode(parent->movieNode[positionSon], pTreeNode);
        connectTreeNode(pTreeNode, parent->children[positionSon + 1]);
        parent->children[positionSon + 1] = pTreeNode;
        parent->children[positionSon] = nullptr;
        removeFromNode(parent->movieNode[positionSon]->key, parent);
        if (pTreeNode->count == 2 * treeGrade) {
            while (pTreeNode->count == 2 * treeGrade) {
                if (pTreeNode == rootTreeNode) {
                    splittingTreeNode(pTreeNode);
                    break;
                } else {
                    splittingTreeNode(pTreeNode);
                    pTreeNode = pTreeNode->parent;
                }
            }
        } else if (parent->count <= treeGrade - 2) {
            repair(parent);
        }
    } else {
        if (positionSon == parent->count) {
            insertMovieNode(parent->movieNode[positionSon - 1], parent->children[positionSon - 1]);
            connectTreeNode(parent->children[positionSon - 1], pTreeNode);
            parent->children[positionSon] = parent->children[positionSon - 1];
            parent->children[positionSon - 1] = nullptr;
            removeFromNode(parent->movieNode[positionSon - 1]->key, parent);
            BalancedTreeNode *temp = parent->children[positionSon];
            if (pTreeNode->count == 2 * treeGrade) {
                while (temp->count == 2 * treeGrade) {
                    if (temp == rootTreeNode) {
                        splittingTreeNode(temp);
                        break;
                    } else {
                        splittingTreeNode(temp);
                        temp = temp->parent;
                    }
                }
            } else if (parent->count <= treeGrade - 2) {
                repair(parent);
            }
        } else {
            insertMovieNode(parent->movieNode[positionSon], pTreeNode);
            connectTreeNode(pTreeNode, parent->children[positionSon + 1]);
            parent->children[positionSon + 1] = pTreeNode;
            parent->children[positionSon] = nullptr;
            removeFromNode(parent->movieNode[positionSon]->key, parent);
            if (pTreeNode->count == 2 * treeGrade) {
                while (pTreeNode->count == 2 * treeGrade) {
                    if (pTreeNode == rootTreeNode) {
                        splittingTreeNode(pTreeNode);
                        break;
                    } else {
                        splittingTreeNode(pTreeNode);
                        pTreeNode = pTreeNode->parent;
                    }
                }
            } else if (parent->count <= treeGrade - 2) {
                repair(parent);
            }
        }
    }
}

//Функция создания узла и записи структуры в файл
MovieNode *BalancedSearchTree::insertMovieToFile(Movie node) {
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

//Функция добавления фильма в узел дерева
void BalancedSearchTree::insertMovieNode(MovieNode *movieNode, BalancedTreeNode *treeNode) {
    treeNode->movieNode[treeNode->count] = movieNode;
    treeNode->count++;
    sort(treeNode);
}

//Функция добавления фильма в узел дерева
void BalancedSearchTree::insertMovie(Movie node) {
    MovieNode *movieNode = insertMovieToFile(node);
    if (rootTreeNode == nullptr) {
        auto *newRoot = new BalancedTreeNode;
        newRoot->movieNode[0] = movieNode;
        for (int j = 1; j <= (2 * treeGrade - 1); j++) {
            newRoot->movieNode[j] = nullptr;
        }
        for (int i = 0; i <= (2 * treeGrade); i++) {
            newRoot->children[i] = nullptr;
        }
        newRoot->count = 1;
        newRoot->countSons = 0;
        newRoot->leaf = true;
        newRoot->parent = nullptr;
        rootTreeNode = newRoot;
    } else {
        BalancedTreeNode *treeNodeLocal = rootTreeNode;
        while (!treeNodeLocal->leaf) {
            for (int i = 0; i <= (2 * treeGrade - 1); i++) {
                if (treeNodeLocal->movieNode[i] != nullptr) {
                    if (movieNode->key < treeNodeLocal->movieNode[i]->key) {
                        treeNodeLocal = treeNodeLocal->children[i];
                        break;
                    }
                    if (treeNodeLocal->movieNode[i + 1] == nullptr &&
                        movieNode->key > treeNodeLocal->movieNode[i]->key) {
                        treeNodeLocal = treeNodeLocal->children[i + 1];
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        insertMovieNode(movieNode, treeNodeLocal);

        while (treeNodeLocal->count == 2 * treeGrade) {
            if (treeNodeLocal == rootTreeNode) {
                splittingTreeNode(treeNodeLocal);
                break;
            } else {
                splittingTreeNode(treeNodeLocal);
                treeNodeLocal = treeNodeLocal->parent;
            }
        }
    }
    if (averageRotation != 0) {
        averageRotation = averageRotation / 2;
    }
}

//Функция поиска узла в дереве по текстовому ключу, которая возвращает данные о фильме
Movie BalancedSearchTree::searchMovie(const std::string &title) {
    int key = 0;
    for (char i: title) {
        if (i != '\0') { key += (int) i; }
    }
    int fileIndex = searchMovie(key);
    return fileIndex >= 0 ? getMovieFromFile(fileIndex) : Movie();
}

//Функция поиска адрес фильма в файле по бинарному дереву поиска
int BalancedSearchTree::searchMovie(int key) {
    auto movieNode = searchMovie(rootTreeNode, key);
    return movieNode ? movieNode->fileIndex : -1;
}

//Функция поиска узла в дереве по ключу
MovieNode *BalancedSearchTree::searchMovie(BalancedTreeNode *treeNode, int key) {
    if (treeNode != nullptr) {
        if (!treeNode->leaf) {
            int i;
            for (i = 0; i <= (2 * treeGrade - 1); i++) {
                if (treeNode->movieNode[i] != nullptr) {
                    if (key == treeNode->movieNode[i]->key) {
                        return treeNode->movieNode[i];
                    }
                    if (key < treeNode->movieNode[i]->key) {
                        return searchMovie(treeNode->children[i], key);
                    }
                } else {
                    break;
                }
            }
            return searchMovie(treeNode->children[i], key);
        } else {
            for (int j = 0; j <= (2 * treeGrade - 1) && j < treeNode->count; j++) {
                if (key == treeNode->movieNode[j]->key) {
                    return treeNode->movieNode[j];
                }
            }
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

//Удаление всей информации из файла об определенном фильме
void BalancedSearchTree::deleteMovie(const std::string &title) {
    int key = 0;
    for (char i: title) {
        if (i != '\0') { key += (int) i; }
    }
    int fileIndex = searchMovie(key);
    if (fileIndex >= 0) {
        deleteMovieNode(key);
        numberMovies--;
    }
}

//Функция удаления узла в дереве по ключу
void BalancedSearchTree::deleteMovieNode(int key) {
    BalancedTreeNode *pTreeNode = rootTreeNode;
    int i;
    if (searchMovie(pTreeNode, key) != nullptr) {
        for (i = 0; i <= pTreeNode->count - 1; i++) {
            if (pTreeNode->movieNode[i] != nullptr) {
                if (key == pTreeNode->movieNode[i]->key) {
                    break;
                } else {
                    if ((key < pTreeNode->movieNode[i]->key)) {
                        pTreeNode = pTreeNode->children[i];
                        i = -1;
                    } else {
                        if (i == (pTreeNode->count - 1)) {
                            pTreeNode = pTreeNode->children[i + 1];
                            i = -1;
                        }
                    }
                }
            } else {
                break;
            }
        }
    } else {
        return;
    }
    if (pTreeNode->leaf) {
        if (pTreeNode->count > (treeGrade - 1)) removeFromNode(key, pTreeNode);
        else removeLeaf(key, pTreeNode);
    } else remove(key, pTreeNode);
}

//Функция удаления узла в дереве
void BalancedSearchTree::removeTreeNode(BalancedTreeNode *treeNode) {
    if (treeNode != nullptr) {
        for (int i = 0; i <= (2 * treeGrade - 1); i++) {
            if (treeNode->children[i] != nullptr) {
                removeTreeNode(treeNode->children[i]);
            } else {
                delete treeNode;
                break;
            }
        }
    }
}

//Функция удаления узла в дереве
void BalancedSearchTree::remove(int key, BalancedTreeNode *treeNode) {
    auto treeNodeLocal = treeNode;
    int position;
    for (int i = 0; i <= treeNode->count - 1; i++) {
        if (key == treeNode->movieNode[i]->key) {
            position = i;
            break;
        }
    }
    if (treeNodeLocal->parent != nullptr) {
        for (int i = 0; i <= treeNodeLocal->parent->count; i++) {
            if (treeNodeLocal->children[i] == treeNodeLocal) {
                break;
            }
        }
    }
    treeNodeLocal = treeNodeLocal->children[position + 1];
    int newKey;
    while (!treeNodeLocal->leaf) {
        treeNodeLocal = treeNodeLocal->children[0];
    }
    if (treeNodeLocal->count > treeGrade - 1) {
        newKey = treeNodeLocal->movieNode[0]->key;
        removeFromNode(newKey, treeNodeLocal);
        treeNode->movieNode[position] = treeNodeLocal->movieNode[0];
    } else {
        treeNodeLocal = treeNode;
        treeNodeLocal = treeNodeLocal->children[position];
        while (!treeNodeLocal->leaf) {
            treeNodeLocal = treeNodeLocal->children[treeNodeLocal->count];
        }
        newKey = treeNodeLocal->movieNode[treeNodeLocal->count - 1]->key;
        treeNode->movieNode[position] = treeNodeLocal->movieNode[treeNodeLocal->count - 1];
        if (treeNodeLocal->count > (treeGrade - 1)) {
            removeFromNode(newKey, treeNodeLocal);
        } else {
            removeLeaf(newKey, treeNodeLocal);
        }
    }
}

//Функция удаления узла в дереве
void BalancedSearchTree::removeFromNode(int key, BalancedTreeNode *node) {
    for (int i = 0; i < node->count; i++) {
        if (node->movieNode[i]->key == key) {
            for (int j = i; j < node->count; j++) {
                node->movieNode[j] = node->movieNode[j + 1];
                node->children[j] = node->children[j + 1];
            }
            node->movieNode[node->count - 1] = nullptr;
            node->children[node->count - 1] = node->children[node->count];
            node->children[node->count] = nullptr;
            break;
        }
    }
    node->count--;
}

//Функция удаления узла в дереве
void BalancedSearchTree::removeLeaf(int key, BalancedTreeNode *node) {
    if ((node == rootTreeNode) && (node->count == 1)) {
        removeFromNode(key, node);
        rootTreeNode->children[0] = nullptr;
        delete rootTreeNode;
        rootTreeNode = nullptr;
        return;
    }
    if (node == rootTreeNode) {
        removeFromNode(key, node);
        return;
    }
    if (node->count > (treeGrade - 1)) {
        removeFromNode(key, node);
        return;
    }
    BalancedTreeNode *pTreeNode = node;
    MovieNode *k1;
    MovieNode *k2;
    int positionSon;
    for (int i = 0; i <= node->count - 1; i++) {
        if (key == node->movieNode[i]->key) {
            break;
        }
    }
    BalancedTreeNode *parent = pTreeNode->parent;
    for (int j = 0; j <= parent->count; j++) {
        if (parent->children[j] == pTreeNode) {
            positionSon = j;
            break;
        }
    }
    if (positionSon == 0) {
        if (parent->children[positionSon + 1]->count > (treeGrade - 1)) {
            k1 = parent->children[positionSon + 1]->movieNode[0];
            k2 = parent->movieNode[positionSon];
            insertMovieNode(k2, pTreeNode);
            removeFromNode(key, pTreeNode);
            parent->movieNode[positionSon] = k1;
            removeFromNode(k1->key, parent->children[positionSon + 1]);
        } else {
            removeFromNode(key, pTreeNode);
            if (pTreeNode->count <= (treeGrade - 2)) repair(pTreeNode);
        }
    } else {
        if (positionSon == parent->count) {
            if (parent->children[positionSon - 1]->count > (treeGrade - 1)) {
                BalancedTreeNode *temp = parent->children[positionSon - 1];
                k1 = temp->movieNode[temp->count - 1];
                k2 = parent->movieNode[positionSon - 1];
                insertMovieNode(k2, pTreeNode);
                removeFromNode(key, pTreeNode);
                parent->movieNode[positionSon - 1] = k1;
                removeFromNode(k1->key, temp);
            } else {
                removeFromNode(key, pTreeNode);
                if (pTreeNode->count <= (treeGrade - 2)) repair(pTreeNode);
            }
        } else {
            if (parent->children[positionSon + 1]->count > (treeGrade - 1)) {
                k1 = parent->children[positionSon + 1]->movieNode[0];
                k2 = parent->movieNode[positionSon];
                insertMovieNode(k2, pTreeNode);
                removeFromNode(key, pTreeNode);
                parent->movieNode[positionSon] = k1;
                removeFromNode(k1->key, parent->children[positionSon + 1]);
            } else {
                if (parent->children[positionSon - 1]->count > (treeGrade - 1)) {
                    BalancedTreeNode *temp = parent->children[positionSon - 1];
                    k1 = temp->movieNode[temp->count - 1];
                    k2 = parent->movieNode[positionSon -
                                           1];
                    insertMovieNode(k2, pTreeNode);
                    removeFromNode(key, pTreeNode);
                    parent->movieNode[positionSon - 1] = k1;
                    removeFromNode(k1->key, temp);
                } else {
                    removeFromNode(key, pTreeNode);
                    if (pTreeNode->count <= (treeGrade - 2)) repair(pTreeNode);
                }
            }
        }
    }
}

//Функция вывода узла бинарного дерева поиска
void BalancedSearchTree::outputMovieNode(MovieNode node, const std::string &mode) {
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
    } else if (mode == "ONLY_STRING_KEY_b") {
        std::cout << movie.title << " ";
    } else if (mode == "ONLY_INT_KEY_b") {
        auto title = movie.title;
        int key = 0;
        for (int i = 0; i < 20; i++) {
            if (title[i] != '\0') { key += (int) title[i]; }
        }
        std::cout << key << " ";
    }

}

//Функция вывода структуры фильма
void BalancedSearchTree::outputMovie(Movie node) {
    if (node.title != "ERROR" && node.numberReviews >= 0 && node.averageRating >= 0) {
        std::cout << node << std::endl;
    } else {
        std::cout << "ERROR" << std::endl;
    }
}

//Функция вывода всего бинарного дерева поиска
void BalancedSearchTree::outputTree() {
    outputTree(rootTreeNode, 0, "STRING");
}

//Функция вывода части бинарного дерева поиска
void BalancedSearchTree::outputTree(BalancedTreeNode *treeNode, int level, const std::string &mode) {
    if (treeNode) {

        if (mode == "STRING") {
            for (int i = 0; i < level; i++) { std::cout << "                         "; }
            for (int i = 0; i < treeNode->count; i++) {
                outputMovieNode(*(treeNode->movieNode[i]), "ONLY_STRING_KEY_b");
            }
            std::cout << std::endl;
        } else if (mode == "INT") {
            for (int i = 0; i < level; i++) { std::cout << "             "; }
            for (int i = 0; i < treeNode->count; i++) {
                outputMovieNode(*(treeNode->movieNode[i]), "ONLY_INT_KEY_b");
            }
            std::cout << std::endl;
        }
        for (int j = 0; j < treeNode->countSons; j++) {
            outputTree(treeNode->children[j], level + 1, mode);
        }
    }
}

void BalancedSearchTree::checkedSearch(const std::string &movieKey) {
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
        result = " в конце файла";
    }
    std::cout << "Выполнен поиск" + result + "за ";
    printf("%.2f секунд(ы)\n", ((double) end - start) / ((double) CLOCKS_PER_SEC));

}

