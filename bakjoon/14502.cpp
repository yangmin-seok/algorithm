// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <climits>
#include <utility>

int N, M;
int map[8][8];
int copy_map[8][8];
int visited[8][8];
int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

using namespace std;

vector<vector<pair<int, int>>> make_combination();
void initialize();
int count_zeros();
void DFS(int y, int x);
int main() {
    // 1. Input 받기
    cin >> N >> M;
    
    // 2. Map 초기화
    // 0: 빈공간, 1: 벽, 2: 바이러스
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    
    // 3. 0 인덱스 좌표 추출 및 3개 조합 vector 생성
    vector<vector<pair<int, int>>> comb = make_combination();
    
    // 3-1. 2 좌표 모두 구해놓기
    vector<pair<int, int>> two_idxs;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 2)
                two_idxs.push_back(make_pair(i, j));
        }
    }
    
    // 4. 각 조합별 안전 영역 크기 구하기
    int max = INT_MIN;
    for (int i = 0; i < comb.size(); i++){
        // 4-1. map 복사 및 방문 초기화
        initialize();
        
        // 4-2. 인덱스 3개 1로 업데이트
        pair<int, int> idx1 = comb[i][0];
        pair<int, int> idx2 = comb[i][1];
        pair<int, int> idx3 = comb[i][2];
        
        copy_map[idx1.first][idx1.second] = 1;
        copy_map[idx2.first][idx2.second] = 1;
        copy_map[idx3.first][idx3.second] = 1;
        
        // 4-3. DFS
        // 모든 2인 좌표에서만 실행
        for (int j = 0; j < two_idxs.size(); j++) {
            int y = two_idxs[j].first;
            int x = two_idxs[j].second;
            DFS(y, x);
        }

        // copy_map 출력
        // 순번도 같이 출력
        // cout << "combination " << i + 1 << endl;
        // for (int j = 0; j < N; j++) {
        //     for (int k = 0; k < M; k++) {
        //         cout << copy_map[j][k] << " ";
        //     }
        //     cout << endl;
        // }
        
        // 4-4. Count 0
        int result = count_zeros();
        
        // 4-5. 최댓값 업데이트
        if (result > max)
            max = result;
    }
    
    cout << max << endl;

    return 0;
}

vector<vector<pair<int, int>>> make_combination() {
    // 1. 0 인덱스 좌표 넣기
    vector<pair<int, int>> zero_idxs;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0)
                zero_idxs.push_back(make_pair(i, j));
        }
    }
    // 2. zero idxs combination
    int size = zero_idxs.size();
    vector<vector<pair<int, int>>> comb;
    pair<int, int> idx1;
    pair<int, int> idx2;
    pair<int, int> idx3;

    for (int i = 0; i < size; i++) {
        idx1 = zero_idxs[i];
        for (int j = i + 1; j < size; j++) {
            idx2 = zero_idxs[j];
            for (int k = j + 1; k < size; k++) {
                idx3 = zero_idxs[k];
                comb.push_back({idx1, idx2, idx3});
            }
        }
    }
    return comb;
}

void initialize() {
    // copy_map 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            copy_map[i][j] = map[i][j];
        }
    }
    
    // 방문 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = 0;
        }
    }
}

int count_zeros() {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (copy_map[i][j] == 0)
                cnt++;
        }
    }
    return cnt;
}
void DFS(int y, int x) {    
    // 방문 처리
    visited[y][x] = 1;
        
    // 인덱스 1 pass
    if (copy_map[y][x] == 1)
        return;
        
    // 빈칸은 바이러스 감염
    if (copy_map[y][x] == 0)
        copy_map[y][x] = 2;
        
    // 상하좌우
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        // 인덱스 초과 확인
        if (ny < 0 || ny >= N || nx < 0 || nx >= M)
            continue;
        if (!visited[ny][nx]) {
            DFS(ny, nx);
        }
    }
}

// backtracking으로 조합 구하기
void wall(int cnt){
    //벽이 3개 세워졌을 때 bfs, 바이러스 퍼뜨림
    if(cnt == 3){
        bfs();
        return;
    }
    //벽을 세움
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            if(tmp[i][j]==0){
                tmp[i][j] = 1;
                wall(cnt+1);
                //기존의 1을 0으로 바꿔줌
                tmp[i][j] = 0;
            }
}