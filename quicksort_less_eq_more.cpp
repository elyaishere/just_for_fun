// quick sort for three partitions: less, equal, more
#include <vector>
using namespace std;

template <class T>
void quicksort(vector<T>& a, int l, int r) {
    T v = a[r];
    if (r <= l)
        return;
    int i = l, j = r - 1, p = l - 1, q = r;
    while (i <= j) {
        while (a[i] < v) ++i;
        while (a[j] > v) --j;
        if (i >= j) break;
        swap(a[i], a[j]);
        if (a[i] == v) {
            ++p;
            swap(a[p], a[i]);
        }
        ++i;
        if (a[j] == v) {
            --q;
            swap(a[q], a[j]);
        }
        --j;
    }
    swap(a[i], a[r]);
    j = i - 1;
    ++i;
    for (int k = l; k <= p; ++k, --j) {
        swap(a[k], a[j]);
    }
    for (int k = r - 1; k >= q; --k, ++i) {
        swap(a[k], a[i]);
    }
    quicksort(a, l, j);
    quicksort(a, i, r);
}
