#include "mvector.hpp"

#include <ostream>
#include <string>
#include <sstream>
#include <cstring>
#include <initializer_list>
#include <new>
#include <memory> //TODO std::allocator
#include <cassert>
#include <exception>
#include <cmath>
#include <algorithm> //TODO std::fill_n


namespace gm{

//& Memory allocation and deallocation
// _allocate_memory
template<typename T>
void vector<T>::_allocate_memory(const std::size_t length){
    
    _deallocate_memory();
    
    m_data = new (std::nothrow) T [length] {};
}

// _deallocate_memory
template<typename T>
void vector<T>::_deallocate_memory(){
    if(!m_data)
        return;

    delete [] m_data;

    m_data = nullptr;
}


//& Constructors
// Constructor 1
template<typename T>
vector<T>::vector(const std::size_t length)
        : m_length{length}
{
    m_capacity = m_length == 0 ? 1 : m_length;

    m_data = new T [m_capacity] {};
}

// Constructor 2
template<typename T>
vector<T>::vector(const std::size_t length, const T init_value)
        : vector(length) //? ()
{
    for(std::size_t i; i < length; i++)
        m_data[i] = init_value;
}

// Constructor 3
template<typename T>
vector<T>::vector(const std::initializer_list<T> list)
        : vector(list.size())
{
    std::size_t i;
    for(auto element: list) // T Element: list
        m_data[i++] = element;
}

// Constructor 4
template<typename T>
vector<T>::vector(const T * carray, const std::size_t carray_len, const std::size_t offset)
{
    if(static_cast<int>(carray_len) - static_cast<int>(offset) < 0)
        throw std::length_error("The result of (carray_len - offset) must be non-negative.");
    ////assert( static_cast<int>(carray_len) - static_cast<int>(offset) >= 0);
    
    m_length = carray_len - offset;
    m_capacity = m_length == 0 ? 1 : m_length;
    _allocate_memory(m_capacity);

    for(std::size_t i{}; i < m_length; ++i){
        m_data[i] = carray[i+offset];
    }
}

//& Copy Initialization
template<typename T>
vector<T>::vector(const vector& orig_vector){
    m_length = orig_vector.m_length;
    m_capacity = orig_vector.m_capacity;

    _allocate_memory(m_capacity);

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] = orig_vector.m_data[i];
}

//& Copy Assignment
template<typename T>
vector<T>& vector<T>::operator=(const vector& orig_vector){
    if(this == &orig_vector) // or *this == orig_vector
        return *this;
    
    // deleting old data
    _deallocate_memory();

    m_length = orig_vector.m_length;
    m_capacity = orig_vector.m_capacity;

    _allocate_memory(m_capacity);

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] = orig_vector.m_data[i];

    return *this;
}

//& Destructor
template<typename T>
vector<T>::~vector(){
    _deallocate_memory();
}

//& _get_next_capacity
template<typename T>
std::size_t vector<T>::_get_next_capacity() const{
    std::size_t new_capacity { static_cast<std::size_t>( pow(static_cast<double>(m_capacity), 1.3) ) };

    new_capacity = new_capacity == m_capacity ? m_capacity + 1 : new_capacity;

    return new_capacity;
}

//& length and capacity
template<typename T>
std::size_t vector<T>::length() const{
    return m_length;
}

template<typename T>
std::size_t vector<T>::capacity() const{
    return m_capacity;
}

//& Resize
template<typename T>
void vector<T>::resize(const std::size_t new_length){
    if (new_length > m_capacity)
        this->reserve(new_length);
    
    ////if(new_length > m_length){
    ////    ////for(std::size_t i{m_length}; i < new_length; ++i)
    ////    ////    memset(&m_data[i], 0, sizeof(T));
    ////    memset(&m_data[m_length], 0, sizeof(T)*(new_length - m_length));
    ////}

    const std::size_t * left_ptr { new_length < m_length ? &new_length : &m_length };
    const std::size_t * right_ptr { new_length > m_length ? &new_length : &m_length };

    memset(&m_data[*left_ptr], 0, sizeof(T)*(*right_ptr - *left_ptr));

    m_length = new_length;
}

