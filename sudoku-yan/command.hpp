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
    CScene* owner_;
    Point point_;
    int pre_value_;
    int cur_value_;  // actually the member is never used
};
#endif /* command_hpp */
