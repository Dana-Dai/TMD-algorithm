#include <iostream>
#include <vector>
#include <list>
using namespace std;

void print(int arr[], int n) {
    for (int i = 0; i < n; i ++)
        cout << arr[i] << " ";
    cout << endl;
}

//冒泡排序
void BubbleSort1(int arr[], int n){
    int tmp = 0;
    for (int i = 0; i < n - 1; i ++) {
        for (int j = 0; j < n - i - 1; j ++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// 冒泡排序第一次优化：设置提前退出冒泡循环的标志位：bool flag = false;
void BubbleSort2(int arr[], int n) {
    int tmp = 0;
    for (int i = 0; i < n - 1; i ++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j ++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;                //存在数据交换
            }
        }
        if (!flag) break;                  //提前结束冒泡
    }
}

//冒泡排序第二次优化：设置无序数列边界，每次排序只要排到无序数列边界，因为后面都是有序；
void BubbleSort3(int arr[], int n) {
    int tmp = 0;
    int lastExchangeIndex = 0;
    int sortBorder = n - 1;
    for (int i = 0; i < n - 1; i ++) {
        bool flag = false;
        for (int j = 0; j < sortBorder; j ++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
                lastExchangeIndex = j;         //确定最后一次交换的位置
            }
        }
        sortBorder = lastExchangeIndex;       //确定无序数列的边界
        if (!flag) break;
    }
}

//插入排序：将序列分为已排序序列和未排序序列，从未排序序列取一个元素，插入已排序序列
void InsertionSort1(int arr[], int n) {
    for (int i = 1; i < n; i ++) {    //将第一个元素，即arr[0]视作已排序序列；从未排序序列选一个元素
        int tmp = arr[i];
        int j = i - 1;                //从后往前
        while (j >= 0 && arr[j] > tmp) {   //从后往前的比较操作
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = tmp;
    }
}

//插入排序的第一次优化：利用二分查找减少比较操作次数(对已排序序列进行二分查找)
void InsertionSort2(int arr[], int n) {
    for (int i = 1; i < n; i ++) {
        int left = 0, right = i - 1, tmp = arr[i];
        int j = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > tmp)
                right = mid - 1;
            else
                left = mid + 1;
        }
        while (j >= right + 1) {
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = tmp;
    }
}

//插入排序的第二次优化：希尔排序，设置一个增量，对原始序列进行分组，再缩小增量，直至为1，完成排序
void InsertionSort3(int arr[], int n) {
    //设置增量
    for (int d = n / 2; d > 0; d /= 2)
        //设置每一组最后一个元素的下角标
        for (int i = d; i < n; i ++)
            //同一组内元素比较
            for (int j = i - d; j >= 0; j -= d)
                if (arr[j] > arr[j + d]) {
                    int tmp = arr[j];
                    arr[j] = arr[j + d];
                    arr[j + d] = tmp;
                }

}

//选择排序，类似于插入排序，分为已排序序列和未排序序列，从未排序序列中选择最小的元素放于已排序序列的末尾
void SelectionSort1(int arr[], int n) {
    for (int i = 0; i < n - 1; i ++) {
        int index = i;
        for (int j = i + 1; j < n; j ++) {
            if (arr[j] < arr[index])
                index = j;
        }
        int tmp = arr[i];
        arr[i] = arr[index];
        arr[index] = tmp;
    }
}

//堆排序，减少选择排序的比较次数，实现优化，堆排序的关键在于建堆和调整
void adjust_heap(int arr[], int len, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int maxIdx = index;
    if (left < len && arr[left] > arr[maxIdx]) maxIdx = left;
    if (right < len && arr[right] > arr[maxIdx]) maxIdx = right;
    if (maxIdx != index) {
        swap(arr[index], arr[maxIdx]);
        adjust_heap(arr, len, maxIdx);
    }
}
void HeapSort(int arr[], int len) {
    //建堆
    for (int i = len / 2 - 1; i >= 0; i --)
        adjust_heap(arr, len, i);

    //调整大根堆
    for (int i = len - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        adjust_heap(arr, i, 0);   //i为len - 1，每次大根堆数据减少1，因为前面已经排序，而只是大根堆
    }                                   //和最后一个叶子节点交换位置，只要维护index = 0即可
}

//归并排序，先分解排序再合并  （自下而上，先递归后排序）
void MergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;   //确定分界点
    MergeSort(arr, l, mid), MergeSort(arr, mid + 1, r);   //递归不断分解

    int k = 0, i = l, j = mid + 1;
    vector<int> tmp(r + 1);
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) tmp[k ++] = arr[i ++];
        else tmp[k ++] = arr[j ++];
    }

    while (i <= mid) tmp[k ++] = arr[i ++];
    while (j <= r) tmp[k ++] = arr[j ++];

    for (i = l, k = 0; i <= r; i ++, k++)
        arr[i] = tmp[k];
}

