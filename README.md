# Expression Evaluator & Converter Suite (C)

A C-based project that evaluates and converts arithmetic expressions across **infix**, **postfix**, and **prefix** notations, built entirely with custom linked-list-based stack data structures (no STL/library stacks). The project demonstrates core data structures & algorithms concepts including stack operations, the Shunting-yard algorithm, and expression parsing.

## Modules -

### Module 1 — Postfix Evaluator
Evaluates postfix (Reverse Polish) expressions using a linked-list-based numeric stack. Supports multi-digit numbers and standard operators (`+ - * / ^`), scanning left to right and pushing operands while resolving operators as they're encountered.

### Module 2 — Infix to Postfix Converter
Converts infix expressions to postfix using the **Shunting-yard algorithm**, correctly handling operator precedence and associativity (e.g., `^` is right-associative, others are left-associative) and parentheses via an operator stack.

### Module 3 — Direct Infix Evaluator
Evaluates infix expressions directly without first converting to postfix, using a **two-stack approach** (one for operands, one for operators) that applies operators on the fly based on precedence rules.

### Module 4 — Prefix Evaluator
Evaluates prefix expressions by scanning **right to left**, using a linked-list stack and careful operand ordering to correctly handle non-commutative operators like subtraction and division.

### Module 5 — Universal Notation Converter
Implements all six conversions between infix, postfix, and prefix:
- Infix ↔ Postfix
- Infix ↔ Prefix
- Postfix ↔ Prefix (chained through infix as an intermediate form)

Uses a custom **string stack** for token-based conversions, and a reverse-and-swap technique (reverse input → swap parentheses → run Shunting-yard → reverse output) for infix-to-prefix conversion.

## Tech Details -
- **Language:** C
- **Data Structures:** Custom linked-list-based stacks (`double` for evaluation modules, `char[100]` strings for conversion modules)
- **Key Algorithms:** Shunting-yard algorithm, two-stack infix evaluation, right-to-left prefix scanning
- **No external libraries** (e.g., exponentiation implemented manually instead of using `math.h`)

## How to Run -
```bash
gcc moduleX.c -o moduleX
./moduleX
```
(Replace `moduleX` with the specific module file you want to run.)

## About Me -
**Ruthvesh Somannagari**
B.Tech CSE @ IIIT Nagpur
[LinkedIn](https://www.linkedin.com/in/ruthvesh-somannagari-591381382) | [GitHub](https://github.com/ruthveshs) | bt25cse129@iiitn.ac.in
