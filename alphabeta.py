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

def alpha_beta(node, depth, alpha, beta, maximizing_player, moves=None):
    if moves is None:
        moves = []
    moves.append((node[0], depth, "MAX" if maximizing_player else "MIN"))

    # Base Case
    if depth == 0 or not node[1]:  # If no children
        return node[0], moves

    if maximizing_player:
        max_eval = float('-inf')
        for child in node[1]:
            eval, child_moves = alpha_beta(child, depth - 1, alpha, beta, False, moves)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break  # Beta cut-off
        return max_eval, moves
    else:
        min_eval = float('inf')
        for child in node[1]:
            eval, child_moves = alpha_beta(child, depth - 1, alpha, beta, True, moves)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break  # Alpha cut-off
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

    # Run Alpha-Beta Pruning
    print("\nRunning Alpha-Beta Pruning...")
    alpha_beta_result, alpha_beta_moves = alpha_beta(root, 3, float('-inf'), float('inf'), True)
    visualize_moves(alpha_beta_moves, "Alpha-Beta")
    print(f"Alpha-Beta Final Value: {alpha_beta_result}")
