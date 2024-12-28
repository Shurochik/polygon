#include <iostream>
#include <vector>

using namespace std;

// функция, проверяющая, можно ли разделить массив не более чем на «k» частей с максимальной суммой «maxSum»
bool isSplitable(vector<int>& nums, int maxSum, int k) {
    int cumulativeSum = 0, parts = 1; //2*4 байта = 8 байт
    for (int num : nums) { //O(n)
        // Добавляем текущее число к cumulative sum
        cumulativeSum += num;
        // Если cumulative sum превышает maxSum, делаем новый подмассив
        if (cumulativeSum > maxSum) { //O(1)
            cumulativeSum = num; // Начинаем новый подмассив
            ++parts;
        }
    } //O(n)
    // Если число необходимых подмассивов меньше или равно k, возвращаем true
    return parts <= k;
}

int splitArray(vector<int>& nums, int k) {
    int minMax = 0, sum = 0; //2*4 байта = 8 байт, инициализируем границы для двоичного поиска
    
    for (int num : nums) { // 4 байта для num при инициализации цикла. 
        //Вычисляем наибольшее число в nums как нижнюю границу и sum как верхнюю границу
        minMax = max(minMax, num);
        sum += num;
    } //O(n)

    // Используем бинарный поиск, чтобы найти minimum largest sum, с которой мы можем разделить массив на k подмассивов
    while (minMax < sum) { //O(log(sum - minMax))
        int mid = (minMax + sum) / 2; // int = 4 байта
        // Если мы можем разделить массив на k подмассивов с максимальной суммой 'mid', ищем в левой части
        if (isSplitable(nums, mid, k)) {  // сложность isSplitable = O(n)
            sum = mid; 
        } 
        // В ином случае ищем в правой части
        else {
            minMax = mid + 1;
        } //O(n) за счет вызова isSplitable
    } //O(log(sum - minMax))*O(n)
    // 'minMax' теперь это minimum largest sum, с которой мы делим массив на k подмассивов
    return minMax;
}//O(log(sum - minMax))*O(n)+O(n)


int main() {
    int k = 2;
    vector<int> array = {10, 2, 3, 20, 1, 5, 100};
    int minMax = splitArray(array, k);
    cout << minMax << endl;

    k = 3;
    array = {1, 2, 2, 2, 6, 5, 1};
    minMax = splitArray(array, k);
    cout << minMax << endl;
}
