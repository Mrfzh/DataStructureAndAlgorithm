#include <stdio.h>
#include <stdbool.h>

/*
 * 主要参考：http://www.cnblogs.com/eniac12/p/5329396.html#s2
 */

void swap(int a[], int i, int j) {
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/*
 * 冒泡排序
 */
void BubbleSort(int a[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) { //需要进行n-1轮冒泡
        for (j = 0; j < n-i-1; j++) {   //每一轮的比较
            if (a[j] > a[j+1]) {
                swap(a, j, j+1);
            }
        }
    }
}

/*
 * 鸡尾酒排序，设置标记位
 */
void CocktailSort(int a[], int n) {
     int left = 0;
     int right = n-1;
     int i;
     bool isSwaped = false;     //设置标记位，标记上一次遍历数组时是否有交换
                                //如果没有交换的话就直接break，因为没有交换就说明已经排好序了
     while (left < right) {
        isSwaped = false;
        for (i = left; i < right; i++) {    //先从左到右选出最大的
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
        for (i = right; i > 0; i--) {   //再从右到左选出最小的
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
 * 选择排序
 */
void SelectionSort(int a[], int n) {
    int i, j, min;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++) { //一轮下来选出最小的元素的下标
            if (a[min] > a[j]) {
                min = j;
            }
        }
        if (i != min) {     //如果最小的元素不是这轮的第一个，则交换
            swap(a, i, min);
        }
    }
}

/*
 * 插入排序
 */
void InsertionSort(int a[], int n) {
    //默认第一个数a[0]是有序的

    //分析：从第二个数开始，每个数依次跟前面已排序序列从后往前比较，
    //若小于前面的数，则前面的数依次往后移位，直到大于前面的数，则放在前面的数的后一位
    int i;
    for (i = 1; i < n; i++) {
        int get = a[i];     //先将拿到的数保存起来
        int j = i - 1;
        //若小于前面的数，则前面的数依次往后移位，直到大于前面的数
        while (j >= 0 && a[j] > get) {
            a[j+1] = a[j];
            j--;
        }
        //放在前面的数的后一位
        a[j+1] = get;
    }
}

/*
 * 插入排序的改进：二分插入排序
 *
 * 二分插入排序：对于插入排序，如果比较操作的代价比交换操作大的话，可以采用二分查找来减少比较操作的次数。
 *
 * 比较：当n较大时，二分插入排序的比较次数比直接插入排序的最差情况好得多，但比直接插入排序的最好情况要差，
 * 所当以元素初始序列已经接近升序时，直接插入排序比二分插入排序比较次数少。
 * 二分插入排序元素移动次数与直接插入排序相同，依赖于元素初始序列。
 */
void InsertionSortDichotomy(int a[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        int get = a[i];
        //已排序数组的左右边界
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int middle = (left + right) / 2;
            if (a[middle] < get) {  //如果拿到的数大于中间数，则应放到后半部分
                left = middle + 1;
            } else {  //否则应放在左半部分（包括了等于中间数的情况）
                right = middle - 1;
            }
        }
        //执行完循环后，拿到的数应放在left的位置（结果就是这样）

        //将所有大于get的数都往右移一位
        int j;
        for (j = i-1; j >= left; j--) {
            a[j+1] = a[j];
        }
        //将get放到正确位置
        a[left] = get;
    }
}

/*
 * 带有增量h的插入排序
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
 * 希尔排序
 *
 * 概述：希尔排序通过将比较的全部元素分为几个区域（第1,1+d,1+2d,...个元素为一组，d为增量）来提升插入排序的性能。
 * 这样可以让一个元素可以一次性地朝最终位置前进一大步。
 * 然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，这时需排序的数据几乎是已排好的了（此时插入排序较快）。
 */
void ShellSort(int A[], int n){
    int h = 0;
    while (h <= n){                          // 生成初始增量
        h = 3 * h + 1;
    }
    while (h >= 1){
        InsertionSortWithIncrement(A, n, h);    //进行一次增量为h的插入排序，当h为1时就是普通的插入排序
        h = (h - 1) / 3;                    // 递减增量
    }
}

/*
 * 进行一趟快排，返回基准索引
 */
int Partition(int a[], int left, int right) {
    int pivot = a[right];     //选择最后一个元素作为基准
    int pivotIndex = right;
    while (left < right) {
        //如果选中第一个元素为基准，应先进行减操作，即将下面两个while循环换个位置
        while (left < right && a[left] <= pivot) {
            left++;
        }
        while (left < right && a[right] >= pivot) {
            right--;
        }
        swap(a, left, right);
    }
    swap(a, left, pivotIndex);      //将基准回归到正确位置（left也可换成right，因为此时left == right）
    return left;
}

/*
 * 快速排序
 * 对于Partition有多种算法，可参考：https://blog.csdn.net/qq_36528114/article/details/78667034
 */
void QuickSort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivotIndex = Partition(a, left, right);   //进行一趟排序后获得基准的索引
    QuickSort(a, left, pivotIndex-1);
    QuickSort(a, pivotIndex+1, right);
}

/*
 * 合并两个已经排好序的数组a[left...mid]和a[mid+1...right]
 */
void Merge(int a[], int left, int mid, int right, int temp[]) {
    int i = left;   //第一个数组开头位标
    int j = mid + 1;    //第二个数组开头位标
    int k = 0;

    //比较两数组元素大小
    while (i <= mid && j <= right) {
        temp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    }
    //将剩余未比较的元素放入temp数组中
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= right) {
        temp[k++] = a[j++];
    }
    //将temp数组（已排好序）赋给数组a
    int len = right - left + 1;     //合并后的数字长度，注意：这里必须先存起来，因为循环体中的赋值操作改变了left
    for (k = 0; k < len; k++) {
        a[left++] = temp[k];    //注意：是从a[left]开始赋值，而不是a[0]
    }
}

