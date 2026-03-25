#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

int N, M;
int map[50][50];

// bfs
int visited[50][50]; // 0: 방문 x, 1: 방문 o
int dist[50][50]; // 거리

int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

vector<int> distances;

vector<pair<int, int>> house_idxs;
vector<pair<int, int>> chicken_idxs;

void remove_chicken(int cnts, int remove_size, int start_idx);
void visited_initialize();
void dist_initialize();
int bfs(int y, int x);

int main() {
    
    // Input
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    
    // 1, 2 위치 구해놓기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 1)
                house_idxs.push_back(make_pair(i, j));
            else if (map[i][j] == 2)
                chicken_idxs.push_back(make_pair(i, j));
        }
    }
    
    // N - M 개만큼 chicken집 제거 후 각 집마다 bfs 실행
    remove_chicken(0, chicken_idxs.size() - M, 0);
    
    // 최솟값 반환
    cout << *min_element(distances.begin(), distances.end()) << endl;
    
    return 0;
}

void remove_chicken(int cnts, int remove_size, int start_idx) {
    if (cnts == remove_size) {
        int results = 0;
        for (int i = 0; i < house_idxs.size(); i++) {
            int hy = house_idxs[i].first;
            int hx = house_idxs[i].second;
            int min = INT_MAX;
            for (int j = 0; j < chicken_idxs.size(); j++) {
                int cy = chicken_idxs[j].first;
                int cx = chicken_idxs[j].second;
                if (map[cy][cx] == 2) {
                    int dist = abs(cy-hy) + abs(cx-hx);
                    if (dist < min)
                        min = dist;
                }
            }
            results += min;
        }
        distances.push_back(results); // 도시의 치킨 거리 저장
        return;
    }

    for (int i = start_idx; i < chicken_idxs.size(); i++) {
        int cy = chicken_idxs[i].first;
        int cx = chicken_idxs[i].second;
        map[cy][cx] = 0; 
        remove_chicken(cnts + 1, remove_size, i + 1);
        map[cy][cx] = 2; // map 원상복구
    }
}