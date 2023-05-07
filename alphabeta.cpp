#include "include.h"

const int INF = 1000000000000;
const int MAXN = 18;  // 棋盘大小
const int MAXM = 324;  // 棋盘格子数
extern std::vector<vector<int>> map;          //抽象后的地图
extern int aiset;                             //ai决策结果
extern double aiPos, myPos;                   //我方和电脑棋局得分



// 评估一个棋盘的得分值
int Get_Points(vector<vector<int>>& map, int player);

// 判断五子棋棋局是否结束
bool Is_Game_Over(vector<vector<int>>& map, int player);

int Get_Points(int x, int y, int player, const vector<vector<int>>& map);

// 递归搜索函数

// Zobrist哈希
unsigned long long zobrist_hash[MAXM][3];
unsigned long long zobrist_key = 0;

// Zobrist哈希初始化
void Zobrist_Init() {
    srand(time(NULL));
    for (int i = 0; i < MAXM; i++) {
        for (int j = 0; j < 3; j++) {
            zobrist_hash[i][j] = ((unsigned long long)rand() << 32) | rand();
        }
    }
    zobrist_key = ((unsigned long long)rand() << 32) | rand();
}

// 计算当前棋盘的哈希值
unsigned long long Zobrist_Hash(vector<vector<int>>& map) {
    unsigned long long res = 0;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (map[i][j] != -1) {
                int k = (map[i][j] == 0) ? 0 : 1;
                res ^= zobrist_hash[i * MAXN + j][k];
            }
        }
    }
    res ^= zobrist_key;
    return res;
}

// αβ剪枝函数
int AlphaBeta(vector<vector<int>>& map, int depth, int alpha, int beta, bool max_player, int& best_x, int& best_y, unordered_map<unsigned long long, int>& cache) {
    unsigned long long hash_value = Zobrist_Hash(map);
    if (cache.count(hash_value) > 0) 
    {
        return cache[hash_value];
    }

    if (depth == 0 || Is_Game_Over(map, 0) || Is_Game_Over(map, 1)) 
    {
        return Get_Points(best_x, best_y, max_player ? 0 : 1, map);
    }

    int n = map.size();
    int m = map[0].size();
    int best_score = max_player ? INT_MIN : INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == -1) {
                map[i][j] = max_player ? 0 : 1;
                int score = AlphaBeta(map, depth - 1, alpha, beta, !max_player, best_x, best_y, cache);
                map[i][j] = -1;
                if (max_player) {
                    if (score > best_score) {
                        best_score = score;
                        best_x = i;
                        best_y = j;
                        alpha = max(alpha, best_score);
                        if (alpha >= beta) {
                            return best_score;
                        }
                    }
                }
                else {
                    if (score < best_score) {
                        best_score = score;
                        best_x = i;
                        best_y = j;
                        beta = min(beta, best_score);
                        if (beta <= alpha) {
                            return best_score;
                        }
                    }
                }
            }
        }
    }
    cache[hash_value] = best_score;
    return best_score;
}

// 判断五子棋棋局是否结束
bool Is_Game_Over(vector<vector<int>>& map, int player)
{
    int n = map.size();
    int m = map[0].size();

    // 横向检查
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m - 5; j++) {
            bool flag = true;
            for (int k = 0; k < 5; k++) {
                if (map[i][j + k] != player) 
                {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
    }

    // 纵向检查
    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j < m; j++) {
            bool flag = true;
            for (int k = 0; k < 5; k++) {
                if (map[i + k][j] != player) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
    }

    // 正对角线检查
    for (int i = 0; i <= n - 5; i++) {
        for (int j = 0; j <= m - 5; j++) {
            bool flag = true;
            for (int k = 0; k < 5; k++) {
                if (map[i + k][j + k] != player) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
    }

    // 反对角线检查
    for (int i = 4; i < n; i++) {
        for (int j = 0; j <= m - 5; j++) {
            bool flag = true;
            for (int k = 0; k < 5; k++) {
                if (map[i - k][j + k] != player) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
    }

    return false;
}

int Get_Points(int x, int y, int player, const vector<vector<int>>& map){
    int n = map.size();
    int m = map[0].size();
    int dx[4] = { 0, 1, 1, 1 };
    int dy[4] = { 1, 1, 0, -1 };
    int score = 0;
    for (int k = 0; k < 4; k++) {
        int count = 1;
        bool blocked1 = false;
        bool blocked2 = false;
        for (int step = 1; step < 5; step++) {
            int new_x = x + step * dx[k];
            int new_y = y + step * dy[k];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || map[new_x][new_y] == (player ^ 1)) {
                blocked1 = true;
                break;
            }
            if (map[new_x][new_y] == -1) {
                blocked2 = true;
                break;
            }
            count++;
        }
        for (int step = 1; step < 5; step++) {
            int new_x = x - step * dx[k];
            int new_y = y - step * dy[k];
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || map[new_x][new_y] == (player ^ 1)) {
                blocked1 = true;
                break;
            }
            if (map[new_x][new_y] == -1) {
                blocked2 = true;
                break;
            }
            count++;
        }
        if (!blocked1) {
            if (count == 5) {
                score += 10000;
            }
            else if (count == 4) {
                if (!blocked2) {
                    score += 5000;
                }
                else {
                    score += 50;
                }
            }
            else if (count == 3) {
                if (!blocked2) {
                    score += 1000;
                }
                else {
                    score += 5;
                }
            }
            else if (count == 2) {
                if (!blocked2) {
                    score += 10;
                }
            }
        }
    }
    return score;
}

