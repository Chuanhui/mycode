
template <typename T> class sorter_t
{
public:
    // ��������
    int qsort(T* begin, T* end);

private:
    const static int sthreshold = 16;

private:
    // �������� (�ٶ����е���СԪ����[begin, begin + threshold)֮��)
    void _insertion_sort(T* begin, T* end, int threshold);

    // [first, last)֮��Ԫ�����򣬱�������last���뵽[first, last)��ʹ��[first, last]����
    inline void _linear_insert(T* first, T* last);

    // ����Ԫ��ʹ�����б��ֳ������֣������Ԫ�� <= pivot <= �ұ�Ԫ��
    inline T* _partition(T* begin, T* end, T pivot);

    // median_of_three: ����Ԫ��ʹ��first < middle < last
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

    // Qsort �����㷨
    void _qsort_loop(T* begin, T* end);
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

template <typename T> T* sorter_t<T>::_partition(T* begin, T* end, T pivot)
{
    while (true)
    {
        while (*begin < pivot)
        {
            ++begin;
        }
        --end;
        while (pivot < *end)
        {
            --end;
        }
        if (!(begin < end))
        {
            break;
        }
        _swap(*begin, *end);
        ++begin;
    }
    return begin;
}

template <typename T> int sorter_t<T>::qsort(T* begin, T* end)
{
    int ret = 0;
    if (NULL == begin || NULL == end)
    {
        fprintf(stderr, "begin or end is NULL");
        ret = -1;
    }
    else
    {
        _qsort_loop(begin, end);
        _insertion_sort(begin, end, sorter_t<T>::sthreshold);
    }
    return ret;
}

template <typename T> void sorter_t<T>::_qsort_loop(T* begin, T* end)
{
    while (end - begin > sorter_t<T>::sthreshold)
    {
        T median_of_three = _median_of_three(*begin, *(begin + (end - begin)/2), *(end - 1));
        T* cut = _partition(begin, end, median_of_three);
        if (cut - begin >= end - cut)
        {
            _qsort_loop(cut, end);
            end = cut;
        } else
        {
            _qsort_loop(begin, cut);
            begin = cut;
        }
    }
}

