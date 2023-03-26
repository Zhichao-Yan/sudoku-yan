//
//  command.hpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/23.
//

#ifndef command_hpp
#define command_hpp

#include <stdio.h>
#include "common.h"
#include "scene.hpp"

// 定义指针或者引用，或者以其作为参数或者返回类型
class CScene; // 申明一个不完全类型

class Command{
public:
    Command();
    Command(const Command &);
    Command(Point p,int value);
    ~Command();
    void Execute(CScene *S,int value);
    void Undo(CScene *S);
    Point GetPoint();
    int PreValue();
private:
    Point point_; // 执行命令的坐标
    int pre_value_; // 命令执行前该点的值
};
#endif /* command_hpp */
