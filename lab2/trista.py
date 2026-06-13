n = int(input())
numbers = list(map(int, input().split()))

total = 0

for num in numbers:
    temp = num
    while temp > 0:
        digit = temp % 10
        if digit % 3 == 0:
            total += digit
        temp //= 10

print(total)
