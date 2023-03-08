#include <cstdint>
#include <climits>

#ifndef RADIX_SORT_H
#define RADIX_SORT_H

namespace RadixSort {

using std::size_t;

const size_t values_in_byte = 1U << CHAR_BIT;

template<int index, typename T>
inline size_t byte(T value)
{
    const size_t lsb_mask = values_in_byte - 1;
    return (value >> (index * CHAR_BIT)) & lsb_mask;
}

template<typename T, typename ExtractByteFuncT, typename BitwiseTransformFuncT>
void copy_with_reordering(T* array, T* array_end, T* temp, size_t size, size_t* freq, 
                          ExtractByteFuncT extract_byte_f, 
                          BitwiseTransformFuncT bitwise_transform_f)
{
    size_t unroll_size = size >> 2;

    T* p = array;

    for (; unroll_size; --unroll_size, p += 4)
    {
        auto p0 = bitwise_transform_f(*p);
        auto p1 = bitwise_transform_f(*(p+1));
        auto p2 = bitwise_transform_f(*(p+2));
        auto p3 = bitwise_transform_f(*(p+3));
        
        temp[freq[extract_byte_f(p0)]++] = *p;
        temp[freq[extract_byte_f(p1)]++] = *(p+1);
        temp[freq[extract_byte_f(p2)]++] = *(p+2);
        temp[freq[extract_byte_f(p3)]++] = *(p+3);
    }
    
    for (; p != array_end; ++p) 
    {
        auto p0 = bitwise_transform_f(*p); 
        temp[freq[extract_byte_f(p0)]++] = *p; 
    }
}

void radix_sort_calculate_offset_table_16(size_t* freq_0, size_t* freq_1)
{
    size_t offset_0 = 0;
    size_t offset_1 = 0;
 
    for (size_t i = 0; i < values_in_byte; i += 4)
    {
        size_t temp_offset = freq_0[i] + offset_0;
        freq_0[i] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+1] + offset_0; 
        freq_0[i+1] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+2] + offset_0; 
        freq_0[i+2] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+3] + offset_0; 
        freq_0[i+3] = offset_0; 
        offset_0 = temp_offset;

        temp_offset = freq_1[i] + offset_1; 
        freq_1[i] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+1] + offset_1; 
        freq_1[i+1] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+2] + offset_1; 
        freq_1[i+2] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+3] + offset_1; 
        freq_1[i+3] = offset_1; 
        offset_1 = temp_offset;
    }
}

void radix_sort_calculate_offset_table_32(size_t* freq_0, size_t* freq_1,
                                          size_t* freq_2, size_t* freq_3)
{
    size_t offset_0 = 0;
    size_t offset_1 = 0; 
    size_t offset_2 = 0;
    size_t offset_3 = 0;

    for (size_t i = 0; i < values_in_byte; i += 4)
    {
        size_t temp_offset = freq_0[i] + offset_0;
        freq_0[i] = offset_0;
        offset_0 = temp_offset;

        temp_offset = freq_0[i+1] + offset_0;
        freq_0[i+1] = offset_0;
        offset_0 = temp_offset;

        temp_offset = freq_0[i+2] + offset_0;
        freq_0[i+2] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+3] + offset_0;
        freq_0[i+3] = offset_0;
        offset_0 = temp_offset;

        temp_offset = freq_1[i] + offset_1;
        freq_1[i] = offset_1;
        offset_1 = temp_offset;

        temp_offset = freq_1[i+1] + offset_1;
        freq_1[i+1] = offset_1;
        offset_1 = temp_offset;

        temp_offset = freq_1[i+2] + offset_1;
        freq_1[i+2] = offset_1;
        offset_1 = temp_offset;

        temp_offset = freq_1[i+3] + offset_1;
        freq_1[i+3] = offset_1;
        offset_1 = temp_offset;

        temp_offset = freq_2[i] + offset_2;
        freq_2[i] = offset_2;
        offset_2 = temp_offset;

        temp_offset = freq_2[i+1] + offset_2;
        freq_2[i+1] = offset_2;
        offset_2 = temp_offset;

        temp_offset = freq_2[i+2] + offset_2;
        freq_2[i+2] = offset_2;
        offset_2 = temp_offset;

        temp_offset = freq_2[i+3] + offset_2;
        freq_2[i+3] = offset_2;
        offset_2 = temp_offset;

        temp_offset = freq_3[i] + offset_3;
        freq_3[i] = offset_3;
        offset_3 = temp_offset;

        temp_offset = freq_3[i+1] + offset_3;
        freq_3[i+1] = offset_3;
        offset_3 = temp_offset;

        temp_offset = freq_3[i+2] + offset_3;
        freq_3[i+2] = offset_3;
        offset_3 = temp_offset;

        temp_offset = freq_3[i+3] + offset_3;
        freq_3[i+3] = offset_3;
        offset_3 = temp_offset;
    }
}

