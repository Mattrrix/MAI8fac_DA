#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 64

typedef struct{
    char key[6+1]; // 'A' + '0' + '0' + '0' + 'A' + 'A' + '\0'
    char value[MAX_LENGTH + 1]; // Value + '\0'
    long long int qsort_key; // Дополнительное поле для сортировки ключей через встроенный qsort
} Pair;

void counting_sort(Pair *pair, int s, int digit){
    Pair output[s];
    int count[100] = {0};
    // Делаем инкремент значения соответствующего разряда в массива уникальных чисел
    for (int i = 0; i < s; i++) {
        int index = (int)pair[i].key[digit];
        count[index]++; 
    }
    // Префиксные суммы
    for (int i = 1; i < 100; i++) {
        count[i] += count[i - 1]; 
    }
    // Формируем результирующий массив с конца с помощью массива уникальных чисел и префиксных сумм
    for (int i = s - 1; i >= 0; i--) { 
        int index = (int)pair[i].key[digit]; 
        output[count[index] - 1] = pair[i];  
        count[index]--; 
    }

    for (int i = 0; i < s; i++) {
        pair[i] = output[i];   
    }
}

int getMax(Pair *pair, int s, int digit) { 
    int max = (int)pair[0].key[digit];
    for (int i = 1; i < s; i++){
        if((int)pair[i].key[digit] > max){
            max = (int)pair[i].key[digit];
        }
    }
    return max;
}

void radix_sort(Pair *pair, int s){
    for (int i = 5; i >= 0; i--){
        int max1 = getMax(pair, s, i);
        counting_sort(pair, s, i);
    }
}

// НЕЭФФЕКТИВНО ПО ВРЕМЕНИ

// void counting_sort(Pair *pair, int s, int exp, int digit){
//     Pair output[s];
//     int i, count[10] = {0};

//     for (i = 0; i < s; i++) {
//         int index = ((int)pair[i].key[digit] / exp) % 10; 
//         count[index]++; 
//     }

//     for (int i = 1; i < 10; i++) {
//         count[i] += count[i - 1]; // Префиксные суммы
//     }

//     for (int i = s - 1; i >= 0; i--) { 
//         int index = ((int)pair[i].key[digit] / exp) % 10;
//         output[count[index] - 1] = pair[i];  
//         count[index]--; 
//     }

//     for (int i = 0; i < s; i++) {
//         pair[i] = output[i];   
//     }
// }

// void radix_sort(Pair *pair, int s){
//     for (int i = 5; i >= 0; i--){
//         int max1 = getMax(pair, s, i);
//         for (int exp = 1; max1 / exp > 0; exp *= 10) {
//             counting_sort(pair, s, exp, i);
//         }
//     }
// }

// Для QucickSort встроенной в C
int compare_pairs(const void *a, const void *b) { // Сравнивает элементы Pair по полю qsort_key
    const Pair *pa = a;
    const Pair *pb = b;
    if (pa->qsort_key < pb->qsort_key) return -1;
    if (pa->qsort_key > pb->qsort_key) return 1;
    return 0;
}

// Function to swap two elements 
void swap(Pair* a, Pair* b) 
{ 
    Pair temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// Partition function 
int partition(Pair* pair, int low, int high) 
{ 
  
    // initialize pivot to be the first element 
    int pivot = pair[low].qsort_key; 
    int i = low; 
    int j = high; 
  
    while (i < j) { 
  
        // condition 1: find the first element greater than 
        // the pivot (from starting) 
        while (pair[i].qsort_key <= pivot && i <= high - 1) { 
            i++; 
        } 
  
        // condition 2: find the first element smaller than 
        // the pivot (from last) 
        while (pair[j].qsort_key > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swap(&pair[i], &pair[j]); 
        } 
    } 
    swap(&pair[low], &pair[j]); 
    return j; 
} 
  
// QuickSort function 
void quickSort(Pair *pair, int low, int high) 
{ 
    if (low < high) { 
  
        // call Partition function to find Partition Index 
        int partitionIndex = partition(pair, low, high); 
  
        // Recursively call quickSort() for left and right 
        // half based on partition Index 
        quickSort(pair, low, partitionIndex - 1); 
        quickSort(pair, partitionIndex + 1, high); 
    } 
} 

int main(){
    int elems = 0;
    srand(time(NULL));

    printf("Введите количество сортируемых пар: ");
    scanf("%d", &elems);
    
    Pair* pairs1 = (Pair*)malloc(elems * sizeof(Pair));

    // Записываем ключи и значения случайным образом в каждую пару
    for (int i = 0; i < elems; i++){
        pairs1[i].key[0] = 'A' + (rand() % 26);
        pairs1[i].qsort_key += (((int)pairs1[i].key[0])-65)*10000000; // Переводим ключи в числовой эквивалент на каждой итерации
        for (int k = 1, temp = 100000; k < 4; k++, temp/10){
            pairs1[i].key[k] = '0' + (rand() % 10);
            pairs1[i].qsort_key += ((int)pairs1[i].key[k])*temp;
        }
        for (int j = 4, temp = 100; j < 6; j++, temp/10){
            pairs1[i].key[j] = 'A' + (rand() % 26);
            pairs1[i].qsort_key += (((int)pairs1[i].key[j])-65)*temp;
        }
        for (int y = 0; y < MAX_LENGTH; y++){
            pairs1[i].value[y] = '0' + (rand() % 10);
        }
        pairs1[i].key[6] = '\0';
        pairs1[i].value[MAX_LENGTH] = '\0';
    }

    Pair* pairs2 = (Pair*)malloc(elems * sizeof(Pair));

    for (int i = 0; i < elems; i++) {
        pairs2[i] = pairs1[i];
    }


    // QuickSort (2 способа реализации)
    clock_t start_quick = clock();
    quickSort(pairs1, 0, elems - 1); // QuickSort, написанная вручную
    // qsort(pairs1, elems, sizeof(Pair), compare_pairs); // QuickSort встроенная в C
    clock_t end_quick = clock();
    double time_quick = (double)(end_quick - start_quick) / CLOCKS_PER_SEC;

    // Поразрядная сортировка
    clock_t start_radix = clock();
    radix_sort(pairs2, elems);
    clock_t end_radix = clock();
    double time_radix = (double)(end_radix - start_radix) / CLOCKS_PER_SEC;

    // for (int i = 0; i < elems; i++) {
    //     printf("%c %c%c%c %c%c\t%s %lld\n", pairs1[i].key[0], pairs1[i].key[1], pairs1[i].key[2],pairs1[i].key[3], pairs1[i].key[4], pairs1[i].key[5], pairs1[i].value, pairs1[i].qsort_key);
    // }

    printf("Время работы быстрой сортировки - %f сек\n", time_quick);
    printf("Время работы поразрядной сортировки - %f сек\n", time_radix);
    free(pairs1);
    free(pairs2);
}   