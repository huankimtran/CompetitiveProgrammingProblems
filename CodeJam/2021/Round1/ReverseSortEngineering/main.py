import itertools

def Reversort(L):
    cost = 0
    for i in range(len(L)-1):
        j = i
        min_j = L[j]
        for k in range(i, len(L)):
            if L[k] < min_j:
                j = k
                min_j = L[k]
        # Reverse
        rv = L[i:j+1]
        rv.reverse()
        L[i:j+1] = rv
        cost += len(rv)
    return cost

def get_dict():
    d = {}
    for N in range(2, 101):
        L = list(range(1, N+1))
        all_per_list = list(itertools.permutations(L))
        for per_list in all_per_list:
            per_list_i = list(per_list)
            cost = Reversort(list(per_list_i))
            d[(N, cost)] = per_list_i
        print(N)
    return d

if __name__ == '__main__':
    KB = get_dict()
    num_case = int(input())
    for case in range(num_case):
        inp = input().split()
        N = int(inp[0])
        C = int(inp[1])
        if (N, C) in KB:
            print(f'Case #{case + 1}: {" ".join([str(c) for c in KB[(N, C)]])}')
        else:
            print(f'Case #{case + 1}: IMPOSSIBLE')
