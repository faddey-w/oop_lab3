#include "Object.hpp"

Object::Ptr Object::Empty() {
    return Object::Ptr(new EmptyObject());
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





