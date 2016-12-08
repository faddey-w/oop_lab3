#ifndef LAB3_TEMPL_UTILS_HPP
#define LAB3_TEMPL_UTILS_HPP


template<typename DataType> class traits {
public:
    typedef std::shared_ptr<DataType> ptr;
    typedef const std::shared_ptr<DataType> const_ptr;
};


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


#endif //LAB3_TEMPL_UTILS_HPP
