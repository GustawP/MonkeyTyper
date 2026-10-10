# MonkeyTyper

A typing game written in C++ with SFML. Words drift across the screen and you clear them by typing them before they reach the right edge.

## Gameplay

Words enter from the left on a random free row and move steadily to the right. Rows are one line of text apart, so words never overlap. Type a word correctly and it disappears, scoring a point. Let one reach the right edge and it counts as lost. The game ends after **10 lost words**, then shows the final score alongside the top five results of all time.

The pressure comes from two things ramping up at once:

- **Spawn rate** starts at one word every 180 frames and tightens by one frame with every word spawned, down to a floor of 20 frames
- **Word speed** starts at 0.3 px/frame and increases by 0.05 every 800 frames

Neither ever resets, so the board fills up faster the longer you survive.

## Before the game starts

Two setup screens run first:

1. **Font selection** – three bundled typefaces, chosen with `1`, `2` or `3`, confirmed with `Enter`
2. **Font size** – type a number, confirm with `Enter`

Font size (10–72) is a genuine difficulty setting rather than a cosmetic one: larger words are easier to read but reach the edge sooner, and fewer rows fit on screen.

## Controls

| Key | Action |
|---|---|
| A–Z | Type the word you are aiming at |
| Backspace | Delete the last character |

Input is lowercased and filtered to letters, so stray keys do not break what you are typing. A match is checked against the whole word, not per character, so you can start typing any word currently on screen. Typing a word clears every copy of it that is on screen.

## Scoring

Scores are appended to `scores.txt` in the working directory and the top five are shown on the game over screen. The word list is 69 hardcoded animal and fruit names.

## Requirements

- C++ compiler
- [SFML](https://www.sfml-dev.org/)
- CMake

Tested on Windows 10/11.

## Build and run

```bash
git clone https://github.com/GustawP/MonkeyTyper.git
cd MonkeyTyper
cmake -B build
cmake --build build
```

CMake copies the three `.ttf` files into the build directory. The game looks for them in the working directory first and one level up second, so it starts both from the build directory and from the project root.

The game over screen stays up for 10 seconds; press any key to close it sooner.

## Fixed in 2026

- **Rows leaked when a word was lost.** A row was freed when a word was typed, but not when it crossed the edge, so the pool of free rows shrank over a session and the loop searching for one could eventually spin forever. Lost words now free their row, and if every row is taken the spawn is skipped instead of searched for.
- **The game over screen froze the window** for 10 seconds with `sf::sleep`. It now keeps processing events and closes on any key.
- **Fonts only loaded when started from one specific directory.**

## Known limitations

- **The word list is hardcoded** in `main.cpp` rather than read from a file.
- **There is no restart.** After game over the program exits.

## What I learned

- Structuring a real-time game loop: input polling, state update and rendering as separate phases at a fixed 60 FPS
- Handling text input through `TextEntered` events rather than key polling, which is what makes backspace and character filtering behave correctly
- Managing a collection of objects whose lifetimes differ, and the bookkeeping that goes wrong when removal happens along more than one code path
- Never writing a loop whose exit depends on a resource that might already be used up
- Simple file-backed persistence for a high score table

## Status

University project from 2024, revisited in 2026 to fix the bugs listed above.
