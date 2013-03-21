//
//  Stopwatch.h
//  memoCraft
//
//  Created by memo on 12/02/13.
//  Copyright (c) 2013 memo. All rights reserved.
//

#ifndef memoCraft_Stopwatch_h
#define memoCraft_Stopwatch_h

#include <sys/time.h>
#ifdef _WIN32
#include <stdint.h>
#endif

class Stopwatch {
    struct timeval start_;
    struct timeval stop_;
public:
    Stopwatch(){}
    void start(){gettimeofday(&start_, NULL);}
    void stop(){gettimeofday(&stop_, NULL);}

#ifdef __APPLE__
    int64_t elapsed_ms()const{ // milliseconds
        //printf("stop:%d start:%d\n",stop_.tv_usec,start_.tv_usec);
        return (stop_.tv_sec - start_.tv_sec)*1000+(stop_.tv_usec - start_.tv_usec)/1000;
    }

#endif
#ifdef __linux__
    __int64_t elapsed_ms()const{ // milliseconds
        //printf("stop:%d start:%d\n",stop_.tv_usec,start_.tv_usec);
        return (stop_.tv_sec - start_.tv_sec)*1000+(stop_.tv_usec - start_.tv_usec)/1000;
    }

#endif
#ifdef _WIN32
    int64_t elapsed_ms()const{ // milliseconds
        //printf("stop:%d start:%d\n",stop_.tv_usec,start_.tv_usec);
        return (stop_.tv_sec - start_.tv_sec)*1000+(stop_.tv_usec - start_.tv_usec)/1000;
    }

#endif


#ifdef __APPLE__
    double mps(const int64_t numOp)const{return (double)(numOp)/((stop_.tv_sec - start_.tv_sec)*1000000+(stop_.tv_usec-start_.tv_usec));}
#endif
#ifdef __linux__
    double mps(const __int64_t numOp)const{return (double)(numOp)/((stop_.tv_sec - start_.tv_sec)*1000000+(stop_.tv_usec-start_.tv_usec));}
#endif

#ifdef _WIN32
    double mps(const int64_t numOp)const{return (double)(numOp)/((stop_.tv_sec - start_.tv_sec)*1000000+(stop_.tv_usec-start_.tv_usec));}
#endif


};

#endif