template<typename T>
void vector<T>::resize(const std::size_t new_length, const T repl_value){
    if (new_length > m_capacity)
        this->reserve(new_length);
    
    const std::size_t * left_ptr { new_length < m_length ? &new_length : &m_length };
    const std::size_t * right_ptr { new_length > m_length ? &new_length : &m_length };

    for(std::size_t i{*left_ptr}; i < (*right_ptr); i++)
        m_data[i] = repl_value;

    m_length = new_length;
}

//& reserve 
template<typename T>
void vector<T>::reserve(const std::size_t new_capacity){

    if(new_capacity == 0)
        throw std::runtime_error("new_capacity must be non-zero.");
    else if(new_capacity == m_capacity)
        return;

    const std::size_t * length_ptr{ new_capacity < m_length ? &new_capacity : &m_length };
    T * temp_ptr{new T [new_capacity] {}};

    for(std::size_t i{}; i < (*length_ptr); ++i)
        temp_ptr[i] = m_data[i];
    
    m_length = *length_ptr;
    m_capacity = new_capacity;

    _deallocate_memory();
    m_data = temp_ptr; //TODO std::move

    temp_ptr = nullptr;
}


//& shrink_to_fit
template<typename T>
void vector<T>::shrink_to_fit(){
    if(m_length == m_capacity)
        return;
    
    T * temp_ptr{ new T [m_length] {} };
    for(std::size_t i{}; i < m_length; i++)
        temp_ptr[i] = m_data[i];

    _deallocate_memory();
    m_capacity = m_length;

    m_data = temp_ptr; //TODO std::move
}

//& Erase
template<typename T>
void vector<T>::erase(){
    m_length = 0;
    m_capacity = 1;

    _deallocate_memory();
}


//& data
template<typename T>
T* vector<T>::data(){
    return m_data;
}

template<typename T>
const T* vector<T>::cdata() const{
    return m_data;
}

//& Getting elements
template<typename T>
T& vector<T>::at(const std::size_t index){
    if (index > m_length)
        throw std::out_of_range(std::to_string(index).append(std::string{" Index is out of range: [0, "}.append(std::to_string(m_length)).append(").")));

    return m_data[index];
}

template<typename T>
T& vector<T>::operator[](const std::size_t index){
    return this->at(index);
}


//& operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& vec){
    
    std::stringstream sstr("{ ");
    for(std::size_t i{}; i < vec.m_length; ++i)
        sstr << vec.m_data[i] << ", ";
    
    auto str{sstr.str()};
    out << str.substr(0, str.length() - 2).append(" }");

    return out;
}

//& Math Operators
//@ operator+, operator+=
template<typename T>
vector<T> operator+(const vector<T>& vec, const T value){
    vector<T> temp(vec.m_length());

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = vec[i] + value;
    
    return temp;
}

template<typename T>
vector<T> operator+(const T value, const vector<T>& vec){
    return (vec + value); // calls operator+(const vector<T>, const T);
}

template<typename T>
vector<T> operator+(const vector<T>& vec1, const vector<T>& vec2){
    if(vec1.m_length != vec2.m_length)
        throw std::range_error("vec1 and vec2 must have the same length (size)");
    
    vector<T> temp(vec1.m_length);

    for(std::size_t i{}; i < vec1.length; ++i)
        temp[i] = vec1[i] + vec2[i];
    
    return temp;
}

template<typename T>
void vector<T>::operator+=(const T value){
    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] += value;
}

template<typename T>
void vector<T>::operator+=(const vector<T> vec){
    if(m_length != vec.m_length)
        throw std::range_error("Both vectors must have the same length (size)");

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] += vec.m_data[i];
}


//@ operator-, operator-=
template<typename T>
vector<T> operator-(const vector<T>& vec, const T value){
    vector<T> temp(vec.m_length());

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = vec[i] - value;
    
    return temp;
}

template<typename T>
vector<T> operator-(const T value, const vector<T>& vec){
    //TODO return -(vec - value); // calls operator+(const vector<T>, const T);

    vector<T> temp(vec.m_length());

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = value - vec[i];
    
    return temp;
}

