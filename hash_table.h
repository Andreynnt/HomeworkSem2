#ifndef DZ_SEM1_HASH_TABLE_H
#define DZ_SEM1_HASH_TABLE_H

#define HASHSIZE 1024


typedef struct Book {
    char *isbn;
    char *author;
    char *bookName;
    int bookCount;
    int bookAvailable;
    struct Book *next;
} Book;

struct Book *library[HASHSIZE];

unsigned hash(char *s);
Book *lookup(char *s);
Book *install(Book *book);
void deleteLibrary(Book *library[]);
void deleteBook(Book *book);




#endif //DZ_SEM1_HASH_TABLE_H
