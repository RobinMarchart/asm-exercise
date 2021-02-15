#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>
#include <ostream>
#include <vector>

struct state {
  uint32_t eax = 0;
  uint32_t ebx = 0;
  uint32_t ecx = 0;
  uint32_t edx = 0;
  uint32_t esi = 0;
  uint32_t edi = 0;
  uint32_t ebp = 0;
  std::vector<uint8_t> stack;
  void push(uint8_t value);
  void push(uint16_t value);
  void push(uint32_t value);

  state operator()(void *label) const;
  bool operator==(state const &other) const;
  bool operator==(state &&other) const;
};

std::ostream &operator<<(std::ostream &os, state const &value);

#endif
