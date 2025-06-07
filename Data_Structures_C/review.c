#include <stdio.h>  // printf, sprintf
#include <stdlib.h>  // malloc, free
#include <string.h>  // strcat, memcpy

// documentation on C functions, printf for example
// $ man 3 printf

// all functions are pass by value:
// copy the arg's value into a local variable
// args that are pointers copy the addr, so simulates pass by ref
// array variables "decay" into pointers, so they are always "pass by ref"
//   this is true no matter how the argument is defined in the function signature
void change_strs(char* name, char name_two[]) {
  name[0] = 'x';
  name_two[0] = 'X';
}

// you can give the ints[] a size, but it doesn't really do anything, no enforcement
// you can't return type[] from arrays, but you can return pointers
void change_arrs(int* ints1, int ints2[]) {
  ints1[0] = 100;
  ints2[0] = 200;
}

// macros are text (code) replacements
// if you allocate space on the stack in a function
//   its pointer is automatically freed when the function frame expires
// this macro could be used to write a function that creates an array
//   string, dynamically on the heap, of any type
// char* substr is defined after this macro is run, needs freed
// [buf, buf, ..., buf]
// worst case a double could have like 15 chars per size, so left over from
//   the buf[20] is enough for , whitespace, [, ], etc
#define ARR_STR(arr, size, format, substr) \
  char* substr = (char*) malloc(((20 * size) + 1) * sizeof(char)); \
  { \
    char buf[20]; \
    *substr = '['; \
    *(substr + 1) = '\0'; \
    for (int i = 0; i < size; ++i) { \
      sprintf(buf, format, arr[i]); \
      substr = strcat(substr, buf); \
      substr = strcat(substr, ", "); \
    } \
    char* nptr = strrchr(substr, '\0'); \
    nptr -= 2; \
    *nptr = ']'; \
    ++nptr; \
    *nptr = '\0'; \
  }

// TODO:
//   github repo

// global struct with a function pointer
// you can initialize objects after the definition } (not shown)
struct iarray {
  int* arr;
  void (*add) (struct iarray *, int, int);  // function pointer
};
void add_to_iarray(struct iarray* iarr, int i, int val) {
  iarr->arr[i] = val;
}

// you can define a struct in a function, like inside main() (not shown)
// struct with typedef
// like simple resizing array structure
typedef struct intarray {
  int maxsize;
  int* arr;
  int cur;
  void (*add) (struct intarray*, int);
} IntArray;

static void addint(IntArray* this, int val) {
  
  if (this->cur + 1 < this->maxsize) {
    this->cur++;
    this->arr[this->cur] = val;
  }
  else {
    // increase the size by 10
    this->maxsize += 10;
    int* oldarr = this->arr;
    this->arr = (int*) malloc (this->maxsize * sizeof(int));
    memcpy(this->arr, oldarr, (this->cur + 1) * sizeof(int));
    this->cur++;
    this->arr[this->cur] = val;
    free(oldarr);
  }
}

// static functions are only usable in this file
// must allocate from the heap inside a function
static void IntArraySetInitFields(IntArray* ia) {
  ia->maxsize = 10;
  int* arr = (int*) malloc (10 * sizeof(int)); // garbage vals from heap
  ia->arr = arr;
  ia->cur = -1;
  ia->add = addint;
  
}


