
#ifndef MVECTOR_H
#define MVECTOR_H

#include <ostream>
#include <initializer_list>
#include <type_traits> // std::enable_if

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

    //& Copy constructor - deepcopy
    ////vector(const vector<T>&) = delete;
    vector(const vector<T>& orig_vector); // Deepcopy
    vector(vector<T>&& orig_vector); // std::move

    //& Assignment operator - deepcopy
    ////vector& operator=(const vector&) = delete;
    vector<T>& operator=(const vector<T>& orig_vector); // Deepcopy
    vector<T>& operator=(vector<T>&& orig_vector); // std::move

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
    const T& cat(const std::size_t index) const; // for const objects
    T& operator[](const std::size_t index);
    const T& operator[](const std::size_t index) const; // for const objects



    //& Math operators for arithmetic types
    // operator+, operator+=
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator+(const vector<U>& vec, const V value);
    
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator+(const V value, const vector<U>& vec);
    
    template<typename U>
    friend std::enable_if_t<std::is_arithmetic<U>::value, vector<U>>
    operator+(const vector<U>& vec1, const vector<U>& vec2);
    
    template<typename V, typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value>
    operator+=(const V value);

    template<typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value>
    operator+=(const vector<U> vec);
    
    // operator-, operator-=
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator-(const vector<U>& vec, const V value);
    
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator-(const V value, const vector<U>& vec);
    
    template<typename U>
    friend std::enable_if_t<std::is_arithmetic<U>::value, vector<U>>
    operator-(const vector<U>& vec1, const vector<U>& vec2);
    
    template<typename V, typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value>
    operator-=(const V value);

    template<typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value>
    operator-=(const vector<U> vec);

    // operator*, operator *=
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator*(const vector<U>& vec, const V value);
    
    template<typename U, typename V>
    friend std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator*(const V value, const vector<U>& vec);
    
    template<typename U>
    friend std::enable_if_t<std::is_arithmetic<U>::value, vector<U>>
    operator*(const vector<U>& vec1, const vector<U>& vec2);
    
    template<typename V, typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value>
    operator*=(const V value);

    template<typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value>
    operator*=(const vector<U> vec);

    // operator/, operator/=
    template<typename U, typename V>
    friend typename std::enable_if<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>::type
    operator/(const vector<U>& vec, const V value);
    
    template<typename U, typename V>
    friend typename std::enable_if<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>::value, vector<U>>::type
    operator/(const V value, const vector<U>& vec);
    
    template<typename U>
    friend typename std::enable_if<std::is_arithmetic<U>::value, vector<U>>::type
    operator/(const vector<U>& vec1, const vector<U>& vec2);
    
    template<typename V, typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value && std::is_arithmetic<V>::value && std::is_convertible<V, U>:: value>::type
    operator/=(const V value);
    
    template<typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    operator/=(const vector<T> vec);
    
    // operator%, operator %=
    //@ for integral types only - SFINAE (Substitution failure is not an error)
    template<typename U, typename V> // default template arguments are not allowed in friend functions (U = T)
    friend std::enable_if_t<std::is_integral<U>::value && std::is_integral<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator%(const vector<U>& vec, const V value);
    
    template<typename U, typename V>
    friend std::enable_if_t<std::is_integral<U>::value && std::is_integral<V>::value && std::is_convertible<V, U>::value, vector<U>>
    operator%(const V value, const vector<U>& vec);

    template<typename U>
    friend std::enable_if_t<std::is_integral<U>::value, vector<U>>
    operator%(const vector<U>& vec1, const vector<U>& vec2);

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////


    //@template<typename V>
    //@typename std::enable_if<std::is_integral<T>::value && std::is_integral<V>::value && std::is_convertible<V, T>::value>::type
    //@operator%=(const V value);
    
    //@std::enable_if_t<std::is_integral<T>::value> operator%=(const vector<T> vec); // default typename is void!
    
    //&template<typename V, typename std::enable_if<std::is_integral<T>::value && std::is_integral<V>::value && std::is_convertible<V, T>::value>::type>
    //&void operator%=(const V value);
    //&
    //&template<typename std::enable_if<std::is_integral<T>::value>::type>
    //&void operator%=(const vector<T> vec);
    
    
    template<typename V, typename U = T>
    typename std::enable_if<std::is_integral<U>::value && std::is_integral<V>::value && std::is_convertible<V, U>::value>::type
    operator%=(const V value);
    
    template<typename V, typename U = T>
    typename std::enable_if<!std::is_integral<U>::value>::type
    operator%=(const V) = delete;
    
    template<typename U = T>
    std::enable_if_t<std::is_integral<U>::value>
    operator%=(const vector<U> vec); // default typename is void!
    
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    //& unary operatos
    // operator+
    //template<typename U = T>
    //std::enable_if_t<std::is_arithmetic<U>::value, vector<U>>
    //operator+() const = default;

    // operator-
    template<typename U = T>
    std::enable_if_t<std::is_arithmetic<U>::value, vector<U>>
    operator-() const;




    //& operator<<    
    template<typename U> friend std::ostream& operator<<(std::ostream& out, const vector<U>& vec);
};

}

#include "mvector.inl"

#endif