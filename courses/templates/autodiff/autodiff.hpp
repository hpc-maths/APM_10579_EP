#ifndef AUTODIFF_HPP
#define AUTODIFF_HPP

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
        variable& operator+=(const E& e)
        {
            *this = e * *this;
            return *this;
        }

    private:

        T m_value;
        T m_derivative;
    };

    template <class E1, class E2>
    struct binary_add
    {
        using value_type = std::common_type_t<typename E1::value_type,
                                              typename E2::value_type>;
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
        using value_type = std::common_type_t<typename E1::value_type,
                                              typename E2::value_type>;
        value_type operator()(const E1& e1, const E2& e2) const
        {
            return e1.value() * e2.value();
        }

        value_type derivative(const E1& e1, const E2& e2) const
        {
            return e1.derivative() * e2.value() + e2.derivative() * e1.value();
        }
    };

    template <class E1, class E2, class F>
    class binary_op
    {
    public:

        using value_type = typename F::value_type;

        binary_op(const E1& lhs, const E2& rhs)
            : m_lhs(lhs)
            , m_rhs(rhs)
            , m_functor()
        {
        }

        value_type value() const
        {
            return m_functor(m_lhs, m_rhs);
        }

        value_type derivative() const
        {
            return m_functor.derivative(m_lhs, m_rhs);
        }

    private:

        const E1& m_lhs;
        const E2& m_rhs;
        F m_functor;
    };



    template <class E1, class E2>
    binary_op<E1, E2, binary_add<E1, E2>> operator+(const E1& e1, const E2& e2)
    {
        return binary_op<E1, E2, binary_add<E1, E2>>(e1, e2);
    }

    template <class E1, class E2>
    binary_op<E1, E2, binary_mul<E1, E2>> operator*(const E1& e1, const E2& e2)
    {
        return binary_op<E1, E2, binary_mul<E1, E2>>(e1, e2);
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
#endif
