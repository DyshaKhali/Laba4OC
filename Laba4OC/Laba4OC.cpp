#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<Windows.h>
#include<iostream>
#include <iomanip>
#include <tchar.h>
#include <strsafe.h>
using namespace std;

const int sizeArr = 3;
const int sizeArr1 = 9;

VOID ExitThread(
    DWORD ExitCode);// код завершения потока

// Функция потока
DWORD WINAPI ThreadFunction(LPVOID Parametr)
{
    int* mas = (int*)Parametr;
    int sum = 0;

    for (size_t i = 0; i < sizeArr; i++)
    {
        for (size_t j = 0; j < sizeArr; j++)
        {
            if (i == 0 && j == 0)
            {
                sum += mas[i * sizeArr + j];
            }
            else if (i == 0 && j == sizeArr - 1)
            {
                sum += mas[i * sizeArr + j];
            }
            else if (i == sizeArr - 1 && j == 0)
            {
                sum += mas[i * sizeArr + j];
            }
            else if (i == sizeArr - 1 && j == sizeArr - 1)
            {
                sum += mas[i * sizeArr + j];
            }
        }
    }

    /*cout << "Сумма крайних элементов квадратной матрицы = " << sum << endl;*/
    cout << sum << endl;
    return sum;
}

DWORD ResumeThread(
    HANDLE hThread // поток, который требуется возобновить
);

DWORD SuspendThread(
    HANDLE hThread // поток, который требуется приостановить
);

VOID Sleep(DWORD MilliSeconds);

HANDLE OpenThread(
    DWORD DesiredAccess,
    BOOL InheritHandle,
    DWORD dwThreadId
);

BOOL SetThreadPriority(
    HANDLE Thread,
    int Priority);

int GetThreadPriority(
    HANDLE Thread);

_int64 FileTimeToQuadWord(PFILETIME pft)
{
    return(Int64ShllMod32(pft->dwHighDateTime, 32) | pft->dwLowDateTime);
}

void main()
{
    setlocale(LC_ALL, "ru");
    HANDLE h1;

    DWORD idH1;
    FILETIME ft[4];
    _int64 time2, time1;
    int arr[sizeArr][sizeArr];

    //Заполнение матрицы
    cout << "Введите элементы:" << endl;
    for (int i = 0; i < sizeArr; ++i)
        for (int j = 0; j < sizeArr; ++j)
            cin >> arr[i][j];
    cout << endl;

    //Вывод матрицы
    for (size_t i = 0; i < sizeArr; i++)
    {
        for (size_t j = 0; j < sizeArr; j++) std::cout << std::setw(2) << arr[i][j] << ' ';
        std::cout << std::endl;
    }

    int arr1[sizeArr1];
    int k = 0;

    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr; j++)
        {
            arr1[k] = arr[i][j];
            k++;
        }
    }

    h1 = CreateThread(NULL, 0, ThreadFunction, arr1, CREATE_SUSPENDED, &idH1);

    if (h1 != NULL)
    {
        SetThreadPriority(h1, THREAD_PRIORITY_HIGHEST);
        //SetThreadPriority(h1, THREAD_PRIORITY_ABOVE_NORMAL);

        ResumeThread(h1);
        WaitForSingleObject(h1, INFINITE);
        GetThreadTimes(h1, &ft[0], &ft[1], &ft[2], &ft[3]);

        time2 = FileTimeToQuadWord(&ft[1]);
        time1 = FileTimeToQuadWord(&ft[0]);

        printf("\n\nВремя выполнение потока в нс: %lld", time2 - time1);

        CloseHandle(h1);
    }
}