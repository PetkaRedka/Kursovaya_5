#include <iostream>

// Функция подсчета НОД
long long GKD(long long a, long long b) {
  if (a % b == 0)
    return b;
  if (b % a == 0)
    return a;
  if (a > b)
    return GKD(a%b, b);
  return GKD(a, b%a);
}

// Функция подсчета a^((p - 1) / 2) (mod p)
long long Modul(long long base, long long exponent,
                                      long long mod)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
 
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
 
    return x % mod;
}
 
// Считаем значение символя Якоби
int calculateJacobian(long long a, long long n)
{
    if (!a)
        return 0;// (0/n) = 0
 
    int ans = 1;

    // Переход к положительным числам
    if (a < 0)
    {
        a = -a;

        if (n % 4 == 3)
            ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
    }
 
    if (a == 1)
        return ans;// (1/n) = 1
 
    while (a)
    {
        if (a < 0)
        {
            a = -a;// (a/n) = (-a/n)*(-1/n)
            if (n % 4 == 3)
                ans = -ans;// (-1/n) = -1 if n = 3 (mod 4)
        }

        // Избавление от четности
        while (a % 2 == 0)
        {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5)
                ans = -ans;
 
        }
 
        std::swap(a, n);

        // Квадратичный закон взаимности
        if (a % 4 == 3 && n % 4 == 3)
            ans = -ans;
        a = a % n;
 
        if (a > n / 2)
            a = a - n;
 
    }
 
    if (n == 1)
        return ans;
 
    return 0;
}

// Функция проверки на простоту
bool SoloveyStrassen(long long p, int iterations)
{

    if (p < 2)
        return false;
    if (p != 2 && p % 2 == 0)
        return false;
 
    for (int i = 0; i < iterations; i++)
    {
        // Создаем рандомное значение для a (a < n)
        long long a = rand() % (p - 1) + 1; 
        // Вычисляем НОД
        if (GKD(a, p) != 1)
            return false;
        // Считаем Значение символа Якоби
        long long jacobian = (p + calculateJacobian(a, p)) % p;
        // Считаем значение a^((p - 1) / 2) (mod p)
        long long mod = Modul(a, (p - 1) / 2, p);

        // Смотрим на эквивалентность
        if (!jacobian || mod != jacobian)
            return false;
    }
    return true;
}


int main()
{
    int iterations;
    long long number;
    std::cout << "Choose number of iterations: : ";
    std::cin >> iterations;
    std::cout << "Choose your number: ";
    std::cin >> number;

    if (SoloveyStrassen(number, iterations))
        std::cout << number << " - prime (with probability 1 - 2^(-" << iterations << ")" << std::endl;
    else
        std::cout << number << " - composite" << std::endl;

    return 0;
}