template<typename T>
vector<T> operator-(const vector<T>& vec1, const vector<T>& vec2){
    if(vec1.m_length != vec2.m_length)
        throw std::range_error("vec1 and vec2 must have the same length (size)");
    
    vector<T> temp(vec1.m_length);

    for(std::size_t i{}; i < vec1.length; ++i)
        temp[i] = vec1[i] - vec2[i];
    
    return temp;
}

template<typename T>
void vector<T>::operator-=(const T value){
    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] -= value;
}

template<typename T>
void vector<T>::operator-=(const vector<T> vec){
    if(m_length != vec.m_length)
        throw std::range_error("Both vectors must have the same length (size)");

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] -= vec.m_data[i];
}

//@ operator*, operator*=
template<typename T>
vector<T> operator*(const vector<T>& vec, const T value){
    vector<T> temp(vec.m_length());

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = vec[i]*value;
    
    return temp;
}

template<typename T>
vector<T> operator*(const T value, const vector<T>& vec){
    return (vec*value); // calls operator*(const vector<T>, const T);
}

template<typename T>
vector<T> operator*(const vector<T>& vec1, const vector<T>& vec2){
    if(vec1.m_length != vec2.m_length)
        throw std::range_error("vec1 and vec2 must have the same length (size)");
    
    vector<T> temp(vec1.m_length);

    for(std::size_t i{}; i < vec1.length; ++i)
        temp[i] = vec1[i]*vec2[i];
    
    return temp;
}

template<typename T>
void vector<T>::operator*=(const T value){
    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] *= value;
}

template<typename T>
void vector<T>::operator*=(const vector<T> vec){
    if(m_length != vec.m_length)
        throw std::range_error("Both vectors must have the same length (size)");

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] *= vec.m_data[i];
}

//@ operator/, operator/=
template<typename T, typename U>
vector<T> operator/(const vector<T>& vec, const U value){
    vector<T> temp (vec.m_length);

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = vec.m_data[i]/value;
    
    return temp;
}

template<typename T>
vector<T> operator/(const T value, const vector<T>& vec){
    return (vec/value); // calls operator/(const vector<T>, const T);
}

template<typename T>
vector<T> operator/(const vector<T>& vec1, const vector<T>& vec2){
    if(vec1.m_length != vec2.m_length)
        throw std::range_error("vec1 and vec2 must have the same length (size)");
    
    vector<T> temp(vec1.m_length);

    for(std::size_t i{}; i < vec1.length; ++i)
        temp[i] = vec1[i]/vec2[i];
    
    return temp;
}

template<typename T>
void vector<T>::operator/=(const T value){
    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] /= value;
}

template<typename T>
void vector<T>::operator/=(const vector<T> vec){
    if(m_length != vec.m_length)
        throw std::range_error("Both vectors must have the same length (size)");

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] /= vec.m_data[i];
}

//@ operator%, operator%=
template<typename T>
vector<T> operator%(const vector<T>& vec, const T value){
    vector<T> temp(vec.m_length());

    for(std::size_t i{}; i < vec.m_length; ++i)
        temp[i] = vec[i] % value;
    
    return temp;
}

template<typename T>
vector<T> operator%(const T value, const vector<T>& vec){
    return (vec % value); // calls operator%(const vector<T>, const T);
}

template<typename T>
vector<T> operator%(const vector<T>& vec1, const vector<T>& vec2){
    if(vec1.m_length != vec2.m_length)
        throw std::range_error("vec1 and vec2 must have the same length (size)");
    
    vector<T> temp(vec1.m_length);

    for(std::size_t i{}; i < vec1.length; ++i)
        temp[i] = vec1[i] % vec2[i];
    
    return temp;
}

template<typename T>
void vector<T>::operator%=(const T value){
    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] %= value;
}

template<typename T>
void vector<T>::operator%=(const vector<T> vec){
    if(m_length != vec.m_length)
        throw std::range_error("Both vectors must have the same length (size)");

    for(std::size_t i{}; i < m_length; ++i)
        m_data[i] %= vec.m_data[i];
}


}