// Online C++ compiler to run C++ program online
#include <iostream>
#include <utility>
#include <vector>
#include <climits>

using namespace std;
int map[500][500];
int N, M;

// 각 도형별 가능한 모양 정리
vector<vector<pair<int, int>>> straight_tetros = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}}};

vector<vector<pair<int, int>>> square_tetros = {
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}}; 

vector<vector<pair<int, int>>> T_tetros = {
    {{0, 0}, {0, 1}, {0, 2}, {-1, 1}}, 
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, 
    {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, 
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}}}; 

vector<vector<pair<int, int>>> skew_tetros = {
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 
    {{0, 0}, {0, 1}, {-1, 1}, {-1, 2}}, 
    {{0, 0}, {1, 0}, {-1, 1}, {0, 1}}, 
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}}}; 

vector<vector<pair<int, int>>> L_tetros = {
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}}, 
    {{0, 0}, {0, 1}, {0, 2}, {1, 0}}, 
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {-1, 2}},
    {{0, 0}, {-2, 1}, {-1, 1}, {0, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {1, 2}}};

int calculate_max_score(vector<vector<pair<int, int>>> tetros);
bool check(vector<pair<int, int>> idx_arr);  
int main() {
    // Map 입력
    cin >> N >> M;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
    
    int result1 = calculate_max_score(straight_tetros);
    int result2 = calculate_max_score(square_tetros);
    int result3 = calculate_max_score(T_tetros);
    int result4 = calculate_max_score(skew_tetros);
    int result5 = calculate_max_score(L_tetros);
    
    // 최댓값 계산
    int results[5] = {result1, result2, result3, result4, result5};
    int max = INT_MIN;
    for (int i = 0; i < 5; i++) {
        if (results[i] > max)
            max = results[i];
    }
    
    cout << max << endl;

    return 0;
}

int calculate_max_score(vector<vector<pair<int, int>>> tetros){
    int max = INT_MIN;
    for (int i = 0; i < tetros.size(); i++) {
        vector<pair<int, int>> tetro = tetros[i];
        
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                // tetro 인덱스 계산
                pair<int, int> idx1 = {j + tetro[0].first, k + tetro[0].second};
                pair<int, int> idx2 = {j + tetro[1].first, k + tetro[1].second};
                pair<int, int> idx3 = {j + tetro[2].first, k + tetro[2].second};
                pair<int, int> idx4 = {j + tetro[3].first, k + tetro[3].second};
                vector<pair<int, int>> idx_arr = {idx1, idx2, idx3, idx4};
                // 인덱스 유효성 검사
                if (check(idx_arr)){
                    int score = map[idx1.first][idx1.second] + map[idx2.first][idx2.second] + map[idx3.first][idx3.second] + map[idx4.first][idx4.second];
                    
                    if (score > max)
                        max = score;
                }
            }
        }
    }
    
    return max;
}

bool check(vector<pair<int, int>> idx_arr) {
    // 좌표가 map을 넘어가지 않는 지 확인
    for (int i = 0; i < idx_arr.size(); i++) {
        int y = idx_arr[i].first;
        int x = idx_arr[i].second;
        
        if (y < 0 || y >= N || x < 0 || x >= M) {
            return false;
        }
    }
    // 모든 좌표가 유효하면 true
    return true;
    
}