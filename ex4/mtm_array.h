#ifndef EX5_MTM_ARRAY_H
#define EX5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>
#include <cstring>
#include <iostream>

template <class T, int SIZE>
class Array
{
    T* data;
public:
    // ARRAY

    //CONSTRUCTOR: get value to initialze array and build array
    explicit Array(T const& initial_value = T()): data(new T[SIZE]) {
        // check size value
        // if size is negative new throws exception
        // throw exception if size is 0
        if (SIZE == 0) throw std::length_error("mtm_array:array constructor:"
                                                       "array size zero!");

        // initialize array
        for (int i = 0; i < SIZE; i++) {
            data[i] = initial_value;
        }
    };

    //  COPY CONSTRUCTOR: get array it copy it
    Array(const Array&);

    // DESTRUCTOR: delete array
    ~Array();

    // OVERLOAD OPERATORS
    Array& operator=(const Array&);    // = overload
    T&  operator[](int index);       // [] overload
    const T& operator[](int index) const;  //  [] overload for const array
    bool operator==(const Array&) const;    // == overload
    bool operator!=(const Array&) const;    // != overload

    // ITERATORS

    // CONST ITERATOR
    class const_iterator{
        const Array<T, SIZE>* array;
        int index;
        friend class Array<T, SIZE>;
    public:
        // CONSTRUCTOR: get array and size and build a const iterator
        const_iterator(const Array<T, SIZE>*, int);

        // COPY CONTRUCTOR + OPERATOR= :
        // I let the compiler build copy ctor and operator= overload by itself
        // and only then it compiled on server. in clion it compiled both ways.
        //const_iterator(const const_iterator&) = default; // copy ctr
        //const_iterator& operator=(const const_iterator&) = default;

        // DESTRUCTOR: delete iterator
        ~const_iterator() = default;      // dtr

        // OPERATOR OVERLOADING
        const T* operator->() const;    // -> overloading
        const T& operator*() const;     // * overloading
        const_iterator& operator++(); // x++ overloading
        const_iterator operator++(int); // ++x overloading
        bool operator==(const const_iterator&) const; // == overloading
        bool operator!=(const const_iterator&) const; // != overloading
    };

    // ITERATOR
    class iterator{
        Array<T, SIZE> *array;
        int index;
        friend class Array<T, SIZE>;
    public:
        // CONSTRUCTOR: get array and size and build an iterator
        iterator(Array<T, SIZE>*, int);
        iterator(const iterator&) = default; // copy ctr
        iterator& operator=(const iterator&) = default; // = overload
        ~iterator() = default;      // destructor
        T* operator->() const;  // -> overload
        T& operator*() const; // * overload
        iterator& operator++(); // x++ overload
        iterator operator++(int); // ++x overload
        bool operator==(const iterator&) const; // == overload
        bool operator!=(const iterator&) const; // != overload
    };

    iterator begin();   // build an iterator for the first cell in array
    const_iterator begin() const;   // build a const iterator for first cell
    iterator end(); // build an iterator for last cell in array
    const_iterator end() const; // build a const iterator for last cell in array

private:
    // VERIFY INDEX: this function check if an index is valid
    // input: an int of an index and string with the name of the function
    //        its call from.
    // output: throws out_of_range exeption if index is not in the array range.
    //         returns index if is in array range.
    static int verify_index(int, std::string);
};

template <class T, int SIZE>
int Array<T, SIZE>::verify_index(int index, std::string s){
    if(index < 0 || index >= SIZE){
        throw std::out_of_range("mtm_array::"+s+": index out of range!");
    }
    // index is valid
    return index;
}

// ---------------------- ARRAY ---------------------------------

// array destructor
template <class T, int SIZE>
Array<T, SIZE>::~Array(){
    delete[] data;
}

// array copy constructor
template <class T, int SIZE>
Array<T, SIZE>::Array(const Array& Array): data(new T[SIZE]){
    // new should return exception if size negative or if allocation failure
    // check if size is 0
    if(SIZE == 0) throw std::bad_alloc();

    // copy each cell in array
    for(int i = 0; i < SIZE; i++){
        data[i] = Array.data[i];
    }
}

