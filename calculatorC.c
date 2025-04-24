#include <stdio.h>
#include <stdlib.h>

float mean(int arr[], int size);
float median(int arr[], int size);
void mode(int arr[], int size);
void sort(int arr[], int size);


int main() {
    //uses an array to store integers and implement sorting and counting
    int numbers[] = {3, 7, 9, 44, 70, 5, 7, 4, 7};
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

void sort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j] + 1) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//calculates the median of the numbers
float median(int arr[], int size) {
    //this allocates memory
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    sort(copy, size);
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
