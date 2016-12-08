#ifndef LAB3_FUNCTION_HPP
#define LAB3_FUNCTION_HPP

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <exception>
#include <stdexcept>
#include <iostream>

template<typename DataType> class traits {
public:
    typedef std::shared_ptr<DataType> ptr;
    typedef const std::shared_ptr<DataType> const_ptr;
};

// special case - returning empty object for functions that returns nothing
//template<> class traits<void> {
//public:
//    typedef void* ptr;
//    typedef const void* const_ptr;
//};


//template<typename ...Types> struct index {
//    template<size_t ...Indices> struct by {
//        typedef Tuple<Pair< Args1, Args2>...> type;
//    };
//};
//
//
//template
//class IndexedItem


// Building indices for variadic templates
template<size_t... Idxs>
struct indices {};

template <size_t N, size_t... Is>
struct build_indices : public build_indices<N-1, N-1, Is...> {};

template <size_t... Is>
struct build_indices<0, Is...> {
    typedef indices<Is...> Indices;
};

template <typename... Sequence>
using IndicesFor = build_indices<sizeof...(Sequence)>;

template<size_t N, typename... Ts> using NthTypeOf =
typename std::tuple_element<N, std::tuple<Ts...>>::type;


//template<size_t Idx, typename DataType>
//struct IndexedArg {
//    typedef typename DataType DataType;
//    static size_t Idx = Idx;
//};


template<typename DeclFT>
class FunctionTraits {};


template<typename RetType, typename... ArgTypes>
class FunctionTraits<RetType(ArgTypes...)> {
public:
    typedef RetType (*DeclFT)(ArgTypes...);
    typedef typename traits<RetType>::ptr (*FT)(typename traits<ArgTypes>::ptr...);
    static const size_t NArgs = sizeof...(ArgTypes);
};


template<typename... ArgTypes>
class FunctionTraits<void(ArgTypes...)> {
public:
    typedef void (*DeclFT)(ArgTypes...);
    typedef void (*FT)(typename traits<ArgTypes>::ptr...);
    static const size_t NArgs = sizeof...(ArgTypes);
};
//template<typename... ArgTypes> FunctionTraits<T>::templStatic = 0;



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



typedef std::map<std::string, Object::Ptr> ArgsMapping;

template<size_t N> using ArgNames = std::array<std::string, N>;


// Public interface class
// To create a new Function, use this syntax:
// Function::New<return_type(arg1_t, arg2_t)>(my_plain_function, {"arg1", "arg2"});
// Functions are called by interpreter by passing arguments mapping into call() method.
// You can call Functions by hands, using this syntax:
// function->call({ {"arg1", val1}, {"arg2", val2} });
// where val1 and val2 are Object::Ptrs that point to values of corresponding types
class Function {
public:
    typedef std::shared_ptr<Function> Ptr;

    template<typename FT>
    static Ptr New(typename FunctionTraits<FT>::FT function,
                   const ArgNames<FunctionTraits<FT>::NArgs> &arg_names);

    virtual Object::Ptr call(const std::map<std::string, Object::Ptr>& args) const = 0;

};


template<size_t Idx, size_t NArgs, typename DataType>
struct ArgumentGetter {
    static typename traits<DataType>::ptr
    get_argument(const ArgsMapping& args, const ArgNames<NArgs>& names) {
        auto pointer = args.find(names[Idx]);
        if (pointer == args.end()) throw TypeError("Missing argument: " + names[Idx]);
        typename traits<DataType>::ptr result = pointer->second->template get<DataType>();
        return result;
    }
};


template<typename IdxsTuple, typename... DataTypes>
struct _FunctionImplBase;


template<size_t... Idxs, typename... DataTypes>
struct _FunctionImplBase<indices<Idxs...>, DataTypes...>
    : public ArgumentGetter<Idxs, sizeof...(DataTypes), DataTypes>... {};


