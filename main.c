#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

double gettime(void);
void writebit(uint8_t *arr, uint64_t *n);
uint8_t readbit(uint8_t *arr, uint64_t n);

int main(void) {
    double mw1, mw2, mw3, mw4, mw5, mw6;
    uint64_t sum = 0, i, j, max, bits, bytes;
    uint8_t popcnt_tbl[0xFF], * arr;

    printf("Anzahl der Primzahlen bis ");
    scanf("%zu", &max);
    fflush(stdin);

    bits = ceil(max / 2.0);
    bytes = ceil(bits / 8.0);

    /////////////////////////////////////////////////////////////////////////////////////
    mw1 = gettime();

    arr = calloc(bytes, 1);

    for (i = 0; i < 0xFF; i++)
        popcnt_tbl[i] = __builtin_popcount((uint8_t)(~i));

    /////////////////////////////////////////////////////////////////////////////////////
    mw2 = gettime();
    printf("Zeit zur Initialisierung: %.8lf sec.\n\n", mw2 - mw1);
    mw3 = gettime();

    for (i = 3; i < sqrt(max); i += 2)
        if (!readbit(arr, i / 2))
            for (j = (i * i) / 2; j < bits; j += i)
                writebit(arr, &j);

    /////////////////////////////////////////////////////////////////////////////////////
    mw4 = gettime();
    printf("Zeit zur Berechnung:      %.8lf sec.\n\n", mw4 - mw3);
    mw5 = gettime();

    for (i = 0; i < bytes; i++)
        sum += popcnt_tbl[arr[i]];

    sum -= bytes * 8 - bits;

    mw6 = gettime();

    ////////////////////////////////////////////////////////////////////////////////////////
    printf("Zeit zur Summierung:      %.8lf sec.\n\n", mw6 - mw5);
    printf("------------------------------------------------\n\n");
    printf("Gesamt:                   %.8lf sec.\n\n", (mw2 - mw1) + (mw4 - mw3) + (mw6 - mw5));
    printf("Es gibt %zu Primzahlen fuer <=%zu.\n\n\n", sum, max);

    free(arr);

    return 0;
}

double gettime(void) {
    struct timeval tmp;
    gettimeofday(&tmp, NULL);
    return tmp.tv_sec + (tmp.tv_usec / 1000000.0);
}

void writebit(uint8_t *arr, uint64_t *n) {
    arr[*n / 8] |= 1 << *n % 8;
}

uint8_t readbit(uint8_t *arr, uint64_t n) {
    return (arr[n / 8] >> (n % 8)) & 1;
}
