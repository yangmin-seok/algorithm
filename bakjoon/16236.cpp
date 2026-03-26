/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <map>
#include <utility>
#include <climits>
#include <queue>

using namespace std;

int N;
int space[20][20];
int visited[20][20];
int dist[20][20];
map<pair<int ,int>, int> fish_info; // search: log(n)
int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

// 상어 정보
int shark_y;
int shark_x;
int shark_size = 2;
int eat_count = 0;

// end 정보
int max_time = 0;
bool flag = true;

void initialize();
void BFS();

int main()
{
    // input
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> space[i][j];
            // 상어 좌표 저장
            if (space[i][j] == 9) {
                shark_y = i;
                shark_x = j;
            }
        }
    }

    // fish_info 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 물고기 좌표 저장
            if (space[i][j] != 0 && space[i][j] != 9) {
                fish_info[{i, j}] = space[i][j];
            }
        }
    }

    // BFS
    while (flag) {
        BFS();
    }
    
    cout << max_time << endl;

    return 0;
}

void BFS() {
    // initialize visited, dist
    initialize();
    
    // 시작 좌표를 queue에 넣고 순회 시작
    queue<pair<int, int>> q;
    visited[shark_y][shark_x] = 1;
    q.push(make_pair(shark_y, shark_x));
    
    // dist 배열 update
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
   
        // 상하좌우 search
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            // 인덱스 초과 제외
            if (ny < 0 || ny >= N || nx < 0 || nx >= N)
                continue;
            if (!visited[ny][nx]) {
                // 상어 사이즈 비교, 크기가 크면 지나갈 수 없음
                // 여기서 접근할 때 fish_info가 업데이트가 됨
                if (space[ny][nx] > shark_size) {
                    // 방문처리해두고 넘넘어가기
                    visited[ny][nx] = 1;
                    continue;
                }
                // 방문 처리하고 queue 넣기
                // dist update
                visited[ny][nx] = 1;
                dist[ny][nx] = dist[y][x] + 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    
    // fish_info를 순회하면서 min_dist, min_y, min_x 뽑기
    int min_dist = INT_MAX;
    int min_y = -1;
    int min_x = -1;

    // fish_info 순회하면서 min_dist, min_y, min_x 뽑기
    for (auto it = fish_info.begin(); it != fish_info.end(); ++it) {
        int temp_y = it->first.first;
        int temp_x = it->first.second;
        int temp_size = it->second;
        int temp_dist = dist[temp_y][temp_x];

        if (temp_size == 0)
            continue;
        
        // size가 같다면 넘어가기
        if (temp_size >= shark_size)
            continue;
        else {    
            if (temp_dist == 0)
                continue;
            // size가 작다면 저장
            if (temp_dist < min_dist) {
                min_dist = temp_dist;
                min_y = temp_y;
                min_x = temp_x;
            } else if (temp_dist == min_dist) {
                // 거리가 같으면 y좌표가 작은게 우선
                if (temp_y < min_y) {
                    min_y = temp_y;
                    min_x = temp_x;
                } else if (temp_y == min_y) {
                    //y좌표 까지 같으면 x좌표가 작은게 우선
                    if (temp_x < min_x) {
                        min_y = temp_y;
                        min_x = temp_x; 
                    }
                }
            }
        }
        
    }
    
    // 좌표 업데이트가 없으면 종료
    if (min_y == -1 && min_x == -1) {
        flag = false;
        return;
    }
    
    // time, shark_size
    max_time += min_dist;
    eat_count++;
    
    if (shark_size == eat_count) {
        shark_size++;
        eat_count = 0;
    }
    
    // map update (물고기 제거)
    space[min_y][min_x] = 0;
    
    // fish_info 제거
    fish_info.erase({min_y, min_x});
    
    // 상어 위치 업데이트 
    space[shark_y][shark_x] = 0;
    shark_y = min_y;
    shark_x = min_x;
    space[shark_y][shark_x] = 9;
    return;
}

void initialize() {
    // visited 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }
    // dist 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = 0;
        }
    }
}