void radix_sort_calculate_offset_table_64(size_t* freq_0, size_t* freq_1,
                                          size_t* freq_2, size_t* freq_3,
                                          size_t* freq_4, size_t* freq_5,
                                          size_t* freq_6, size_t* freq_7)
{
    size_t offset_0 = 0;
    size_t offset_1 = 0;
    size_t offset_2 = 0;
    size_t offset_3 = 0;
    size_t offset_4 = 0;
    size_t offset_5 = 0;
    size_t offset_6 = 0;
    size_t offset_7 = 0;

    for (size_t i = 0; i < values_in_byte; i += 4)
    {
        size_t temp_offset = freq_0[i] + offset_0; 
        freq_0[i] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+1] + offset_0; 
        freq_0[i+1] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+2] + offset_0; 
        freq_0[i+2] = offset_0; 
        offset_0 = temp_offset;
        
        temp_offset = freq_0[i+3] + offset_0; 
        freq_0[i+3] = offset_0; 
        offset_0 = temp_offset;

        temp_offset = freq_1[i] + offset_1; 
        freq_1[i] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+1] + offset_1; 
        freq_1[i+1] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+2] + offset_1; 
        freq_1[i+2] = offset_1; 
        offset_1 = temp_offset;
        
        temp_offset = freq_1[i+3] + offset_1; 
        freq_1[i+3] = offset_1; 
        offset_1 = temp_offset;

        temp_offset = freq_2[i] + offset_2; 
        freq_2[i] = offset_2; 
        offset_2 = temp_offset;
        
        temp_offset = freq_2[i+1] + offset_2; 
        freq_2[i+1] = offset_2; 
        offset_2 = temp_offset;
        
        temp_offset = freq_2[i+2] + offset_2; 
        freq_2[i+2] = offset_2; 
        offset_2 = temp_offset;
        
        temp_offset = freq_2[i+3] + offset_2; 
        freq_2[i+3] = offset_2; 
        offset_2 = temp_offset;

        temp_offset = freq_3[i] + offset_3; 
        freq_3[i] = offset_3; 
        offset_3 = temp_offset;
        
        temp_offset = freq_3[i+1] + offset_3; 
        freq_3[i+1] = offset_3; 
        offset_3 = temp_offset;
        
        temp_offset = freq_3[i+2] + offset_3; 
        freq_3[i+2] = offset_3; 
        offset_3 = temp_offset;
        
        temp_offset = freq_3[i+3] + offset_3; 
        freq_3[i+3] = offset_3; 
        offset_3 = temp_offset;

        temp_offset = freq_4[i] + offset_4; 
        freq_4[i] = offset_4; 
        offset_4 = temp_offset;
        
        temp_offset = freq_4[i+1] + offset_4; 
        freq_4[i+1] = offset_4; 
        offset_4 = temp_offset;
        
        temp_offset = freq_4[i+2] + offset_4; 
        freq_4[i+2] = offset_4; 
        offset_4 = temp_offset;
        
        temp_offset = freq_4[i+3] + offset_4; 
        freq_4[i+3] = offset_4; 
        offset_4 = temp_offset;

        temp_offset = freq_5[i] + offset_5; 
        freq_5[i] = offset_5; 
        offset_5 = temp_offset;
        
        temp_offset = freq_5[i+1] + offset_5; 
        freq_5[i+1] = offset_5; 
        offset_5 = temp_offset;
        
        temp_offset = freq_5[i+2] + offset_5; 
        freq_5[i+2] = offset_5; 
        offset_5 = temp_offset;
        
        temp_offset = freq_5[i+3] + offset_5; 
        freq_5[i+3] = offset_5; 
        offset_5 = temp_offset;

        temp_offset = freq_6[i] + offset_6; 
        freq_6[i] = offset_6; 
        offset_6 = temp_offset;
        
        temp_offset = freq_6[i+1] + offset_6; 
        freq_6[i+1] = offset_6; 
        offset_6 = temp_offset;
        
        temp_offset = freq_6[i+2] + offset_6; 
        freq_6[i+2] = offset_6; 
        offset_6 = temp_offset;
        
        temp_offset = freq_6[i+3] + offset_6; 
        freq_6[i+3] = offset_6; 
        offset_6 = temp_offset;

        temp_offset = freq_7[i] + offset_7; 
        freq_7[i] = offset_7; 
        offset_7 = temp_offset;
        
        temp_offset = freq_7[i+1] + offset_7; 
        freq_7[i+1] = offset_7; 
        offset_7 = temp_offset;
        
        temp_offset = freq_7[i+2] + offset_7; 
        freq_7[i+2] = offset_7; 
        offset_7 = temp_offset;
        
        temp_offset = freq_7[i+3] + offset_7; 
        freq_7[i+3] = offset_7; 
        offset_7 = temp_offset;
    }
}

