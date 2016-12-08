#ifndef LAB3_OBJECT_HPP
#define LAB3_OBJECT_HPP

#include <memory>
#include <string>
#include <exception>
#include "templ_utils.hpp"

class Object {
public:
    typedef std::shared_ptr<Object> Ptr;

    template<typename DataType>
    static Ptr New(typename traits<DataType>::ptr value);

    static Ptr Empty();

    template<typename DataType>
    typename traits<DataType>::ptr get();

    template<typename DataType>
    typename traits<DataType>::const_ptr get() const;

    template<typename DataType>
    bool has_type() const;

    virtual bool has_same_type(const Object& other) const = 0;
};


class TypeError : public std::runtime_error {
public:
    TypeError(): std::runtime_error("") {};
    TypeError(const std::string& s): std::runtime_error(s) {};
};


class EmptyObject : public Object {
public:
    bool has_same_type(const Object& other) const;
};

Object::Ptr Object::Empty() {
    return Object::Ptr(new EmptyObject());
}

template<typename DataType>
class ObjectImpl: public Object {

public:
    typedef typename traits<DataType>::ptr DataPtr;

    ObjectImpl(DataPtr data_ptr): data(data_ptr) {};

    bool has_same_type(const Object& other) const {
        return other.has_type<DataType>();
    }

    DataPtr get_data() const { return data; }

private:

    DataPtr data;

};

template<typename DataType>
Object::Ptr Object::New(typename traits<DataType>::ptr value) {
    return Object::Ptr(new ObjectImpl<DataType>(value));
}

template<typename DataType>
typename traits<DataType>::ptr Object::get() {
    auto coerced = dynamic_cast<ObjectImpl<DataType>*>(this);
    if (coerced == nullptr) throw TypeError();
    return coerced->get_data();
}

template<typename DataType>
typename traits<DataType>::const_ptr Object::get() const {
    auto coerced = dynamic_cast<const ObjectImpl<DataType>*>(this);
    if (coerced == nullptr) throw TypeError();
    return coerced->get_data();
}

template<typename DataType>
bool Object::has_type() const {
    auto coerced = dynamic_cast<const ObjectImpl<DataType>*>(this);
    return (coerced != nullptr);
}

template<>
typename traits<void>::ptr Object::get<void>() {
    throw TypeError("Empty object does not have data");
}

template<>
typename traits<void>::const_ptr Object::get<void>() const {
    throw TypeError("Empty object does not have data");
}

template<>
bool Object::has_type<void>() const {
    auto coerced = dynamic_cast<const EmptyObject*>(this);
    return (coerced != nullptr);
}


bool EmptyObject::has_same_type(const Object& other) const  {
    return other.has_type<void>();
}





#endif //LAB3_OBJECT_HPP
