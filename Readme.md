# ️ RISC-V YAML ↔ C Header Round-Trip Converter

This project demonstrates a round-trip transformation between YAML and C using the [RISC-V Unified Database](https://github.com/riscv-software-src/riscv-unified-db). The flow involves converting a RISC-V instruction YAML file into a C header file, emitting it back to YAML using C, and verifying that the transformation is consistent across multiple passes.

---

##  Files

─ script.py # Python script to convert YAML → C header
├── cToYaml.c # C code to parse header and print YAML
├── sameCheck.c # C code to compare two YAML files
├── instructions.h # Header generated from original YAML
├── generatedYml.yaml # YAML output after first C transformation
├── generatedYml1.yaml # YAML output after second C transformation


---

## ️ Requirements

- Python 3
- GCC compiler
- PyYAML module (`pip install pyyaml`)

---

##  Usage

```bash
# Convert original YAML to C header
python3 script.py spec/std/isa/inst/and.yaml instructions.h

# Compile C program and generate first YAML output
gcc cToYaml.c
./a.out > generatedYaml.yaml

# Convert the generated YAML back to header
python3 script.py generatedYaml.yaml instructions.h

# Recompile and generate second YAML output
gcc cToYaml.c -o regenerate
./regenerate > generatedYam1.yaml

# Compile comparison tool and verify outputs match
gcc sameCheck.c -o check
./check generatedYaml.yaml generatedYaml1.yaml