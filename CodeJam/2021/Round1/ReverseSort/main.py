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

if __name__ == '__main__':
    num_case = int(input())
    for case in range(num_case):
        lenL = int(input())
        L = [int(x) for x in input().split()]
        print(f'Case #{case + 1}: {Reversort(L)}')