template <typename T, typename F>
void radix_sort_16_impl(T* array, size_t size, T* temp, F bitwise_transform)
{
    size_t frequencies[2][values_in_byte] = { 0 };

    size_t* freq_0 = frequencies[0];
    size_t* freq_1 = frequencies[1];

    T* array_end = array + size;
    T* temp_end = temp + size;

    size_t unroll_size = size >> 2;

    T* p = array;

    for (; unroll_size; --unroll_size, p += 4)
    {
        auto element0 = bitwise_transform(*p);
        auto element1 = bitwise_transform(*(p+1));
        auto element2 = bitwise_transform(*(p+2));
        auto element3 = bitwise_transform(*(p+3));

        freq_0[byte<0>(element0)]++;
        freq_1[byte<1>(element0)]++;

        freq_0[byte<0>(element1)]++;
        freq_1[byte<1>(element1)]++;

        freq_0[byte<0>(element2)]++;
        freq_1[byte<1>(element2)]++;

        freq_0[byte<0>(element3)]++;
        freq_1[byte<1>(element3)]++;
    }

    for (; p != array_end; ++p)
    {
        auto h = bitwise_transform(*p);

        freq_0[byte<0>(h)]++;
        freq_1[byte<1>(h)]++;
    }

    radix_sort_calculate_offset_table_16(freq_0, freq_1);

    using Ret = decltype(bitwise_transform(T()));

    copy_with_reordering(array, array_end, temp, size, freq_0, byte<0, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_1, byte<1, Ret>, bitwise_transform);
}

template <typename T, typename F>
void radix_sort_32_impl(T* array, size_t size, T* temp, F bitwise_transform)
{
    size_t frequencies[4][values_in_byte] = { 0 };

    size_t* freq_0 = frequencies[0];
    size_t* freq_1 = frequencies[1];
    size_t* freq_2 = frequencies[2];
    size_t* freq_3 = frequencies[3];

    T* array_end = array + size;
    T* temp_end = temp + size;

    size_t unroll_size = size >> 2;

    T* p = array;

    for (; unroll_size; --unroll_size, p += 4)
    {
        auto element0 = bitwise_transform(*(p));
        auto element1 = bitwise_transform(*(p+1));
        auto element2 = bitwise_transform(*(p+2));
        auto element3 = bitwise_transform(*(p+3));

        freq_0[byte<0>(element0)]++;
        freq_1[byte<1>(element0)]++;
        freq_2[byte<2>(element0)]++;
        freq_3[byte<3>(element0)]++;

        freq_0[byte<0>(element1)]++;
        freq_1[byte<1>(element1)]++;
        freq_2[byte<2>(element1)]++;
        freq_3[byte<3>(element1)]++;

        freq_0[byte<0>(element2)]++;
        freq_1[byte<1>(element2)]++;
        freq_2[byte<2>(element2)]++;
        freq_3[byte<3>(element2)]++;

        freq_0[byte<0>(element3)]++;
        freq_1[byte<1>(element3)]++;
        freq_2[byte<2>(element3)]++;
        freq_3[byte<3>(element3)]++;
    }

    for (; p != array_end; ++p)
    {
        auto h = bitwise_transform(*p);

        freq_0[byte<0>(h)]++;
        freq_1[byte<1>(h)]++;
        freq_2[byte<2>(h)]++;
        freq_3[byte<3>(h)]++;
    }

    radix_sort_calculate_offset_table_32(freq_0, freq_1, freq_2, freq_3);

    using Ret = decltype(bitwise_transform(T()));

    copy_with_reordering(array, array_end, temp, size, freq_0, byte<0, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_1, byte<1, Ret>, bitwise_transform);
    copy_with_reordering(array, array_end, temp, size, freq_2, byte<2, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_3, byte<3, Ret>, bitwise_transform);
}

