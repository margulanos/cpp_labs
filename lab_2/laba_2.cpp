#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>



//Часть 1. Шейкерная сортировка
void forward_step(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps)
{
    for (unsigned i = begin_idx; i < end_idx; i++)
        if (arr[i] > arr[i + 1])
        {
            std::swap(arr[i], arr[i + 1]);
            swaps++;
        }
}

void backward_step(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps)
{
    for (unsigned i = end_idx; i > begin_idx; i--)
        if (arr[i - 1] > arr[i])
        {
            std::swap(arr[i], arr[i + 1]);
            swaps++;
        }
}

void shaker_sort(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps)
{
    unsigned l = begin_idx;
    unsigned r = end_idx;
    bool swapped = false;
    while (l < r)
    {
        forward_step(arr, l, r, swaps);
        r--;
        backward_step(arr, l, r, swaps);
        l++;
    }
}

void puzyrok(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps)
{
    for (unsigned j = begin_idx; j < end_idx; j++)
        for (unsigned i = begin_idx; i < end_idx - (j - begin_idx); i++)
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swaps++;
            }
}

void test_shaker()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream shaker_mid_file("shaker_mid.txt");
    std::ofstream shaker_swap_file("shaker_swap.txt");
    std::ofstream shaker_check_file("shaker_check.txt");
    std::ofstream N_file("N.txt");
    unsigned progony = 1;
    long long swaps = 0;

    //Проверка сортировки
    unsigned arr_mid[10] = {0};
    for (unsigned i = 0; i < 10; i++)
        arr_mid[i] = i;
    std::shuffle(arr_mid, arr_mid + 10, gen);
    for (unsigned i = 0; i < 10; i++)
        shaker_check_file << arr_mid[i] << ' ';
    shaker_sort(arr_mid, 0, 9, swaps);
    shaker_check_file << '\n';
    for (unsigned i = 0; i < 10; i++)
        shaker_check_file << arr_mid[i] << ' ';
    shaker_check_file.close();

    //Измерение времени
    for (unsigned N = 1000; N <= 100000; N += 1000)
    {
        N_file << N << std::endl;
        
        long long swaps = 0;
        long long time_mid = 0;
        unsigned arr_mid[N] = {0};

        for (unsigned i = 0; i < N; i++)
            arr_mid[i] = i;
        
        for (int k = 0; k < progony; k++)
        {
            std::shuffle(arr_mid, arr_mid + N, gen);

            auto begin_mid = std::chrono::steady_clock::now();
            shaker_sort(arr_mid, 0, N - 1, swaps);
            auto end_mid = std::chrono::steady_clock::now();
            auto time_span_mid = std::chrono::duration_cast<std::chrono::milliseconds>(end_mid - begin_mid);
            time_mid += time_span_mid.count();           
        }
        shaker_mid_file << time_mid << std::endl;
        shaker_swap_file << swaps << std::endl;
    }
    shaker_mid_file.close();
    shaker_swap_file.close();
    N_file.close();
}

void test_puzyrok()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream puzyrok_mid_file("puzyrok_mid.txt");
    std::ofstream puzyrok_swap_file("puzyrok_swap.txt");
    std::ofstream puzyrok_check_file("puzyrok_check.txt");
    std::ofstream N_file("N.txt");
    unsigned progony = 1;
    long long swaps = 0;

    //Проверка сортировки
    unsigned arr_mid[10] = {0};
    for (unsigned i = 0; i < 10; i++)
        arr_mid[i] = i;
    std::shuffle(arr_mid, arr_mid + 10, gen);
    for (unsigned i = 0; i < 10; i++)
        puzyrok_check_file << arr_mid[i] << ' ';
    puzyrok(arr_mid, 0, 9, swaps);
    puzyrok_check_file << '\n';
    for (unsigned i = 0; i < 10; i++)
        puzyrok_check_file << arr_mid[i] << ' ';
    puzyrok_check_file.close();

    //Измерение времени
    for (unsigned N = 1000; N <= 100000; N += 1000)
    {
        N_file << N << std::endl;
        
        long long swaps = 0;
        long long time_mid = 0;
        unsigned arr_mid[N] = {0};

        for (unsigned i = 0; i < N; i++)
            arr_mid[i] = i;

        for (int k = 0; k < progony; k++)
        {
            std::shuffle(arr_mid, arr_mid + N, gen);

            auto begin_mid = std::chrono::steady_clock::now();
            puzyrok(arr_mid, 0, N - 1, swaps);
            auto end_mid = std::chrono::steady_clock::now();
            auto time_span_mid = std::chrono::duration_cast<std::chrono::milliseconds>(end_mid - begin_mid);
            time_mid += time_span_mid.count();           
        }
            puzyrok_mid_file << time_mid << std::endl;
            puzyrok_swap_file << swaps << std::endl;
    }
    puzyrok_mid_file.close();
    puzyrok_swap_file.close();
    N_file.close();
}



//Часть 2. Сортировка расческой
void comb_check(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, unsigned const step, long long &swaps)
{
    for (unsigned i = begin_idx; i + step <= end_idx; i++)
        if (arr[i] > arr[i + step])
        {
            std::swap(arr[i], arr[i + step]);
            swaps++;
        }
}


void comb_sort(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps)
{
    unsigned step = (end_idx - begin_idx);
    while (step > 1)
    {
        step = step - 1;
        if (step < 1)
            step = 1;
        comb_check(arr, begin_idx, end_idx, step, swaps);
    }
}

