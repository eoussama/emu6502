#ifndef ERROR_HPP
#define ERROR_HPP

#include <sstream>
#include <stdexcept>

#include "../common/types.hpp"

namespace Core
{
  class InvalidOpCodeError : public std::runtime_error
  {
  public:
    InvalidOpCodeError(const Byte opcode) : std::runtime_error(formatMessage(opcode)) {}

  private:
    static std::string formatMessage(const Byte opcode)
    {
      std::ostringstream error;
      error << "Unknown OpCode: 0x" << std::hex << std::uppercase << static_cast<int>(opcode);

      return error.str();
    }
  };
}

#endif