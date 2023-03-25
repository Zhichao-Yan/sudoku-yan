//
//  utility.h
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/21.
//

#ifndef utility_h
#define utility_h

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

inline unsigned int random(unsigned int begin, unsigned int end)
{
    assert(end>=begin&&begin>=0); // 用于添加诊断，表达式为false，那么会在stderr上输出诊断信息，并且中止程序运行
    srand((unsigned int)time(0));// 时间种子随机初始化
    return (unsigned int)rand()%(end-begin+1)+begin;
}


// system() is used to invoke an operating system command from a C/C++ program.
inline void cls(void)
{
#ifdef _WIN32
    system("cls"); // cls是window终端清屏命令
#else
    system("clear"); // clear是Unix终端的清屏命令
#endif
    
}


/*
 conio.h是Console Input/Output（控制台输入输出）的简写，
 其中定义了通过控制台进行数据输入和数据输出的函数，
 主要是一些用户通过按键盘产生的对应操作，比如getch()函数等等。
*/
#ifdef _WIN32
#include <conio.h>
#else
    #ifdef __linux__
    #include <termio.h>
    #include <cstdio>
    #elif __APPLE__
    #include <termios.h>
    #endif
    inline char getch(void)
    {
        struct termios tmtemp, tm;
        char c;
        int fd = 0;
        if (tcgetattr(fd, &tm) != 0)
        { /*获取当前的终端属性设置，并保存到tm结构体中*/
            return -1;
        }
        tmtemp = tm;
        cfmakeraw(&tmtemp); /*将tetemp初始化为终端原始模式的属性设置*/
        if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
        { /*将终端设置为原始模式的设置*/
            return -1;
        }
        c = getchar();
        if (tcsetattr(fd, TCSANOW, &tm) != 0)
        { /*接收字符完毕后将终端设置回原来的属性*/
            return 0;
        }
        return c;
    }
#endif


#endif /* utility_h */

