//
//  input.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/21.
//


#include "input.hpp"

InputMode InputKeyboardMode()
{
    std::string mode;
    InputMode md;
    do{
        std::cout <<"选择按键模式：1-正常 2-VIM " << std::endl;
        std::cout <<"设置模式:";
        std::cin >> mode;
        try{
            md = static_cast<InputMode>(std::stoi(mode));
            break;
        }catch(...){
            std::cout << "输入错误！" << std::endl;
        }
    }while(true);
    return md;
}

int InputDiffculty()
{
    cls();
    std::string cmd;
    int grids=0;// 需要去除的
    while(true)
    {
        std::cout << "难度等级：1-简单 2-普通 3-困难" << std::endl;
        std::cout << "设置难度：";
        std::cin  >> cmd;
        
        try{
            Difficulty d=static_cast<Difficulty>(std::stoi(cmd)); // 强制类型转换成枚举类型
            switch(d)
            {
                case Difficulty::EASY:
                    grids = 20;
                    break;
                case Difficulty::NORMAL:
                    grids = 35;
                    break;
                case Difficulty::HARD:
                    grids = 50;
                    break;
            }
        }catch(...){ // 接受所有异常
            grids=0;
        }
        if(grids > 0)
            break;
        std::cout << "输入出错！" << std::endl;
    }
    return grids;
}
