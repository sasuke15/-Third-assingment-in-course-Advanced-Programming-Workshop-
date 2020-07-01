

/*
Assigend by:
Re'em Rothenberg #307903682,:61108
Shay Bach #204263842,:61108
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 8
typedef char board[SIZE][SIZE];
board bin_board;
typedef struct employee {
    int code;
    char name[15];
    float salary;
} Employee;

void create_file(char* file)
{

    FILE* f = fopen(file, "wb");
    Employee worker;
    int n, i;
    char ch;

    worker.name[14] = '\0';

    printf("Please enter the number of workers\n");
    scanf("%d", &n);

    for (i = 0; n > i; i++) {

        printf(" Plese enter the worker %d code\n", i + 1);
        scanf("%d", &worker.code);

        printf(" Plese enter the worker %d name\n", i + 1);
        scanf("%s", worker.name);

        printf(" Plese enter the worker %d salary\n", i + 1);
        scanf("%f", &worker.salary);

        fwrite(&worker, sizeof(Employee), 1, f);
    }

    fclose(f);
}
void updateSalary(char* filename, float threshold)
{

    Employee worker;
    float rise;
    FILE* f = fopen(filename, "rb");
    FILE* d = fopen("kie", "wb");

    while (!feof(f)) {

        fread(&worker, sizeof(Employee), 1, f);

        printf("Please enter  the  rise to the rise to %s\n", worker.name);
        scanf("%f", &rise);

        worker.salary += rise;

        if (threshold >= worker.salary)
            fwrite(&worker, sizeof(Employee), 1, d);
    }

    fclose(f);
    fclose(d);

    f = fopen(filename, "wb");
    d = fopen("kie", "rb");

    while (!feof(d)) {

        fread(&worker, sizeof(Employee), 1, d);
        fwrite(&worker, sizeof(Employee), 1, f);
    }

    fclose(f);
    fclose(d);
}
void print(char* file)
{

    Employee worker;
    FILE* f = fopen(file, "rb");

    worker.name[14] = '\0';

    printf("List of the workers\n\n");

    while (!feof(f)) {

        fread(&worker, sizeof(Employee), 1, f);

        printf("code:%d name:%s salary:%0.0f\n\n", worker.code, worker.name, worker.salary);
    }

    fclose(f);
}
void Ex1()
{

    char* file = "name";
    float threshold;

    create_file(file);

    printf("Please enter the threshold\n");
    scanf("%f", &threshold);

    updateSalary(file, threshold);

    print(file);
}

void displayShortString(char* short_dig_str)
{

    int value, num = 0, i, j, mask = 1 << 3, condition = 0;

    printf("The number is:\n");

    for (i = 0; short_dig_str[i] != '\0'; i++) {

        value = short_dig_str[i];

        if (value < 0)
            value += 256;

        if (value == 154)
            value = 0;

        num += value >> 4;

        num *= 10;

        num += value - ((value >> 4) << 4);

        num *= 10;
    }

    num /= 10;

    printf("%d = ", num);

    if (num == 0)
        printf("0000");

    else
        for (i = 0; short_dig_str[i] != '\0'; i++) {

            if (short_dig_str[i] == -102)
                printf("0000 0000");

            else {
                num = short_dig_str[i] >> 4;

                if (num != 0 || condition == 1)
                    for (j = 0; 4 > j; j++) {

                        if ((num & mask) != 0)
                            printf("1");

                        else
                            printf("0");

                        num <<= 1;
                    }

                condition = 1;

                printf(" ");

                num = short_dig_str[i] - ((short_dig_str[i] >> 4) << 4);

                for (j = 0; 4 > j; j++) {

                    if ((num & mask) != 0)
                        printf("1");

                    else
                        printf("0");

                    num <<= 1;
                }
            }
            printf(" ");
        }

    printf("\n");

    free(short_dig_str);
}
char* codingToShortString(char* dig_str)
{

    int k, n, i = 0, j = 0;
    char* short_dig_str;

    for (n = 0; dig_str[n] != '\0'; n++)
        ;

    k = n;

    if (n % 2 == 0)
        n /= 2;

    else {
        n /= 2;
        n += 1;
    }

    short_dig_str = (char*)malloc((n + 1) * sizeof(char));

    short_dig_str[n] = '\0';

    if (k % 2 == 1) {
        short_dig_str[0] = dig_str[0] - 48;

        if (short_dig_str[0] == 0)
            short_dig_str[0] = 154;

        i = 1;
        j = 1;
    }

    for (i, j; n > i; i++, j += 2) {
        short_dig_str[i] = ((dig_str[j] - 48) << 4) + (dig_str[j + 1] - 48);

        if (short_dig_str[i] == 0)
            short_dig_str[i] = 154;
    }
    free(dig_str);

    return short_dig_str;
}
void Ex2()
{

    char* dig_str;
    int n;

    printf("Please enter the  size of the dig string\n");
    scanf("%d", &n);

    dig_str = (char*)malloc((n + 1) * sizeof(char));

    dig_str[n] = '\0';

    printf("Please enter the dig string\n");
    scanf("%s", dig_str);

    displayShortString(codingToShortString(dig_str));
}

void fillBoard(board bin_board)
{

    int i, j;

    printf("The mat is:\n\n");

    for (i = 0; 8 > i; i++) {
        for (j = 0; 8 > j; j++) {
            bin_board[i][j] = (rand() % 2);
            printf("%d ", bin_board[i][j]);
        }
        printf("\n");
    }
}
unsigned long long boardToBits(board bin_board)
{

    int i, j;
    unsigned long long num = 0;

    for (i = 0; 8 > i; i++)
        for (j = 0; 8 > j; j++) {

            if (bin_board[i][j] == 1)
                num += 1;
            num *= 2;
        }

    num /= 2;

    printf("%u\n", num % 2);

    return num;
}
void displayBinaryBoard(unsigned long long coded_bin_board)
{

    unsigned long long temp = 0;
    int i, j;

    printf("\n");

    printf("The mat is:\n\n");

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            temp += coded_bin_board % 2;
            temp *= 2;
            coded_bin_board /= 2;
        }

    temp /= 2;
    temp += 1;

    for (i = 0; 8 > i; i++) {
        for (j = 0; 8 > j; j++) {

            if (temp % 2 == 1)
                printf("1 ");

            else
                printf("0 ");

            temp /= 2;
        }
        printf("\n");
    }
}
void Ex3()
{

    fillBoard(bin_board);
    displayBinaryBoard(boardToBits(bin_board));
}

void main()
{

    void (*funk[3])() = { Ex1, Ex2, Ex3 };
    int i, num, n;

    printf("Enter number of Ex you want to run: ");
    scanf("%d", &num);
    printf("\n");

    for (i = 0; num > i; i++) {
        printf("Plese enter the Ex you want to run:");
        scanf("%d", &n);
        printf("\n");

        (*funk[n - 1])();
    }
}


