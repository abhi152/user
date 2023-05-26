#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int serialMin(int n, vector<int>& v) {
    int mini = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(v[i] < mini)  {
            mini = v[i];
        }
    }
    return mini;
}

int parallelMin(int n, vector<int>& v) {
    int mini = INT_MAX;
    #pragma omp parallel for reduction(min : mini)
    for(int i = 0; i < n; i++) {
        if(v[i] < mini)  {
            mini = v[i];
        }
    }
    return mini;
}

int serialMax(int n, vector<int>& v) {
    int maxi = INT_MIN;
    for(int i = 0; i < n; i++) {
        if(v[i] > maxi)  {
            maxi = v[i];
        }
    }
    return maxi;
}

int parallelMax(int n, vector<int>& v) {
    int maxi = INT_MIN;
    #pragma omp parallel for reduction(max : maxi)
    for(int i = 0; i < n; i++) {
        if(v[i] > maxi)  {
            maxi = v[i];
        }
    }
    return maxi;
}

int serialSum(int n, vector<int>& v) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum;
}

int parallelSum(int n, vector<int>& v) {
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum;
}

int serialAvg(int n, vector<int>& v) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum*1.0/n;
}

int parallelAvg(int n, vector<int>& v) {
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    return sum*1.0/n;
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // Serial Min 
    double start = omp_get_wtime();
    cout << "Serial Minimum: " << serialMin(n, v) << endl;
    double end = omp_get_wtime();
    printf("Serial Minimum Time: %g", end - start);

    // Parallel Min
    start = omp_get_wtime();
    cout << "\nParallel Minimum: " << parallelMin(n, v) << endl;
    end = omp_get_wtime();
    printf("Parallel Minimum Time: %g", end - start);

    // Serial Max
    start = omp_get_wtime();
    cout << "\nSerial Maximum: " << serialMax(n, v) << endl;
    end = omp_get_wtime();
    printf("Serial Maximum Time: %g", end - start);

    // Parallel Max
    start = omp_get_wtime();
    cout << "\nParallel Maximum: " << parallelMax(n, v) << endl;
    end = omp_get_wtime();
    printf("Parallel Maximum Time: %g", end - start);

    // Serial Sum
    start = omp_get_wtime();
    cout << "\nSerial Sum: " << serialSum(n, v) << endl;
    end = omp_get_wtime();
    printf("Serial Sum Time: %g", end - start);

    // Parallel Sum
    start = omp_get_wtime();
    cout << "\nParallel Sum: " << parallelSum(n, v) << endl;
    end = omp_get_wtime();
    printf("Parallel Sum Time: %g", end - start);

    // Serial Average
    start = omp_get_wtime();
    cout << "\nSerial Average: " << serialAvg(n, v) << endl;
    end = omp_get_wtime();
    printf("Serial Average Time: %g", end - start);

    // Parallel Average
    start = omp_get_wtime();
    cout << "\nParallel Average: " << parallelAvg(n, v) << endl;
    end = omp_get_wtime();
    printf("Parallel Average Time: %g", end - start);

    return 0;
}

/*
Input:
8
54 49 1 -3 -69 76 98 4

Output:
*/