void test_comb()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream comb_mid_file("comb_mid.txt");
    std::ofstream comb_swap_file("comb_swap.txt");
    std::ofstream comb_check_file("comb_check.txt");
    std::ofstream N_file("N.txt");
    unsigned progony = 1;
    long long swaps = 0;

    //Проверка сортировки
    unsigned arr_mid[10] = {0};
    for (unsigned i = 0; i < 10; i++)
        arr_mid[i] = i;
    std::shuffle(arr_mid, arr_mid + 10, gen);
    for (unsigned i = 0; i < 10; i++)
        comb_check_file << arr_mid[i] << ' ';
    comb_sort(arr_mid, 0, 9, swaps);
    comb_check_file << '\n';
    for (unsigned i = 0; i < 10; i++)
        comb_check_file << arr_mid[i] << ' ';
    comb_check_file.close();

    //Измерение времени
    for (unsigned N = 1000; N <= 100000; N += 1000)
    {
        N_file << N << std::endl;
        
        long long swaps = 0;
        long long time_mid = 0;
        unsigned arr_mid[N] = {0};

        for (unsigned i = 0; i < N; i++)
            arr_mid[i] = i;
        
        for (int k = 0; k < progony; k++)
        {
            std::shuffle(arr_mid, arr_mid + N, gen);

            auto begin_mid = std::chrono::steady_clock::now();
            comb_sort(arr_mid, 0, N - 1, swaps);
            auto end_mid = std::chrono::steady_clock::now();
            auto time_span_mid = std::chrono::duration_cast<std::chrono::milliseconds>(end_mid - begin_mid);
            time_mid += time_span_mid.count();           
        }
        comb_mid_file << time_mid << std::endl;
        comb_swap_file << swaps << std::endl;
    }
    comb_mid_file.close();
    comb_swap_file.close();
    N_file.close();
}





//Часть 3. Сортировка Шелла
void shell_check(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, unsigned const step, long long &swaps)
{
    for (unsigned i = begin_idx + step; i <= end_idx; i++)
    {
        unsigned temp = arr[i];
        unsigned j = i;
        while (j >= step && arr[j - step] > temp) {
            arr[j] = arr[j - step];
            j -= step;
            swaps++;
        }
        arr[j] = temp;
    }
}

void shell_sort(unsigned arr [], unsigned const begin_idx, unsigned const end_idx, long long &swaps, unsigned fib_prelast, unsigned fib_last)
{
    unsigned N = (end_idx - begin_idx) + 1;
    /*//1 вариант
    unsigned step = N;*/
    /*//2 вариант
    unsigned i = log2(N + 1);
    unsigned step = pow(2, i) - 1;*/
    //3 вариант
    unsigned step = fib_last;

    shell_check(arr, begin_idx, end_idx, step, swaps);
    while (step > 1)
    {
        /*//1 вариант
        step = step / 2;*/
        //2 вариант
        /*i--;
        step = pow(2, i) - 1;*/
        //3 вариант
        fib_prelast = fib_last - fib_prelast;
        fib_last = fib_last - fib_prelast;
        step = fib_last;
        if (step < 1)
            step = 1;
        shell_check(arr, begin_idx, end_idx, step, swaps);
    }
}



void test_shell()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream shell_mid_file("shell3_mid.txt");
    std::ofstream shell_swap_file("shell3_swap.txt");
    std::ofstream shell_check_file("shell3_check.txt");
    std::ofstream N_shell_file("N_shell.txt");
    unsigned progony = 10;
    long long swaps = 0;
    
    //Проверка сортировки
    unsigned fib_prelast = 0, fib_last = 1;
    while (fib_last + fib_prelast < 10)
    {
        fib_last = fib_prelast + fib_last;
        fib_prelast = fib_last - fib_prelast;
    }

    unsigned arr_mid[10] = {0};
    for (unsigned i = 0; i < 10; i++)
        arr_mid[i] = i;
    std::shuffle(arr_mid, arr_mid + 10, gen);
    for (unsigned i = 0; i < 10; i++)
        shell_check_file << arr_mid[i] << ' ';
    shell_sort(arr_mid, 0, 9, swaps, fib_prelast, fib_last);
    shell_check_file << '\n';
    for (unsigned i = 0; i < 10; i++)
        shell_check_file << arr_mid[i] << ' ';
    shell_check_file.close();

    //Измерение времени
    for (unsigned N = 10000; N <= 1000000; N += 10000)
    {
        N_shell_file << N << std::endl;

        unsigned fib_prelast = 0, fib_last = 1;
        while (fib_last + fib_prelast < N)
        {
            fib_last = fib_prelast + fib_last;
            fib_prelast = fib_last - fib_prelast;
        }
        long long swaps = 0;
        long long time_mid = 0;
        unsigned arr_mid[N] = {0};

        for (unsigned i = 0; i < N; i++)
            arr_mid[i] = i;
        
        for (int k = 0; k < progony; k++)
        {
            std::shuffle(arr_mid, arr_mid + N, gen);

            auto begin_mid = std::chrono::steady_clock::now();
            shell_sort(arr_mid, 0, N - 1, swaps, fib_prelast, fib_last);
            auto end_mid = std::chrono::steady_clock::now();
            auto time_span_mid = std::chrono::duration_cast<std::chrono::milliseconds>(end_mid - begin_mid);
            time_mid += time_span_mid.count();           
        }
        shell_mid_file << time_mid << std::endl;
        shell_swap_file << swaps << std::endl;
    }
    shell_mid_file.close();
    shell_swap_file.close();
    N_shell_file.close();
}






int main()
{
    //test_shaker();
    //test_puzyrok();
    //test_comb();
    //test_shell();
    return 0;
}