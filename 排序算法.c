#include <stdio.h>
#include <stdbool.h>

/*
 * ��Ҫ�ο���http://www.cnblogs.com/eniac12/p/5329396.html#s2
 */

void swap(int a[], int i, int j) {
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/*
 * ð������
 */
void BubbleSort(int a[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) { //��Ҫ����n-1��ð��
        for (j = 0; j < n-i-1; j++) {   //ÿһ�ֵıȽ�
            if (a[j] > a[j+1]) {
                swap(a, j, j+1);
            }
        }
    }
}

/*
 * ��β���������ñ��λ
 */
void CocktailSort(int a[], int n) {
     int left = 0;
     int right = n-1;
     int i;
     bool isSwaped = false;     //���ñ��λ�������һ�α�������ʱ�Ƿ��н���
                                //���û�н����Ļ���ֱ��break����Ϊû�н�����˵���Ѿ��ź�����
     while (left < right) {
        isSwaped = false;
        for (i = left; i < right; i++) {    //�ȴ�����ѡ������
            if (a[i] > a[i+1]) {
                swap(a, i, i+1);
                isSwaped = true;
            }
        }
        if (!isSwaped) {
            break;
        }
        right--;

        isSwaped = false;
        for (i = right; i > 0; i--) {   //�ٴ��ҵ���ѡ����С��
            if (a[i] < a[i-1]) {
                swap(a, i, i-1);
                isSwaped = true;
            }
        }
        if (!isSwaped) {
            break;
        }
        left++;
     }
}

/*
 * ѡ������
 */
void SelectionSort(int a[], int n) {
    int i, j, min;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++) { //һ������ѡ����С��Ԫ�ص��±�
            if (a[min] > a[j]) {
                min = j;
            }
        }
        if (i != min) {     //�����С��Ԫ�ز������ֵĵ�һ�����򽻻�
            swap(a, i, min);
        }
    }
}

/*
 * ��������
 */
void InsertionSort(int a[], int n) {
    //Ĭ�ϵ�һ����a[0]�������

    //�������ӵڶ�������ʼ��ÿ�������θ�ǰ�����������дӺ���ǰ�Ƚϣ�
    //��С��ǰ���������ǰ���������������λ��ֱ������ǰ������������ǰ������ĺ�һλ
    int i;
    for (i = 1; i < n; i++) {
        int get = a[i];     //�Ƚ��õ�������������
        int j = i - 1;
        //��С��ǰ���������ǰ���������������λ��ֱ������ǰ�����
        while (j >= 0 && a[j] > get) {
            a[j+1] = a[j];
            j--;
        }
        //����ǰ������ĺ�һλ
        a[j+1] = get;
    }
}

/*
 * ��������ĸĽ������ֲ�������
 *
 * ���ֲ������򣺶��ڲ�����������Ƚϲ����Ĵ��۱Ƚ���������Ļ������Բ��ö��ֲ��������ٱȽϲ����Ĵ�����
 *
 * �Ƚϣ���n�ϴ�ʱ�����ֲ�������ıȽϴ�����ֱ�Ӳ���������������õö࣬����ֱ�Ӳ��������������Ҫ�
 * ������Ԫ�س�ʼ�����Ѿ��ӽ�����ʱ��ֱ�Ӳ�������ȶ��ֲ�������Ƚϴ����١�
 * ���ֲ�������Ԫ���ƶ�������ֱ�Ӳ���������ͬ��������Ԫ�س�ʼ���С�
 */
void InsertionSortDichotomy(int a[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        int get = a[i];
        //��������������ұ߽�
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int middle = (left + right) / 2;
            if (a[middle] < get) {  //����õ����������м�������Ӧ�ŵ���벿��
                left = middle + 1;
            } else {  //����Ӧ������벿�֣������˵����м����������
                right = middle - 1;
            }
        }
        //ִ����ѭ�����õ�����Ӧ����left��λ�ã��������������

        //�����д���get������������һλ
        int j;
        for (j = i-1; j >= left; j--) {
            a[j+1] = a[j];
        }
        //��get�ŵ���ȷλ��
        a[left] = get;
    }
}

/*
 * ��������h�Ĳ�������
 */
void InsertionSortWithIncrement(int a[], int n, int h) {
    int i;
    for (i = h; i < n; i++) {
        int get = a[i];
        int j = i - h;

        while (j >= 0 && a[j] > get) {
            a[j+h] = a[j];
            j = j - h;
        }

        a[j+h] = get;
    }
}

/*
 * ϣ������
 *
 * ������ϣ������ͨ�����Ƚϵ�ȫ��Ԫ�ط�Ϊ�������򣨵�1,1+d,1+2d,...��Ԫ��Ϊһ�飬dΪ������������������������ܡ�
 * ����������һ��Ԫ�ؿ���һ���Եس�����λ��ǰ��һ�󲽡�
 * Ȼ���㷨��ȡԽ��ԽС�Ĳ������������㷨�����һ��������ͨ�Ĳ���������ʱ����������ݼ��������źõ��ˣ���ʱ��������Ͽ죩��
 */