//// helper function: statically get item from arguments names list
//template<size_t... Is>
//const std::string& _get(const ArgNames& names, indices<Is...>){
//    return names[Is];
//}
//
//template<size_t N>
//const std::string& _get(const ArgNames& names){
//    static_assert(names.size() == N);
//    return _get<>(p, build_indices<sizeof...(Args)>{});
//}


// Implementation of public interface:
// templated class that implements function call
// This is done via inheritance to allow polymorphism at public level

//template<typename RetType, template<size_t, typename> typename ... Args>
template<typename FT>//, size_t ... ArgIndices>
class _FunctionImpl {};

//
//template<typename RetType, template<typename...> typename ArgTypes, size_t... Indices>
//class _FunctionImpl<> {};


template<typename RetType, typename ... ArgTypes>
class _FunctionImpl<RetType(ArgTypes...)>
    : public Function
    , public _FunctionImplBase<typename IndicesFor<ArgTypes...>::Indices, ArgTypes...> {
public:
    typedef typename FunctionTraits<RetType(ArgTypes...)>::DeclFT DeclFT;
    typedef typename FunctionTraits<RetType(ArgTypes...)>::FT FT;
    static const size_t NArgs = sizeof...(ArgTypes);

    _FunctionImpl(FT function, const ArgNames<sizeof...(ArgTypes)>& arg_names)
        : function(function), arg_names(arg_names) {};

    Object::Ptr call(const ArgsMapping& args) const {

        // raise for extra arguments
        if (args.size() != sizeof...(ArgTypes)) {
            throw TypeError("Unexpected arguments");
        }

        return _make_call(args, typename IndicesFor<ArgTypes...>::Indices());
//        return Object::New<RetType>(function(
//            _get_argument<ArgTypes, ArgIndices, sizeof...(ArgTypes)>(args, arg_names)...
//        ));
    }

    template<size_t ... Idxs>
    Object::Ptr _make_call(const ArgsMapping& args, indices<Idxs...> const&) const {
        return Object::New<RetType>(function(
            ArgumentGetter<Idxs, NArgs, ArgTypes>::get_argument(args, arg_names)...
        ));
    }

private:
    FT function;
    ArgNames<sizeof...(ArgTypes)> arg_names;
};

template<typename ... ArgTypes>
class _FunctionImpl<void(ArgTypes...)>
    : public Function
    , public _FunctionImplBase<typename IndicesFor<ArgTypes...>::Indices, ArgTypes...> {
public:
    typedef typename FunctionTraits<void(ArgTypes...)>::DeclFT DeclFT;
    typedef typename FunctionTraits<void(ArgTypes...)>::FT FT;
    static const size_t NArgs = FunctionTraits<void(ArgTypes...)>::NArgs;

    _FunctionImpl(FT function, const ArgNames<sizeof...(ArgTypes)>& arg_names)
        : function(function), arg_names(arg_names) {};


    Object::Ptr call(const ArgsMapping& args) const {

        // raise for extra arguments
        if (args.size() != sizeof...(ArgTypes)) {
            throw TypeError("Unexpected arguments");
        }

        return _make_call(args, typename IndicesFor<ArgTypes...>::Indices());
//        return Object::New<RetType>(function(
//            _get_argument<ArgTypes, ArgIndices, sizeof...(ArgTypes)>(args, arg_names)...
//        ));
    }

    template<size_t ... Idxs>
    Object::Ptr _make_call(const ArgsMapping& args, indices<Idxs...> const&) const {
        function(
            ArgumentGetter<Idxs, NArgs, ArgTypes>::get_argument(args, arg_names)...
        );
        return Object::Empty();
    }

private:
    FT function;
    ArgNames<sizeof...(ArgTypes)> arg_names;
};


template<typename FT>
Function::Ptr Function::New(typename FunctionTraits<FT>::FT function,
                            const ArgNames<FunctionTraits<FT>::NArgs> &arg_names) {
    return Function::Ptr(new _FunctionImpl<
        FT
    >(function, arg_names));
};


#endif //LAB3_FUNCTION_HPP
