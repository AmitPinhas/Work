#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "i_operator.hpp"
#include "i_expression.hpp"

namespace advcpp
{

template <typename T>    
class Addition : public IOperator<T>
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;
 
    virtual T operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const;

    virtual std::string ToString() const;
};

template <typename T>    
class Subtraction : public IOperator<T>
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;

    virtual T operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const;

    virtual std::string ToString() const;
};

template <typename T>    
class Multiplication : public IOperator<T>
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;

    virtual T operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const;

    virtual std::string ToString() const;
};

template <typename T>    
class Division : public IOperator<T>
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;

    virtual T operator()(const IExpressionPtr& a_lhs, const IExpressionPtr& a_rhs) const;

    virtual std::string ToString() const;
};

} // namespace advcpp

#include "inl/operators.inl"

#endif // OPERATORS_HPP
