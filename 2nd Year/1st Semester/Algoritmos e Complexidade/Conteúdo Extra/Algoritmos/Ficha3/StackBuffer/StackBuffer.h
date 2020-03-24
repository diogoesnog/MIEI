#ifndef StackBuffer_h
#define StackBuffer_h

// Linked List Buffer

typedef struct bufferLList *BufferLList;

BufferLList InitLL(void);
int EmptyLL(BufferLList);
void AddLL(BufferLList, int);
int NextLL(BufferLList, int *);
int RemoveLL(BufferLList, int *);
void ClearLL(BufferLList);

// Array Buffer

typedef struct bufferArray *BufferArray;

BufferArray InitArray(int capacity);
int EmptyArray(BufferArray);
void AddArray(BufferArray, int);
int NextArray(BufferArray, int *);
int RemoveArray(BufferArray, int *);
void ClearArray(BufferArray);

#endif 

