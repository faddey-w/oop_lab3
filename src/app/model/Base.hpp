#ifndef LAB3_BASE_HPP
#define LAB3_BASE_HPP

#include <memory>
#include <stdexcept>
#include <string>

namespace CM {

    class ModelLogicError : public std::runtime_error {
    public:
        ModelLogicError(const std::string& msg) : std::runtime_error(msg) {};
    };


    template<typename T>
    class Base : public std::enable_shared_from_this<T> {
    public:

        typedef std::shared_ptr<T> Ptr;

        template<typename... Args>
        static Ptr New(std::shared_ptr<Args> ...args) {
            return std::make_shared<T>(args...);
        }

        Ptr new_ptr() {
            return this->shared_from_this();
        }

    protected:

        void check(bool condition, const std::string& msg="") const {
            if (!condition) throw ModelLogicError(msg);
        }

    };

};

#endif //LAB3_BASE_HPP