// you can only have one main function
int another_main(int argc, const char* argv[]) {
  
  // memory info
  // int is stored in 4 bytes
  // each byte is 8 bits, 2 hex digits
  // stored in little endian: LSB first, so 0xAFEF is in EF AF 00 00 order
 
  
  // normal pointer (on STACK)
  int val = 0xAFEF;
  int *val_ptr = &val;  // addr operator &
  *val_ptr = 0xAAAA;  // assign value by deref
  printf("%d\n", val);  // int value of val variable
  printf("int is %zu bytes\n", sizeof(val));   // %zu is unsigned size_t type
  printf("%p\n", val_ptr);  // addr where 4 is stored
  printf("%d\n", *val_ptr);  // deref ptr for value contained in addr
  
  printf("\n");
  
  // non-char array
  // variable name is a pointer to the first element in the array
  // read and assign by index
  // has pointer arithmetic: int_ptr + 1 = int_ptr + 1 * (1 int in bytes)
  int vals[] = {0, 1, 2, 3, 4, 5};
  vals[0] = 6;
  int first_val = vals[0];
  printf("%p\n", vals);
  printf("%d\n", *vals);  // deref pointer to read 1st val
  printf("%d\n", *(vals + 1));  // deref pointer to read 2nd val
  printf("%p\n", &vals[1]);  // address of the 2nd value in the array
  
  printf("\n");
  
  // char arrays (strings) are similar to arrays
  char name[] = "Ben";  // automatically allocates enough space for a \0
  char name_no_null[3] = "Ben";   // manual allocation may not
  name[1] = 'A';   // can assign value through index
  printf("%s\n", name);   // prints chars up to \0
  printf("%p\n", name);  // addr to the first char, held by name variable
  printf("%c\n", *name);  // deref the addr to the first char val
  printf("%c\n", *(name + 1));  // look at one more char past it
  printf("%p\n", &name[2]);  // addr to the 3rd char
  char* name_two = "Harki";  // create a read only string by pointer

  printf("\n");
  
  // test the functions;
  char another_name[] = "Mags";
  change_strs(name, another_name);
  printf("%s\n", name);
  printf("%s\n", another_name);
  int one[] = {0, 1, 2, 3, 4};
  int two[] = {5, 6, 7, 8, 9};
  change_arrs(one, two);
  
  printf("\n");

  // test the macro
  ARR_STR(one, 5, "%d", iarr_str);  // defines a char* iarr_str
  float fvals[] = {0.1, 0.2, 0.3};
  ARR_STR(fvals, 3, "%f", farr_str);
  printf("%s\n", iarr_str);
  printf("%s\n", farr_str);
  
  printf("\n");
  
  // void* allows some type independent code
  // needs cast before you dereference, but there is ptr arithmetic
  // void* + 1 is one byte forward
  // void* points to one void value or an array of void values
  void *vptr = (void*) one;
  printf("%p\n", vptr);
  printf("%p\n", vptr + 1);
  
  printf("\n");
  
  // test the struct without typedef, no constructor
  // shows reading a field through the struct value with .
  // shows reading a field through a struct pointer with (.,*), and the -> operator
  // also reading the first array value with deref * or []
  int ivals[] = {3, 2, 1, 0};
  struct iarray myiarr = {ivals, add_to_iarray};  // on the stack
  struct iarray* myiarr_ptr = &myiarr;
  printf("%d\n", *(myiarr.arr));  // first value
  printf("%d\n", myiarr.arr[0]);  // first value
  printf("%d\n", *(myiarr_ptr->arr)); // first value
  printf("%d\n", (myiarr_ptr->arr)[0]); // first value
  printf("%d\n", *((*myiarr_ptr).arr) ); // first value
  printf("%d\n", (*myiarr_ptr).arr[0] ); // first value
  
  printf("\n");

  // test the resizing array
  IntArray iarr2;  // garbage
  IntArray *iarr2_ptr = &iarr2;
  IntArraySetInitFields(iarr2_ptr);
  iarr2_ptr->add(iarr2_ptr, 1);
  iarr2_ptr->add(iarr2_ptr, 2);
  iarr2_ptr->add(iarr2_ptr, 3);
  iarr2_ptr->add(iarr2_ptr, 4);
  iarr2_ptr->add(iarr2_ptr, 5);
  iarr2_ptr->add(iarr2_ptr, 6);
  iarr2_ptr->add(iarr2_ptr, 7);
  iarr2_ptr->add(iarr2_ptr, 8);
  iarr2_ptr->add(iarr2_ptr, 9);
  iarr2_ptr->add(iarr2_ptr, 10);
  iarr2_ptr->add(iarr2_ptr, 11);
  
  ARR_STR(iarr2_ptr->arr, iarr2_ptr->cur + 1, "%d", iarr2str);
  printf("%s\n", iarr2str);
  
  printf("\n");
  free(iarr2_ptr->arr);
  free(iarr2str);
  free(iarr_str);
  free(farr_str);
  return 0;
}
