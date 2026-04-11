#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int conveyor[200];
vector<int> robot_idxs;
int up_idx;
int down_idx;
int N, K;

void rotate();
void move();
void generate_robot();
bool check();

int main() {
    // 1. 변수 초기화 및 입력
    cin >> N >> K;
    
    for (int i = 0; i < 2 * N; i++) {
        cin >> conveyor[i];
    }

    up_idx = 0;
    down_idx = N-1;
    int curr_stage = 1;

    bool flag = true;
    
    // 2. 시뮬레이션
    while (flag) {
        // 2-1 rotate
        rotate();

        // 2-2. move
        move();
       
        // 2-3. generate_robot
        generate_robot();
        
        // 2-4. check
        flag = check();
        if (!flag) {
            cout << curr_stage << endl;
            return 0;
        }
        
        // 2-5. stage 추가
        curr_stage++;

    }

    return 0;
}

void rotate() {
    // 1. conveyor 회전
    int temp1 = conveyor[0];
    int temp2;
    for (int i = 1; i < 2*N; i++) {
        // swap
        temp2 = conveyor[i];
        conveyor[i] = temp1;
        temp1 = temp2;
    }
    // 마지막은 첫 번째로 이동
    conveyor[0] = temp1;
    
    // 2. robot_idxs ++ 
    for (int i = 0; i < robot_idxs.size(); i++) {
        robot_idxs[i]++;
    }

    // 3. 내리기
    // 첫번째 로봇만 확인하면 됨
    if (robot_idxs.size() > 0) {
        if (robot_idxs[0] == down_idx) {
            robot_idxs.erase(robot_idxs.begin());
        }
    }
}

void move() {
    // 로봇 이동
    for (int i = 0; i < robot_idxs.size(); i++) {
        // 다음 칸에 로봇이 없는지 확인
        // 내구도도 같이 확인 
        int next_idx = robot_idxs[i] + 1;
        // 해당 위치에 로봇이 있거나 / 내구도가 0보다 작거나 같거나 -> pass
        if (find(robot_idxs.begin(), robot_idxs.end(), next_idx) != robot_idxs.end() || conveyor[next_idx] <= 0) {
            continue;
        } else {
            // 로봇도 없고 내구도도 0보다 크면
            conveyor[next_idx]--;
            robot_idxs[i] = next_idx;
        }
        
    }
    // 내리기 + empty check
    if (robot_idxs.size() > 0) {
        if (robot_idxs[0] == down_idx) {
            robot_idxs.erase(robot_idxs.begin());
        }
    }
}

void generate_robot() {
    // 내구도가 0보다 크면 로봇 생성
    if (conveyor[up_idx] > 0) {
        conveyor[up_idx]--;
        robot_idxs.push_back(up_idx);
    }
}

bool check() {
    int cnt = 0;
    for (int i = 0; i < 2*N; i++) {
        if (conveyor[i] == 0) 
            cnt++;
    }
    
    // K개 이상인지 확인
    if (cnt >= K) 
        return false;
    else 
        return true;
}