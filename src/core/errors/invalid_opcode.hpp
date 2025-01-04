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
    InvalidOpCodeError(const Word address, const Byte opcode) : std::runtime_error(formatMessage(address, opcode)) {}

  private:
    static std::string formatMessage(const Word address, const Byte opcode)
    {
      std::ostringstream error;
      error << "Unknown OpCode: 0x"
            << std::hex << std::uppercase << static_cast<int>(opcode)
            << " at address: 0x" << std::hex << std::uppercase << static_cast<int>(address);

      return error.str();
    }
  };
}

#endif