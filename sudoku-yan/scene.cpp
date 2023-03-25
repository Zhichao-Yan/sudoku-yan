//
//  scene.cpp
//  sudoku-yan
//
//  Created by zhichao.yan on 2023/3/7.
//

#include "scene.hpp"
CScene::CScene(int index) // 构造函数
    : index_(index)
    , cur_point_({0,0}) //设置当前坐标
{
    Init();
}
CScene::~CScene() // 析构函数
{
    if(boad_) delete boad_;
}
void CScene::Init()
{
    memset(map_, kNotSelected, sizeof(map_));
    for(int col = 0; col < index_; col++)
    {
        CBlock block;
        for(int row = 0; row < index_; row++)
        {
            block.PushBack(map_ + row * 9 + col);
        }
        column_blocks_[col] = block;
    }
    for(int row = 0; row < index_; row++)
    {
        CBlock block;
        for(int col = 0; col < index_; col++)
        {
            block.PushBack(map_ + row * 9 + col);
        }
        row_blocks_[row] = block;
    }
    for(int k= 0; k < index_; ++k)
    {
        CBlock block;
        int x = ( k / 3 ) * 3; // 取得小模块的左上角元素的横坐标
        int y = ( k % 3 ) * 3; // 取得小模块的左上角元素的纵坐标
        for(int i = 0; i < 3; ++i) // 小模块为3*3大小
        {
            for(int j = 0; j < 3; ++j)
            {
                // 取得小模块内元素在大模块的坐标
                int row = x + i;
                int col = y + j;
                block.PushBack(map_ + row * 9 + col);
            }
        }
        mini_blocks_[k/3][k%3] = block;
    }
    return;
}
void CScene::Generate()
{
    // 固定的模版
    // 每一行每一列的字母都没有重复
    static char pattern[10][10] = {
        "ighcabfde",
        "cabfdeigh",
        "fdeighcab",
        "ghiabcdef",
        "abcdefghi",
        "defghiabc",
        "higbcaefd",
        "bcaefdhig",
        "efdhigbca"};
    
    // 产生字母到数字的随机映射，每一次运行都不同
    std::vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    std::unordered_map<char, int> map;
    for(int i=1;i<=9;i++)
    {
        unsigned int pos = random(0,(unsigned int)v.size()-1);
        map[v[pos]] = i;
        v.erase(v.begin()+pos);
    }
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
        {
            Point p={i,j}; // 第i行 第j列
            char c=pattern[i][j];
            SetValue(p, map[c]); // 设置某个位置p的字符对应的整数值
        }
    }
    assert(IsCompleted());
    EraseGrids();
    return;
}
void CScene::EraseGrids()
{
    int n = InputDiffculty(); // n代表随机删除的格子
    PointValue p = {kNotSelected,State::ERASED};
    std::vector<int> v(81);
    for(int i = 0; i < 81; ++i)
    {
        v[i]=i;
    }
    for(int i =0; i < n; ++i)
    {
        unsigned int loc = random(0, (unsigned int)v.size()-1);
        map_[v[loc]] = p;
        v.erase(v.begin()+loc);
    }
}
void CScene::SetInputMode()
{
    InputMode mode=InputKeyboardMode();
    switch (mode) {
        case InputMode::NORMAL:
            boad_= new Normal;
            break;
            
        case InputMode::VIM:
            boad_ = new Vim;
            break;
    }
}
void CScene::Show() const
{
    cls(); // 先清屏
    PrintUnderLine(); // 打印最上方的顶线
    for(int row = 0; row < index_; ++row)
    {
        CBlock block = row_blocks_[row];
        block.Print();
        PrintUnderLine(row);
    }
}
void CScene::PrintUnderLine(int line) const
{
    for(int col = 0; col < 9; col++)
    {
        std::cout << "\u254B" << "\u2501" << ((cur_point_.x == line && cur_point_.y == col)?"^":"\u2501") << "\u2501"; // 会在当前位置的下标线上输出'^'字符
    }
    std::cout << "\u254B" << std::endl;
}
void CScene::Play()
{
    SetInputMode(); // 选择输入键盘模式
    Show(); // 输出显示数独棋盘
    char key = '\0';
    while(1)
    {
        key = getch();
        if (key >= '0' && key <= '9')
        {
            Command com(this); // 利用当前场景指针创建一个命令对象
            if(!com.execute(key - '0' )) // 输入数字字符进行修改
            {
                std::cout << "this number can't be modified." << std::endl;
            }else{
                commands_.push_back(com);
                Show();
                continue;
            }
        }
        if(key == boad_->ESC) // 如果键盘按入了ESC按键
        {
            std::cout << "want to quit now?[Y/N] : " ;
            std::string str;
            std::cin >> str;
            if(str[0] == 'y' || str[1] == 'Y')
            {
                std::cout << "want to save the game?[Y/N] : " ;
                std::cin >> str;
                if(str[0] == 'y' || str[1] == 'Y')
                {
                    std::cout << " Please input the path of the progress file : " << std::endl;
                    std::string path;
                    std::cin >> path;
                    Save(path);
                }
                exit(0);// 退出游戏
            }else{
                std::cout << "continue!!" << std::endl;
            }
        }else if(key == boad_->U)
        {
            if(commands_.empty())
            {
                std::cout << "no more actions to undo!!" << std::endl;
            }else{
                Command& com = commands_.back();
                com.undo();
                commands_.pop_back();
                Show();
            }
        }else if(key == boad_->UP)
        {
            cur_point_.x = (cur_point_.x > 0 ? cur_point_.x-1 : 0);
            Show();
        }else if(key == boad_->DOWN)
        {
            cur_point_.x = (cur_point_.x < 8 ? cur_point_.x+1 : 8);
            Show();
        }else if(key == boad_->RIGHT)
        {
            cur_point_.y = (cur_point_.y < 8 ? cur_point_.y+1 : 8);
            Show();
        }else if(key == boad_->LEFT)
        {
            cur_point_.y = (cur_point_.y > 0 ? cur_point_.y-1 : 0);
            Show();
        }else if(key == boad_->ENTER)
        {
            if(IsCompleted())
            {
                std::cout << "Congradulations! Game finished!!" <<std::endl;
                getchar();
                exit(0);
            }else{
                std::cout << "Sorry! Game not completed!" << std::endl;
            }
        }
    }
    
}
void CScene::SetValue(const Point &p, const int value)
{
    map_[ p.x*9 + p.y ].value = value; // 从二维映射到一维空间
}
void CScene::SetValue(const int value)
{
    SetValue(cur_point_, value); // 设置当前点的值
}

