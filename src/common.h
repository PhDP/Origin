#ifndef COMMON_H_
#define COMMON_H_

// The initial capacity of vectors
#ifndef VECTOR_INIT_CAPACITY
#define VECTOR_INIT_CAPACITY 32
#endif

// The rate of growth of vectors
#ifndef VECTOR_GROW_RATE
#define VECTOR_GROW_RATE 2
#endif

// The initial capacity of lists in graphs
#ifndef GRAPH_INIT_CAPACITY
#define GRAPH_INIT_CAPACITY 16
#endif

// The character to use as separator for int_with_space and long_with_space
#ifndef UTILS_SEPARATOR 
#define UTILS_SEPARATOR ' '
#endif

#ifndef NULL
#define NULL 0
#endif

#endif
