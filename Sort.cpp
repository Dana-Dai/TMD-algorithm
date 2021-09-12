#include <iostream>
#include <vector>
#include <list>
using namespace std;

void print(int arr[], int n) {
    for (int i = 0; i < n; i ++)
        cout << arr[i] << " ";
    cout << endl;
}

//ð������
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

// ð�������һ���Ż���������ǰ�˳�ð��ѭ���ı�־λ��bool flag = false;
void BubbleSort2(int arr[], int n) {
    int tmp = 0;
    for (int i = 0; i < n - 1; i ++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j ++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;                //�������ݽ���
            }
        }
        if (!flag) break;                  //��ǰ����ð��
    }
}

//ð������ڶ����Ż��������������б߽磬ÿ������ֻҪ�ŵ��������б߽磬��Ϊ���涼������
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
                lastExchangeIndex = j;         //ȷ�����һ�ν�����λ��
            }
        }
        sortBorder = lastExchangeIndex;       //ȷ���������еı߽�
        if (!flag) break;
    }
}

//�������򣺽����з�Ϊ���������к�δ�������У���δ��������ȡһ��Ԫ�أ���������������
void InsertionSort1(int arr[], int n) {
    for (int i = 1; i < n; i ++) {    //����һ��Ԫ�أ���arr[0]�������������У���δ��������ѡһ��Ԫ��
        int tmp = arr[i];
        int j = i - 1;                //�Ӻ���ǰ
        while (j >= 0 && arr[j] > tmp) {   //�Ӻ���ǰ�ıȽϲ���
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = tmp;
    }
}

//��������ĵ�һ���Ż������ö��ֲ��Ҽ��ٱȽϲ�������(�����������н��ж��ֲ���)
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

//��������ĵڶ����Ż���ϣ����������һ����������ԭʼ���н��з��飬����С������ֱ��Ϊ1���������
void InsertionSort3(int arr[], int n) {
    //��������
    for (int d = n / 2; d > 0; d /= 2)
        //����ÿһ�����һ��Ԫ�ص��½Ǳ�
        for (int i = d; i < n; i ++)
            //ͬһ����Ԫ�رȽ�
            for (int j = i - d; j >= 0; j -= d)
                if (arr[j] > arr[j + d]) {
                    int tmp = arr[j];
                    arr[j] = arr[j + d];
                    arr[j + d] = tmp;
                }

}

//ѡ�����������ڲ������򣬷�Ϊ���������к�δ�������У���δ����������ѡ����С��Ԫ�ط������������е�ĩβ
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

//�����򣬼���ѡ������ıȽϴ�����ʵ���Ż���������Ĺؼ����ڽ��Ѻ͵���
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
    //����
    for (int i = len / 2 - 1; i >= 0; i --)
        adjust_heap(arr, len, i);

    //���������
    for (int i = len - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        adjust_heap(arr, i, 0);   //iΪlen - 1��ÿ�δ�������ݼ���1����Ϊǰ���Ѿ����򣬶�ֻ�Ǵ����
    }                                   //�����һ��Ҷ�ӽڵ㽻��λ�ã�ֻҪά��index = 0����
}

//�鲢�����ȷֽ������ٺϲ�  �����¶��ϣ��ȵݹ������
void MergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;   //ȷ���ֽ��
    MergeSort(arr, l, mid), MergeSort(arr, mid + 1, r);   //�ݹ鲻�Ϸֽ�

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

//�������򣬷�������ѡ��һ�������㣬���ڷ�����������ұߣ�С�ڷ������������ߣ����ϵݹ飨���϶��£��������ݹ飩
void QuickSort(int arr[], int l, int r) {
    if (l < r) {
        int i = l, j = r;
        int k = arr[i];  //����ѡһ�㣬����ѡ���һ��
        while (i < j) {
            while (i < j && arr[j] >= k) j --;
            if (i < j) arr[i ++] = arr[j];     //������������������j���䱣���arr[i]����arr[i]�Ѿ�������ǰ���kֵ��
            while (i < j && arr[i] <= k) i ++;
            if (i < j) arr[j --] = arr[i];     //������������������i���䱣���arr[j]����arr[j]�Ѿ�������ǰ���arr[i + 1]ֵ��
        }
        arr[i] = k;                   //���һ�����򣬽�kֵ�����±�Ϊi��λ��
        QuickSort(arr, l, i - 1);
        QuickSort(arr, i + 1, r);
    }
}

