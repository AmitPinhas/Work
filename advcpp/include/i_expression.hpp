#ifndef I_EXPRESSION_HPP
#define I_EXPRESSION_HPP

#include <string>
#include <tr1/memory> // std::tr1::shared_ptr
#include "common.hpp" // NOEXCEPT
#include "i_logic.hpp"

namespace advcpp
{

template <typename T>    
class IExpression 
{
public:
    virtual ~IExpression() NOEXCEPT = 0; 

    virtual T Value() const = 0; 

    virtual void Traverse(const ILogic<T> & a_logic) const = 0;

    virtual std::tr1::shared_ptr<IExpression> Left() const = 0;
    virtual std::tr1::shared_ptr<IExpression> Right() const = 0;

    virtual std::string ToString() const = 0;

protected:
    IExpression();
    IExpression(const IExpression& a_rhs);
    IExpression& operator=(const IExpression& a_rhs);

};

} // namespace advcpp

#include "i_expression.inl"

#endif // I_EXPRESSION_HPP