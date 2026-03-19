# 🛠️ Kotlin Compiler

A compiler for a **subset of the Kotlin language** that generates **x86-64 assembly code** (AT&T syntax, System V ABI). Built entirely in **C++** as an academic project, it covers the full compilation pipeline: **lexical analysis → parsing → AST construction → code generation**.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Supported Language Features](#supported-language-features)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Grammar](#grammar)
- [Build & Run](#build--run)
- [Example](#example)
- [Test Cases](#test-cases)

---

## Overview

This compiler takes a `.kt` source file written in a defined Kotlin subset and produces equivalent x86-64 assembly (`.s`), ready to be assembled and linked on a Linux system using `gcc` or `as`/`ld`.

The compilation pipeline follows a classic three-stage architecture:

```
Source (.kt) → Scanner → Parser → AST → GenCodeVisitor → Assembly (.s)
```

---

## Supported Language Features

### Data Types
| Type   | Description              | Size    |
|--------|--------------------------|---------|
| `Int`  | Signed 32-bit integer    | 32 bits |
| `Long` | Signed 64-bit integer    | 64 bits |
| `UInt` | Unsigned 32-bit integer  | 32 bits |
| `ULong`| Unsigned 64-bit integer  | 64 bits |

### Variable Declarations
- `var` (mutable) and `val` (immutable — parsed but not enforced at compile time)
- Multiple declarations per line using `;` separator
- Global and local scope

### Operators
| Category           | Operators                                                |
|--------------------|----------------------------------------------------------|
| Arithmetic         | `+`, `-`, `*`, `/`, `%`                                  |
| Augmented Assign   | `+=`, `-=`, `*=`, `/=`, `%=`                             |
| Comparison         | `<`, `<=`, `>`, `>=`, `==`, `!=`                         |
| Logical            | `&&`, `\|\|`, `!`                                        |
| Bitwise            | `and`, `or`, `xor`, `inv`                                |
| Bit Shift          | `shl`, `shr`, `ushr`                                     |
| Prefix             | `+`, `-`, `!`, `++`, `--`, `inv`                         |

### Control Flow
- **`if / else`** — conditional branching
- **`for (i in start..end [step s])`** — range-based for loops with optional step
- **`while (condition)`** — while loops

### Functions
- Function declarations with `fun`
- Up to **6 parameters** (passed via registers: `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`)
- Optional return type annotation
- `return` statements
- Function calls with argument lists

### Type Conversions
- `.toInt()`, `.toLong()`, `.toUInt()`, `.toULong()`

### I/O
- `print(expression)` and `println(expression)` — outputs integer values via `printf`

---

## Architecture

The compiler is organized into four main components, following classical compiler design patterns:

### 1. Scanner (`scanner.h` / `scanner.cpp`)
The **lexical analyzer** that converts raw source text into a stream of tokens. Features:
- Whitespace handling and keyword recognition
- Multi-character token support (`+=`, `==`, `..`, `&&`, etc.)
- Number literal scanning with suffix handling (`u`, `U`, `l`, `L`) using an internal token queue
- String literal scanning (parsed but not used in code generation)

### 2. Token (`token.h` / `token.cpp`)
Defines the **`Token`** class with a comprehensive enum of all token types (~50 types), including keywords, operators, literals, and special symbols.

### 3. Parser (`parser.h` / `parser.cpp`)
A **recursive descent parser** that builds an Abstract Syntax Tree (AST) from the token stream. Key methods:
- `parseProgram()` — entry point
- `parseFunDec()` / `parseFunDecList()` — function declarations
- `parseStatement()` / `parseStatementList()` — all statement types
- `parseCExp()` → `parseLogicalExp()` → ... → `parseFactor()` — expression hierarchy with proper precedence

### 4. AST & Visitor (`exp.h` / `exp.cpp` / `visitor.h` / `visitor.cpp`)
The **Abstract Syntax Tree** node hierarchy and the **Visitor pattern** for code generation:

- **Expression nodes**: `IdentifierExp`, `NumberExp`, `BoolExp`, `BinaryExp`, `PrefixExp`, `FCallExp`, `ConversionExp`
- **Statement nodes**: `AssignStatement`, `AugmentedAssignStatement`, `PrintLnStatement`, `PrintStatement`, `IfStatement`, `ForStatement`, `WhileStatement`, `ReturnStatement`
- **Structural nodes**: `VarDec`, `VarDecList`, `Body`, `FunDec`, `FunDecList`, `StatementList`, `Program`

The **`GenCodeVisitor`** traverses the AST and emits x86-64 assembly:
- Manages **stack-based local variables** with `%rbp` offsets
- Handles **global variables** via RIP-relative addressing
- Generates proper **function prologues/epilogues** with 16-byte stack alignment
- Emits labeled **control flow** (`if/else`, `while`, `for` with unique label counters)

---

## Project Structure

```
Kotlin-Compiler/
├── Compiler/
│   ├── main.cpp          # Entry point: reads file, runs scanner, parser, and code gen
│   ├── scanner.h/.cpp    # Lexical analyzer
│   ├── token.h/.cpp      # Token definitions
│   ├── parser.h/.cpp     # Recursive descent parser
│   ├── exp.h/.cpp        # AST node definitions
│   ├── visitor.h/.cpp    # Visitor pattern & x86-64 code generation
│   ├── input.txt         # Sample Kotlin input
│   └── input.s           # Sample generated assembly output
├── Test_Cases/
│   ├── group_test_cases/         # Test cases by feature category
│   │   ├── 1_Test_VarDecs/       # Variable declarations
│   │   ├── 2_Test_Expressions/   # Arithmetic & logical expressions
│   │   ├── 3_Test_SelectiveControl_Stm/  # if/else, while, for
│   │   ├── 4_Test_FunDecs/       # Function declarations & calls
│   │   ├── 5_Test_Unsign_Int/    # Unsigned integer operations
│   │   ├── 5_Test_Unsigned_Int/  # Additional unsigned int tests
│   │   ├── 6_Test_Long_Int/      # Long integer operations
│   │   └── 7_Extras/             # Additional/combined tests
│   └── teacher_test_cases/       # Reference examples provided by instructor
├── Kotlin_Grammar.mkd    # Formal grammar in EBNF notation
├── Project_Instructions.pdf  # Original project specification
└── .gitignore
```

---

## Grammar

The compiler implements the following grammar (EBNF notation). Full specification available in [`Kotlin_Grammar.mkd`](Kotlin_Grammar.mkd).

```ebnf
Program      ::= VarDecList FunDecList
FunDec       ::= fun id ([ParamDecList]) [: Type] {Body}
Body         ::= VarDecList StmList

Stm          ::= id = CExp
               | id AugAssign CExp
               | println(CExp) | print(CExp)
               | if (CExp) {Body} [else {Body}]
               | for (id in CExp..CExp [step CExp]) {Body}
               | while (CExp) {Body}
               | return CExp

CExp         ::= LogicalExp ([ < | <= | >= | > | == | != ] LogicalExp)?
Exp          ::= Term (( + | - ) Term)*
Factor       ::= id | Num | Bool | (CExp) | PrefixOp Factor
               | id([ArgList]) | id.("toInt"|"toLong"|"toUInt"|"toULong")()
```

---

## Build & Run

### Prerequisites
- A **C++ compiler** with C++17 support (e.g., `g++`)
- **Linux environment** (or WSL) for assembling and running the generated code
- `gcc` for linking the assembly output

### Compile the Compiler

```bash
cd Compiler
g++ -std=c++17 -o compiler main.cpp scanner.cpp token.cpp parser.cpp exp.cpp visitor.cpp
```

### Run the Compiler

```bash
./compiler input.txt
```

This prints the generated x86-64 assembly to stdout. To save it to a file:

```bash
./compiler input.txt > output.s
```

### Assemble & Execute the Output

```bash
gcc -o program output.s -no-pie
./program
```

---

## Example

### Input (`input.txt`)
```kotlin
fun main() {
    var x: Int
    val y: Int
    val z: Long
    x = 1
    y = 10
    z = 1000000
    x = 20
    println(x)
    println(z)
    println(y)
}
```

### Generated Assembly (`input.s`)
```asm
.data
print_fmt: .string "%ld \n"
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
 movl $1, %eax
 movq %rax, -8(%rbp)
 movl $10, %eax
 movq %rax, -16(%rbp)
 movl $1000000, %eax
 movq %rax, -24(%rbp)
 movl $20, %eax
 movq %rax, -8(%rbp)
 movq -8(%rbp), %rax
 movq %rax, %rsi
 leaq print_fmt(%rip), %rdi
 movq $0, %rax
 call printf@PLT
 ...
.end_main:
 leave
 ret
.section .note.GNU-stack,"",@progbits
```

### Expected Output
```
20
1000000
10
```

---

## Test Cases

The project includes **two sets of test cases**:

| Set                    | Description                                      | Count |
|------------------------|--------------------------------------------------|-------|
| `group_test_cases/`    | Tests organized by feature (7 categories)        | 26+   |
| `teacher_test_cases/`  | Reference examples provided by the instructor    | 4     |

### Categories (Group Test Cases)
1. **Variable Declarations** — `var`/`val` with different types
2. **Expressions** — arithmetic, logical, bitwise, comparisons
3. **Control Flow** — `if/else`, `while`, `for` loops
4. **Function Declarations** — functions with parameters and return values
5. **Unsigned Integers** — `UInt` operations and suffix handling
6. **Long Integers** — `Long` type operations
7. **Extras** — combined/advanced test scenarios

### Running a Test

```bash
./compiler ../Test_Cases/teacher_test_cases/Example_1.kt > output.s
gcc -o program output.s -no-pie
./program
```
