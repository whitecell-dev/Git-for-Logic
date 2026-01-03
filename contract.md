# 📜 LLM WORKING CONTRACT

**(Atlas · No More Lies · Guard)**

> *A minimal, language‑agnostic framework for making LLM collaboration reliable, scalable, and safe.*

---

## 0. Motivation

LLMs are powerful, but unreliable when working on real codebases at scale.
The failure mode is not intelligence — it is **entropy**:

* Losing context in large repos
* Taking unsafe shortcuts to “make it compile”
* Modifying load‑bearing interfaces without realizing the consequences

This repository adopts a **three‑file contract** that every LLM must follow before making changes.

These files are **not documentation**.
They are **operational constraints** — closer to compiler inputs than README text.

---

## 1. The Three Required Files

Every repo that expects LLM contributions should include:

```
/calyx/
├── atlas.xx          # What exists
├── no_more_lies.yaml   # How to behave
├── guard.yaml          # What must not change
```

Each file solves a different failure mode.

---

## 2. ATLAS — The Map of Reality

**Purpose:**
Give the LLM a shared, explicit mental model of the codebase.

**Problem it solves:**
LLMs hallucinate structure when structure is implicit.

**Atlas answers only one question:**

> *“What exists, and how does it connect?”*

### What Atlas Contains

* Modules / files
* Dependencies (imports / includes)
* Exports / public symbols
* Layering (core, io, parsing, runtime, etc.)
* Ownership boundaries

### What Atlas Does NOT Contain

* Style rules
* Opinions
* Instructions
* Safety policy

Atlas is **descriptive, not prescriptive**.

### Example (simplified)

```yaml
modules:
  git_for_logic.c:
    layer: utility
    imports:
      - git_for_logic.h
    exports:
      - repo_init
      - repo_execute
      - repo_close

  git_for_logic.h:
    layer: interface
    exports:
      - repo_t
      - error_t
      - repo_init
      - repo_execute
```

**Mental model:**
Atlas is the **symbol table + dependency graph** for humans *and* LLMs.

---

## 3. NO MORE LIES — The Compiler Contract

**Purpose:**
Force the LLM to tell the truth to the language and the machine.

**Problem it solves:**
LLMs optimize for “task completion,” not correctness.

**No More Lies defines:**

* What *must* be checked
* What *cannot* be ignored
* What constitutes a valid implementation

### Language‑Specific by Design

There is **one No More Lies file per language**.

This is intentional.

C, Rust, Python, Lua, TypeScript all lie differently.

### Example (C)

```yaml
rules:
  - name: no_ignored_returns
    requirement: "All function return values must be checked"

  - name: no_bare_malloc
    requirement: "malloc/calloc must be paired with a checked allocator"

  - name: no_unbounded_copy
    requirement: "strcpy/strcat forbidden; bounds required"

  - name: explicit_error_flow
    requirement: "Functions return error_t, never void on failure paths"
```

### Mental model

**No More Lies is a compiler flag file**, not advice.

Think:

* `-Wall -Wextra -Werror`
* `mypy --strict`
* `jest --ci --no-silent`

If a rule is violated, the output is invalid — even if it “works.”

---

## 4. GUARD — The Load‑Bearing Walls

**Purpose:**
Prevent architectural damage.

**Problem it solves:**
LLMs helpfully “fix” things they should never touch.

**Guard answers one question:**

> *“What is frozen?”*

### What Guard Protects

* Public headers
* ABI / API contracts
* Stable interfaces
* Serialization formats
* Database schemas
* External guarantees

### Example

```yaml
frozen:
  - git_for_logic.h
  - public_api/*
  - error_codes.yaml

rules:
  - "Do not change function signatures"
  - "Do not reorder struct fields"
  - "Do not remove exported symbols"

allowed:
  - git_for_logic.c
  - internal/*
```

### Mental model

Guard is **ABI discipline for LLMs**.

Equivalent to:

* “You may refactor internals”
* “You may not move load‑bearing walls”
* “Breaking changes require explicit human approval”

---

## 5. How LLMs Are Expected to Work

Any LLM operating on this repo must:

1. **Read Atlas first**
   Understand what exists before touching anything.

2. **Obey No More Lies**
   Safety is part of correctness, not optional.

3. **Respect Guard**
   Frozen means frozen — even if refactoring would be “cleaner.”

If an LLM cannot comply, it must stop and ask for clarification.

---

## 6. Why This Scales Across LLMs

This system is **model‑agnostic**.

You can hand off work between:

* ChatGPT
* Claude
* DeepSeek
* Local models
* Future tools

Because the constraints live **in the repo**, not in someone’s head.

### Result:

* Shared mental map
* Shared safety rules
* Shared boundaries

No tribal knowledge required.

---

## 7. Why This Is Not Overhead

These files:

* Are small
* Change slowly
* Encode decisions you already made implicitly

They replace:

* Endless prompt repetition
* Post‑hoc code review
* Fear‑driven over‑prompting
* Fragile one‑developer + LLM workflows

---

## 8. The Philosophy (Short)

* **Atlas** reduces *confusion*
* **No More Lies** reduces *entropy*
* **Guard** reduces *blast radius*

Together, they turn LLMs from:

> “Fast but dangerous”

into:

> “Constrained, predictable collaborators”

---

## 9. Status

This is **Version 0**.

More passes will come:

* Additional validation passes
* Automated Guard enforcement
* Atlas generation tooling
* Language‑specific No More Lies libraries

But the core idea is intentionally minimal.

---

## 10. Final Note

This is not about making LLMs smarter.

It’s about making **software systems honest enough** that imperfect tools can work safely within them.

> *“You don’t need a perfect assistant — you need a system that tolerates imperfection.”*



