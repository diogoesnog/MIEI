#ifndef QueueBuffer_h
#define QueueBuffer_h

// LList Buffer

typedef struct lListBuffer *LListBuffer;

LListBuffer InitLL(void);
int EmptyLL(LListBuffer);
int AddLL(LListBuffer, int);
int NextLL(LListBuffer, int *);
int RemoveLL(LListBuffer, int *);
void ClearLL(LListBuffer);


// Array Buffer

typedef struct arrayBuffer *ArrayBuffer;

ArrayBuffer InitArray(int capacity);
int EmptyArray(ArrayBuffer);
int AddArray(ArrayBuffer, int);
int NextArray(ArrayBuffer, int *);
int RemoveArray(ArrayBuffer, int *);
void ClearArray(ArrayBuffer);
void PrintArray(ArrayBuffer);

#endif


