#include "FileControlClass.h"
#include "BinarySearchTree.h"
#include "BalancedSearchTree.h"

using namespace std;

void test() {
    cout << "Линейный поиск в файле" << endl;
    FileControlClass *fileControlClass;
    fileControlClass = new FileControlClass("data.txt");
    fileControlClass->checkedSearch("Sp6lfmtmfK");
    fileControlClass->checkedSearch("k6nv0qHLL8");
    fileControlClass->checkedSearch("zOV4uOLKeW");

    cout << "Поиск по бинарному дереву поиска" << endl;
    BinarySearchTree *binarySearchTree;
    binarySearchTree = new BinarySearchTree();
    binarySearchTree->checkedSearch("Sp6lfmtmfK");
    binarySearchTree->checkedSearch("k6nv0qHLL8");
    binarySearchTree->checkedSearch("zOV4uOLKeW");

    cout << "Поиск по сбалансированному В-дереву" << endl;
    BalancedSearchTree *balancedSearchTree;
    balancedSearchTree = new BalancedSearchTree();
    balancedSearchTree->checkedSearch("Sp6lfmtmfK");
    balancedSearchTree->checkedSearch("k6nv0qHLL8");
    balancedSearchTree->checkedSearch("zOV4uOLKeW");
}

int main() {
    setlocale(LC_ALL, "rus");
    cout
            << "Лабораторная работа №4. Сбалансированные деревья поиска (СДП) и их применение для поиска данных в файле. Писарев Дмитрий"
               "\nВыберите класс для работы с данными:"
               "\n1 - Класс управления файлом;"
               "\n2 - Класс «Бинарное дерево поиска»;"
               "\n3 - Класс «Сбалансированное дерево поиска»;"
               "\n4 - Тестирование времени поиска записей в начале/середине/конце файла для каждого класса;"
               "\n0 - Закончить;\n";
    int classMode;
    int mode;
    cin >> classMode;
    switch (classMode) {
        case 1: {
            FileControlClass *fileControlClass;
            do {
                cout << "Выберите действие:"
                     << "\n1 - Создание двоичного файла записей фиксированной длины из заранее подготовленных данных в текстовом файле;"
                     << "\n2 - Поиск и вывод записи в файле с помощью линейного поиска;"
                     << "\n3 - Вывод записи по известному адресу в файле;"
                     << "\n4 - Добавление записи в файл;"
                     << "\n5 - Вывод содержимого файла;"
                     << "\n0 - Закончить;\n";
                cin >> mode;
                switch (mode) {
                    case 1: {
                        fileControlClass = new FileControlClass("data.txt");
                    }
                        break;
                    case 2: {
                        cout << "Введите ключ в формате {title}: ";
                        string title;
                        cin >> title;
                        fileControlClass->output(fileControlClass->search(title));
                        fileControlClass->checkedSearch(title);
                    }
                        break;
                    case 3: {
                        cout << "Введите адрес в формате {address}: ";
                        int address;
                        cin >> address;
                        fileControlClass->output(fileControlClass->getMovie(address));
                    }
                        break;
                    case 4: {
                        cout << "Введите значения структуры в формате {title numberReviews averageRating}: ";
                        string title;
                        int numberReviews;
                        double averageRating;
                        cin >> title >> numberReviews >> averageRating;
                        Movie movie(title, numberReviews, averageRating);
                        fileControlClass->insert(movie);
                    }
                        break;
                    case 5: {
                        fileControlClass->outputAll();
                    }
                        break;
                    default:
                        break;
                }
            } while (mode != 0);
        }
            break;
        case 2: {
            BinarySearchTree *binarySearchTree;
            do {
                cout << "Выберите действие:"
                     << "\n1 - Построение дерева по существующему файлу;"
                     << "\n2 - Добавление элемента в дерево;"
                     << "\n3 - Поиск по ключу в дереве;"
                     << "\n4 - Удаление элемента из дерева;"
                     << "\n5 - Вывод дерева в форме дерева;"
                     << "\n0 - Закончить;\n";
                cin >> mode;
                switch (mode) {
                    case 1: {
                        binarySearchTree = new BinarySearchTree();
                    }
                        break;
                    case 2: {
                        cout << "Введите значения структуры в формате {title numberReviews averageRating}: ";
                        string title;
                        int numberReviews;
                        double averageRating;
                        cin >> title >> numberReviews >> averageRating;
                        Movie movie(title, numberReviews, averageRating);
                        binarySearchTree->insertMovie(movie);
                    }
                        break;
                    case 3: {
                        cout << "Введите ключ в формате {title}: ";
                        string title;
                        cin >> title;
                        binarySearchTree->outputMovie(binarySearchTree->searchMovie(title));
                        binarySearchTree->checkedSearch(title);
                    }
                        break;
                    case 4: {
                        cout << "Введите ключ в формате {title}: ";
                        string title;
                        cin >> title;
                        binarySearchTree->deleteMovie(title);
                    }
                        break;
                    case 5: {
                        binarySearchTree->outputTree();
                    }
                        break;
                    default:
                        break;
                }
            } while (mode != 0);
        }
            break;
        case 3: {
            BalancedSearchTree *balancedSearchTree;
            do {
                cout << "Выберите действие:"
                     << "\n1 - Построение дерева по существующему файлу;"
                     << "\n2 - Добавление элемента в дерево;"
                     << "\n3 - Поиск по ключу в дереве;"
                     << "\n4 - Удаление элемента из дерева;"
                     << "\n5 - Вывод дерева в форме дерева;"
                     << "\n0 - Закончить;\n";
                cin >> mode;
                switch (mode) {
                    case 1: {
                        balancedSearchTree = new BalancedSearchTree();
                        cout << "Среднее число поворотов при вставке узла в дерево: "
                             << balancedSearchTree->averageRotation << endl;
                    }
                        break;
                    case 2: {
                        cout << "Введите значения структуры в формате {title numberReviews averageRating}: ";
                        string title;
                        int numberReviews;
                        double averageRating;
                        cin >> title >> numberReviews >> averageRating;
                        Movie movie(title, numberReviews, averageRating);
                        balancedSearchTree->insertMovie(movie);
                    }
                        break;
                    case 3: {
                        cout << "Введите ключ в формате {title}: ";
                        string title;
                        cin >> title;
                        balancedSearchTree->outputMovie(balancedSearchTree->searchMovie(title));
                        balancedSearchTree->checkedSearch(title);
                    }
                        break;
                    case 4: {
                        cout << "Введите ключ в формате {title}: ";
                        string title;
                        cin >> title;
                        balancedSearchTree->deleteMovie(title);
                    }
                        break;
                    case 5: {
                        balancedSearchTree->outputTree();
                    }
                        break;
                    default:
                        break;
                }
            } while (mode != 0);
        }
            break;
        case 4: {
            test();
        }
        default:
            break;
    }
    return 0;
}
