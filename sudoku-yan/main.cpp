//
//  main.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/7.
//

#include <iostream>
#include <string>
#include "scene.hpp"

using std::string,std::cout,std::endl;

#define _TEST_ 0
// #define __APPLE__ 1

static void Help() // 运行说明
{
    cout<<endl<<"NAME"<<endl<<"\t Sudoku - a little game in command line"<<endl;
    cout<<endl<<"OPTIONS"<<endl<<"\t -l <path> "<<endl<<"\t   specify path of progress file saved before to load and contine your game, it is optional."<<endl;
    return;
}
// argc是命令行参数个数,指定argv的大小，argv是命令行参数字符串数组，参数以字符串形式保存
// 程序需要在操作系统命令行运行 文件名+实际运行参数
int main(int argc, const char * argv[]) {

#if _TEST_ // 根据宏定义_TEST_判断是否进行测试，默认为0，不测试

    
#else
    CScene Scene;
    if(argc==1) // 默认为1，除了文件名本身没有其他参数
    {
        Scene.Generate();
    }else if(argc==3&&string(argv[1])==string("-l")){ // 带有参数，从之前的保存的文件读取游戏进度
        Scene.Load(argv[2]); // load saved progress file，argv[2]是备份文件的路径
    }else{
        Help(); // 显示帮助
        return 0;
    }
    Scene.Play();
#endif
    return 0;
}
