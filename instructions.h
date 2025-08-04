#ifndef __GENERATED_INSTRUCTIONS_H__
#define __GENERATED_INSTRUCTIONS_H__

/* Data structure for a single key-value pair */
typedef struct {
    const char* key;
    const char* value;
} KeyValuePair;

/* Array containing all key-value pairs from the YAML file */
static const KeyValuePair data_pairs[] = {
    { .key = "$schema", .value = "\"inst_schema.json#\"" },
    { .key = "kind", .value = "\"instruction\"" },
    { .key = "name", .value = "\"andn\"" },
    { .key = "long_name", .value = "\"AND with inverted operand\"" },
    { .key = "description", .value = "\"Performs the bitwise logical AND operation between `xs1` and the\\nbitwise inversion of `xs2`.\\n\"" },
    { .key = "definedBy", .value = "{\"anyOf\":[\"Zbb\",\"Zbkb\"]}" },
    { .key = "assembly", .value = "\"xd, xs1, xs2\"" },
    { .key = "format", .value = "{\"$inherits\":[\"inst_subtype/R/R-x.yaml#/data\"],\"opcodes\":{\"funct7\":{\"display_name\":\"ANDN\",\"value\":32},\"funct3\":{\"display_name\":\"ANDN\",\"value\":7},\"opcode\":{\"$inherits\":\"inst_opcode/OP.yaml#/data\"}}}" },
    { .key = "access", .value = "{\"s\":\"always\",\"u\":\"always\",\"vs\":\"always\",\"vu\":\"always\"}" },
    { .key = "data_independent_timing", .value = "true" },
    { .key = "operation()", .value = "\"if (implemented?(ExtensionName::B) && (CSR[misa].B == 1'b0)) {\\n  raise (ExceptionCode::IllegalInstruction, mode(), $encoding);\\n}\\n\\nX[xd] = X[xs2] & ~X[xs1];\\n\"" },
    { .key = "sail()", .value = "\"{\\n  let rs1_val = X(rs1);\\n  let rs2_val = X(rs2);\\n  let result : xlenbits = match op {\\n    RISCV_ANDN => rs1_val & ~(rs2_val),\\n    RISCV_ORN  => rs1_val | ~(rs2_val),\\n    RISCV_XNOR => ~(rs1_val ^ rs2_val),\\n    RISCV_MAX  => to_bits(sizeof(xlen), max(signed(rs1_val),   signed(rs2_val))),\\n    RISCV_MAXU => to_bits(sizeof(xlen), max(unsigned(rs1_val), unsigned(rs2_val))),\\n    RISCV_MIN  => to_bits(sizeof(xlen), min(signed(rs1_val),   signed(rs2_val))),\\n    RISCV_MINU => to_bits(sizeof(xlen), min(unsigned(rs1_val), unsigned(rs2_val))),\\n    RISCV_ROL  => if sizeof(xlen) == 32\\n                  then rs1_val <<< rs2_val[4..0]\\n                  else rs1_val <<< rs2_val[5..0],\\n    RISCV_ROR  => if sizeof(xlen) == 32\\n                  then rs1_val >>> rs2_val[4..0]\\n                  else rs1_val >>> rs2_val[5..0]\\n  };\\n  X(rd) = result;\\n  RETIRE_SUCCESS\\n}\\n\"" },
};

/* Total number of key-value pairs in the array */
#define NUM_DATA_PAIRS (sizeof(data_pairs) / sizeof(data_pairs[0]))

#endif // __GENERATED_INSTRUCTIONS_H__
