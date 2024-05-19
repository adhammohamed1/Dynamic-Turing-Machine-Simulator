# Dynamic-Turing-Machine-Simulator
A Turing Machine (TM) Simulator. The simulator takes a TM 5-tuple (K,Σ,Γ,S,δ), and executes on an input tape. More details in README.

# Features
1. A dynamic and robust experience in input
2. The user can enter a TM 5-tuple (K,Σ,Γ,S,δ). The input is thoroughly checked and validated.
3. The user can enter an input tape. The tape is thoroughly checked and validated.
4. Given a valid TM and tape, the TM executes, displaying all the steps taken from start to finish.
5. The simulator translates the Turing Machine into a unary-encoding Universal Turing Machine representation

# But what is a Turing Machine?

A Turing Machine (TM) is a theoretical model of computation that defines an abstract machine. This model helps in understanding the limits of what can be computed. It was introduced by Alan Turing in 1936 and forms the foundation of modern theoretical computer science.

## Components of a Turing Machine

A Turing Machine consists of several components that work together to perform computations:

1. **Tape**: An infinite strip divided into cells, each capable of holding a symbol. The tape acts as the memory of the machine.
2. **Head**: A device that can read and write symbols on the tape and move left or right one cell at a time.
3. **State Register (Finite Control)**: Holds the state of the Turing Machine. The machine can be in one of a finite number of states.
4. **Finite Table of Instructions**: Describes the actions of the machine, depending on the current state and the symbol being read on the tape.

## The TM 5-tuple (K, Σ, Γ, S, δ)

A Turing Machine is formally defined by a 5-tuple (K, Σ, Γ, S, δ):

1. **K**: A finite set of states. The Turing Machine can only be in one state at a time from this set.
2. **Σ (Sigma)**: The input alphabet, a finite set of symbols that can appear on the input tape.
3. **Γ (Gamma)**: The tape alphabet, a finite set of symbols that can appear on the tape. This set includes all symbols in Σ and a special blank symbol (often denoted by ' ' or '□').
4. **S**: The initial state, one of the states in K, where the Turing Machine begins its computation.
5. **δ (delta)**: The transition function. It defines the rules for moving from one state to another, based on the current state and the symbol being read on the tape. Formally, δ is a function:
   
   δ: K × (Γ ∪ {<}) → K × (Γ ∪ {<}) × A

   Where A represents the set of valid actions = {L, R, Y, N} and {<} represents the left mark.
   This means that given a state and a tape symbol, δ produces a new state, a symbol to write on the tape, and a direction to move (L for left, R for right) or accept (Y) or reject (N).

## Examples

### 1. Easy Example: Bit Toggle Turing Machine

Let's consider a simple Turing Machine designed to toggle the bits on the tape. This example will help illustrate the TM 5-tuple and how a Turing Machine operates.

#### Problem Statement

Given a binary string on the tape, the Turing Machine should toggle each bit. For example, if the tape initially contains `1011`, after processing, it should become `0100`.

#### TM 5-tuple (K, Σ, Γ, S, δ)

1. **K**: The set of states
   - K = {q0}
   - q0: Initial state

2. **Σ (Sigma)**: The input alphabet
   - Σ = {0, 1}

3. **Γ (Gamma)**: The tape alphabet
   - Γ = {0, 1, #}
   - Note: `#` represents the blank symbol

4. **S**: The initial state
   - S = q0

5. **δ (delta)**: The transition function
   - δ: K × (Γ ∪ {<}) → K × (Γ ∪ {<}) × A
   - Describes the actions to be taken based on the current state and symbol read from the tape

#### Transition Function δ

| Current State | Read Symbol | New State | Write Symbol | Move Direction |
|---------------|-------------|-----------|--------------|----------------|
| q0            | 0           | q0        | 1            | R              |
| q0            | 1           | q0        | 0            | R              |
| q0            | #           | q0        | #            | Y              |

#### Explanation of the Transition Function

1. **State q0**:
   - The machine starts in state q0 and moves right (R) over the tape.
   - If it reads a `0`, it writes `1` and stays in q0.
   - If it reads a `1`, it writes `0` and stays in q0.
   - When it encounters a blank symbol (`#`), it accepts and halts.

#### Example Execution

For the input `1011`:

1. The machine starts in q0 and processes each bit:
   - Reads `1`, writes `0`, and moves right (stays in q0).
   - Reads `0`, writes `1`, and moves right (stays in q0).
   - Reads `1`, writes `0`, and moves right (stays in q0).
   - Reads `1`, writes `0`, and moves right (stays in q0).
2. When it encounters the blank symbol (`#`), it accepts and halts.

The final tape will be `0100`.

This simple Turing Machine example helps illustrate the concept of the TM 5-tuple and how Turing Machines perform computations.

______________________________

### 2. A more Involved Example: Binary Increment Turing Machine

Let's consider a simple Turing Machine designed to increment a binary number by one. This example will help illustrate the TM 5-tuple and how a Turing Machine operates.

#### Problem Statement

Given a binary number on the tape, the Turing Machine should increment this number by one. For example, if the tape initially contains `1011`, after processing, it should become `1100`.

#### TM 5-tuple (K, Σ, Γ, S, δ)

1. **K**: The set of states
   - K = {q0, q1}
   - q0: Initial state
   - q1: Moving left and checking for binary addition

2. **Σ (Sigma)**: The input alphabet
   - Σ = {0, 1}

3. **Γ (Gamma)**: The tape alphabet
   - Γ = {0, 1, #} 
   - Note: `#` represents the blank symbol

4. **S**: The initial state
   - S = q0

5. **δ (delta)**: The transition function
   - δ: K × (Γ ∪ {<}) → K × (Γ ∪ {<}) × A
   - Describes the actions to be taken based on the current state and symbol read from the tape

#### Transition Function δ

| Current State | Read Symbol | New State | Write Symbol | Move Direction |
|---------------|-------------|-----------|--------------|----------------|
| q0            | 0           | q0        | 0            | R              |
| q0            | 1           | q0        | 1            | R              |
| q0            | #           | q1        | #            | L              |
| q1            | 0           | q1        | 1            | Y              |
| q1            | 1           | q1        | 0            | L              |
| q1            | #           | q1        | 1            | Y              |

#### Explanation of the Transition Function

1. **State q0**:
   - The machine starts in state q0 and moves right (R) over the tape, reading each symbol (0 or 1) and staying in q0.
   - When it encounters a blank symbol (#), it moves to state q1 and moves left (L).

2. **State q1**:
   - In q1, the machine moves left (L) and performs the binary addition.
   - If it reads a 0, it writes 1 and accepts.
   - If it reads a 1, it writes 0 (carry the 1) and stays in q1, moving left (L).
   - If it reads a blank (#), it writes 1 and accepts.

#### Example Execution

For the input `1011`:

1. The machine starts in q0 and moves right until it encounters the blank symbol (#).
2. It then moves to q1, moves left, and starts the addition:
   - Reads `1`, writes `0`, and carries the 1 (stays in q1).
   - Reads `1`, writes `0`, and carries the 1 (stays in q1).
   - Reads `0`, writes `1`, and accepts (addition completed).

The final tape will be `1100`.

This simple Turing Machine example helps illustrate the concept of the TM 5-tuple and how Turing Machines perform computations.



## Significance

Turing Machines are essential in the theory of computation because they help define what it means for a function to be computable. They are used to explore the capabilities and limits of algorithmic processes and have deep implications in computer science, mathematics, and logic.

This basic understanding of Turing Machines and the 5-tuple notation will help you grasp more complex concepts in theoretical computer science and computational theory.
