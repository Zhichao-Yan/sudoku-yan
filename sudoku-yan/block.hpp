//
//  block.hpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/22.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <cassert>
#include <iostream>
#include "common.h"
#include "color.h"

class CBlock{
    static const int kMaxCount=9;
public:
    CBlock();
    bool IsValid() const;
    bool IsFull() const;
    void Print() const;
    void PushBack(PointValue *point); // 将一个PointValue指针放入block
private:
    int count_; // 包含的值个数
    PointValue* numbers_[kMaxCount]; // 该模块实际保存的map_指针
};
#endif /* block_hpp */
