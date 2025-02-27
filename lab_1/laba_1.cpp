#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


//Часть 1. Поиск
unsigned random_key(int N);
void linear(int *arr, int N, int key);
void binary(int *arr, int N, int key);
unsigned time_worst_linear(int *arr, int N, int key);
unsigned time_worst_binary(int *arr, int N, int key);
unsigned time_average_linear(int *arr, int N, int *key_arr);
unsigned time_average_binary(int *arr, int N, int *key_arr);
void worst_linear();
void worst_binary();
void average_linear();
void average_binary();

//Часть 2. Сумма двух
void vtupuyu(int *arr, int N, int key);
void poumnomu(int *arr, int N, int key);
unsigned time_worst_vtupuyu(int *arr, int N, int key);
unsigned time_worst_poumnumu(int *arr, int N, int key);
void worst_vtupuyu();
void worst_poumnomu();

//Часть 3. Часто используемый элемент
int str_A(int *arr, int N, int key);
int str_B(int *arr, int N, int key);
int str_C(int *arr, int N, int key, int *arr_0);
unsigned time_B(int *arr, int N, int key);
unsigned time_B(int *arr, int N, int key);
unsigned time_C(int *arr, int N, int key, int *arr_0);
void worst_A();
void worst_B();
void worst_C();

int main() {
    //worst_linear();
    //worst_binary();
    //average_linear();
    //average_binary();
    //worst_vtupuyu();
    //worst_poumnomu();
    //worst_A();
    //worst_B();
    worst_C();
return 0 ;
}



//часть 1


unsigned random_key_index(int N)
{
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution <unsigned> dstr(0, N-1);
    return dstr(rng);
}

unsigned random_key(int N)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    //std::default_random_engine generator (time(NULL));
    std::uniform_int_distribution <unsigned> dstr(0, N-1);
    return dstr(generator);
}

void linear(int *arr, int N, int key)
{
    for (int i = 0; i < N; i++)
        if(arr[i] == key) return;
    return;
}

void binary(int *arr, int N, int key)
{
    int l = 0;
    int r = N-1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (key == arr[m]) return;
        else if (key > arr[m]) l = m + 1;
        else r = m - 1;
    }
    return;
}

unsigned time_worst_linear(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 10000; cnt != 0 ; --cnt)
        linear(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

unsigned time_worst_binary(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 10000000; cnt != 0 ; --cnt)
        binary(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

unsigned time_average_linear(int *arr, int N, int *key_arr)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 0; cnt < 10000 ; ++cnt)
        linear(arr, N, key_arr[cnt]);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

unsigned time_average_binary(int *arr, int N, int *key_arr)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 0; cnt < 1000000 ; ++cnt)
        binary(arr, N, key_arr[cnt]);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

void worst_linear()
{
    std::ofstream outFile("lab_1/worst_linear.txt");
    std::ofstream outFileN("lab_1/N_linear.txt");
    for(int N = 100; N <= 1000000; N +=  50000)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = random_key(N);
        outFileN << N << std::endl;
        outFile << time_worst_linear(arr, N, N) << std::endl;
    }
    outFileN.close();
    outFile.close();
}

void worst_binary()
{
    std::ofstream outFile("lab_1/worst_binary.txt");
    std::ofstream outFileN("lab_1/N_binary.txt");
    for(int N = 100; N <= 1000000; N *= 1.6237)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = i;
        outFileN << N << std::endl;
        outFile << time_worst_binary(arr, N, N) << std::endl;
    }
    outFileN.close();
    outFile.close();
}

void average_linear()
{
    
    std::ofstream outFile("lab_1/average_linear.txt");
    for(int N = 100; N <= 1000000; N += 50000)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = random_key(N);
            
        int key_arr[100000];
        for (unsigned cnt = 0; cnt < 100000 ; ++cnt)
            key_arr[cnt] = arr[random_key(N)];
        outFile << time_average_linear(arr, N, key_arr) << std::endl;
    }
    outFile.close();
}

void average_binary()
{
    std::ofstream outFile("lab_1/average_binary.txt");
    for(int N = 1000; N <= 1000000; N *= 1.6237)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = i;

        int key_arr[1000000];
        for (unsigned cnt = 0; cnt < 1000000 ; ++cnt)
            key_arr[cnt] = arr[random_key(N)];
        outFile << time_average_binary(arr, N, key_arr) << std::endl;
    }
    outFile.close();
}



//Часть 2. Сумма двух
void vtupuyu(int *arr, int N, int key)
{
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if(arr[i] + arr[j] == key) return;
    return;
}

void poumnomu(int* arr, int N, int key)
{
    int l = 0;
    int r = N - 1;

    while (l < r)
    {
        int sum = arr[l] + arr[r];

        if (sum == key)
            return;
        else if (sum < key)
            l++;
        else
            r--;
    }
    return;
}

