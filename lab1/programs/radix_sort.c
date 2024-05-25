#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 64

typedef struct{
    char key[6+1]; // 'A' + '0' + '0' + '0' + 'A' + 'A' + '\0'
    char value[MAX_LENGTH + 1]; // Value + '\0'
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
//     // Делаем инкремент значения соответствующего разряда в массива уникальных чисел
//     for (i = 0; i < s; i++) {
//         int index = ((int)pair[i].key[digit] / exp) % 10;
//         count[index]++; 
//     }
//     // Префиксные суммы
//     for (int i = 1; i < 10; i++) {
//         count[i] += count[i - 1]; 
//     }
//     // Формируем результирующий массив с конца с помощью массива уникальных чисел и префиксных сумм
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

int main() {
    int size = 0;
    Pair* elems = (Pair*)malloc(0 * sizeof(Pair));
    char line[75];  
    memset(line, ' ', strlen(line));
    line[strlen(line) - 1] = '\0';
    // Построчно считываем стандартный ввод до EOF (CTRL + D)
    while (fgets(line, sizeof(line), stdin) != NULL){ 
        // Пропускаем пустую строку
        if (line[0] == '\t' || line[0] == '\n') { 
            continue;
        }
        line[strlen(line) - 1] = '\0';
        // Перевыделяем память под каждую введенную пару типа ключ-значение
        elems = (Pair*)realloc(elems, (size+1) * sizeof(Pair));
        if (elems == NULL){
            perror("realloc failed:");
            free(elems);
            exit(EXIT_FAILURE);
        }
        char temp[3];
        sscanf(line, "%c %c%c%c %c%c\t%s\n", &elems[size].key[0], &elems[size].key[1], &elems[size].key[2], &elems[size].key[3], &elems[size].key[4], &elems[size].key[5], elems[size].value);
        elems[size].key[6] = '\0';
        elems[size].value[MAX_LENGTH] = '\0';
        size++;
    }
 
    radix_sort(elems, size);

    for (int i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%s\n", elems[i].key[0], elems[i].key[1], elems[i].key[2],elems[i].key[3], elems[i].key[4], elems[i].key[5], elems[i].value);
    }

    free(elems);
    return 0;
}
