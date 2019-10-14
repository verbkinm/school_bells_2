#ifndef CIRCULAR_VECTOR_H
#define CIRCULAR_VECTOR_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

template <class C>
class Circular_Vector
{
public:
    Circular_Vector(const std::vector<C> &vector);
    typename std::vector<C>::const_iterator iterrator();
    typename std::vector<C>::const_iterator next_iterrator();
    typename std::vector<C>::const_iterator previos_iterrator();
    typename std::vector<C>::const_iterator next();
    typename std::vector<C>::const_iterator previos();

    typename std::vector<C>::const_iterator begin();
    typename std::vector<C>::const_iterator end();

    size_t size();
    const C& at(size_t index);

private:
    const std::vector<C> &_vector;
    typename std::vector<C>::const_iterator _current_iterrator;
};

template<class C>
Circular_Vector<C>::Circular_Vector(const std::vector<C> &vector) : _vector(vector), _current_iterrator(vector.cbegin())
{
    if(!vector.size())
        throw std::length_error("Circular_Vector size is 0 (zero)");
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::begin()
{
    return _vector.cbegin();
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::end()
{
    return _vector.cend();
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::iterrator()
{
    return _current_iterrator;
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::next_iterrator()
{
    auto it = _current_iterrator;
    if(++it == _vector.end())
        it = _vector.begin();
    return it;
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::previos_iterrator()
{
    auto it = _current_iterrator;
    if(it == _vector.begin())
        it = _vector.end();
    return --it;
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::next()
{
    if(++_current_iterrator == _vector.end())
        _current_iterrator = _vector.begin();
    return _current_iterrator;
}

template<class C>
typename std::vector<C>::const_iterator Circular_Vector<C>::previos()
{
    if(_current_iterrator == _vector.begin())
        _current_iterrator = _vector.end();
    return --_current_iterrator;
}

template<class C>
size_t Circular_Vector<C>::size()
{
    return _vector.size();
}

template<class C>
const C &Circular_Vector<C>::at(size_t index)
{
    return _vector.at(index);
}
#endif // CIRCULAR_VECTOR_H