template <typename T, typename F>
void radix_sort_64_impl(T* array, size_t size, T* temp, F bitwise_transform)
{
    size_t frequencies[8][values_in_byte] = { 0 };

    size_t* freq_0 = frequencies[0];
    size_t* freq_1 = frequencies[1];
    size_t* freq_2 = frequencies[2];
    size_t* freq_3 = frequencies[3];
    size_t* freq_4 = frequencies[4];
    size_t* freq_5 = frequencies[5];
    size_t* freq_6 = frequencies[6];
    size_t* freq_7 = frequencies[7];

    T* array_end = array + size;
    T* temp_end = temp + size;

    size_t unroll_size = size >> 2;

    T* p = array;

    for (; unroll_size; --unroll_size, p += 4)
    {
        auto element0 = bitwise_transform(*p);
        auto element1 = bitwise_transform(*(p + 1));
        auto element2 = bitwise_transform(*(p + 2));
        auto element3 = bitwise_transform(*(p + 3));

        freq_0[byte<0>(element0)]++;
        freq_1[byte<1>(element0)]++;
        freq_2[byte<2>(element0)]++;
        freq_3[byte<3>(element0)]++;
        freq_4[byte<4>(element0)]++;
        freq_5[byte<5>(element0)]++;
        freq_6[byte<6>(element0)]++;
        freq_7[byte<7>(element0)]++;

        freq_0[byte<0>(element1)]++;
        freq_1[byte<1>(element1)]++;
        freq_2[byte<2>(element1)]++;
        freq_3[byte<3>(element1)]++;
        freq_4[byte<4>(element1)]++;
        freq_5[byte<5>(element1)]++;
        freq_6[byte<6>(element1)]++;
        freq_7[byte<7>(element1)]++;

        freq_0[byte<0>(element2)]++;
        freq_1[byte<1>(element2)]++;
        freq_2[byte<2>(element2)]++;
        freq_3[byte<3>(element2)]++;
        freq_4[byte<4>(element2)]++;
        freq_5[byte<5>(element2)]++;
        freq_6[byte<6>(element2)]++;
        freq_7[byte<7>(element2)]++;

        freq_0[byte<0>(element3)]++;
        freq_1[byte<1>(element3)]++;
        freq_2[byte<2>(element3)]++;
        freq_3[byte<3>(element3)]++;
        freq_4[byte<4>(element3)]++;
        freq_5[byte<5>(element3)]++;
        freq_6[byte<6>(element3)]++;
        freq_7[byte<7>(element3)]++;
    }

    for (; p != array_end; ++p)
    {
        auto h = bitwise_transform(*p);

        freq_0[byte<0>(h)]++;
        freq_1[byte<1>(h)]++;
        freq_2[byte<2>(h)]++;
        freq_3[byte<3>(h)]++;
        freq_4[byte<4>(h)]++;
        freq_5[byte<5>(h)]++;
        freq_6[byte<6>(h)]++;
        freq_7[byte<7>(h)]++;
    }

    radix_sort_calculate_offset_table_64(freq_0, freq_1, freq_2, freq_3, freq_4, freq_5, freq_6, freq_7);

    using Ret = decltype(bitwise_transform(T()));

    copy_with_reordering(array, array_end, temp, size, freq_0, byte<0, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_1, byte<1, Ret>, bitwise_transform);
    copy_with_reordering(array, array_end, temp, size, freq_2, byte<2, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_3, byte<3, Ret>, bitwise_transform);

    copy_with_reordering(array, array_end, temp, size, freq_4, byte<4, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_5, byte<5, Ret>, bitwise_transform);
    copy_with_reordering(array, array_end, temp, size, freq_6, byte<6, Ret>, bitwise_transform);
    copy_with_reordering(temp, temp_end, array, size, freq_7, byte<7, Ret>, bitwise_transform);
}

