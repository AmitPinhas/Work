#ifndef I_LOGIC_HPP
#define I_LOGIC_HPP

#include <tr1/memory> // std::tr1::shared_ptr
//#include "i_expression.hpp"

namespace advcpp
{

template <typename T>
class IExpression;

template <typename T>
class ILogic
{
public:
    virtual ~ILogic() = 0;

    virtual void Execute(const IExpression<T>& a_expression) const = 0;

protected:
    ILogic();
    ILogic(const ILogic& a_rhs);
    ILogic& operator =(const ILogic& a_rhs);

};

} // namespace advcpp

#include "inl/i_logic.inl"

#endif // I_LOGIC_HPP