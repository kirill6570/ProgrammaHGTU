fun main() {
    print("Введите натуральное число N = ")
    val N = readLine()!!.toInt()

    var zeros = 0
    var divisor = 5
    while (divisor <= N) {
        zeros += N / divisor
        divisor *= 5
    }

    println("Количество конечных нулей в $N! = $zeros")
}