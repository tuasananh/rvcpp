#include <rvcpp/machine.h>

#include <iostream>
#include <string>
#include <unordered_map>

int main(int argc, char** argv) {
  std::vector<std::byte> program
      = {// 1. addi x1, x0, 10  (00A00093) -> Bytes: 93 00 A0 00
         std::byte{0x93}, std::byte{0x00}, std::byte{0xA0}, std::byte{0x00},

         // 2. addi x2, x0, 5   (00500113) -> Bytes: 13 01 50 00
         std::byte{0x13}, std::byte{0x01}, std::byte{0x50}, std::byte{0x00},

         // 3. add  x3, x1, x2  (002081B3) -> Bytes: B3 81 20 00
         std::byte{0xB3}, std::byte{0x81}, std::byte{0x20}, std::byte{0x00},

         // 4. sub  x4, x1, x2  (40208233) -> Bytes: 33 82 20 40
         std::byte{0x33}, std::byte{0x82}, std::byte{0x20}, std::byte{0x40},

         // 5. addi x5, x0, 0   (00000293) -> Bytes: 93 02 00 00
         std::byte{0x93}, std::byte{0x02}, std::byte{0x00}, std::byte{0x00},

         // 6. sw   x3, 0(x5)   (0032A023) -> Bytes: 23 A0 32 00
         std::byte{0x23}, std::byte{0xA0}, std::byte{0x32}, std::byte{0x00},

         // 7. lw   x6, 0(x5)   (0002A303) -> Bytes: 03 A3 02 00
         std::byte{0x03}, std::byte{0xA3}, std::byte{0x02}, std::byte{0x00},

         // 8. bne  x1, x2, 8   (00209463) -> Bytes: 63 94 20 00
         std::byte{0x63}, std::byte{0x94}, std::byte{0x20}, std::byte{0x00},

         // 9. addi x1, x0, 1   (00100093) -> Bytes: 93 00 10 00 (Skipped if
         // branch taken)
         std::byte{0x93}, std::byte{0x00}, std::byte{0x10}, std::byte{0x00},

         // 10. lui x7, 0x1     (000013B7) -> Bytes: B7 13 00 00
         std::byte{0xB7}, std::byte{0x13}, std::byte{0x00}, std::byte{0x00},

         // 11. jal x0, 0       (0000006F) -> Bytes: 6F 00 00 00
         std::byte{0x6F}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}};
  static rvcpp::Machine machine(program);
  machine.simulate();
}
