import yaml
import argparse
import sys
import json

def escape_c_string(s: str) -> str:
    """Escapes special characters for inclusion in a C string literal."""
    s = s or ""
    return s.replace('\\', '\\\\').replace('"', '\\"')

def main():
    parser = argparse.ArgumentParser(
        description="Convert any YAML file to a generic C header file."
    )
    parser.add_argument("input_yaml", help="Path to the input YAML file.")
    parser.add_argument("output_header", help="Path for the generated output C header file.")
    args = parser.parse_args()

    #parsing the yaml file and reading 
    try:
        with open(args.input_yaml, 'r') as f:
            data = yaml.safe_load(f)
    except Exception as e:
        print(f"Error reading or parsing YAML file: {e}", file=sys.stderr)
        sys.exit(1)

    if not isinstance(data, dict):
        print("Error: YAML content must be a top-level dictionary.", file=sys.stderr)
        sys.exit(1)

    #  generating the C header file 
    header_content = []
    header_guard = f"__GENERATED_{args.output_header.upper().replace('.', '_')}__"
    header_content.extend([
        f"#ifndef {header_guard}",
        f"#define {header_guard}",
        "",
        "/* Data structure for a single key-value pair */",
        "typedef struct {",
        "    const char* key;",
        "    const char* value;",
        "} KeyValuePair;",
        "",
        "/* Array containing all key-value pairs from the YAML file */",
        "static const KeyValuePair data_pairs[] = {"
    ])

    for key, value in data.items():
          #taking the value into json file
        json_value = json.dumps(value, separators=(',', ':'))
        escaped_json_value = escape_c_string(json_value)

        line = f'    {{ .key = "{key}", .value = "{escaped_json_value}" }},'
        header_content.append(line)

    header_content.extend([
        "};",
        "",
        "/* Total number of key-value pairs in the array */",
        f"#define NUM_DATA_PAIRS (sizeof(data_pairs) / sizeof(data_pairs[0]))",
        "",
        f"#endif // {header_guard}",
        ""
    ])

    #writing the content to the output file
    try:
        with open(args.output_header, 'w') as f:
            f.write("\n".join(header_content))
    except IOError as e:
        print(f"Error writing to output file '{args.output_header}': {e}", file=sys.stderr)
        sys.exit(1)

    print(f" Success '{args.output_header}' with {len(data)} key-value pairs.")

if __name__ == "__main__":
    main()