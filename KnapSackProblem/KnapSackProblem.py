import copy

#weights = [2, 3.14, 1.98, 5, 3]
#values =  [40, 50, 100, 95, 30]

values =  [100, 40, 95, 50, 30, 32, 14, 30, 16, 6, 1]
weights = [1.98, 2, 5, 3.14, 3, 4, 2, 5, 4, 3, 1]


sack_size = 10

permutations = []

def permutate(max_depth, depth, current):
    if depth == max_depth:
        permutations.append(copy.deepcopy(current))
        return
    
    current[depth] = 0;
    permutate(max_depth, depth + 1, current)

    current[depth] = 1;
    permutate(max_depth, depth + 1, current)

solutions = []

def caclulate(depth, current):
    global weights, values, check_count
    check_count += depth
    # print(current)
    weight = sum([a*b for a,b in zip(current[0:depth],weights[0:depth])])
    value = sum([a*b for a,b in zip(current[0:depth],values[0:depth])])
    return value, weight

def findBruteForce(depth, current):
    global max_depth, max_value, solution, check_count
    if depth == max_depth:
    # possible solution found
        value, weight = caclulate(depth, current)
        if weight <= sack_size and value > max_value:
            max_value = value
            solution = (value, weight, copy.deepcopy(current))
        #solution.append((value, weight, copy.deepcopy(current)))
        return
    
    current[depth] = 0;
    findBruteForce(depth + 1, current)

    current[depth] = 1;
    findBruteForce(depth + 1, current)

memo = { '' : (0, 0)}
def caclulateMemo(depth, current):
    global weights, values, memo, check_count
    if depth == 0:
        return (0.0, 0.0)

    prev_key = ''.join(map(str, current[0:depth-1]))
    new_key = prev_key + str(current[depth-1])

    if prev_key in memo:
        check_count += 1
        memo[new_key] = (memo[prev_key][0] + values[depth-1]*current[depth-1], memo[prev_key][1] + weights[depth-1]*current[depth-1])
    else:
        print(f"not found {key}")
    return memo[new_key]

def findBacktracking(depth, current):
    global max_depth, max_value, solution
    # possible solution found
    value, weight = caclulateMemo(depth, current)
    if weight > sack_size:
        return
    elif depth == max_depth:
        if value > max_value:
            max_value = value
            solution = (value, weight, copy.deepcopy(current))
        return
    
    current[depth] = 0;
    findBacktracking(depth + 1, current)

    current[depth] = 1;
    findBacktracking(depth + 1, current)

def bound(depth):
    return sum(values[depth:len(values)+1])

def findBranchAndBound(depth, current):
    global max_depth, max_value, solution, upbound
    # possible solution found
    value, weight = caclulateMemo(depth, current)
    if weight > sack_size:
        return
    elif depth == max_depth:
        if value > max_value:
            max_value = value
            solution = (value, weight, copy.deepcopy(current))
        return

    if value > upbound:
        upbound = value

    cur_upbound = value + bound(depth)
    if cur_upbound <= upbound:
        return
    
    current[depth] = 0;
    findBranchAndBound(depth + 1, current)

    current[depth] = 1;
    findBranchAndBound(depth + 1, current)


if __name__ == "__main__":
    max_depth = len(weights)

    check_count = 0
    max_value = 0
    solution = []
    current = [0] * max_depth
    findBruteForce(0, current)
    print(solution)
    print(f"number of checks {check_count}")

    check_count = 0
    max_value = 0
    solution = []
    current = [0] * max_depth

    findBacktracking(0, current)
    print(solution)
    print(f"number of checks {check_count}")
    
    for val in zip([a/b for a,b in zip(values,weights)]):
        print(val)

    upbound = 0
    check_count = 0
    max_value = 0
    solution = []
    current = [0] * max_depth

    findBranchAndBound(0, current)
    print(solution)
    print(f"number of checks {check_count}")
