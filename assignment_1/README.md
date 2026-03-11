```markdown
# SONU Electronic Voting System

## Overview
The SONU Electronic Voting System is a stand-alone console-based application written in C. It allows candidates to register for positions, voters to register and vote, and the system to tally votes and announce results after the election.

## Features
- Candidate registration
- Voter registration
- Voting functionality
- Election start and stop control
- Automatic vote tallying
- Display of election results

## System Requirements
- GCC Compiler
- Linux / macOS / Windows (with MinGW or WSL)

## Project Structure
```

sonu-voting-system/
│
├── voting_system.c
├── Makefile
├── README.md
├── voters.dat
└── candidates.dat

```

## Data Files

### voters.dat
Stores voter records.

Structure:
```

VoterID | Name | HasVoted

```

### candidates.dat
Stores candidate records.

Structure:
```

CandidateID | Name | Position | Votes

```

## Compilation
```

make

```

## Run Program
```

./voting

```

## Clean Build Files
```

make clean

```

## Example Program Flow

Main Menu
```

1. Admin Menu
2. Voter Menu
3. Exit

```

Admin Menu
```

1. Register Candidate
2. View Candidates
3. Start Election
4. End Election
5. View Results
6. Back

```

Voter Menu
```

1. Register Voter
2. Vote
3. Back

```
```
