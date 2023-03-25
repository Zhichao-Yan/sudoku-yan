//
//  scene.hpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/7.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "utility.h"
#include "common.h"
#include "block.hpp"
#include "input.hpp"
#include "command.hpp"



class Command;

class CScene
{
public:
    CScene(int index = 9);
    virtual ~CScene();
    void Generate();
    void Show() const;
    void Load(std::string filename);
    void Play();
    bool IsCompleted();
    void EraseGrids();
    void SetInputMode();
    
    Point GetCurPoint();
    bool SetCurValue(const int curvalue, int& lastvalue);
    bool SetPointValue(const Point& p, const int value);
private:
    void Init(); // 将每个格子（共81个）放入相对应的block中。每一个格子对应多个block即行block/列block/方块block
    void SetValue(const Point &p, const int value);
    void SetValue(const int value);
    void PrintUnderLine(int line = -1) const;
    void Save(const std::string filepath);
private:
    int index_ = 9;
    KeyBoard *boad_;
    PointValue map_[81];
    Point cur_point_;
    CBlock column_blocks_[9]; // 每一个CScene对象有9个列模块，即有9个列
    CBlock row_blocks_[9]; // 每一个CScene对象有9个行模块，即有9个行
    CBlock mini_blocks_[3][3]; // 每一个CScene对象有9个的子模块模块，子模块为3*3的大小
    std::vector<Command> commands_; // 使用过的命令向量，便于回撤
};

#endif /* scene_hpp */