void ShellSort(int A[], int n){
    int h = 0;
    while (h <= n){                          // ���ɳ�ʼ����
        h = 3 * h + 1;
    }
    while (h >= 1){
        InsertionSortWithIncrement(A, n, h);    //����һ������Ϊh�Ĳ������򣬵�hΪ1ʱ������ͨ�Ĳ�������
        h = (h - 1) / 3;                    // �ݼ�����
    }
}

/*
 * ����һ�˿��ţ����ػ�׼����
 */
int Partition(int a[], int left, int right) {
    int pivot = a[right];     //ѡ�����һ��Ԫ����Ϊ��׼
    int pivotIndex = right;
    while (left < right) {
        //���ѡ�е�һ��Ԫ��Ϊ��׼��Ӧ�Ƚ��м�������������������whileѭ������λ��
        while (left < right && a[left] <= pivot) {
            left++;
        }
        while (left < right && a[right] >= pivot) {
            right--;
        }
        swap(a, left, right);
    }
    swap(a, left, pivotIndex);      //����׼�ع鵽��ȷλ�ã�leftҲ�ɻ���right����Ϊ��ʱleft == right��
    return left;
}

/*
 * ��������
 * ����Partition�ж����㷨���ɲο���https://blog.csdn.net/qq_36528114/article/details/78667034
 */
void QuickSort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivotIndex = Partition(a, left, right);   //����һ��������û�׼������
    QuickSort(a, left, pivotIndex-1);
    QuickSort(a, pivotIndex+1, right);
}

/*
 * �ϲ������Ѿ��ź��������a[left...mid]��a[mid+1...right]
 */
void Merge(int a[], int left, int mid, int right, int temp[]) {
    int i = left;   //��һ�����鿪ͷλ��
    int j = mid + 1;    //�ڶ������鿪ͷλ��
    int k = 0;

    //�Ƚ�������Ԫ�ش�С
    while (i <= mid && j <= right) {
        temp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    }
    //��ʣ��δ�Ƚϵ�Ԫ�ط���temp������
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= right) {
        temp[k++] = a[j++];
    }
    //��temp���飨���ź��򣩸�������a
    int len = right - left + 1;     //�ϲ�������ֳ��ȣ�ע�⣺��������ȴ���������Ϊѭ�����еĸ�ֵ�����ı���left
    for (k = 0; k < len; k++) {
        a[left++] = temp[k];    //ע�⣺�Ǵ�a[left]��ʼ��ֵ��������a[0]
    }
}

/*
 * �鲢����
 */
void MergeSort(int a[], int left, int right, int temp[]) {
    if (left == right) {
        return;
    }
    int mid = (left + right) / 2;
    MergeSort(a, left, mid, temp);
    MergeSort(a, mid+1, right, temp);
    //�ϲ��������ź����������
    Merge(a, left, mid, right, temp);
}

/*
 * ����Ϊ�󶥶ѣ���a[i]��ʼ������
 */
void adjustHeap(int a[], int i, int length) {
    int temp = a[i];    //����a[i];
    int k;  //k���ڴ洢�ӽڵ�
    for (k = i*2 + 1; k < length; k = k*2 + 1) {    //��i�ڵ�����ӽڵ㿪ʼ
        if (k+1 < length && a[k] < a[k+1]) {    //������ӽڵ�С�����ӽڵ㣬��kָ�����ӽڵ�
            k++;
        }
        if (a[k] > temp) {  //����ӽڵ���ڸ��ڵ㣬���ӽڵ㸳�����ڵ㣨���ý��н������ӽڵ��ֵ��ʱ��temp��
            a[i] = a[k];
            i = k;
        } else {  //�����˳�ѭ��
            break;
        }
    }
    //��tempֵ�ŵ����յ�λ��
    a[i] = temp;
}

/*
 * ���ѣ��󶥶ѣ�
 */
int BuildHeap(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) { //�����һ����Ҷ�ӽڵ㿪ʼ���жѵ���
         adjustHeap(a, i, n);
    }
}

/*
 * ������
 * 1. ���������й�����һ���ѣ�����ѡ��󶥶ѣ�����ѡ��С����;
 */
void HeapSort(int a[], int n) {
    //�ȹ����󶥶�
    BuildHeap(a, n);
    //�����ѽṹ
    int i;
    for (i = n-1; i > 0; i--) {
        swap(a, 0, i);  //�����Ѷ�Ԫ�غ�ĩβԪ��
        adjustHeap(a, 0, i);    //���¶Զѽ������򣨲������ѽ�����ĩβ����õ�Ԫ�أ�
    }
}


int main() {
    int a[] = {21, 11, 48, 6, 92, 41, 39, 77, 20, 1};
    int n = sizeof(a)/sizeof(int);
    int temp[n];  //�����濪��һ����ʱ����(���ظ�����)�������ڹ鲢�ĵݹ�����ж�ο��ٿռ�

    //BubbleSort(a, n);
    //CocktailSort(a, n);
    //SelectionSort(a, n);
    //InsertionSort(a, n);
    //InsertionSortDichotomy(a, n);
    //ShellSort(a, n);
    //QuickSort(a, 0, n-1);
    //MergeSort(a, 0, n-1, temp);
    HeapSort(a, n);

    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);    //��ȷ��Ϊ��1 6 11 20 21 39 41 48 77 92
    }
    printf("\n");

    return 0;
}
