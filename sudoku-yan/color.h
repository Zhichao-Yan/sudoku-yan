//
//  color.h
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/23.
//

#ifndef color_h
#define color_h

#include <iostream>
namespace Color
{
enum Code
{
    BOLD = 1,
    RESET = 0,
    BG_BLUE = 44,
    BG_DEFAULT = 49,
    BG_GREEN = 42,
    BG_RED = 41,
    FG_BLACK = 30,
    FG_BLUE = 34,
    FG_CYAN = 36,
    FG_DARK_GRAY = 90,
    FG_DEFAULT = 39,
    FG_GREEN = 32,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_CYAN = 96,
    FG_LIGHT_GRAY = 37,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_RED = 91,
    FG_LIGHT_YELLOW = 93,
    FG_MAGENTA = 35,
    FG_RED = 31,
    FG_WHITE = 97,
    FG_YELLOW = 33,
};

class Modifier
{
    Code code;

public:
    Modifier(Code color) : code(color) {}
    // 普通函数作为友员可以定义在类内，但是最好是和类的成员定义在一起
    friend std::ostream & // Modifier类的非成员函数，但是它是友员函数
    operator<<(std::ostream &os, const Modifier &md)
    {
        return os << "\033[" << md.code << "m";
    }
};
// 除了类内部的友员声明，类外部最好友友员的函数声明，同时将该友员函数和类成员一起定义在源文件中
} // namespace Color

#endif /* color_h */
