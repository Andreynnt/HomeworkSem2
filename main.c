
#include "read.h"
#include "menu.h"


int main() {
    //сохраням из файла в хэш таблицу
    saveBooks("books.csv", library);
    //вывод меню
    show_menu();
    //удаляем библиотеку
    deleteLibrary(library);
    return 0;
}