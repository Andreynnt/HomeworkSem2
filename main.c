
#include "read.h"
#include "menu.h"


int main() {
    saveBooks("books.csv", library);
    show_menu();
    deleteLibrary(library);
    return 0;
}