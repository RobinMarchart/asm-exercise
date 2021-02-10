#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>
#include <ostream>

struct registers {
  uint32_t eax = 0;
  uint32_t ebx = 0;
  uint32_t ecx = 0;
  uint32_t edx = 0;
  uint32_t esi = 0;
  uint32_t edi = 0;
  uint32_t ebp = 0;

  registers operator()(void *label, bool set_ebp);
  bool operator==(registers const &other);
  bool operator==(registers &&other);
};

std::ostream &operator<<(std::ostream &os, registers const &value);

#endif
