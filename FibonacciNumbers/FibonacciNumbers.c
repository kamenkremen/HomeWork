#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int recursiveFibonacci(const int numberOfFibonacciNumber)
{
    if (numberOfFibonacciNumber == 1)
    {
        return 0;
    }
    if (numberOfFibonacciNumber <= 3)
    {
        return 1;
    }
    return recursiveFibonacci(numberOfFibonacciNumber - 1) + recursiveFibonacci(numberOfFibonacciNumber - 2);
}

int iterativeFibonacci(const int numberOfFibonacciNumber)
{
    if (numberOfFibonacciNumber <= 2)
    {
        return numberOfFibonacciNumber - 1;
    }
    int firstNumber = 0;
    int secondNumber = 1;
    int thirdNumber = 1;
    for (int currentNumber = 3; currentNumber < numberOfFibonacciNumber; currentNumber++)
    {
        firstNumber = secondNumber;
        secondNumber = thirdNumber;
        thirdNumber = firstNumber + secondNumber;
    }
    return thirdNumber;
}

void testDifferenceBetweenRecursiveAndIterativeMethod()
{
    // тест для итеративного алгоритма вычисления
    {
        int iForTest = 10000;
        clock_t timeBeforeTest = clock();
        int fibonacciNumber = iterativeFibonacci(iForTest);
        printf("AMOUGS %d\n", fibonacciNumber);
        clock_t timeAfterTest = clock();
        double duration = (double)(timeAfterTest - timeBeforeTest) / CLOCKS_PER_SEC;
        printf("Iterative algorithm for finding the %d Fibonacci number works for %2.20fs\n", iForTest, duration);
    }
    // даже с 10000 работает так быстро, что человеку не заметно
    // тест для рекурсивного вычисления
    for (int i = 38; i <= 42; i++)
    {
        clock_t timeBeforeTest = clock();
        int fibonacciNumber = recursiveFibonacci(i);
        clock_t timeAfterTest = clock();
        double duration = (double)(timeAfterTest - timeBeforeTest) / CLOCKS_PER_SEC;
        printf("Recursive algorithm for finding the %d Fibonacci number works for %2.20fs\n", i, duration);
    }
    // при 41 время вычислений на моем ноутбуке стабильно больше секунды
    // при 39 время вычислений ~0.5 секунды, что уже становится крайне заметно
}

int main()
{
    int number = 0;
    printf("Enter a number of Fibonacci number what you wish to get:");
    scanf_s("%d", &number);
    printf("%d Fibonacci number = %d", number, iterativeFibonacci(number));
    return 0;
}