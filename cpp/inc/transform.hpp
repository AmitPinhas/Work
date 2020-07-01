#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "i_input_text.hpp"
#include "i_output_text.hpp"

namespace cpp
{

class ITransform
{
public:
	// ITransform(const ITransform& a_other) = delete
	// ITransform& operator=(const ITransform& a_other) = delete
	
	virtual ~ITransform() = 0;
	
	virtual void Transform(cpp::IInputText* a_in, cpp::IOutputText* a_out) = 0;	
};

}

#endif // TRANSFORM_HPP
