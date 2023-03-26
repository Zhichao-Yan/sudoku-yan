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
    void Load(std::string filename);
    void Play();
    Point GetCurPoint(); // 获取当前的点
    int  GetValue(const Point &p); // 获取p点的值
    void SetValue(const Point &p, const int value);
    void SetValue(const int value);
private:
    void Init(); // 将每个格子（共81个）放入相对应的block中。每一个格子对应多个block即行block/列block/方块block
    void EraseGrids();
    void PrintUnderLine(int line = -1) const;
    void Show() const;
    void SetInputMode();
    bool IsCompleted();
    void Save(const std::string filepath); // 保存游戏进度
    bool Available(Point p);
    static const unsigned int kNotSelected = 0; // 代表暂时没有填入，其他1-9代表以及存在的数

private:
    int index_ = 9;
    KeyBoard *boad_; // 代表键盘的输入模式 w-s-a-d / h-j-k-ls 设计成指针，根据对象的值进行操作
    PointValue map_[81]; // 实际保存数独方格的值，共81个方格
    Point cur_point_; // 当前落子点
    CBlock column_blocks_[9]; // 每一个CScene对象有9个列模块，即有9个列
    CBlock row_blocks_[9]; // 每一个CScene对象有9个行模块，即有9个行
    CBlock mini_blocks_[3][3]; // 每一个CScene对象有9个的子模块模块，子模块为3*3的大小
    std::vector<Command> commands_; // 使用过的命令向量，便于回撤
};

#endif /* scene_hpp */
