#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int board[100][100]; // 0: 비어있음, 1: 뱀, 2: 사과

bool checkCollision(int y, int x, int N, int board[100][100]);
int main(void) {
    // 배열 크기 N, 사과의 개수 K
    int N, K;
    int L;
    cin >> N >> K;

    // 보드 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0; // 모든 칸을 비어있는 상태로 초기화
        }
    }
    
    // 사과의 위치
    for (int i = 0; i < K; i++){
        int y, x;
        cin >> y >> x;
        board[y-1][x-1] = 2; // 사과 위치 표시
    }

    // 뱀의 방향 변환 횟수 L
    cin >> L;

    // 뱀의 방향 변환 정보: (x초, 방향)
    // (3, D), (15, L)
    vector<pair<int, char>> direction_info;
    
    for (int i = 0; i < L; i++) {
        int t;
        char d;
        cin >> t >> d;
        direction_info.push_back(make_pair(t, d));
    }
    
    // 뱀 위치 놓기
    board[0][0] = 1;
    
    // 움직임 -> time count -> 회전
    int time = 0;
    
    // 동남서북
    int dy[4] = {0, 1, 0, -1};
    int dx[4] = {1, 0, -1, 0};
    
    // 뱀 머리 방향, 좌표
    int cur_dir = 0;
    int dir_idx = 0;
    int head_y = 0;
    int head_x = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(head_y, head_x));
    
    while (true){
        // 0. 시간을 확인하고 회전
        // D: cur_dir++, L: cur_dir-- -> % 4 를 통해서 0~3 맞춰주기
        // pair은 first, second로 접근 가능
        if (direction_info[dir_idx].first == time) {
            if (direction_info[dir_idx].second == 'D') {
                cur_dir = (cur_dir + 1) % 4;
            } else if (direction_info[dir_idx].second == 'L'){
                cur_dir = (cur_dir - 1 + 4) % 4;
            } else {
                return 0;
            }
            dir_idx++; // direction index update
        }
        
        // 1. 몸길이를 늘려 머리를 다음칸에 위치
        int new_y = head_y + dy[cur_dir];
        int new_x = head_x + dx[cur_dir];
        q.push(make_pair(new_y, new_x));
        time++;
        head_y = new_y; // 머리 좌표 업데이트
        head_x = new_x; 
     
        // 2. 벽, 자기자신 몸과 닿았는지 확인
        if (checkCollision(new_y, new_x, N, board)) {
            cout << time << endl;
            return 0;
        }
        // 3. 사과가 있다면 사과가 없어지고 꼬리는 움직이지 않는다.
        if (board[new_y][new_x] == 2)
            board[new_y][new_x] = 1; // 뱀 머리 위치 업데이트
        else {
            // 4. 사과가 없다면 몸길이를 줄여 꼬리가 위치한 칸을 비워준다.
            // 꼬리 위치를 파악하기 위해서는 뱀의 경로를 queue를 통해서 저장하고 있어야함.
            int tail_y;
            int tail_x;
            
            tail_y = q.front().first;
            tail_x = q.front().second;
            q.pop();
            
            board[tail_y][tail_x] = 0;
            board[new_y][new_x] = 1;
        }
    }
    
    return 0;
}
// 2차원 배열을 입력으로 넘겨주기 위해서는 배열의 크기를 명시적으로 지정해야 합니다.
bool checkCollision(int y, int x, int N, int board[100][100]) {
    // 1. 벽과 충돌 체크
    if (y < 0 || x < 0 || y >= N || x >= N)
        return true;
        
    // 2. 자기 자신 몸과 충돌 체크
    if (board[y][x] == 1)
        return true;
    
    return false;
}