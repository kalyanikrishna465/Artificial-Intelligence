from typing import List,Tuple,Dict, Set
from heapq import heappush , heappop
from collections import deque

graph={
    'A': ['B', 'C', 'E'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F', 'G'],
    'D': ['B'],
    'E': ['A', 'B', 'D'],
    'F': ['C'],
    'G': ['C']
}

heuristic={
    'A': 3,
    'B': 2,
    'C': 1,
    'D': 4,
    'E': 3,
    'F': 2,
    'G': 0
}

weights = {
    ('A', 'B'): 1,
    ('A', 'C'): 2,
    ('B', 'D'): 3,
    ('B', 'E'): 1,
    ('C', 'F'): 4,
    ('D', 'G'): 1,
    ('F', 'G'): 2
}

and_nodes={
    'B'
}

start='A'
goal='G'

oracle_path=['A','C','G']
oracle_cost=3

def british_museum(graph:Dict[str,List[str]],start:str,goal:str)->List[str]:
    all_paths=[]
    
    def find_all_paths(current_path:List[str])->None:
        current_node=current_path[-1]
        
        if current_node==goal:
            all_paths.append(current_path.copy())
            return
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                current_path.append(neighbor)
                find_all_paths(current_path)
                current_path.pop()
    find_all_paths([start])
    return all_paths

def bfs(graph:Dict[str,List[str]],start:str,goal:str)->List[str]:
    queue=deque([[start]])
    
    while queue:
        current_path=queue.popleft()
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                queue.append(new_path)
    return None
                
def dfs(graph:Dict[str,List[str]],start:str,goal:str)->List[str]:
    stack=[[start]]
    
    while stack:
        current_path=stack.pop()
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                stack.append(new_path)
    return None

def hill_climb(graph:Dict[str,List[str]],start:str,goal:str,heuristic:Dict[str,int])->List[str]:
    current_node=start
    path=[current_node]
    
    while current_node!=goal:
        neighbors=graph.get(current_node,[])
        
        if not neighbors:
            return None
        
        best_neighbor=min(neighbors,key = lambda x:heuristic.get(x,float('inf')))
        
        if heuristic.get(best_neighbor,float('inf'))>=heuristic.get(current_node,float('inf')):
            return None
        
        current_node=best_neighbor
        path.append(best_neighbor)
        
    return path

def beam_search(graph:Dict[str,List[str]],start:str,goal:str,heuristic:Dict[str,int],w:int=2)->List[str]:
    current_nodes=[(heuristic[start],[start])]
    
    while current_nodes:
        new_nodes=[]
        
        for h,current_path in sorted(current_nodes)[:w]:
            current_node=current_path[-1]
            
            if current_node==goal:
                return current_path
            
            for neighbor in graph.get(current_node,[]):
                if neighbor not in current_path:
                    new_path=current_path+[neighbor]
                    new_h=sum(heuristic.get(node,0) for node in new_path)
                    heappush(new_nodes,(new_h,new_path))
        current_nodes=new_nodes
    return current_nodes

def best_first(graph:Dict[str,List[str]],start:str,goal:str,heuristic:Dict[str,int])->List[str]:
    pq=[(heuristic[start],[start])]
    
    while pq:
        cost,current_path=heappop(pq)
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                new_cost=heuristic.get(neighbor,0)
                heappush(pq,(new_cost,new_path))
    return None 

def branch_and_bound(graph:Dict[str,List[str]],start:str,goal:str,heuristic:Dict[str,int])->List[str]:
    pq=[(0,[start])]
    
    while pq:
        cost,current_path=heappop(pq)
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                new_cost=cost+1
                heappush(pq,(new_cost,new_path))
    return None

def bb_el(graph:Dict[str,List[str]],start:str,goal:str)->List[str]:
    pq=[(0,[start])]
    visited=set()
    
    while pq:
        cost,current_path=heappop(pq)
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        if current_node in visited:
            continue
        
        visited.add(current_node)
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                new_cost=cost+1
                heappush(pq,(new_cost,new_path))
    return None

def bb_he(graph:Dict[str,List[str]],start:str,goal:str,heuristic: Dict[str,int])->List[str]:
    pq=[(heuristic[start],[start])]
    
    while pq:
        cost,current_path=heappop(pq)
        current_node=current_path[-1]
        
        if current_node==goal:
            return current_path
        
        for neighbor in graph.get(current_node,[]):
            if neighbor not in current_path:
                new_path=current_path+[neighbor]
                new_cost=cost+heuristic.get(neighbor,0)
                heappush(pq,(new_cost,new_path))
    return None  

def oracle_search(graph: Dict[str, List[Tuple[str, int]]], start: str, goal: str, oracle_path: List[str], oracle_cost: int) -> List[str]:
    pq = [(0, [start])]
    best_path = oracle_path
    min_cost = oracle_cost
    
    while pq:
        cost, current_path = heappop(pq)
        current_node = current_path[-1]
        
        if current_node == goal:
            if cost < min_cost:
                best_path, min_cost = current_path, cost
            continue  

        neighbors = graph.get(current_node, [])
        
        for neighbor_info in neighbors:
            if isinstance(neighbor_info, tuple) and len(neighbor_info) == 2:
                neighbor, edge_cost = neighbor_info
                if neighbor not in current_path:  
                    new_path = current_path + [neighbor]
                    new_cost = cost + edge_cost
                    if new_cost < min_cost:
                        heappush(pq, (new_cost, new_path))
            else:
                print(f"Unexpected neighbor format: {neighbor_info} for current node: {current_node}")

    return best_path

def oracle_he(graph:Dict[str,list[str]],start: str, goal: str) -> List[str]:
    if oracle_path[0] != start or oracle_path[-1] != goal:
        return None
    return oracle_path


def a_star_search(graph: Dict[str, List[str]], start: str, goal: str, heuristic: Dict[str, int]) -> List[str]:
    pq = [(heuristic[start], 0, [start])]
    
    while pq:
        f_cost, g_cost, current_path = heappop(pq)
        current_node = current_path[-1]
     
        if current_node == goal:
            return current_path
        
        for neighbor in graph.get(current_node, []):
            if neighbor not in current_path:
                new_path = current_path + [neighbor]
                new_g_cost = g_cost + 1  
                new_f_cost = new_g_cost + heuristic.get(neighbor, 0)
                heappush(pq, (new_f_cost, new_g_cost, new_path))

def ao_star(graph: Dict[str, List[str]], start: str, goal: str, heuristic: Dict[str, int], weights: Dict[Tuple[str, str], int], and_nodes: Set[str]) -> List[str]:
    """AO* Search Algorithm"""

    def calculate_cost(node: str, visited: Set[str]) -> Tuple[float, List[str]]:
        # If we've reached the goal node, return 0 cost with only the goal node in path
        if node == goal:
            return 0, [node]

        # Prevent cycles by stopping if node is already in the visited set
        if node in visited:
            return float('inf'), []
        
        # Add the current node to the visited set
        visited.add(node)
        
        # For AND nodes, all children need to be explored
        if node in and_nodes:
            total_cost = 0
            total_path = [node]
            for neighbor in graph.get(node, []):
                cost, path = calculate_cost(neighbor, visited.copy())
                total_cost += cost + weights.get((node, neighbor), 1)
                total_path.extend(path)
            return total_cost, total_path
        
        # For OR nodes, select the child with the minimum cost path
        else:
            min_cost = float('inf')
            best_path = []
            for neighbor in graph.get(node, []):
                cost, path = calculate_cost(neighbor, visited.copy())
                total_cost = cost + weights.get((node, neighbor), 1)
                
                # Update if a better path is found
                if total_cost < min_cost:
                    min_cost = total_cost
                    best_path = [node] + path
            return min_cost, best_path

    # Start the calculation from the start node
    _, path = calculate_cost(start, set())
    return path if path else []


def menu():
    print("1.British Museum Search")
    print("2.Breadth First Search")
    print("3.Depth First Search")
    print("4.Hill Climbing Search")
    print("5.Beam Search")
    print("6.Best First Search")
    print("7.Branch and Bound")
    print("8.Branch and Bound with Extended List")
    print("9.Branch and Bound with Heuristics")
    print("10.Oracle search")
    print("11.Oracle search with Heuristics")
    print("12.A* search")
    print("13.AO* search")
    
    choice=int(input("\nEnter the number of the Algorithm you want to choose : "))
    if choice==1:
        print("You have chosen British museum search")
        bms_path=british_museum(graph,start,goal)
        print("Path: ",bms_path)
        
    elif choice==2:
        print("You have chosen Breadth First search")
        bfs_path=bfs(graph,start,goal)
        print("Path: ",bfs_path)
        
    elif choice==3:
        print("You have chosen Depth First search")
        dfs_path=dfs(graph,start,goal)
        print("Path: ",dfs_path)
        
    elif choice==4:
        print("You have chosen Hill Climbing search")
        hcs_path=hill_climb(graph,start,goal,heuristic)
        print("Path: ",hcs_path)
        
    elif choice==5:
        print("You have chosen Beam search")
        bs_path=beam_search(graph,start,goal,heuristic)
        print("Path: ",bs_path)
        
    elif choice==6:
        print("You have chosen Best First search")
        best_path=best_first(graph,start,goal,heuristic)
        print("Path: ",best_path)
        
    elif choice==7:
        print("You have chosen Branch and Bound search")
        bab=branch_and_bound(graph,start,goal,heuristic)
        print("Path: ",bab)
        
    elif choice==8:
        print("You have chosen Branch and Bound with Extended List search")
        bbel=bb_el(graph,start,goal)
        print("Path: ",bbel)
        
    elif choice==9:
        print("You have chosen Branch and Bound with Heuristics search")
        bbhe=bb_he(graph,start,goal,heuristic)
        print("Path: ",bbhe)
        
    elif choice==10:
        print("You have chosen Oracle search")
        oracle = oracle_search(graph,start, goal,oracle_path,oracle_cost)
        print("Path: ",oracle)
        
    elif choice==11:
        print("You have chosen Oracle search with heuristics")
        oraclehe=oracle_he(graph,start,goal)
        print("Path: ",oraclehe)
    
    elif choice==12:
        print("You have chosen A* search with heuristics")
        astar=a_star_search(graph,start,goal,heuristic)
        print("Path: ",astar)
        
    elif choice==13:
        print("You have chosen AO* search with heuristics")
        aostar=ao_star(graph,start,goal,heuristic,weights, and_nodes)
        print("Path: ",aostar)
        
    else:
        print()
menu()
