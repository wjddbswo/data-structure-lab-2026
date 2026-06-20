from collections import deque

A = {
    0: [1, 2, 3],
    1: [0, 4, 5],
    2: [0, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    # TODO : BFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.
    """
    너비 우선 탐색으로 탐색한다.
    시작 노드(0번)에서 가까운 노드부터 방문한다.
    먼저 발견한 노드를 먼저 처리해야 하므로 FIFO 구조인 deque를 사용한다.
    같은 깊이의 이웃이 여러 개일 때는 더 작은 번호부터 방문해야 하므로
    각 노드의 인접 리스트를 오름차순 정렬한 뒤 큐에 넣는다.
    """
    answer = []
    start = 0
    visited = {start} # 큐에 넣은 노드
    queue = deque([start])

    while queue:
        node = queue.popleft() #FIFO
        answer.append(node) 

        for neighbor in sorted(A[node]):    # 작은 순으로 큐에 저장
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return answer


def dfs(A):
    # TODO : DFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.
    """
    깊이 우선 탐색으로 탐색한다.
    시작 노드에서 갈 수 있는 한 끝까지 내려간 뒤,
    더 갈 곳이 없으면 직전 갈림길로 되돌아와 다른 경로를 탐색한다.
    한 노드에서 여러 이웃으로 갈라질 때는 더 작은 번호부터 내려가야 하므로
    인접 리스트를 sorted()로 정렬한다.
    """
    start = 0
    answer = []
    visited = set()

    def _visit(node):
        """재귀적으로 node를 방문하고, 방문하지 않은 이웃으로 우선 진입한다."""
        visited.add(node)
        answer.append(node)

        for neighbor in sorted(A[node]):
            if neighbor not in visited:
                _visit(neighbor)

    _visit(start)
    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')

