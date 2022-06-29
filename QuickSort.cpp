// QuickSort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
/*int main(void) {
    size_t number_count;
    std::cin >> number_count;
    std::vector<long> numbers(number_count);
    for (auto& number : numbers) {
        std::cin >> number;
    }
    std::vector <long> num(11);
    for (int i = 0; i < number_count; ++i)
    {
        num[numbers[i]]++;
    }
    int k = 0;
    for (int i = 0; i < num.size(); ++i)
    {
        while (num[i] != 0)
        {
            numbers[k++] = i;
            num[i]--;
        }
    }
    for (auto& number : numbers)
        std::cout << number << " ";
    std::cout << std::endl;
    }*/
   
typedef std::pair <int, int> Segment;

int partition(std::vector <long> &arr, int left, int right)
{
    int i = left, j = right;
    srand(time(0));
    rand();
    int t = (rand() % (right - left)) + left;
    int pivot = arr[t];
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i >= j)
            break;
        std::swap(arr[i++], arr[j--]);
    };
    return j;
}

void quickSort(std::vector <long> &arr, int left, int right) 
{
    int m;
    while (left < right)
    {
        m = partition(arr, left, right);
        quickSort(arr, left, m);
        left = m + 1;
    }
}

long get_pos(const std::vector<long>& numbers, long &number) {
    // TODO optimize this function
    int l = 0;
    int r = numbers.size() - 1;
    int m = l + ((r - l) / 2);
    if (number > numbers[r])
        return r;
    if (number < numbers[l])
        return l;
    while (l <= r)
    {
        m = l + ((r - l) / 2);
        if (numbers[m] > number)
            r = m - 1;
        else if (numbers[m] < number)
            l = m + 1;
        else
            return m;
    }
    if (numbers[l] == number)
        return l;
    else
        return m;
}

long count_b(std::vector<long> &begins, long &point)
{
    long k = get_pos(begins, point);
    long i;
    for (i = k; i < begins.size() && begins[i] <= point; i++, k++);
    return k;
}

long count_e(std::vector<long>& ends, long &point)
{
    long l = get_pos(ends, point);
    long m = l;
    if (ends[m] >= point)
    {
        for (; m > 0 && ends[m] >= point; m--);
    }
    if (ends[m] < point)
    {
        for (; m < ends.size() && ends[m] < point; m++);
    }
    l = m;
    return l;
}
int main(void) {
    auto start = std::chrono::high_resolution_clock::now();
    int segments_count, count_points;
    std::cin >> segments_count >> count_points;
    std::vector <Segment> segments(segments_count);
    for (int i = 0; i < segments_count; i++) 
       std::cin >> segments[i].first >> segments[i].second;
    std::vector<long> begins;
    for (int i = 0; i < segments_count; i++) {
        begins.push_back(segments[i].first);
    }
    std::vector<long> ends;
    for (int i = 0; i < segments_count; i++) {
        ends.push_back(segments[i].second);
    }
    quickSort(begins, 0, begins.size() - 1);
    quickSort(ends, 0, ends.size() - 1);
    std::vector<long> points(count_points);
    for (int i = 0; i < count_points; ++i)
        std::cin >> points[i];
    std::cout << std::endl;
    for (int i = 0; i < count_points; ++i)
        std::cout << count_b(begins, points[i]) - count_e(ends, points[i]) << " ";
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;
    std::chrono::duration<float> duration = end - start;
    std::cout << "runtime = " << duration.count() << "s " << std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
