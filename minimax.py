def create_game_tree():
    # Represents a tree where each node is [value, [children]]
    return [
        3, [
            [5, [[1, []], [7, []], [4, []]]],
            [2, [[5, []]]],
            [9, [[2, []], [8, []], [3, []]]]
        ]
    ]

def print_tree(node, level=0, prefix="Root: "):
    """Print the tree structure"""
    print("  " * level + prefix + str(node[0]))
    for i, child in enumerate(node[1]):
        print_tree(child, level + 1, f"Child {i + 1}: ")

def minimax(node, depth, maximizing_player, moves=None):
    if moves is None:
        moves = []
    moves.append((node[0], depth, "MAX" if maximizing_player else "MIN"))

    # Base Case
    if depth == 0 or not node[1]:  # If no children
        return node[0], moves

    if maximizing_player:
        max_eval = float('-inf')
        for child in node[1]:
            eval, child_moves = minimax(child, depth - 1, False, moves)
            max_eval = max(max_eval, eval)
        return max_eval, moves
    else:
        min_eval = float('inf')
        for child in node[1]:
            eval, child_moves = minimax(child, depth - 1, True, moves)
            min_eval = min(min_eval, eval)
        return min_eval, moves


def visualize_moves(moves, algorithm_name):
    print(f"\n{algorithm_name} Algorithm Traversal:")
    print("=" * 50)
    print("Format: (Node Value, Depth, Player Type)")
    print("-" * 50)

    for move in moves:
        value, depth, player = move
        print(f"Depth {depth}: {player} evaluates node {value}")

if __name__ == "__main__":
    # Create the game tree
    root = create_game_tree()

    # Print the tree
    print("Game Tree Structure:")
    print_tree(root)

    # Run Minimax
    print("\nRunning Minimax...")
    minimax_result, minimax_moves = minimax(root, 3, True)
    visualize_moves(minimax_moves, "Minimax")
    print(f"Minimax Final Value: {minimax_result}")


