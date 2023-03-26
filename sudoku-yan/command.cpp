//
//  command.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/23.
//

#include "command.hpp"

Command::Command(CScene *owner):owner_(owner){}

Command::Command(CScene *owner, const Point &point, int pre_value, int cur_value)
:owner_(owner),point_(point),pre_value_(pre_value),cur_value_(cur_value){}

Command::Command(const Command &rhs)
: owner_(rhs.owner_), point_(rhs.point_), pre_value_(rhs.pre_value_), cur_value_(rhs.cur_value_){}

Command::~Command(){}

bool Command::execute(int inputvalue)
{
    if(!owner_) // owner_不存在，前提是这个ower_存在
        return false;
    point_ = owner_->GetCurPoint(); // 获取当前的坐标
    return owner_->SetCurValue(inputvalue, pre_value_);
}
void Command::undo()
{
    if(owner_)
    {
        owner_->SetPointValue(point_, pre_value_); // 给上一个命令操作的点返回之前的值
    }
    return;
}
