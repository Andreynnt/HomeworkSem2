#ifndef DZ_SEM1_READ_H
#define DZ_SEM1_READ_H

#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

//расширяем видимость структуры book для ост. файлов
extern Book book;


FILE* open_file(char* fileName);
void readBook(char *s, Book *book);
void saveBooks(char* fileName,  Book *library[HASHSIZE]);
void update(Book *library[HASHSIZE]);

void addBook();
int delete();
int showBook();
int compare(const void * x1, const void * x2);
void showLibrary(Book *library[]);
int changeBook();
void countAvailable();
void giveBook();
void takeBook();

#endif //DZ_SEM1_READ_H
