#include "registers.hpp"
#include "catch.hpp"
#include <array>
#include <cstring>

struct stack_info {
  uint32_t size;
  const uint8_t *source;
  const uint8_t *target;
  stack_info(uint32_t size, const uint8_t *source, const uint8_t *target) {
    this->size = size;
    this->source = source;
    this->target = target;
  }
};

state state::operator()(void *label) const {
  state results;
  results.stack.resize(stack.size());

  stack_info info(stack.size(), stack.data(), results.stack.data());
  // inline assembly in at&t syntax
  // this initializes the registers according to this object, and fills results
  // with the state after the call

  asm("mov %%ebp, 24(%%eax)\r\n" // write current ebp value to source ebp
      "movd %%ebx, %%xmm0\r\n"   // safe registers
      "movd %%edx, %%xmm1\r\n"
      "push %%ebp\r\n"
      "push %%eax\r\n"
      "push %%ebx\r\n"
      "push %%ecx\r\n"
      "push %%edx\r\n"
      "xor %%esi, %%esi\r\n" // write stack
      "mov 4(%%edx), %%ebx\r\n"
      "mov (%%edx), %%edx\r\n"
      "jmp stack_push_check\r\n"
      "stack_push:\r\n"
      "mov (%%ebx,%%esi), %%edi\r\n"
      "push %%edi\r\n"
      "add $1, %%esi\r\n"
      "stack_push_check:\r\n"
      "cmp %%edx, %%esi\r\n"
      "jnz stack_push\r\n"
      "mov %%ecx, -4(%%esp)\r\n" // fun hack, please never use ever again
      "mov 4(%%eax), %%ebx\r\n"  // set call registers
      "mov 8(%%eax), %%ecx\r\n"
      "mov 12(%%eax), %%edx\r\n"
      "mov 16(%%eax), %%esi\r\n"
      "mov 20(%%eax), %%edi\r\n"
      "mov (%%eax), %%eax\r\n"
      "calll -4(%%esp)\r\n" // call
      "push %%eax\r\n"
      "movd %%xmm0, %%eax\r\n"  // get output address
      "mov %%ebx, 4(%%eax)\r\n" // safe output registers
      "mov %%ecx, 8(%%eax)\r\n"
      "mov %%edx, 12(%%eax)\r\n"
      "mov %%esi, 16(%%eax)\r\n"
      "mov %%edi, 20(%%eax)\r\n"
      "mov %%ebp, 24(%%eax)\r\n"
      "pop %%ebx\r\n"
      "mov %%ebx, (%%eax)\r\n"
      "movd %%xmm1, %%edx\r\n" // remove stack
      "mov 8(%%edx), %%ebx\r\n"
      "mov (%%edx), %%eax\r\n"
      "jmp stack_pop_check\r\n"
      "stack_pop:\r\n"
      "sub $1, %%eax\r\n"
      "pop %%ecx\r\n"
      "mov %%ecx, (%%ebx, %%eax)\r\n"
      "stack_pop_check:\r\n"
      "cmp $0, %%eax\r\n"
      "jnz stack_pop\r\n"
      "pop %%edx\r\n" // restore registers
      "pop %%ecx\r\n"
      "pop %%ebx\r\n"
      "pop %%eax\r\n"
      "pop %%ebp"
      :
      : "a"(&eax), "b"(&results.eax), "c"(label), "d"(&info.size)
      : "cc", "memory", "esi", "edi", "xmm0", "xmm1");
  return results;
}

bool state::operator==(state const &other) const {
  return eax == other.eax && ebx == other.ebx && ecx == other.ecx &&
         edx == other.edx && esi == other.esi && edi == other.edi &&
         ebp == other.ebp && stack == other.stack;
}
bool state::operator==(state &&other) const {
  return eax == other.eax && ebx == other.ebx && ecx == other.ecx &&
         edx == other.edx && esi == other.esi && edi == other.edi &&
         ebp == other.ebp && stack == other.stack;
}

// convert to string
std::ostream &operator<<(std::ostream &os, state const &value) {
  os << "Stack:" << os.widen('\n');
  for (unsigned int i = 0; i < value.stack.size(); i++)
    os << std::dec << (value.stack.size() - i) << ": " << std::hex
       << (uint32_t)value.stack.at(i) << os.widen('\n');
  os << std::hex << "Register:" << os.widen('\n');
  return os << "eax: " << value.eax << os.widen('\n') << "ebx: " << value.ebx
            << os.widen('\n') << "ecx: " << value.ecx << os.widen('\n')
            << "edx: " << value.edx << os.widen('\n') << "esi: " << value.esi
            << os.widen('\n') << "edi: " << value.edi << os.widen('\n')
            << "ebp: " << value.ebp << os.widen('\n');
}

void state::push(uint8_t value) { stack.push_back(value); }

void state::push(uint16_t value) {
  std::array<uint8_t, 2> value_arr;
  std::memcpy(value_arr.data(), &value, 2);
  stack.push_back(value_arr.at(0));
  stack.push_back(value_arr.at(1));
}

void state::push(uint32_t value) {
  std::array<uint8_t, 4> value_arr;
  std::memcpy(value_arr.data(), &value, 4);
  stack.push_back(value_arr.at(0));
  stack.push_back(value_arr.at(1));
  stack.push_back(value_arr.at(2));
  stack.push_back(value_arr.at(3));
}

extern "C" {
extern void registers_test();
};

TEST_CASE("noop asm") {
  void *test = (void *)&registers_test;
  state input;
  input.eax = 1;
  input.ebx = 5;
  input.ecx = 33;
  input.edx = 123;
  input.esi = 333;
  input.edi = 1337;
  SECTION("empty stack") { REQUIRE(input == input(test)); }
  SECTION("unchanged state") {
    state output;
    output.eax = 1;
    output.ebx = 5;
    output.ecx = 33;
    output.edx = 123;
    output.esi = 333;
    output.edi = 1337;
    input(test);
    output.ebp = input.ebp;
    REQUIRE(input == output);
  }
  SECTION("1 stack") {
    input.push((uint8_t)255);
    REQUIRE(input == input(test));
  }
  SECTION("64 stack") {
    for (int i = 0; i < 16; i++)
      input.push(13376969u);
    REQUIRE(input == input(test));
  }
}
