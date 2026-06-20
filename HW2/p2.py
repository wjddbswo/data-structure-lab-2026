import sys
from collections import deque

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int, input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
###################################


def count_stages(concerts):
    """
    콘서트장에서 무대공간(0)의 개수를 센다
    아직 방문하지 않은 0을 만나면 개수를 1 늘리고 그 칸에서 연결된 모든 0을 찾는다
    0이 하나도 없으면 0개, 1이 하나도 없으면 전체가 하나의 0이다.
    대각선은 상하죄우 4방향만 이웃으로 취급한다
    """
    n = len(concerts)                    # 행 개수
    m = len(concerts[0]) if n else 0     # 열 개수
    visited = [[False] * m for _ in range(n)]   # 방문 여부
    answer = 0

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]   # 상, 하, 좌, 우

    for i in range(n):
        for j in range(m):
            # 0 이면서 아직 방문 안 한 칸 -> 새로운 무대공간
            if concerts[i][j] == 0 and not visited[i][j]:
                answer += 1
                queue = deque([(i, j)])
                visited[i][j] = True
                while queue:
                    r, c = queue.popleft()
                    for dr, dc in directions:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < n and 0 <= nc < m \
                                and not visited[nr][nc] and concerts[nr][nc] == 0:
                            visited[nr][nc] = True   # 중복 방지
                            queue.append((nr, nc))

    return answer


print(count_stages(concerts))
