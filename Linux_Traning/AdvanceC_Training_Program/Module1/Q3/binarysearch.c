int binarySearchMatrix(int size, int matrix[size][size], int target) {
    int left = 0, right = size * size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int row = mid / size;
        int col = mid % size;

        if (matrix[row][col] == target) {
            printf("Key found at matrix[%d][%d]\n", row, col);
            return 1;
        } else if (matrix[row][col] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return 0;
}
void printMatrix(int size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the size of the  2D array (n x n): ");
    scanf("%d", &size);

    int matrix[size][size];

    printf("Enter %d elements in sorted manner:\n", size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
     int key;
    printf("Enter the key to search: ");
    scanf("%d", &key);
if (!binarySearchMatrix(size, matrix, key)) {
        printf("Key not found.\n");
    }
    return 0;
}