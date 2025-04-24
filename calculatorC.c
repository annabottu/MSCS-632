#include <stdio.h>
#include <stdlib.h>


float mean(int arr[], int size);
float median(int arr[], int size);
void mode(int arr[], int size);

int compare(const void *a, const void *b);

int main() {
    //uses an array to store integers and implement sorting and counting
    int numbers[] = {7, 9, 11, 25, 5, 9, 77, 9, 2, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Mean: %.2f\n", mean(numbers, size));
    printf("Median: %.2f\n", median(numbers, size));
    printf("Mode: ");
    mode(numbers, size);

    return 0;
}

//calculates the mean of the numbers
float mean(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;
}

//compares two integers (used for sorting)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

//calculates the median of the numbers
float median(int arr[], int size) {
    //this allocates memory
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    qsort(copy, size, sizeof(int), compare);
    float median;
    if (size % 2 == 0) {
        median = (copy[size / 2 - 1] + copy[size / 2]) / 2.0;
    } else {
        median = copy[size / 2];
    }
    //free up the memory
    free(copy);
    return median;
}

//calculates and prints the mode
void mode(int arr[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > max) {
            max = count;
        }
    }

    int printed[100] = {0}; 
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count == max && !printed[arr[i]]) {
            printf("%d ", arr[i]);
            printed[arr[i]] = 1;
        }
    }
    printf("\n");
}
