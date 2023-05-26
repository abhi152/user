#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void printVector(vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void serialBubbleSort(int n, vector<int>& v) {
    for(int i = 0; i < n-1; i++) {
        bool swapped = false;
        for(int j = 0; j < n-i-1; j++) {
            if(v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}

void parallelBubbleSort(int n, vector<int>& v) {
    for(int i = 0; i < n-1; i++) {
        bool swapped = false;
        #pragma omp parallel for shared(v, swapped)
        for(int j = 0; j < n-i-1; j++) {
            if(v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}

void merge(vector<int>& v, int start, int mid, int end) {
    int i=start, j=mid+1, k=0;
    vector<int> temp(end-start+1, 0);
    while(i <= mid && j <= end) {
        if(v[i] < v[j]) {
            temp[k++] = v[i++];
        }
        else {
            temp[k++] = v[j++];
        }
    }
    while(i <= mid) {
        temp[k++] = v[i++];
    }
    while(j <= end) {
        temp[k++] = v[j++];
    }
    for(k=start; k <= end; k++) {
        v[k] = temp[k-start];
    }
}

void serialMergeSort(vector<int>& v, int start, int end) {
    if(start < end) {
        int mid = start + (end - start)/2;
        serialMergeSort(v, start, mid);
        serialMergeSort(v, mid+1, end);
        merge(v, start, mid, end);
    }
}

void parallelMergeSort(vector<int>& v, int start, int end) {
    if(start < end) {
        int mid = start + (end - start)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                serialMergeSort(v, start, mid);
            }

            #pragma omp section
            {
                serialMergeSort(v, mid+1, end);
            }
        }
        merge(v, start, mid, end);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> unsorted = v;

    // Serial Bubble Sort
    double start = omp_get_wtime();
    serialBubbleSort(n, v);
    double end = omp_get_wtime();
    cout << "Serial Bubble Sort: ";
    printVector(v);
    printf("Serial Bubble Sort Time: %g", end - start);
    v = unsorted;

    // Parallel Bubble Sort
    start = omp_get_wtime();
    parallelBubbleSort(n, v);
    end = omp_get_wtime();
    cout << "\nParallel Bubble Sort: ";
    printVector(v);
    printf("Parallel Bubble Sort Time: %g", end - start);
    v = unsorted;

    // Serial Merge Sort
    start = omp_get_wtime();
    serialMergeSort(v, 0, n-1);
    end = omp_get_wtime();
    cout << "\nSerial Merge Sort: ";
    printVector(v);
    printf("Serial Merge Sort Time: %g", end - start);
    v = unsorted;

    // Parallel Merge Sort
    start = omp_get_wtime();
    parallelBubbleSort(n, v);
    end = omp_get_wtime();
    cout << "\nParallel Merge Sort: ";
    printVector(v);
    printf("Parallel Merge Sort Time: %g", end - start);
    v = unsorted;

    return 0;
}

/*
Input:
8
54 49 1 -3 -69 76 98 4

Output:
Serial Bubble Sort: -69 -3 1 4 49 54 76 98 
Serial Bubble Sort Time: 0
Parallel Bubble Sort: -69 -3 1 4 54 49 76 98
Parallel Bubble Sort Time: 0
Serial Merge Sort: -69 -3 1 4 49 54 76 98 
Serial Merge Sort Time: 0
Parallel Merge Sort: -69 -3 1 4 49 54 76 98
Parallel Merge Sort Time: 0
*/