//Ͱ����
void insert(list<int> &bucket, int val) {
    auto iter = bucket.begin();     //list��begin������ʼλ�õ�iterator
    while (iter != bucket.end() && val > *iter) ++ iter;
    bucket.insert(iter, val);      //��iter���λ�ò���һ��val��
}

void BucketSort(int arr[], int len) {
    if (len <= 1) return;

    //�ҵ���������ֵ����Сֵ
    int min = arr[0], max = arr[0];
    for (int i = 0; i < len; i ++) {
        min = arr[i] < min ? arr[i] : min;
        max = arr[i] > max ? arr[i] : max;
    }

    //������ֵ����Сֵ��ȣ���������Ϊͬһ��ֵ
    if (max == min) return;

    //����Ͱ��Ͱ��Ͱ֮��Ĳ�ֵ
    int k = 20;
    int bucketsNum = (max - min) / k + 1;   //����ȡ��
    vector<list<int>> buckets(bucketsNum);

    //�������е�ÿһ��ֵ����Ͱ��
    for (int i = 0; i < len; i ++) {
        int value = arr[i];
        insert(buckets[(value - min) / k], value);
    }

    //�����Ͱ��������ó���
    int index = 0;
    for (int i = 0; i < bucketsNum; i ++)
        if (buckets[i].size())
            for (auto &value : buckets[i])
                arr[index ++] = value;
}

//��������
void CountingSort(int arr[], int len) {
    //����������������Ҫȷ������������
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i ++) {
        max = arr[i] > max ? arr[i] : max;
        min = arr[i] < min ? arr[i] : min;
    }
    vector<int> count(max - min + 1, 0);

    //��¼Ƶ�Σ���arr��ÿ��ֵ���ֵĴ���
    for (int i = 0; i < len; i ++)
        count[arr[i] - min] ++;

    //�ۻ�����
    for (int i = 1; i <= max - min; i ++)
        count[i] += count[i - 1];

    //�������ԭʼ����
    vector<int> tmp(len);
    for (int i = len - 1; i >= 0; i --) {
        tmp[count[arr[i] - min] - 1] = arr[i];  //count[arr[i] - min]��ָ�����Լ����ں���ô������Ǵ�71��ʼ�����ģ�
        count[arr[i] - min] --;                 //��tmp�ĳ�ʼλ��Ϊ0�����Ҫ-1��
    }

    for(int i = 0; i < len; i ++)
        arr[i] = tmp[i];
}

//��������
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
    //����d������
    for (int i = 1; i <= d; i ++) {
        //��ռ�����
        for (int j = 0; j < 10; j ++)
            count[j] = 0;

        //��¼Ƶ��
        for (int j = 0; j < len; j ++)
            count[(arr[j] / radix) % 10] ++;

        //�ۼ�
        for (int j = 1; j < 10; j ++)
            count[j] += count[j - 1];

        //�������ԭʼ����
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
    int len = sizeof(arr) / sizeof(arr[0]);   //������Ϊ�������ݵ�������ʹ�� sizeof ����������,��Ϊ������Ϊ�����������ݺ�
                                                // ���˻�Ϊָ�룬���Լ��� sizeof(s) = 4����sizeof(arr) / sizeof(arr[0]) = 1
                                                // ����ȡǰ����ֵ����9��6
    cout << len << " ";
    cout << endl;
    cout << "��ʼ����:";
    print(arr, len);
    RadixSort(arr, len);
    cout << "������:";
    print(arr, len);
    return 0;
}
