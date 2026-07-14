# sizefile

A minimal CLI tool that tells you how big a file is. Or several files. In human-readable units. That's it. That's the whole program.

```
$ sizefile video.mkv notes.txt kernel.tar.xz
video.mkv: 1.23 GB
notes.txt: 4.2 KB
kernel.tar.xz: 142.8 MB
```

No flags. No config files. No spinners. No 2,000-line `main.cpp`. Just `stat()` the file, convert the bytes, print it, go home. The entire program is 31 lines.

---

## Features

- **Accepts multiple files** — pass as many paths as you want, all processed in order
- **Human-readable output** — `numutils::bytes()` converts raw byte counts to KB / MB / GB automatically
- **Silently skips non-files** — if a path doesn't resolve to a file, it moves on without complaint (the commented-out `Log::warn` in the source suggests this was a design decision, not an oversight)
- **Version flag** — `sizefile -v` prints the current version (`0.4`)
- **Helpful error on no args** — prints usage hint and an ominous note about `sudo` before exiting

---

## Usage

```bash
sizefile file1 [file2 file3 ...]
```

```bash
# Single file
sizefile /var/log/syslog

# Multiple files at once
sizefile video.mkv audio.flac image.png

# Check the version
sizefile -v

# No args → usage hint
sizefile
# ERROR: sizefile needs 1 argument or more.
# INFO:  Usage: sizefile file1 file2 file3 ...
# INFO:  If it doesn't work you might have to run as sudo.
```

The `-v` flag is position-sensitive — it's checked separately from the file loop, so you can mix it in:

```bash
sizefile -v file.txt    # prints version, then file size
```

---

## Building

Only `g++` with C++20 support and `make`. The `libutils` library is bundled — no external packages needed.

```bash
git clone https://github.com/HassanIQ777/sizefile
cd sizefile
make
```

The Makefile handles three states of `libutils` automatically:

- `libutils/libutils.a` already exists → links against it directly, no rebuild
- `libutils/` exists but no `.a` → builds `libutils` from source first
- `libutils/` is absent entirely → compiles without it (header-only fallback)

```bash
# Release build (default) — -O2 -march=native -flto
make

# Debug build — ASan + UBSan, -Og, -DDEBUG
make debug

# Build and run with args
make run ARGS="file1.txt file2.txt"

# Install to /usr/local/bin
make install

# Install to a custom prefix
make install PREFIX=~/.local

# Uninstall ("yeeted into the void")
make uninstall

# Clean build artifacts ("Nothing but echoes remain...")
make clean
```

The binary lands in the project root as `./sizefile`, or in `$(PREFIX)/bin` after install.

---

## Project Structure

```
sizefile/
├── main.cpp          # 31 lines. The whole program.
├── Makefile          # 96 lines. More than twice the program.
├── libutils/         # Bundled utility library
│   └── libutils.hpp  # CLIParser, File, Log, numutils and friends
├── .gitignore
└── LICENSE           # MIT
```

The Makefile is longer than the program it builds. This is fine.

---

## License

MIT — measure freely.

---

*Made by [HassanIQ777](https://github.com/HassanIQ777)*