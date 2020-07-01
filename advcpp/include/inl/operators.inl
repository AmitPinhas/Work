#ifndef OPERATORS_INL
#define OPERATORS_INL

namespace advcpp
{

template <typename T>     
T Addition<T>::operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const
{
    return (a_lhs->Value()) + (a_rhs->Value());
}

template <typename T>  
std::string Addition<T>::ToString() const
{
    return "+ ";
}

template <typename T>     
T Subtraction<T>::operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const
{
    return (a_lhs->Value()) - (a_rhs->Value());
}

template <typename T>  
std::string Subtraction<T>::ToString() const
{
    return "- ";
}

template <typename T>     
T Multiplication<T>::operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const
{
    return a_lhs->Value() * a_rhs->Value();
}

template <typename T>  
std::string Multiplication<T>::ToString() const
{
    return "* ";
}

template <typename T>     
T Division<T>::operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const
{
    return a_lhs->Value() / a_rhs->Value();
}

template <typename T>  
std::string Division<T>::ToString() const
{
    return "/ ";
}

} // namespace advcpp

#endif // OPERATORS_INL
