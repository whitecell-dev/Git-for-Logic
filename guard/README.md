# 🛡️ GUARD: The Semantic-to-Structural Firewall

### *“Implementation is fluid. Contracts are frozen.”*

## 📖 Overview

In a serious translation project (e.g., TypeScript logic → C execution), the **GUARD** is the final arbiter of correctness. While the LLM acts as the "Translator," the GUARD acts as the "Notary." It ensures that the semantic intent defined in the **ATLAS** is structurally preserved in the binary.

Without this layer, an LLM-driven compiler is just a "guess-engine." With GUARD, it becomes a **Verifiable Compilation Pipeline.**

---

## 🏗️ Why GUARD is Mandatory for Translation

When moving logic across language boundaries (High-Level to Low-Level), two types of "Lies" occur that GUARD is designed to catch:

### 1. The ABI Lie (Binary Level)

In C, the machine doesn't see "Variable Names," it sees **Memory Offsets**.

* **The Risk:** An LLM might refactor a struct to be more readable, inadvertently shifting the memory location of a critical field.
* **The Guard:** Our `guard_abi_checker.py` uses `libabigail` to compare the compiled candidate against the gold standard. If a single byte of padding shifts, the translation is rejected.

### 2. The Signature Lie (Interface Level)

In TypeScript or Python, the LLM might "improve" a function by adding an optional parameter or changing a return type.

* **The Risk:** This breaks **Source Compatibility**. Every other module that expects the old signature will now fail or, worse, behave unpredictably.
* **The Guard:** GUARD enforces **Frozen Interfaces**. It treats function signatures as immutable constants. You can renovate the "interior" (the logic), but you cannot move the "load-bearing walls" (the API).

---

## 🛠️ The Guard Toolkit

| Tool | Purpose | Enforcement Type |
| --- | --- | --- |
| `guard_abi_checker.py` | Detects shifts in struct offsets, sizes, and alignment. | **Binary (Hard)** |
| `_Static_assert` | Compile-time verification of type sizes and field positions. | **Compiler (Hard)** |
| `frozen_configs.yaml` | Defines which API signatures are forbidden from changing. | **Policy (Soft)** |

---

## 🚦 The Verification Workflow

1. **ATLAS Extraction:** Identify `@frozen` symbols and structures.
2. **LLM Translation:** The LLM generates C code based on the Atlas and "No More Lies" constraints.
3. **Static Check:** The compiler runs `_Static_assert` checks embedded in the headers.
4. **Binary Check:** `guard_abi_checker.py` compares the new `.o` file against the previous version.
5. **Commit:** Only if all guards pass is the code "promoted" to the production source.

---

## 🧠 Philosophy: The "Smalltalk Image" for C

In high-level environments, the runtime protects you. In C, you are the runtime.
**GUARD** creates a "Virtual Managed Environment" for C by ensuring that the **Shape of Reality** (The ABI) remains consistent across every LLM-driven iteration.

> **We don't trust the LLM to be careful. We trust the GUARD to be pedantic.**

---

## 🚀 How to Add a New Guard

To freeze a new structure:

1. Add the struct name to your `atlas.bundle`.
2. Wrap the struct in the C header with `CALYX_GUARD_BEGIN` / `END`.
3. Add a `sizeof` assertion:
```c
_Static_assert(sizeof(struct MyStruct) == EXPECTED_SIZE, "GUARD: ABI Shift detected!");

```
