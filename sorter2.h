
/*
template <typename T>
inline bool my_less(T& first, T& second)
{
    return first < second;
}
*/

template <typename T>
class Comparator
{
public:
    inline bool operator() (T& first, T& second) const
    {
        return first < second;
    }
};

template <typename T> class sorter_t
{
public:
    // 快速排序
    int qsort(T* begin, T* end, Comparator<T>& my_less);

private:
    const static int sthreshold = 16;

private:
    // 插入排序 (假定序列的最小元素在[begin, begin + threshold)之间)
    void _insertion_sort(T* begin, T* end, int threshold);

    // [first, last)之间元素有序，本函数将last插入到[first, last)中使得[first, last]有序
    inline void _linear_insert(T* first, T* last);

    // 划分元素使得序列被分成两部分，且左边元素 <= pivot <= 右边元素
    inline T* _partition(T* begin, T* end, T pivot, Comparator<T>& my_less);

    // median_of_three: 交换元素使得first < middle < last
    inline const T& _median_of_three(T& first, T& middle, T& last)
    {
        if (middle < first)
        {
            _swap(first, middle);
        }
        if (last < middle)
        {
            _swap(middle, last);
            if (middle < first)
            {
                _swap(first, middle);
            }
        }
        return middle;
    }

    inline void _swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    // Qsort 排序算法
    void _qsort_loop(T* begin, T* end, Comparator<T>& my_less);
};

template <typename T> void sorter_t<T>::_insertion_sort(T* begin, T* end, int threshold)
{
    T* p = NULL;
    if (begin < end)
    {
        T* min = begin;
        for (p = begin + 1; p < begin + threshold && p < end; ++p)
        {
            if (*p < *min)
            {
                min = p;
            }
        }
        _swap(*begin, *min);
        for (p = begin + 1; p < end; ++p)
        {
            _linear_insert(begin, p);
        }
    }
}

template <typename T> void sorter_t<T>::_linear_insert(T* first, T* last)
{
    T value = *last;
    T* p = NULL;

    if (value < *first)
    {
        for (p = last; p > first; --p)
        {
            *p = *(p-1);
        }
        *last = value;
    } else
    {
        p = last - 1;
        while (value < *p)
        {
            *(p+1) = *p;
            --p;
        }
        *(p+1) = value;
    }
}

template <typename T> T* sorter_t<T>::_partition(T* begin, T* end, T pivot, Comparator<T>& my_less)
{
    while (true)
    {
        //while (*begin < pivot)
	while (my_less(*begin, pivot))
        {
            ++begin;
        }
        --end;
        //while (pivot < *end)
	while (my_less(pivot, *end))
        {
            --end;
        }
        //if (!(begin < end))
	while (!my_less(begin, end))
        {
            break;
        }
        _swap(*begin, *end);
        ++begin;
    }
    return begin;
}

template <typename T> int sorter_t<T>::qsort(T* begin, T* end, Comparator<T>& my_less)
{
    int ret = 0;
    if (NULL == begin || NULL == end)
    {
        fprintf(stderr, "begin or end is NULL");
        ret = -1;
    }
    else
    {
        _qsort_loop(begin, end, my_less);
        _insertion_sort(begin, end, sorter_t<T>::sthreshold);
    }
    return ret;
}

template <typename T> void sorter_t<T>::_qsort_loop(T* begin, T* end, Comparator<T>& my_less)
{
    while (end - begin > sorter_t<T>::sthreshold)
    {
        T median_of_three = _median_of_three(*begin, *(begin + (end - begin)/2), *(end - 1));
        T* cut = _partition(begin, end, median_of_three, my_less);
        if (cut - begin >= end - cut)
        {
            _qsort_loop(cut, end, my_less);
            end = cut;
        } else
        {
            _qsort_loop(begin, cut, my_less);
            begin = cut;
        }
    }
}

