#ifndef AUTODIFF_HPP
#define AUTODIFF_HPP

#include <tuple>
#include <type_traits>

namespace ad
{




    template <class T>
    class variable
    {
    public:

        using value_type = T;

        variable(const T& value);

        template <class E>
        variable(const E& e);

        template <class E>
        variable& operator=(const E& e);

        T value() const;
        T derivative() const;

        void activate(bool active);

        template <class E>
        variable& operator+=(const E& e)
        {
            *this = e + *this;
            return *this;
        }

        template <class E>
        variable& operator*=(const E& e)
        {
            *this = e * *this;
            return *this;
        }

    private:

        T m_value;
        T m_derivative;
    };

    namespace detail
    {
        template <class T>
        struct operand_type
        {
            using type = std::conditional_t<
                    std::is_arithmetic<T>::value,
                    variable<T>,
                    const T&>;
        };

        template <class T>
        using operand_type_t = typename operand_type<T>::type;
    }

    template <class E1, class E2>
    struct binary_add
    {
        using value_type = std::common_type_t<typename std::decay_t<E1>::value_type,
                                              typename std::decay_t<E2>::value_type>;
        value_type operator()(const E1& e1, const E2& e2) const
        {
            return e1.value() + e2.value();
        }

        value_type derivative(const E1& e1, const E2& e2) const
        {
            return e1.derivative() + e2.derivative();
        }
    };

    template <class E1, class E2>
    struct binary_mul
    {
        using value_type = std::common_type_t<typename std::decay_t<E1>::value_type,
                                              typename std::decay_t<E2>::value_type>;
        value_type operator()(const E1& e1, const E2& e2) const
        {
            return e1.value() * e2.value();
        }

        value_type derivative(const E1& e1, const E2& e2) const
        {
            return e1.derivative() * e2.value() + e2.derivative() * e1.value();
        }
    };

    template <class In, template <class...> class Out>
    struct mpl_transform;

    template <template <class...> class In, class... T, template <class...> class Out>
    struct mpl_transform<In<T...>, Out>
    {
        using type = Out<T...>;
    };

    template <class In, template <class...> class Out>
    using mpl_transform_t = typename mpl_transform<In, Out>::type;

    template <template <class...> class F, class... T>
    class universal_op
    {
    public:

        using operand_type = std::tuple<detail::operand_type_t<T>...>;

        //using functor_type = F<detail::operand_type_t<T>...>;
        using functor_type = mpl_transform_t<operand_type, F>;

        using value_type = typename functor_type::value_type;

        template <class... U>
        universal_op(U&&... u)
            : m_operands(std::forward<U>(u)...)
            , m_functor()
        {
        }

        value_type value() const
        {
            return value_impl(std::make_integer_sequence<size_t, sizeof...(T)>());
        }

        value_type derivative() const
        {
            return derivative_impl(std::make_integer_sequence<size_t, sizeof...(T)>());
        }

    private:

        template <size_t... I>
        value_type value_impl(std::integer_sequence<size_t, I...>) const
        {
            return m_functor(std::get<I>(m_operands)...);
        }

        template <size_t... I>
        value_type derivative_impl(std::integer_sequence<size_t, I...>) const
        {
            return m_functor.derivative(std::get<I>(m_operands)...);
        }
        operand_type m_operands;
        functor_type m_functor;
    };



    template <class E1, class E2>
    universal_op<binary_add, E1, E2> operator+(const E1& e1, const E2& e2)
    {
        return universal_op<binary_add, E1, E2>(e1, e2);
    }

    template <class E1, class E2>
    universal_op<binary_mul, E1, E2> operator*(const E1& e1, const E2& e2)
    {
        return universal_op<binary_mul, E1, E2>(e1, e2);
    }

    /***************************
     * variable implementation *
     ***************************/

    template <class T>
    variable<T>::variable(const T& value)
        : m_value(value)
        , m_derivative(T(0))
    {
    }

    template <class T>
    T variable<T>::value() const
    {
        return m_value;
    }

    template <class T>
    T variable<T>::derivative() const
    {
        return m_derivative;
    }

    template <class T>
    void variable<T>::activate(bool active)
    {
        m_derivative = active ? 1. : 0.;
    }

    template <class T>
    template <class E>
    variable<T>::variable(const E& e)
        : m_value(e.value())
        , m_derivative(e.derivative())
    {
    }

    template <class T>
    template <class E>
    variable<T>& variable<T>::operator=(const E& e)
    {
        m_value = e.value();
        m_derivative = e.derivative();
        return *this;
    }
}



/*template <class D>
class expression
{
public:

    auto value() const { return (*this)().value_impl(); }
    auto derivative() const { return (*this)().derivative_impl(); }

private:

    D& operator()() { return *static_cast<D*>(this); }
    const D& operator()() const { return *static_cast<const D*>(this); }
};


template <class T>
class variable : public expression<variable<T>>
{
public:

    template <class E>
    variable& operator=(const expression<E>& e)
    {
        m_value = e().value();
        m_derivative = e().derivative();
        return *this;
    }
};*/




/*
template <class T>
struct add_reference
{
    using type = T&;
};

template <class T>
struct add_reference<T&>
{
    using type = T&;
};

template <class T>
using add_reference_t = typename add_reference<T>::type;

using reference = add_reference_t<T>;*/


/*template <class... T>
class my_class
{
    // ...
};

my_class<E1, E2> m1;
my_class<E> m2;

template <class T1, class T2>
void func(T1 t1, T2 t2 = T2());

template <class... T>
void my_func(const T&... args)
{
    func(args...);
}

my_func(1., 42, "math");

class... T => double, int, std::string
const T&... => const double&, const int1, const std::string&

template <class... T>
void universal_func(T&&... t)
{
}

template <class T>
void universal_func(T&& t)
{
    call_func(std::forward<T>(t));
}


template <class T>
void universal_func(std::vector<T>&& t); // Pas universal reference



int x = 42;
int& rx = x
const int& cx = x;

universal_func(x);
universal_func(rx);
universal_func(cx);
universal_func(std::move(x));
universal_func(42);

class my_class
{
public:

    my_class(const my_class&);
    my_class(my_class&&);

    void method() &;
    void method() &&;


    
};*/

/*
template <class... T>
class mpl_vector;

template <class TL1, class TL2>
struct concatenate;

template <template <class...> class TL1, template <class...> class TL2, class... L1, class... L2>
struct concatenate<TL1<L1...>, TL2<L2...>>
{
};

concatenate<mpl_vector<int, double, float>, mpl_vector<string, char>>;*/
#endif
