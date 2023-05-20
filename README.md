# 五子棋

## 1. 已经完成的功能

1. 五子棋的基本运行逻辑
2. 五子棋的判断
3. 界面设计
4. 对弈Ai(贪心算法) E算法
5. 对弈Ai版本迭代(α，β剪切树，最大最小树) F算法

## 2. 未完成的功能

1. 排名系统
2. 登入系统(数据库)
3. 聊天功能

## 程序说明

### 接口

1. ```
   extern std::vector<vector<int>> map;          //抽象后的地图
   extern int aiset;                             //ai决策结果
   extern double aiPos, myPos;                   //我方和电脑棋局得分
   ```

2. ```
   vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map是棋盘，-1空，0电脑，1友方
   stack<pair<int, int>> stk;			//用以控制悔棋-待删除
   double myPos = 0, aiPos = 0;		//我方和电脑棋局得分
   ```

### 功能

1. **Ai.cpp**

   #### 功能实现:  

   人机对弈 

   #### 输出接口为 

```
extern int aiset;                             //ai决策结果`
```

#### 输入接口为

```
extern std::vector<vector<int>> map;          //抽象后的地图
```



2. **Score.cpp**

      #### 功能实现：

评价得分和用户等级评价

#### 输出接口为

​     UI界面

#### 输入接口为

```
extern std::vector<vector<int>> map;          //用户实时胜率
```

```
user.txt 文件                                  //用户评价
```



3. **Show.cpp**

#### 功能实现

输出图形化界面



4.**Save.h**

#### 功能实现

存档与读档

#### 输出接口为

```
user.txt 文件                                  //存档
```



#### 输出接口为

```
user.txt 文件                                  //存档
```

3. 参考资料
https://github.com/lihongxun945/myblog 算法思想提纲

https://blog.csdn.net/livingsu/article/details/104536005 qt实现