unsigned time_worst_vtupuyu(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0 ; --cnt)
        vtupuyu(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

unsigned time_worst_poumnomu(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 10000; cnt != 0 ; --cnt)
        poumnomu(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}
void worst_vtupuyu()
{
    std::ofstream outFile("lab_1/worst_vtupuyu.txt");
    std::ofstream outFileN("lab_1/N_vtupuyu.txt");
    for(int N = 100; N <= 10000; N += 500)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = random_key(N);
        
        outFileN << N << std::endl;
        outFile << time_worst_vtupuyu(arr, N, N) << std::endl;
    }
    outFileN.close();
    outFile.close();
}

void worst_poumnomu()
{
    std::ofstream outFile("lab_1/worst_poumnomu.txt");
    for(int N = 100; N <= 1000000; N += 50000)
    {
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = i;
        outFile << time_worst_poumnomu(arr, N, 5*N) << std::endl;
    }
    outFile.close();
}



//Часть 3.
int str_A(int *arr, int N, int key)
{
    int rez = 0;
    for(; rez < N; ++rez) 
        if(arr[rez] == key)
        {
            if(rez == 0)
                return rez;
            else
            {
                std::swap(arr[rez], arr[0]);
                return rez;
            }
        }
    return -1;
}

int str_B(int *arr, int N, int key)
{
    int rez = 0;
    for(; rez < N; ++rez) 
        if(arr[rez] == key)
        {
            if(rez == 0)
                return rez;
            else
            {
                std::swap(arr[rez], arr[rez-1]);
                return rez;
            }
        }
    return -1;
}

int str_C(int *arr, int N, int key, int *arr0)
{
    int rez = 0;
    for(; rez < N; ++rez) 
        if(arr[rez] == key)
        {
            arr0[rez]++;
            if(rez == 0) return rez;
            else
            {
                if(arr0[rez] > arr0[rez-1])
                {
                    std::swap(arr[rez], arr[rez-1]);
                    std::swap(arr0[rez], arr0[rez-1]);
                    return rez;
                }
            }
        }
    return -1;
}


unsigned time_A(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 1000; cnt != 0 ; --cnt)
        str_A(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}
unsigned time_B(int *arr, int N, int key)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 1000; cnt != 0 ; --cnt)
        str_B(arr, N, key);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}
unsigned time_C(int *arr, int N, int key, int *arr_0)
{
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 1000; cnt != 0 ; --cnt)
        str_C(arr, N, key, arr_0);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast < std::chrono::milliseconds > (end - begin);
    return time_span.count();
}

void worst_A()
{
    std::ofstream outFile("lab_1/A_ner.txt");
    std::ofstream outFileN("lab_1/N_3.txt");
    for(int N = 100; N <= 1000000; N += 20000)
    {
        unsigned seed = 1001;
        std::default_random_engine rng(seed);
        std::uniform_int_distribution <unsigned> dstr(0, N-1);
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = dstr(rng);
        int key = random_key(N);
        if (key > N*0.01 && key < N*0.49) key = N/4;
        else if (key > N*0.50 && key < N*0.99) key = 3*N/2;
        outFileN << N << std::endl;
        outFile << time_A(arr, N, key) << std::endl;
    }
    outFileN.close();
    outFile.close();
}
void worst_B()
{
    std::ofstream outFile("lab_1/B_ner.txt");
    for(int N = 100; N <= 1000000; N += 20000)
    {
        unsigned seed = 1001;
        std::default_random_engine rng(seed);
        std::uniform_int_distribution <unsigned> dstr(0, N-1);
        int arr[N];
        for (int i = 0; i < N; i++)
            arr[i] = dstr(rng);
        int key = random_key(N);
        if (key > N*0.01 && key < N*0.69) key = N/4;
        else if (key > N*0.70 && key < N*0.99) key = 3*N/2;
        outFile << time_B(arr, N, key) << std::endl;
    }
    outFile.close();
}
void worst_C()
{
    std::ofstream outFile("lab_1/C_ner.txt");
    for(int N = 100; N <= 1000000; N += 20000)
    {
        unsigned seed = 1001;
        std::default_random_engine rng(seed);
        std::uniform_int_distribution <unsigned> dstr(0, N-1);
        int arr[N];
        int arr_0[N] = {0};
        for (int i = 0; i < N; i++)
            arr[i] = dstr(rng);
        int key = random_key(N);
        if (key > N*0.01 && key < N*0.69) key = N/4;
        else if (key > N*0.70 && key < N*0.99) key = 3*N/2;
        outFile << time_C(arr, N, key, arr_0) << std::endl;
    }
    outFile.close();
}
