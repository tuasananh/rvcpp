#pragma once
// Represents memory layout of a 4gb ram
// 32-bit address
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <cstring>

namespace rvcpp {

  template <typename T>
  concept AllowedMemoryType
      = std::same_as<T, uint8_t> || std::same_as<T, uint16_t>
        || std::same_as<T, uint32_t> || std::same_as<T, int8_t>
        || std::same_as<T, int16_t> || std::same_as<T, int32_t>
        || std::same_as<T, std::byte>;

  constexpr size_t operator""_KiB(unsigned long long x) { return x * 1024; }
  constexpr size_t operator""_MiB(unsigned long long x) {
    return x * 1024 * 1024;
  }
  constexpr size_t operator""_GiB(unsigned long long x) {
    return x * 1024 * 1024 * 1024;
  }

  class Memory {
    static constexpr size_t MEMORY_SIZE = 4_GiB;
    static constexpr size_t DATA_SIZE
        = 16_MiB;  // i think this is enough for now
    static constexpr size_t TEXT_SIZE
        = 1_MiB;  // very small program for testing
    static constexpr size_t STACK_SIZE = 1_MiB;
    static constexpr size_t RESERVED_SIZE = 1_MiB;

    /*
    Low Address (0x0000)
    |------------------|
    |      TEXT        |  <-- PC starts here (Entry Point)
    |  (Instructions)  |
    |------------------|
    |      DATA        |
    | (Global Vars)    |
    |------------------|
    |      HEAP        |  <-- Grows Upwards (optional for now)
    |------------------|
    |       ...        |
    |     UNUSED       |
    |       ...        |
    |------------------|
    |      STACK       |  <-- Grows Downwards
    |------------------|
    |     RESERVED     |
    |------------------|
    High Address (Max)
    */

    static constexpr size_t TEXT_BASE_ADDRESS
        = 0;  // text segment starts after data segment
    static constexpr size_t DATA_BASE_ADDRESS
        = TEXT_SIZE;  // data segment starts at 0
    static constexpr size_t STACK_BASE_ADDRESS
        = MEMORY_SIZE - RESERVED_SIZE - STACK_SIZE;
    static constexpr size_t HEAP_BASE_ADDRESS = DATA_BASE_ADDRESS + DATA_SIZE;
    static constexpr size_t STACK_TOP_ADDRESS
        = MEMORY_SIZE
          - RESERVED_SIZE;  // stack grows downwards from the top of memory

    static inline bool address_in_text(uint32_t addr) {
      return addr >= TEXT_BASE_ADDRESS && addr < TEXT_BASE_ADDRESS + TEXT_SIZE;
    }

    static inline bool address_in_data(uint32_t addr) {
      return addr >= DATA_BASE_ADDRESS && addr < DATA_BASE_ADDRESS + DATA_SIZE;
    }

    static inline bool address_in_stack(uint32_t addr) {
      return addr >= STACK_BASE_ADDRESS && addr < STACK_TOP_ADDRESS;
    }

    static inline bool address_in_heap(uint32_t addr) {
      return addr >= HEAP_BASE_ADDRESS
             && addr < MEMORY_SIZE - RESERVED_SIZE - STACK_SIZE;
    }

    std::array<std::byte, TEXT_SIZE> text_memory;
    std::array<std::byte, DATA_SIZE> data_memory;
    std::array<std::byte, STACK_SIZE> stack_memory;
    std::vector<std::byte> heap_memory;  // dynamic size

  public:
    Memory();

    static constexpr uint32_t get_initial_program_counter() {
      return TEXT_BASE_ADDRESS;
    }

    static constexpr uint32_t get_initial_stack_pointer() {
      return STACK_TOP_ADDRESS;
    }

    static constexpr uint32_t get_initial_global_pointer() {
      return DATA_BASE_ADDRESS + (DATA_SIZE / 2);
    }

    static constexpr size_t get_text_size() { return TEXT_SIZE; }

    template <AllowedMemoryType T> T read(uint32_t addr) const {
      constexpr size_t type_size = sizeof(T);
      if (addr % type_size != 0) {
        throw std::runtime_error("Misaligned memory access");
      }

      const std::byte* src = nullptr;
      if (address_in_text(addr)) {
        src = &text_memory[addr - TEXT_BASE_ADDRESS];
      } else if (address_in_data(addr)) {
        src = &data_memory[addr - DATA_BASE_ADDRESS];
      } else if (address_in_stack(addr)) {
        src = &stack_memory[addr - STACK_BASE_ADDRESS];
      } else if (addr >= HEAP_BASE_ADDRESS) {
        // may fail if addr is out of current heap size
        auto heap_addr = addr - HEAP_BASE_ADDRESS;
        if (heap_addr + type_size > heap_memory.size()) {
          throw std::runtime_error("Heap memory access out of bounds");
        }
        src = &heap_memory[heap_addr];
      } else {
        throw std::runtime_error("Memory access out of bounds");
      }

      T value;
      std::memcpy(&value, src, type_size);
      return value;
    }

    template <AllowedMemoryType T> void write(uint32_t addr, T value) {
      constexpr size_t type_size = sizeof(T);
      if (addr % type_size != 0) {
        throw std::runtime_error("Misaligned memory access");
      }

      std::byte* dest = nullptr;
      if (address_in_text(addr)) {
        dest = &text_memory[addr - TEXT_BASE_ADDRESS];
      } else if (address_in_data(addr)) {
        dest = &data_memory[addr - DATA_BASE_ADDRESS];
      } else if (address_in_stack(addr)) {
        dest = &stack_memory[addr - STACK_BASE_ADDRESS];
      } else if (address_in_heap(addr)) {
        auto heap_addr = addr - HEAP_BASE_ADDRESS;
        if (heap_addr + type_size > heap_memory.size()) {
          throw std::runtime_error("Heap memory access out of bounds");
        }
        dest = &heap_memory[heap_addr];
      } else {
        throw std::runtime_error("Memory access out of bounds");
      }

      std::memcpy(dest, &value, type_size);
    }
  };
}  // namespace rvcpp
