#ifndef I_OPERATOR_HPP
#define I_OPERATOR_HPP

#include <tr1/memory> // std::tr1::shared_ptr
#include "common.hpp" // NOEXCEPT
#include "i_expression.hpp"
//#include "shared_ptr.hpp"

namespace advcpp
{

template <typename T>    
class IOperator
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;
    virtual ~IOperator() NOEXCEPT = 0; 

    virtual T operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const = 0; 

    virtual std::string ToString() const = 0;

protected:
    IOperator();
    IOperator(const IOperator& a_rhs);
    IOperator& operator=(const IOperator& a_rhs);

};

} // namespace advcpp

#include "i_operator.inl"

#endif // I_OPERATOR_HPP
