#ifndef LOGICS_HPP
#define LOGICS_HPP

#include <iostream>
#include <stack>
#include "i_logic.hpp"

namespace advcpp
{

template <typename T>
class PostOrder : public ILogic<T>
{
public:
    explicit PostOrder(ILogic<T>& a_logic);

    virtual void Execute(const IExpression<T>& a_expression) const;

private:
    ILogic<T>& m_logic;

};

template <typename T>
class InOrder : public ILogic<T>
{
public:
    explicit InOrder(ILogic<T>& a_logic);

    virtual void Execute(const IExpression<T>& a_expression) const;

private:
    ILogic<T>& m_logic;

};

template <typename T>
class PreOrder : public ILogic<T>
{
public:
    explicit PreOrder(ILogic<T>& a_logic);
    virtual void Execute(const IExpression<T>& a_expression) const;

private:
    ILogic<T>& m_logic;

};

template <typename T>
class Printer : public ILogic<T>
{
public:
    explicit Printer(std::ostream& a_os);
    virtual void Execute(const IExpression<T>& a_expression) const;

private:
    std::ostream& m_os;

};

template <typename T>
class Evaluetor : public ILogic<T>
{
public:
    virtual void Execute(const IExpression<T>& a_expression) const;

private:
    std::stack<T> m_stack;

};

} // namespace advcpp

#include "inl/logics.inl"

#endif // LOGICS_HPP