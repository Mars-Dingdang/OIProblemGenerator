## Key Observations

1. **Binary is fundamental**: All computer operations happen in binary. Understanding binary helps with bit manipulation, bitmasks, and low-level optimizations.

2. **Hex is compact**: One hex digit represents 4 binary digits (bits), making it convenient for representing binary data concisely.

3. **Conversion patterns**:
   - Decimal to other base: Repeated division, collect remainders in reverse order
   - Other base to decimal: Multiply and add (Horner's method)
   - Between binary/octal/hex: Group bits (3 for octal, 4 for hex) and convert directly

## Optimizations

1. **Bit operations for binary**: Use `<<`, `>>`, `&`, `|`, `^` for efficient binary manipulation instead of string operations.

2. **Precomputation**: For frequent base conversions, precompute digit mappings or use lookup tables.

3. **Two's complement**: Understand how negative numbers are represented in binary for bitwise operations.

## Common Problem Patterns

1. **Palindrome in different bases**: Check if a number reads the same in multiple bases.
2. **Base conversion as intermediate step**: Often used in problems involving bit manipulation or when input/output formats differ.
3. **Finding minimal base**: Given a number representation, find the smallest possible base.
4. **Arithmetic in different bases**: Implement addition/multiplication directly in a given base.

## Implementation Tips

- For bases > 10, use string "0123456789ABCDEF..." for digit mapping
- Handle negative numbers carefully in conversion
- For fractional parts, be aware of precision limits and potential infinite representations
- Use `std::stoi`/`std::stol` with base parameter for quick conversions in C++
- When converting between binary/octal/hex, group bits directly without going through decimal