void radix_sort(uint16_t* array, size_t size, uint16_t* temp)
{
    auto identity = [](uint16_t v) -> uint16_t
    {
        return v;
    };

    radix_sort_16_impl(array, size, temp, identity);
}

void radix_sort(int16_t* array, size_t size, int16_t* temp)
{
    auto flip_sign = [](int16_t v) -> uint16_t
    {
        return *reinterpret_cast<uint16_t*>(&v) ^ (uint16_t(1) << 15);
    };

    radix_sort_16_impl(array, size, temp, flip_sign);
}

void radix_sort(uint32_t * array, size_t size, uint32_t* temp)
{
    auto identity = [](uint32_t v) -> uint32_t
    {
        return v;
    };

    radix_sort_32_impl(array, size, temp, identity);
}

void radix_sort(int32_t * array, size_t size, int32_t* temp)
{
    auto flip_sign = [](int32_t v) -> uint32_t
    {
        return *reinterpret_cast<uint32_t*>(&v) ^ (uint32_t(1) << 31);
    };

    radix_sort_32_impl(array, size, temp, flip_sign);
}

void radix_sort(uint64_t* array, size_t size, uint64_t* temp)
{
    auto identity = [](uint64_t v) -> uint64_t
    {
        return v;
    };

    radix_sort_64_impl(array, size, temp, identity);
}

void radix_sort(int64_t * array, size_t size, int64_t* temp)
{
    auto flip_sign = [](int64_t v) -> uint64_t
    {
        return *reinterpret_cast<uint64_t*>(&v) ^ (uint64_t(1) << 63);
    };

    radix_sort_64_impl(array, size, temp, flip_sign);
}

void radix_sort(float* array, size_t size, float* temp)
{
    auto flip = [](float v) -> uint32_t
    {
        uint32_t as_uint = *reinterpret_cast<uint32_t*>(&v);
        uint32_t mask = -int32_t(as_uint >> 31) | (uint32_t(1) << 31);
        return as_uint ^ mask;
    };

    radix_sort_32_impl(array, size, temp, flip);
}

void radix_sort(uint8_t * array, size_t size)
{    
    size_t frequencies[values_in_byte] = { 0 };

    for(size_t i = 0; i < size; ++i)
        ++frequencies[array[i]];

    size_t write_index = 0;

    for(size_t value = 0; value < values_in_byte; ++value)
    {
        size_t element_count = frequencies[value];

        for (size_t i = 0; i < element_count; ++i, ++write_index)
            array[write_index] = uint8_t(value);
    }
}

void radix_sort(int8_t * array, size_t size)
{
    size_t frequencies[values_in_byte] = { 0 };

    for(size_t i = 0; i < size; ++i)
        ++frequencies[int32_t(array[i]) + int32_t(128)];

    size_t write_index = 0;

    for(int32_t value = 0; value < values_in_byte; ++value)
    {
        size_t element_count = frequencies[value];

        const int8_t write_value = int8_t(value - int32_t(128));

        for (size_t i = 0; i < element_count; ++i, ++write_index)
            array[write_index] = write_value;
    }
}

template <typename T>
void radix_sort(T* array, size_t size)
{
    T * temp = new T[size];
    radix_sort(array, size, temp);
    delete[] temp;
}

}; // end namespace RadixSort
#endif //RADIX_SORT_H
