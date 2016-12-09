#ifndef LAB3_FUNCTION_HPP
#define LAB3_FUNCTION_HPP

#include <memory>
#include <map>
#include <string>
#include <array>
#include "templ_utils.hpp"
#include "Object.hpp"


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
                   const ArgNames<FunctionTraits<FT>::NArgs> &arg_names,
                   const std::string& help_text="");

    virtual Object::Ptr call(const std::map<std::string, Object::Ptr>& args) const = 0;

    virtual const std::string& get_help_text() const = 0;

};


// Implementation of public interface:
// templated class that implements function call
// This is done via inheritance to allow polymorphism at public level
// There are some difficulties with applying variadic templates for
// validating input arguments, that's why there are so many classes.
// Solution is not understood perfectly, but works. Source:
// https://habrahabr.ru/post/101430/


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


template<typename FT>
class _FunctionImpl {};


template<typename RetType, typename ... ArgTypes>
class _FunctionImpl<RetType(ArgTypes...)>
        : public Function
        , public _FunctionImplBase<typename IndicesFor<ArgTypes...>::Indices, ArgTypes...> {
public:
    typedef typename FunctionTraits<RetType(ArgTypes...)>::DeclFT DeclFT;
    typedef typename FunctionTraits<RetType(ArgTypes...)>::FT FT;
    static const size_t NArgs = sizeof...(ArgTypes);

    _FunctionImpl(FT function, const ArgNames<sizeof...(ArgTypes)>& arg_names,
                  const std::string& help_text="")
        : function(function), arg_names(arg_names), help_text(help_text) {};

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

    const std::string& get_help_text() const { return help_text; }

private:
    FT function;
    ArgNames<sizeof...(ArgTypes)> arg_names;
    std::string help_text;
};

// The same as previous class, just a specialization for functions the returns nothing
template<typename ... ArgTypes>
class _FunctionImpl<void(ArgTypes...)>
        : public Function
        , public _FunctionImplBase<typename IndicesFor<ArgTypes...>::Indices, ArgTypes...> {
public:
    typedef typename FunctionTraits<void(ArgTypes...)>::DeclFT DeclFT;
    typedef typename FunctionTraits<void(ArgTypes...)>::FT FT;
    static const size_t NArgs = FunctionTraits<void(ArgTypes...)>::NArgs;

    _FunctionImpl(FT function, const ArgNames<sizeof...(ArgTypes)>& arg_names,
                  const std::string& help_text="")
        : function(function), arg_names(arg_names), help_text(help_text) {};


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

    const std::string& get_help_text() const { return help_text; }

private:
    FT function;
    ArgNames<sizeof...(ArgTypes)> arg_names;
    std::string help_text;
};


template<typename FT>
Function::Ptr Function::New(typename FunctionTraits<FT>::FT function,
                            const ArgNames<FunctionTraits<FT>::NArgs> &arg_names,
                            const std::string& help_text) {
    return Function::Ptr(new _FunctionImpl<FT>(function, arg_names, help_text));
};


#endif //LAB3_FUNCTION_HPP
