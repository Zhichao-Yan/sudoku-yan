//
//  block.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/22.
//

#include "block.hpp"

CBlock::CBlock(): count_(0){}

void CBlock::PushBack(PointValue *point)
{
    assert(nullptr != point);
    numbers_[count_++] = point;
    return;
}
bool CBlock::IsValid() const
{
    assert(kMaxCount == count_); // 如果count_不等于kMaxCount的话进行出错诊断
    for(int i = 0; i < count_; ++i) // 二重循环选择不同的i和j
    {
        for(int j=i+1; j < count_; ++j)
        {
            //如果2个都没被填入，那么暂时无法比较，进行continue
            if(numbers_[i]->value == kNotSelected || numbers_[j]->value == kNotSelected)
                continue;
            // 如果存在两个相同的数值，则不合法
            if(numbers_[i]->value == numbers_[j]->value)
                return false;
        }
    }
    return true;
}

void CBlock::Print() const
{
    std::cout << "\u2503" << " ";
    for (int i = 0; i < count_; ++i)
    {
        PointValue number = *(numbers_[i]);
        if (number.value == 0)
            std::cout << ' ' << " \u2503 ";
        else
        {
            if (number.state == State::ERASED) // 此数为被填入的数需要着色
                std::cout << Color::Modifier(Color::FG_GREEN) << number.value << Color::Modifier(Color::RESET) << " \u2503 ";
            else
                std::cout << number.value << " \u2503 "; // 此数为初始数字直接输出
        }
    }
    std::cout << std::endl;
}
