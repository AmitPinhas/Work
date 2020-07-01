#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include "i_expression.hpp"
#include "i_operator.hpp"

namespace advcpp
{

template <typename T>
class BinaryExp : public IExpression<T>
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > IExpressionPtr;
    typedef std::tr1::shared_ptr<IOperator<T> > IOperatorPtr;

    BinaryExp(IExpressionPtr a_lhsExpressionPtr, IExpressionPtr a_rhsExpressionPtr, IOperatorPtr a_operatorPtr);

    virtual void Traverse(const ILogic<T> & a_logic) const;

    virtual std::tr1::shared_ptr<IExpression<T> > Left() const;
    virtual std::tr1::shared_ptr<IExpression<T> > Right() const;

    virtual std::string ToString() const;

    ~BinaryExp() NOEXCEPT;

    virtual T Value() const;

private:    
    IExpressionPtr m_lhsExpressionPtr;
    IExpressionPtr m_rhsExpressionPtr;
    IOperatorPtr m_operatorPtr;
    T m_value;
};

template <typename T>
class Num : public IExpression<T>
{
public:
    explicit Num(T a_num);

    virtual void Traverse(const ILogic<T> & a_logic) const;

    virtual std::tr1::shared_ptr<IExpression<T> > Left() const;
    virtual std::tr1::shared_ptr<IExpression<T> > Right() const;

    virtual std::string ToString() const;

    virtual T Value() const;

private:
    std::string numToString() const;

private:
    T m_num;

};

} // namespace advcpp

#include "expressions.inl"

#endif // EXPRESSIONS_HPP
