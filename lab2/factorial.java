import java.util.Scanner;

class factorial {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите натуральное число N = ");
        int N = sc.nextInt();
        sc.close();

        int zeros = 0;
        int divisor = 5;
        while (divisor <= N) {
            zeros += N / divisor;
            divisor *= 5;
        }

        System.out.printf("Количество конечных нулей в %d! = %d\n", N, zeros);
    }
}