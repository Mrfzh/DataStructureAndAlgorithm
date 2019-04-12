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
 * ��������
 *
 * @param a ���飬��Ŵ����е���
 * @param n ���鳤��
 */
void radixSort(int a[], int n) {
    int exp;    //ָ�����������е�������λ����ʱ��exp=1����ʮλ����ʱ��exp=10��.......
    int max = getMax(a, n);   //��ȡ�����е����ֵ

    //�Ӹ�λ��ʼ���������������
    for (exp = 1; max/exp > 0; exp *= 10) {
        countSort(a, n, exp);
    }
}

/*
 * ��ȡa������������������
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
 * ����ָ������������һλ������
 *
 * @param exp ָ��
 */
void countSort(int a[], int n, int exp) {
    int output[n];    //�洢�����������ݡ�����ʱ����
    int i;
    int buckets[10] = {0};      //ʮ����Ͱ������0~9

    //��0~9���ֵĴ����洢��Ͱ��
    for (i = 0; i < n; i++) {
        buckets[ (a[i]/exp)%10 ]++;
    }

    //���ĺ��buckets[i]��ֵ���Ǹ����ݳ�����output[]�е�λ��
    //ע�⣺�������3��5��������ôbuckets[3]ָ����3�е�5������output[]�е�λ�á�
    for (i = 1; i < 10; i++) {
        buckets[i] += buckets[i-1];
    }

    //�����ݴ洢��output������
    //ע�⣺��������ȴӺ��������ʼ�ţ���Ϊ��ͬ���������������ŵġ��Ƿ���output�����λ��
    //����Ϊ�˱�֤���ݵ��ȶ��ԣ��Ӻ��������ʼ�š�
    for (i = n-1; i >= 0; i--) {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;     //�����ͬ���������ж������ô�����Ҫ��һ�������ŵġ��ŵ�ǰ��ȥ���������Ų����ԭ���������ǵ�
    }

    //�����кõ����ݸ�������a
    for (i = 0; i < n; i++) {
        a[i] = output[i];
    }

}
