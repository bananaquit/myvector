
#ifndef MVECTOR_H
#define MVECTOR_H

#include <ostream>
#include <initializer_list>

namespace gm{

template<typename T>
class vector;

template<typename T>
std::ostream& operator<<(std::ostream&, const vector<T>&);

//& Declaration

template<typename T>
class vector{ //? final
private:
    T * m_data{nullptr};
    void _allocate_memory(const std::size_t) noexcept(false);
    void _deallocate_memory() noexcept(false);

protected:
    std::size_t m_length{};
    std::size_t m_capacity{};

public:
    //& Constructors
    vector(const std::size_t length = 0);
    vector(const std::size_t length, const T init_value);
    vector(const std::initializer_list<T> list);
    vector(const T * carray, const std::size_t carray_length, const std::size_t offset = 0);

    //& Copy initializer - deepcopy
    ////vector(const vector<T>&) = delete;
    vector(const vector<T>& orig_vector); // Deepcopy

    //& Assignment operator - deepcopy
    ////vector& operator=(const vector&) = delete;
    vector<T>& operator=(const vector<T>& orig_vector); // Deepcopy

    //& Destructor
    virtual ~vector();

private:
    std::size_t _get_next_capacity() const;

public:
    std::size_t length() const;
    std::size_t capacity() const;

    void resize(const std::size_t new_length) noexcept(false);
    void resize(const std::size_t new_length, const T repl_val) noexcept(false);
    void reserve(const std::size_t new_capacity) noexcept(false);
    void shrink_to_fit();
    void erase();

    T * data();
    const T * cdata() const;

    // getting elements
    T& at(const std::size_t index);
    //const T& cat(const std::size_t index);
    T& operator[](const std::size_t index);
    //const T& operator[](const std::size_t index);



    //& Math operators
    // operator+, operator+=
    template<typename U> friend vector<U> operator+(const vector<U>& vec, const U value);
    template<typename U> friend vector<U> operator+(const U value, const vector<U>& vec);
    template<typename U> friend vector<U> operator+(const vector<U>& vec1, const vector<U>& vec2);
    void operator+=(const T value);
    void operator+=(const vector<T> vec);
    
    // operator-, operator-=
    template<typename U> friend vector<U> operator-(const vector<U>& vec, const U value);
    template<typename U> friend vector<U> operator-(const U value, const vector<U>& vec);
    template<typename U> friend vector<U> operator-(const vector<U>& vec1, const vector<U>& vec2);
    void operator-=(const T value);
    void operator-=(const vector<T> vec);

    // operator*, operator *=
    template<typename U> friend vector<U> operator*(const vector<U>& vec, const U value);
    template<typename U> friend vector<U> operator*(const U value, const vector<U>& vec);
    template<typename U> friend vector<U> operator*(const vector<U>& vec1, const vector<U>& vec2);
    void operator*=(const T value);
    void operator*=(const vector<T> vec);

    // operator/, operator/=
    template<typename U, typename V> friend vector<U> operator/(const vector<U>& vec, const V value);
    template<typename U> friend vector<U> operator/(const U value, const vector<U>& vec);
    template<typename U> friend vector<U> operator/(const vector<U>& vec1, const vector<U>& vec2);
    void operator/=(const T value);
    void operator/=(const vector<T> vec);
    
    // operator/, operator /=
    template<typename U> friend vector<U> operator%(const vector<U>& vec, const U value);
    template<typename U> friend vector<U> operator%(const U value, const vector<U>& vec);
    template<typename U> friend vector<U> operator%(const vector<U>& vec1, const vector<U>& vec2);
    void operator%=(const T value);
    void operator%=(const vector<T> vec);

    //& unary operatos
    // operator+

    // operator-




    //& operator<<    
    template<typename U> friend std::ostream& operator<<(std::ostream& out, const vector<U>& vec);
};




}

#include "mvector.inl"

#endif