#include "registers.hpp"

registers registers::operator()(void *label, bool set_ebp) {
  registers results;

  // inline assembly in at&t syntax
  // this initializes the registers according to this object, and fills results
  // with the state after the call

  asm("cmp $0, %%ecx\r\n"
      "jz no_set_ebp\r\n"
      "mov %%ebp, 24(%%eax)\r\n"
      "no_set_ebp:\r\n"
      "push %%ebp\r\n"
      "push %%eax\r\n"
      "push %%ebx\r\n"
      "push %%ecx\r\n"
      "push %%edx\r\n"
      "mov 4(%%eax), %%ebx\r\n"
      "mov 8(%%eax), %%ecx\r\n"
      "mov 12(%%eax), %%edx\r\n"
      "mov 16(%%eax), %%esi\r\n"
      "mov 20(%%eax), %%edi\r\n"
      "mov 24(%%eax), %%ebp\r\n"
      "mov (%%eax), %%eax\r\n"
      "call (%%esp)\r\n"
      "push %%eax\r\n"
      "mov 8(%%esp), %%eax\r\n"
      "mov %%ebx, 4(%%eax)\r\n"
      "mov %%ecx, 8(%%eax)\r\n"
      "mov %%edx, 12(%%eax)\r\n"
      "mov %%esi, 16(%%eax)\r\n"
      "mov %%edi, 20(%%eax)\r\n"
      "mov %%ebp, 24(%%eax)\r\n"
      "pop %%ebx\r\n"
      "mov %%ebx, (%%eax)\r\n"
      "pop %%edx\r\n"
      "pop %%ecx\r\n"
      "pop %%ebx\r\n"
      "pop %%eax\r\n"
      "pop %%ebp"
      :
      : "eax"(&eax), "ebx"(&results.eax), "ecx"(set_ebp), "edx"(label)
      : "cc", "memory", "esi", "edi");
  return results;
}

bool registers::operator==(registers const &other) {
  return eax == other.eax && ebx == other.ebx && ecx == other.ecx &&
         edx == other.edx && esi == other.esi && edi == other.edi &&
         ebp == other.ebp;
}
bool registers::operator==(registers &&other) {
  return eax == other.eax && ebx == other.ebx && ecx == other.ecx &&
         edx == other.edx && esi == other.esi && edi == other.edi &&
         ebp == other.ebp;
}

// convert to string
std::ostream &operator<<(std::ostream &os, registers const &value) {
  return os << std::hex << "eax: " << value.eax << os.widen('\n')
            << "ebx: " << value.ebx << os.widen('\n') << "ecx: " << value.ecx
            << os.widen('\n') << "edx: " << value.edx << os.widen('\n')
            << "esi: " << value.esi << os.widen('\n') << "edi: " << value.edi
            << os.widen('\n') << "ebp: " << value.ebp << os.widen('\n');
}