//快速排序，分区排序，选择一个分区点，大于分区点的数放右边，小于分区点的数放左边，不断递归（自上而下，先排序后递归）
void QuickSort(int arr[], int l, int r) {
    if (l < r) {
        int i = l, j = r;
        int k = arr[i];  //任意选一点，而我选择第一点
        while (i < j) {
            while (i < j && arr[j] >= k) j --;
            if (i < j) arr[i ++] = arr[j];     //当遇到不满足条件的j将其保存给arr[i]，而arr[i]已经保存在前面的k值里
            while (i < j && arr[i] <= k) i ++;
            if (i < j) arr[j --] = arr[i];     //当遇到不满足条件的i将其保存给arr[j]，而arr[j]已经保存在前面的arr[i + 1]值里
        }
        arr[i] = k;                   //完成一次排序，将k值赋予下标为i的位置
        QuickSort(arr, l, i - 1);
        QuickSort(arr, i + 1, r);
    }
}

//桶排序
void insert(list<int> &bucket, int val) {
    auto iter = bucket.begin();     //list的begin返回起始位置的iterator
    while (iter != bucket.end() && val > *iter) ++ iter;
    bucket.insert(iter, val);      //在iter这个位置插入一个val；
}

void BucketSort(int arr[], int len) {
    if (len <= 1) return;

    //找到数组的最大值和最小值
    int min = arr[0], max = arr[0];
    for (int i = 0; i < len; i ++) {
        min = arr[i] < min ? arr[i] : min;
        max = arr[i] > max ? arr[i] : max;
    }

    //如果最大值和最小值相等，即数组中为同一个值
    if (max == min) return;

    //创建桶，桶与桶之间的差值
    int k = 20;
    int bucketsNum = (max - min) / k + 1;   //向上取整
    vector<list<int>> buckets(bucketsNum);

    //把数组中的每一个值放入桶中
    for (int i = 0; i < len; i ++) {
        int value = arr[i];
        insert(buckets[(value - min) / k], value);
    }

    //按序把桶里的数据拿出来
    int index = 0;
    for (int i = 0; i < bucketsNum; i ++)
        if (buckets[i].size())
            for (auto &value : buckets[i])
                arr[index ++] = value;
}

//计数排序
void CountingSort(int arr[], int len) {
    //建立计数器，首先要确定计数器个数
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i ++) {
        max = arr[i] > max ? arr[i] : max;
        min = arr[i] < min ? arr[i] : min;
    }
    vector<int> count(max - min + 1, 0);

    //记录频次，即arr中每个值出现的次数
    for (int i = 0; i < len; i ++)
        count[arr[i] - min] ++;

    //累积加数
    for (int i = 1; i <= max - min; i ++)
        count[i] += count[i - 1];

    //倒序遍历原始数列
    vector<int> tmp(len);
    for (int i = len - 1; i >= 0; i --) {
        tmp[count[arr[i] - min] - 1] = arr[i];  //count[arr[i] - min]是指包括自己在内含这么多个，是从71开始计数的；
        count[arr[i] - min] --;                 //而tmp的初始位置为0，因而要-1；
    }

    for(int i = 0; i < len; i ++)
        arr[i] = tmp[i];
}

//基数排序
int max_bit(int arr[], int len) {
    int max = arr[0];
    for (int i = 1; i < len; i ++)
        max = arr[i] > max ? arr[i] : max;
    int bit = 1;
    while (max >= 10) {
        max /= 10;
        bit ++;
    }
    return bit;
}
void RadixSort(int arr[], int len) {
    int d = max_bit(arr, len);
    vector<int> count(10);
    int radix = 1;
    vector<int> tmp(len);
    //进行d次排序
    for (int i = 1; i <= d; i ++) {
        //清空计数器
        for (int j = 0; j < 10; j ++)
            count[j] = 0;

        //记录频次
        for (int j = 0; j < len; j ++)
            count[(arr[j] / radix) % 10] ++;

        //累加
        for (int j = 1; j < 10; j ++)
            count[j] += count[j - 1];

        //倒序遍历原始数列
        for (int j = len - 1; j >= 0; j --) {
            tmp[count[(arr[j] / radix) % 10] - 1] = arr[j];
            count[(arr[j] / radix) % 10] --;
        }

        for (int j = 0; j < len; j ++)
            arr[j] = tmp[j];

        radix = radix * 10;
    }
}

int main(){
    int arr[10]= {91,65,37,84,52,21,73,49,15,6};
    int len = sizeof(arr) / sizeof(arr[0]);   //数组作为参数传递到函数后，使用 sizeof 产生的问题,因为数组作为函数参数传递后，
                                                // 会退化为指针，所以计算 sizeof(s) = 4，即sizeof(arr) / sizeof(arr[0]) = 1
                                                // 所以取前两个值，即9和6
    cout << len << " ";
    cout << endl;
    cout << "初始序列:";
    print(arr, len);
    RadixSort(arr, len);
    cout << "排序结果:";
    print(arr, len);
    return 0;
}
