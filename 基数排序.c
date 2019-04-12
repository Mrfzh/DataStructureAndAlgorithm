#include <stdio.h>

void radixSort(int a[], int n);
int getMax(int a[], int n);
void countSort(int a[], int n, int exp);

int main() {

    int a[] = {42, 865, 442, 95, 134, 3, 339, 17, 1024, 555};

    radixSort(a, 10);

    int i;
    for (i = 0; i < 10; i++) {
        printf("%d  ", a[i]);
    }

    return 0;
}

/*
 * 基数排序
 *
 * @param a 数组，存放待排列的数
 * @param n 数组长度
 */
void radixSort(int a[], int n) {
    int exp;    //指数。对数组中的数按个位排列时，exp=1；按十位排列时，exp=10；.......
    int max = getMax(a, n);   //获取数组中的最大值

    //从个位开始，对数组进行排序
    for (exp = 1; max/exp > 0; exp *= 10) {
        countSort(a, n, exp);
    }
}

/*
 * 获取a数组中最大的数并返回
 */
int getMax(int a[], int n) {
    int i, max;
    max = a[0];
    for (i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    return max;
}

/*
 * 根据指数来决定按哪一位来排序
 *
 * @param exp 指数
 */
void countSort(int a[], int n, int exp) {
    int output[n];    //存储“被排序数据”的临时数组
    int i;
    int buckets[10] = {0};      //十个“桶”代表0~9

    //将0~9出现的次数存储在桶中
    for (i = 0; i < n; i++) {
        buckets[ (a[i]/exp)%10 ]++;
    }

    //更改后的buckets[i]的值，是该数据出现在output[]中的位置
    //注意：如果基数3有5个数，那么buckets[3]指的是3中第5个数在output[]中的位置。
    for (i = 1; i < 10; i++) {
        buckets[i] += buckets[i-1];
    }

    //将数据存储到output数组中
    //注意：这里必须先从后面的数开始排，因为相同基数的数，“先排的”是放在output靠后的位置
    //所以为了保证数据的稳定性，从后面的数开始排。
    for (i = n-1; i >= 0; i--) {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;     //如果相同基数的数有多个，那么这里就要减一（”后排的“排到前面去），这样才不会把原来的数覆盖掉
    }

    //将排列好的数据赋给数组a
    for (i = 0; i < n; i++) {
        a[i] = output[i];
    }

}