/*
 * 归并排序
 */
void MergeSort(int a[], int left, int right, int temp[]) {
    if (left == right) {
        return;
    }
    int mid = (left + right) / 2;
    MergeSort(a, left, mid, temp);
    MergeSort(a, mid+1, right, temp);
    //合并两个已排好序的子数组
    Merge(a, left, mid, right, temp);
}

/*
 * 调整为大顶堆（从a[i]开始调整）
 */
void adjustHeap(int a[], int i, int length) {
    int temp = a[i];    //保存a[i];
    int k;  //k用于存储子节点
    for (k = i*2 + 1; k < length; k = k*2 + 1) {    //从i节点的左子节点开始
        if (k+1 < length && a[k] < a[k+1]) {    //如果左子节点小于右子节点，则k指向右子节点
            k++;
        }
        if (a[k] > temp) {  //如果子节点大于父节点，将子节点赋给父节点（不用进行交换，子节点的值暂时是temp）
            a[i] = a[k];
            i = k;
        } else {  //否则退出循环
            break;
        }
    }
    //将temp值放到最终的位置
    a[i] = temp;
}

/*
 * 建堆（大顶堆）
 */
int BuildHeap(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) { //从最后一个非叶子节点开始进行堆调整
         adjustHeap(a, i, n);
    }
}

/*
 * 堆排序
 * 1. 将无序序列构建成一个堆，升序选择大顶堆，降序选择小顶堆;
 */
void HeapSort(int a[], int n) {
    //先构建大顶堆
    BuildHeap(a, n);
    //调整堆结构
    int i;
    for (i = n-1; i > 0; i--) {
        swap(a, 0, i);  //交换堆顶元素和末尾元素
        adjustHeap(a, 0, i);    //重新对堆进行排序（不包括已交换到末尾排序好的元素）
    }
}


int main() {
    int a[] = {21, 11, 48, 6, 92, 41, 39, 77, 20, 1};
    int n = sizeof(a)/sizeof(int);
    int temp[n];  //在外面开辟一个临时数组(可重复利用)，避免在归并的递归操作中多次开辟空间

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
        printf("%d ", a[i]);    //正确答案为：1 6 11 20 21 39 41 48 77 92
    }
    printf("\n");

    return 0;
}
