#include "SortAlgo.h"

#include <iostream>
#include <algorithm>
#include <iterator>

SortAlgo::SortAlgo() {
}

/**
 * Bubble sort: O(n^2)
 * 1. Start at the beginning of the array
 * 2. Compare adjacent elements
 * 3. If the adjacent elements are in wrong order, swap them
 */
std::vector<int> SortAlgo::bubbleSort(std::vector<int> vec) {
    std::cout << "bubbleSort:" << std::endl;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size() - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
    
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    
    return vec;
}

/**
 * Insertion sort: O(n^2)
 * 1. Start at the beginning of the array
 * 2. Insert each pointer into the elements that are on the left of the pointer in ascending order
 * 3. Sort the elements that are on the left of the pointer
 */
std::vector<int> SortAlgo::insertionSort(std::vector<int> vec) {
    std::cout << "insertionSort:" << std::endl;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    
    for (int i = 1; i < vec.size(); i++) {
        int j = i - 1;
        while (j >= 0) {
            if (vec[j] > vec[j + 1]) {
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
            j--;
        }
    }
    
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    
    return vec;
}


std::vector<int> SortAlgo::merge(std::vector<int> lvec, std::vector<int> rvec) {
    std::vector<int> result = std::vector<int>(lvec.size() + rvec.size());
    int pResult = 0;
    int pl = 0;
    int pr = 0;

    // Loop through lvec and rvec
    // Compare elements in lvec and rvec. Insert the smaller into result.
    while (pl < lvec.size() && pr < rvec.size()) {
        if (lvec[pl] > rvec[pr]) {
            result[pResult] = rvec[pr];
            pr++;
        } else {
            result[pResult] = lvec[pl];
            pl++;
        }
        pResult++;
    }

    //If one vector is done, insert the rest of the other
    while (pl < lvec.size()) {
        result[pResult] = lvec[pl];
        pl++;
        pResult++;
    }
    while (pr < rvec.size()) {
        result[pResult] = rvec[pr];
        pr++;
        pResult++;
    }

    return result;
}
/**
 * Merge sort: O(nlogn)
 * 1. Split the array in half until the arrays have only one element:
 * 2. Recursively merge the two halves and sort them:
 *
 * Each merge need to iterate through all the elements from both halve arrays: n
 * The number of the split is O(logn)
 * Time Complexity: O(nlogn)
 *            arr(n)
 *        /          \
 *      l(n/2)      r(n/2)
 *     /     \        /   \
 *   l(n/4)  r(/4)  l(n/4)  r(n/4)
 *   /  \  /  \    /  \
 *  l   r l   r   l   r ...
 */
std::vector<int> SortAlgo::mergeSort(std::vector<int> vec) {
    if (vec.size() <= 1)
        return vec;
    
    int mid = vec.size() / 2;
    std::vector<int> lvec(vec.begin(), vec.begin() + mid);
    std::vector<int> rvec(vec.begin() + mid, vec.end());
    lvec = mergeSort(lvec);
    rvec = mergeSort(rvec);

    vec = merge(lvec, rvec);
    
    return vec;
}

std::vector<int> SortAlgo::quickSort(std::vector<int> vec) {
    if (vec.size() <= 1)
        return vec;
    
    //partition
    int pivot = vec[vec.size() - 1];
    std::vector<int> lessPart;
    std::vector<int> greaterPart;
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i] <= pivot) {
            lessPart.push_back(vec[i]);
        } else {
            greaterPart.push_back(vec[i]);
        }
    }

    lessPart = quickSort(lessPart);
    greaterPart = quickSort(greaterPart);

    // merge partitions
    std::vector<int> result = lessPart;
    result.push_back(pivot);
    result.insert(result.end(), greaterPart.begin(), greaterPart.end());

    return result;
}

void SortAlgo::quickSort2(std::vector<int>& vec, int low, int high) {
    if (low >= high)
        return;
    
    //partition
    int pivot = vec[high];    // Pivot element
    int ptrLessPart = low - 1; // Point to the partition that is less than the pivot
    for (int ptrGreaterPart = low; ptrGreaterPart < high; ptrGreaterPart++) {
        // If current element is smaller than or equal to pivot
        if (vec[ptrGreaterPart] < pivot) {
            ptrLessPart++;
            std::swap(vec[ptrLessPart], vec[ptrGreaterPart]);
        }
    }
    std::swap(vec[ptrLessPart + 1], vec[high]);
    pivot = ptrLessPart + 1;

    quickSort2(vec, low, pivot - 1);
    quickSort2(vec, pivot + 1, high);
}