<a id="readme-top"></a>

<br />
<div align="center">
  <h1 align="center">Json Parser</h1>
  <p align="center">
    A simple C++ console JSON validator that checks common syntax issues in a JSON file (Json.txt).
    <br />
  </p>
</div>

---

## Table of Contents
- [About The Project](#about-the-project)
- [How It Works](#how-it-works)
- [Example Features](#example-features)
- [Limitations](#limitations)
- [Demo](#demo)
- [Built With](#built-with)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)

---

## About The Project
This project provides a small JSON validator written in C++.  
It reads a local file named `Json.txt`, analyzes its structure, and prints either a specific error message (with a line number) or a final summary: `VALID` or `INVALID`.

The program is interactive:
- Press `o` to print the contents of `Json.txt`.
- Press `d` to validate the JSON and print the result.

---

## How It Works
The validator in `main.cpp` performs lightweight checks:
- The file is read while removing whitespace outside of strings. Newlines are not stored but line numbers are tracked internally to report where issues occur.
- String boundaries toggle only on unescaped quotes (e.g., `\"` does not end a string).
- Several structural checks are performed over the compacted JSON text.

This is a validator only. It does not build an in-memory JSON object.

---

## Example Features
- Verifies balanced brackets `{}` and `[]`.
- Checks for odd number of `"` quotes (unbalanced strings).
- Detects misplaced commas (e.g., trailing commas before `}` or `]`, or commas immediately after `{` or `[`).
- Ensures that after `{`, `,`, or `:` the next value is not an unquoted word (i.e., keys and string values must be quoted).
- Allows JSON keywords without quotes: `true`, `false`, `null`.
- Reports the line number for the first detected error.

---

## Limitations
- Not a full RFC 8259/ECMA-404 JSON parser.
- Does not fully validate numbers (e.g., exponents, leading zeros).
- Does not validate escape sequences or Unicode surrogate pairs inside strings beyond detecting escaped quotes.
- No support for comments.
- Only the first error is reported.
- The JSON echoed back after validation is compacted (whitespace outside strings removed).

---

## Demo

Create a `Json.txt` file alongside the executable.

Valid example (Json.txt):
```json
{
  "name": "Alice",
  "age": 25,
  "active": true,
  "tags": ["dev", "cpp"],
  "address": { "city": "Krakow", "zip": "30-001" }
}
```

Invalid example (missing quotes around key, trailing comma):
```json
{
  name: "Bob",
  "age": 30,
}
```

Sample run:
```
Welcome to the JSON Parser!
Press 'o' to open JSON file.
Press 'd' to validate JSON content.
d
Error: Unquoted word at line 2
Final result: INVALID
```

---

## Built With

| Language | Description |
|----------|-------------|
| 🟦 C++ | Core programming language |

---

## Prerequisites
- C++ compiler.

Windows options:
- Microsoft Visual C++ (MSVC) from Visual Studio or Build Tools.
- MinGW-w64 (g++).

Linux:
- g++ or clang++ (e.g., via build-essential).

---

## Installation

### 1) Clone the repository

Windows (PowerShell or CMD):
```bat
cd path\to\your\workspace
git clone https://github.com/<your-user>/<your-repo>.git
cd <your-repo>
```

Linux:
```bash
cd /path/to/your/workspace
git clone https://github.com/<your-user>/<your-repo>.git
cd <your-repo>
```

Alternatively, with SSH:
```bash
git clone git@github.com:<your-user>/<your-repo>.git
cd <your-repo>
```

Place a `Json.txt` file in the repository root (same folder you will run the program from).

### 2) Build

Windows (MSVC, from “x64 Native Tools Command Prompt for VS”):
```bat

```

Windows (MinGW-w64 in PowerShell or CMD):
```bat

```

Linux (Debian/Ubuntu):
```bash

```

Optional (clang++ on Linux):
```bash

```

---

## Usage

Windows:
```bat
JsonParser.exe
```

Linux:
```bash
./json_parser
```

Then:
- Press `o` and Enter to print the contents of `Json.txt`.
- Press `d` and Enter to validate. The program prints the compacted JSON and `Final result: VALID` or `INVALID`.

Notes:
- The program stops after validation (`d`). Run it again for another check.
- Ensure `Json.txt` is readable and encoded in UTF-8 (no BOM preferred).

---

## Troubleshooting
- “Failed to open file Json.txt”: make sure `Json.txt` exists in the current working directory.
- Unexpected “Unquoted word” errors: ensure all object keys and string values are wrapped in double quotes.
- Misplaced comma errors: remove trailing commas before `}` or `]` and avoid commas right after `{` or `[`.
- If you need a full JSON parser/loader, consider integrating a library (e.g.,