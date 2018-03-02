/*************************************************************************
	> File Name: debug.h
	> Author: 
	> Mail: 
	> Created Time: Mon 18 Sep 2017 11:55:00 AM PDT
 ************************************************************************/

#ifndef _DEBUG_H
#define _DEBUG_H

#include <sys/time.h>
#include <time.h>
#include <stdio.h>


/****************************************************************
            debug in compile time
****************************************************************/
#ifdef TEST_DEF
#warning "TEST_DEF has already defined" 
#endif 

#ifdef PRAGMA_MSG
#pragma message "this is pragma message produced in compile time."
#endif 

#ifdef ERROR_MSG_DEF
#error "if this message is printed out, then the compile process will ended."
#endif 

#ifndef NULL
#define NULL 	((void *)0)
#endif

/*ATTR_UNUSED attribute suppresses the warining -Wunused-but-set-variable*/
#define ATTR_UNUSED		__attribute__ ((unused)) 
#define COMMON_EXTERN	extern

/****************************************************************
            Standard I/O Macros 
****************************************************************/
#define TRACE			puts			/*'\n' will be automatically added in the end of the string.*/
#define DEBUG			printf			/* equals: #define DEBUG printf */

#define debug_info()	                                                    \
do{								                                            \
	printf("-------- Function:%s  File:%s --------\n",__func__, __FILE__);	\
}while(0)

/*Both Dec and Hex Format */
#ifdef DETAIL_DEBUG_INFO /* with detail debug info */

#define debug_str(exp) 		{printf("Debug: "); printf(#exp" = %s, Line:%d, Func:%s, File:%s\n", exp, __LINE__, __func__, __FILE__);}

#define debug_var(exp)	        {printf("Debug: "); \
                                 printf(#exp" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", \
                                 (int)exp, (int)exp, __LINE__, __func__, __FILE__);}
                                            
#define debug_2_var(exp1,exp2)  {printf("Debug: "); \
                                 printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", \
                                 (int)exp1, (int)exp1, (int)exp2, (int)exp2, __LINE__, __func__, __FILE__);}
                                 
#define debug_3_var(exp1,exp2,exp3) (printf("Debug: "), \
                                     printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X), "#exp3" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", \
                                     (int)exp1, (int)exp1, (int)exp2, (int)exp2, (int)exp3, (int)exp3, __LINE__, __func__, __FILE__))
#else /* basic debug info */

#define debug_str(exp) 			{printf("Debug: "); printf(#exp" = %s\n", (char *)exp);}
#define debug_char(exp) 		{printf("Debug: "); printf(#exp" = %c\n", (char)exp);}
#define debug_var(exp)			{printf(#exp" = %d(0x%X)\n", (int)exp, (int)exp);}
#define debug_2_var(exp1,exp2)		{printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X)\n", (int)exp1, (int)exp1, (int)exp2, (int)exp2);}
#define debug_3_var(exp1,exp2,exp3)	(printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X), "#exp3" = %d(0x%X)\n", \
                                     (int)exp1, (int)exp1, (int)exp2, (int)exp2, (int)exp3, (int)exp3))	
#endif

/****************************************************************
            main_parameter_parse 
****************************************************************/
#define main_parameter_parse(argc, argv)	\
do{											\
	static int i = 0;			            \
	DEBUG("NumberOfParameters: %d\n", argc);\
	TRACE("TheInputString: ");				\
	for(i=0; argv[i] != '\0'; i++)		\
	{									\
		DEBUG("%s\n", argv[i]);			\
	}									\
}while(0)


/****************************************************************
            runtime measurement 
****************************************************************/
#define CURRENT_TIME()          \
{                               \
	time_t now;                 \
	time(&now);                 \
	DEBUG("%s", ctime(&now));   \
	return EXIT_SUCCESS;        \
}

#define sec()                   \
{                               \
    	struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_sec % 60);    \
}

#define msec()                  \
{                               \
    	struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_usec/1000);   \
}

#define usec()                  \
{                               \
    	struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_usec);        \
}

#define busy_wait()             \
{                               \
    unsinged int tnow;          \
    unsigned int elapsed;       \
    static int start_time = msec(); \
    do                          \
    {                           \
        tnow = msec();          \
        elapsed = (unsigned int)(tnow - start_time);    \
    } while (elapsed < 2000);                           \
    start_time += 2000;         \
}

#define MEAS_WALL_TIME(funcs)   \
{                               \
    struct timeval ss, ee;      \
    gettimeofday(&ss, NULL);    \
    funcs;                      \
    gettimeofday(&ee, NULL);    \
    double timediff = (double)(ee.tv_sec - ss.tv_sec) + (double)(ee.tv_usec - ss.tv_usec)/1000000000.0; \
    printf("\t Runtime (wall time): %.6f\n", timediff);    \
}

#define MEAS_CPU_TIME(funcs)    \
{                               \
    double ss, ee;              \
    ss = (double)clock()/CLOCKS_PER_SEC;    \
    funcs;                                  \
    ee = (double)clock()/CLOCKS_PER_SEC;    \
    printf("\t Runtime (cpu time): %.6f\n", ee-ss);    \
}

#define RUNTIME_MEAS(func,arg)				\
{											\
    struct timespec ss;						\
    struct timespec ee;						\
    clock_gettime(CLOCK_MONOTONIC, &ss);	\
    func(arg);								\
    clock_gettime(CLOCK_MONOTONIC, &ee);	\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    printf("\t *** Runtime of %s:  %.12f\n", #func, timediff);					\
}

#define MEA_PRE()	\
{                   \
    struct timespec ss;						\
    struct timespec ee;						\
    clock_gettime(CLOCK_MONOTONIC, &ss);	

#define MEA_POST()	\
    clock_gettime(CLOCK_MONOTONIC, &ee);	\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    printf("\t *** Runtime:  %.12f\n", timediff);   \
}
		
#define MEAS_RUNTIME(func_call)	\
	MEA_PRE();		\
	func_call;		\
	MEA_POST();
	
    
#define PRINT_TIMESTAMP()	\
    std::time_t timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());	\
    std::cout << "\t *** timestamp: " << std::ctime(&timestamp_);

/****************************************************************
            FPS measurement 
****************************************************************/
#define PRINT_FPS()						\
{										\
    int fps = 0;					\
    struct timespec ss;			\
    struct timespec ee;					\
    fps++;								\
    clock_gettime(CLOCK_MONOTONIC, &ee);\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    if(timediff > 1)						\
    {										\
    	printf("\t *** FPS = %d\n", fps);	\
    	fps = 0;							\
    	ss.tv_sec = ee.tv_sec;				\
    	ss.tv_nsec = ee.tv_nsec;			\
    }										\
}


#endif
