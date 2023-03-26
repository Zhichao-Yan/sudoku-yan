//
//  command.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/23.
//

#include "command.hpp"

Command::Command(){}

Command::Command(const Command &rhs)
: point_(rhs.point_), pre_value_(rhs.pre_value_){}

Command::Command(Point p,int value)
: point_(p),pre_value_(value){}

Command::~Command(){}

void Command::Execute(CScene *S,int value)
{
    point_ = S->GetCurPoint();
    pre_value_ = S->GetValue(point_);
    S->SetValue(value); // 设置当前值为value
}
void Command::Undo(CScene *S)
{
    S->SetValue(point_,pre_value_); // 设置回之前的值
    return;
}
Point Command::GetPoint()
{
    return point_;
}
int Command::PreValue()
{
    return pre_value_;
}