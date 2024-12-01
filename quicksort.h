#include <vector>

template <class T> void swap(T *, T *);
template <class T> int partition(std::vector<T> &, int, int);
template <class T> void quicksort(std::vector<T> &);
template <class T> void quicksort_sub(std::vector<T> &, int, int);

template <class T> void swap(T *x, T *y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

template <class T> int partition(std::vector<T> &v, int low, int high) {
    T pivot = v[high];
    int left = low;
    int right = high;
    bool L = true;
    while (left < right) {
        if (!L) {
            if (v[right] < pivot) {
                swap(&v[left], &v[right]);
                left++;
                L = true;
            } else {
                right--;
            }
        } else {
            if (v[left] > pivot) {
                swap(&v[left], &v[right]);
                right--;
                L = false;
            } else {
                left++;
            }
        }
    }
    return right; // or left
}

template <class T> void quicksort(std::vector<T> &v) {
    int low = 0;
    int high = v.size() - 1;
    if (low < high) {
        int pivot = partition(v, low, high);
        quicksort_sub(v, low, pivot - 1);
        quicksort_sub(v, pivot + 1, high);
    }
}

template <class T> void quicksort_sub(std::vector<T> &v, int low, int high) {
    if (low < high) {
        int pivot = partition(v, low, high);
        quicksort_sub(v, low, pivot - 1);
        quicksort_sub(v, pivot + 1, high);
    }
}
