//
//  common.h
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/22.
//

#ifndef common_h
#define common_h

static const unsigned int kNotSelected = 0; // 代表暂时没有填入，其他1-9代表以及存在的数

enum class Difficulty : int
{
    EASY = 1,
    NORMAL,
    HARD
};
// 键盘输入模式
enum class InputMode : int
{
    NORMAL = 1,
    VIM
};

struct KeyBoard{
    const char ESC = 0x1B;
    const char U = 0x75;
    char UP;
    char LEFT;
    char DOWN;
    char RIGHT;
    const char ENTER = 0x0D;
};
struct Normal : KeyBoard
{
    Normal()
    {
        UP = 0x77;
        LEFT = 0x61;
        DOWN = 0x73;
        RIGHT = 0x64;
    }
};
struct Vim : KeyBoard {
    Vim()
    {
        UP = 0x6B;
        LEFT = 0x68;
        DOWN = 0x6A;
        RIGHT = 0x6C;
    }
};
// 定义了限定作用域的枚举类型，枚举成员在枚举类作用域外不可访问
enum class State : int // 使用int指定这个enum中使用的类型，不指定的话默认限定作用域类型枚举的潜在类型为int
{
    INITED = 0, // 初始化的就有的
    ERASED = 1 // 代表需要被填入的
};

struct Point{
    int x;
    int y;
};

struct PointValue{
    int value;
    State state;
};
#endif /* common_h */
