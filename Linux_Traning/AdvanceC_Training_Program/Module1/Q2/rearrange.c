#include <stdio.h>

void rearrange_even_before_odd(int *array, int length)
{
    int *endPtr = array + length;
    int *current = array;

    for (; current < endPtr; ++current)
    {
        if (*current % 2 != 0) 
        {
            int *nextEven = current + 1;
            while (nextEven < endPtr && *nextEven % 2 != 0)
                ++nextEven;

            if (nextEven == endPtr) break; 

            int evenValue = *nextEven;
            for (int *ptr = nextEven; ptr > current; --ptr)
                *ptr = *(ptr - 1);
            *current = evenValue;
        }
    }
}

int main()
{
    int length;
    printf("Enter the size of the array: ");
    scanf("%d", &length);

    int array[length];
    printf("Enter the %d values:\n", length);
    for (int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
    }

    rearrange_even_before_odd(array, length);

    printf("The rearranged order (even numbers first):\n");
    for (int *ptr = array; ptr < array + length; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");

    return 0;
}
