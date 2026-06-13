def count_even_length_numbers(numbers):
    count = 0
    for num in numbers:
        if len(str(num)) % 2 == 0:
            count += 1
    return count

def main():
    n = int(input("Введите количество чисел N: "))
    numbers = list(map(int, input("Введите числа через пробел: ").split()))
    
    result = count_even_length_numbers(numbers)
    print(f"числа с чётной длиной: {result}")

if __name__ == "__main__":
    main()
