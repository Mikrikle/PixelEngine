#include "PixelEngine.h"
using namespace px;


void PxError::show(Error e, std::string func_name, std::string msg)
{
	std::cerr << "Error::";
	switch (e)
	{
	case Error::INVALID_VALUE:
		std::cerr << "INVALID_VALUE::";
		break;
	case Error::OPEN_GL:
		std::cerr << "OPEN_GL::";
		break;
	default:
		break;
	}
	std::cerr << func_name << "()\n";
	std::cerr << " info: " << msg << std::endl;
}