// 设置新值，保留旧值
bool CScene::SetCurValue(const int curvalue, int &lastvalue)
{
    auto v = map_[cur_point_.x * 9 + cur_point_.y];
    if(v.state == State::ERASED)
    {
        lastvalue = v.value;
        SetValue(curvalue);
        return true;
    }else
        return false;
}
// 设置p点的值
bool CScene::SetPointValue(const Point& p, const int value)
{
    auto v = map_[p.x * 9 + p.y];
    if (v.state == State::ERASED) // 原始为空格才可修改
    {
        cur_point_ = p;
        SetValue(value);
        return true;
    }
    else
        return false;
}
Point CScene::GetCurPoint()
{
    return cur_point_;
}

void CScene::Save(const std::string filepath)
{
    std::ofstream out;
    out.open(filepath); // 默认截断打开保存新纪录
    if(out) // 如果打开成功
    {
        for(int i = 0; i < 81; ++i)
        {
            out << map_[i].value << ' ' << static_cast<int>(map_[i].state) << std::endl;
        }
        out << cur_point_.x << ' ' << cur_point_.y <<std::endl;
        for(auto c:commands_)
        {
            Point p = c.GetPoint();
            out << p.x << ' ' << p.y << ' ' << c.GetCurValue() << ' ' << c.GetPreValue() << std::endl;
        }
        out.close();
    }
    
}
void CScene::Load(std::string filename)
{
    std::ifstream in;
    in.open(filename);
    if(in)
    {
        for(int i = 0; i < 81; ++i)
        {
            int state;
            in >> map_[i].value >> state;
            map_[i].state = static_cast<State>(state);
        }
        in >> cur_point_.x >> cur_point_.y;
        while(in)
        {
            Point p;
            int cur_value,pre_value;
            in >> p.x >> p.y >> cur_value >> pre_value;
            commands_.emplace_back(this,p,pre_value,cur_value);
        }
    }
}

bool CScene::IsCompleted()
{
    // 任何一个空格为0，那么它意味着没有被填满
    for(int i = 0; i < 81; i++)
    {
        if(map_[i].value == kNotSelected)
            return false;
    }
    
    // 有效的定义是在其中没有重复的元素
    // 数独的原理就是同一行同一列同一子模块没有重复值
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(!row_blocks_[i].IsValid() || // 检查第i行是否有效
               !column_blocks_[j].IsValid() || // 检查第j列是否有效
               !mini_blocks_[i/3][j/3].IsValid()) // 检查第(i,j)所在的3*3子模块是否有效
                return false;
        }
    }
    return true;
}