// operator =
template <class T, int SIZE>
Array<T, SIZE>& Array<T, SIZE>::operator=(const Array& a){
    if(this == &a) return *this;
    delete[] data;
    data = new T[SIZE]; // bad alloc might be thrown here
    for(int i = 0; i < SIZE; ++i){
        data[i] = a.data[i];
    }
    return *this;
}

// operator []
template <class T, int SIZE>
T&  Array<T, SIZE>::operator[](int index){
    return data[verify_index(index, "operator []")];
}

// const operator []
template <class T, int SIZE>
const T&  Array<T, SIZE>::operator[](int index) const{
    return data[verify_index(index, "operator [] const array")];
}

// operator ==
template <class T, int SIZE>
bool Array<T, SIZE>::operator==(const Array& a) const {
    for(int i = 0; i < SIZE; i++){
        if (data[i] != a.data[i])
            return false;
    }
    return true;
}

// operator !=
template <class T, int SIZE>
bool Array<T, SIZE>::operator!=(const Array& a) const {
    for(int i = 0; i < SIZE; i++){
       if (data[i] != a.data[i])
           return true;
    }
    return false;
}

// ------------------------- ITERATOR ------------------------------

// iterator constructor
template <class T, int SIZE>
Array<T, SIZE>::iterator::iterator(Array* a, int index):
        index(index), array(a) {}

// operator ==
template <class T, int SIZE>
bool Array<T, SIZE>::iterator::operator==(const iterator& i) const {
    return (index == i.index && &(*array) == &(*(i.array)));
}

// operator !=
template <class T, int SIZE>
bool Array<T, SIZE>::iterator::operator!=(const iterator& i) const {
    return !(*this == i);
}

// operator *
template <class T, int SIZE>
T& Array<T, SIZE>::iterator::operator*() const {
    return array->data[verify_index(index, "iterator::operator *")];
}

// operator ->
template <class T, int SIZE>
T* Array<T, SIZE>::iterator::operator->() const {
    return &(array->data[verify_index(index, "iterator::operator ->")]);
}

// ++x
template <class T, int SIZE>
typename Array<T, SIZE>::iterator& Array<T, SIZE>::iterator::operator++(){
  ++index;
  return *this;
}

// x++
template <class T, int SIZE>
typename Array<T, SIZE>::iterator Array<T, SIZE>::iterator::operator++(int){
    iterator result = *this;
    ++*this;
    return result;
}

// begin
template <class T, int SIZE>
typename Array<T, SIZE>::iterator Array<T, SIZE>::begin(){
    return iterator(this, 0);
}

// end
template <class T, int SIZE>
typename Array<T, SIZE>::iterator Array<T, SIZE>::end(){
    return iterator(this, SIZE);
}


// --------------------- CONST ITERATOR ------------------

// build ctr
template <class T, int SIZE>
Array<T, SIZE>::const_iterator::const_iterator(const Array* a, int index):
        index(index),
        array(a){}

// operator ==
template <class T, int SIZE>
bool Array<T,SIZE>::const_iterator::operator==(const const_iterator& i) const {
    return (index == i.index && &(*array) == &(*i.array));
}

// operator !=
template <class T, int SIZE>
bool Array<T, SIZE>::const_iterator::operator!=(const const_iterator& i) const {
    return !(*this == i);
}

// operator *
template <class T, int SIZE>
T const& Array<T, SIZE>::const_iterator::operator*() const {
    return array->data[verify_index(index, "const_iterator::operator *")];
}

// operator ->
template <class T, int SIZE>
T const* Array<T, SIZE>::const_iterator::operator->() const {
    return &(array->data[verify_index(index, "const_iterator::operator ->")]);
}

// ++x
template <class T, int SIZE>
typename Array<T, SIZE>::const_iterator& Array<T, SIZE>::const_iterator::
operator++(){
    ++index;
    return *this;
}

// x++
template <class T, int SIZE>
typename Array<T, SIZE>::const_iterator Array<T, SIZE>::const_iterator::
operator++(int){
    const_iterator result = *this;
    ++*this;
    return result;
}

// begin
template <class T, int SIZE>
typename Array<T, SIZE>::const_iterator Array<T, SIZE>::begin() const{
    return const_iterator(this, 0);
}

// end
template <class T, int SIZE>
typename Array<T, SIZE>::const_iterator Array<T, SIZE>::end() const{
    return const_iterator(this, SIZE);
}

#endif //EX5_MTM_ARRAY_H
