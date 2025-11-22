#include <doctest/doctest.h>
#include <rvcpp/instruction.h>

TEST_CASE("Instruction Decoding") {
  SUBCASE("R-type Instruction (add x1, x2, x3)") {
    // add x1, x2, x3
    // opcode: 0110011 (0x33)
    // rd: 1
    // funct3: 000
    // rs1: 2
    // rs2: 3
    // funct7: 0000000
    // Binary: 0000000 00011 00010 000 00001 0110011
    // Hex: 0x003100B3
    uint32_t raw = 0x003100B3;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x33);
    CHECK(instr.rd() == 1);
    CHECK(instr.funct3() == 0);
    CHECK(instr.rs1() == 2);
    CHECK(instr.rs2() == 3);
    CHECK(instr.funct7() == 0);
  }

  SUBCASE("I-type Instruction (addi x1, x2, -1)") {
    // addi x1, x2, -1
    // opcode: 0010011 (0x13)
    // rd: 1
    // funct3: 000
    // rs1: 2
    // imm: -1 (0xFFF)
    // Binary: 111111111111 00010 000 00001 0010011
    // Hex: 0xFFF10093
    uint32_t raw = 0xFFF10093;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x13);
    CHECK(instr.rd() == 1);
    CHECK(instr.funct3() == 0);
    CHECK(instr.rs1() == 2);
    CHECK(instr.sign_extended_imm_i() == 0xFFFFFFFF);  // -1 sign extended
  }

  SUBCASE("S-type Instruction (sw x2, 4(x1))") {
    // sw x2, 4(x1)
    // opcode: 0100011 (0x23)
    // funct3: 010 (0x2)
    // rs1: 1
    // rs2: 2
    // imm: 4 (0x004) -> imm[11:5]=0, imm[4:0]=4
    // Binary: 0000000 00010 00001 010 00100 0100011
    // Hex: 0x0020A223
    uint32_t raw = 0x0020A223;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x23);
    CHECK(instr.funct3() == 0x2);
    CHECK(instr.rs1() == 1);
    CHECK(instr.rs2() == 2);
    CHECK(instr.sign_extended_imm_s() == 4);
  }

  SUBCASE("B-type Instruction (beq x1, x2, -4)") {
    // beq x1, x2, -4
    // opcode: 1100011 (0x63)
    // funct3: 000
    // rs1: 1
    // rs2: 2
    // imm: -4 (0xFFC) -> 1111 1111 1100
    // imm[12]=1, imm[10:5]=111111, imm[4:1]=1110, imm[11]=1
    // Binary: 1 111111 00010 00001 000 1110 1 1100011
    // Hex: 0xFE208E63
    uint32_t raw = 0b1'111111'00010'00001'000'1110'1'1100011;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x63);
    CHECK(instr.funct3() == 0);
    CHECK(instr.rs1() == 1);
    CHECK(instr.rs2() == 2);
    CHECK(instr.branch_target_address(0) == 0xFFFFFFFC);  // -4 sign extended
  }

  SUBCASE("U-type Instruction (lui x1, 0x12345)") {
    // lui x1, 0x12345
    // opcode: 0110111 (0x37)
    // rd: 1
    // imm: 0x12345
    // Binary: 00010010001101000101 00001 0110111
    // Hex: 0x123450B7
    uint32_t raw = 0x123450B7;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x37);
    CHECK(instr.rd() == 1);
    CHECK(instr.shifted_upimm() == 0x12345000);  // shifted by 12
  }

  SUBCASE("J-type Instruction (jal x1, -4)") {
    // jal x1, -4
    // opcode: 1101111 (0x6F)
    // rd: 1
    // imm: -4 (0xFFFFC) -> 1111 1111 1111 1111 1100
    // imm[20]=1, imm[10:1]=1111111110, imm[11]=1, imm[19:12]=11111111
    // Binary: 1 1111111110 1 11111111 00001 1101111
    // Hex: 0xFFDFF0EF
    uint32_t raw = 0xFFDFF0EF;
    rvcpp::Instruction instr(raw);

    CHECK(instr.op() == 0x6F);
    CHECK(instr.rd() == 1);
    CHECK(instr.jump_target_address(0) == 0xFFFFFFFC);  // -4 sign extended
  }
}  // // // // // // //  ////  // ////  ////  ////  //