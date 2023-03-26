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
    Command(CScene* owner);
    Command(CScene *owner, const Point &point, int pre_value, int cur_value);
    Command(const Command &);
    ~Command();
    Point GetPoint() { return point_;}
    int GetPreValue() { return pre_value_; }
    int GetCurValue() { return cur_value_; }
    bool execute(int inputvalue);
    void undo();
private:
    CScene* owner_; // 指针
    Point point_; // 执行命令的坐标
    int pre_value_; // 命令执行前该点的值
    int cur_value_;  // 命令执行后该点的值
};
#endif /* command_hpp */
