#ifndef __MACROS_H__
#define __MACROS_H__

#define MALLOC(ptr, elements, type) \
({\
	ptr = NULL;\
	ptr = (type *) malloc(elements * sizeof(type));\
	if(ptr == NULL)\
	{\
		fprintf(stderr, "ERROR::%s:%d:%s: Memory allocation did not complete susccessfully!\n", __FILE__, __LINE__, __func__);\
		return 1;\
	}\
})

#define MALLOC2D(ptr, elements, type) \
({\
	ptr = NULL;\
	ptr = (type **) malloc(elements * sizeof(type *));\
	if(ptr == NULL)\
	{\
		fprintf(stderr, "ERROR::%s:%d:%s: Memory allocation did not complete susccessfully!\n", __FILE__, __LINE__, __func__);\
		return 1;\
	}\
})

#define FREE(ptr) \
({\
	free(ptr);\
	if(ptr == NULL)\
	{\
		fprintf(stderr, "ERROR::%s:%d:%s: Memory deallocation did not complete susccessfully!\n", __FILE__, __LINE__, __func__);\
		return 1;\
	}\
})

#define CHECK_ERROR(error) \
({\
	if(error != 0)\
	{\
		printf("ERROR is %d\n", error);\
		return error;\
	}\
})

#endif //__MACROS_H__

/* sizeof(int) means the size of int type(typically is 8 bytes at 64 bit machine) */
/* sizeof(int *) means the size of pointer type itself(typically is 4 bytes at 64 bit machine) */