//
//  main.c
//  Small_Proto_Thread_example
//
//  Created by Arjun Passi on 3/5/14.
//  Copyright (c) 2014 Arjun Passi. All rights reserved.
//

#include "pt-1.3/pt.h"
#include <stdio.h>

static int protothread1_flag, protothread2_flag;

static int
protothread1(struct pt *pt)
{
    
    PT_BEGIN(pt);
    
    while(1)
    {
        PT_WAIT_UNTIL(pt, protothread2_flag != 0);
        printf("ProtoThread 1 is running!\n");
        
        protothread2_flag = 0;
        protothread1_flag = 1;
    }
    
    PT_END(pt);
}

static int
protothread2(struct pt *pt)
{
    PT_BEGIN(pt);
    
    while( 1 )
    {
        protothread2_flag = 1;
        
        PT_WAIT_UNTIL(pt, protothread1_flag != 0);
        printf("ProtoThread 2 is running!\n");
        
        protothread2_flag = 1;
        protothread1_flag = 0;
    }
    
    PT_END(pt);
}

static struct pt pt1, pt2;

int main(int argc, const char * argv[])
{
    
    PT_INIT(&pt1);
    PT_INIT(&pt2);
    
    while(1){
        protothread1(&pt1);
        protothread2(&pt2);
    }
    
    return 0;
}

