#include "BadException.h"

const char* bad_range::what() const noexcept
{
	return "Index out of range!";
}

const char* bad_length::what() const noexcept
{
	return "Invalid array length!";
}

