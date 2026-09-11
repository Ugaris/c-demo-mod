# Ugaris Native Demo Mod

A simple native C mod demonstrating the Ugaris Client mod API. This mod serves as a starting point for developing native/compiled mods.

## Features

- **Simple HUD Overlay** - Displays HP, Mana, Gold, and frame counter
- **Chat Commands** - Custom commands to interact with the mod
- **Cross-Platform** - Builds for Windows, macOS, and Linux

## Commands

| Command | Description |
|---------|-------------|
| `#hello` | Display available commands |
| `#stats` | Show current player stats |
| `#overlay` | Toggle the HUD overlay |

## Installation

### Via Ugaris Launcher (Recommended)

1. Open the Ugaris Launcher
2. Go to **Options > Developer > Enable Mod Manager**
3. Navigate to the **Mods** section
4. Click **Install from URL**
5. Enter: `ugaris/ugaris-native-demo-mod`

### Manual Installation

1. Download the appropriate binary for your platform from [Releases](https://github.com/ugaris/ugaris-native-demo-mod/releases):
   - Windows: `c_demo_mod.dll`
   - macOS: `c_demo_mod.dylib`
   - Linux: `c_demo_mod.so`
2. Create a folder for it under the game's user directory and drop the
   library in beside a `mod.json`:

   ```
   <userdir>/mods/my-c-demo-mod/
     mod.json          # {"name": "C Demo Mod", "version": "1.0.1"}
     c_demo_mod.so
   ```

   `<userdir>` is `~/.local/share/Astonia/` on Linux, `%APPDATA%\Astonia\` on
   Windows and `~/Library/Application Support/Astonia/` on macOS — or whatever
   the launcher passes as `--userdir`. A folder without a `mod.json` is
   deliberately ignored.

## Building from Source

### Requirements

- CMake 3.16+
- C11 compatible compiler (GCC, Clang, or MSVC)

### Build Commands

```bash
# Create build directory
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# The output will be in build/ directory
```

### Platform-Specific Notes

**Windows:**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
# Output: build/Release/c_demo_mod.dll
```

**macOS (Universal Binary):**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
cmake --build build
# Output: build/c_demo_mod.dylib
```

**Linux:**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
# Output: build/c_demo_mod.so
```

## Mod API Overview

Native mods are dynamic libraries that implement callback functions and call client-exported functions.

### Lifecycle Callbacks

```c
char *amod_version(void);      // Return version string
void amod_init(void);          // Called when mod loads
void amod_exit(void);          // Called when mod unloads
void amod_gamestart(void);     // Called when player enters game
void amod_tick(void);          // Called 24 times per second
void amod_frame(void);         // Called every frame (60+ FPS)
```

### Input Callbacks

Return `1` to consume the event, `0` to pass through:

```c
int amod_mouse_click(int x, int y, int what);
int amod_keydown(int key);
int amod_keyup(int key);
int amod_client_cmd(const char *buf);
```

### Client Functions

```c
// Logging
void addline(const char *format, ...);   // Add message to chat
int note(const char *format, ...);       // Log to console

// Rendering
void render_rect(int sx, int sy, int ex, int ey, unsigned short color);
void render_line(int fx, int fy, int tx, int ty, unsigned short color);
int render_text(int sx, int sy, unsigned short color, int flags, const char *text);

// GUI helpers
int dotx(int didx);  // Get screen X coordinate for anchor point
int doty(int didx);  // Get screen Y coordinate for anchor point
```

### Game Data Access

```c
// Player state (read-only)
extern int hp, mana, rage, endurance, gold, experience;

// Stats: value[0][x] = modified, value[1][x] = base
extern int value[2][V_MAX];

// Map data
extern struct map map[MAPDX * MAPDY];
extern struct player player[MAXCHARS];
```

### Color Macros

Colors use RGB 5-5-5 format (0-31 per channel):

```c
#define IRGB(r, g, b) (((r) << 10) | ((g) << 5) | ((b) << 0))

// Example: bright yellow
unsigned short yellow = IRGB(31, 31, 0);
```

## Project Structure

```
ugaris-native-demo-mod/
├── .github/
│   └── workflows/
│       └── build.yml        # CI/CD for cross-platform builds
├── include/
│   ├── amod.h               # Main API header
│   ├── amod_structs.h       # Structures and constants
│   ├── astonia.h            # Basic types
│   └── dll.h                # Export/import macros
├── src/
│   └── main.c               # Mod implementation
├── CMakeLists.txt           # Build configuration
├── mod.json                 # Mod metadata
├── README.md                # This file
└── LICENSE                  # MIT License
```

## Creating Your Own Mod

1. Fork this repository
2. Modify `src/main.c` with your code
3. Update `mod.json` with your mod's info
4. Push a version tag to trigger a build:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
5. GitHub Actions will build and create a release

## How the client finds your mod

Each mod is one folder under the player's user directory, holding a `mod.json`
plus your library:

```
<userdir>/mods/
  Ugaris-c-demo-mod/
    mod.json
    c_demo_mod.so
```

- The **filename does not matter** — the client loads whatever library it finds
  in the folder. The old `amod`..`fmod` slots are gone, and so is the limit on
  how many mods can be installed.
- Ship more than one library for a platform (say a bundled dependency) and you
  must add `"entry"` to your `mod.json` naming your own, without the extension.
  The client will not guess.
- `amod` is still special, but it is not a slot you can claim: the Ugaris
  system mod ships in the game depot at `bin/amod.<ext>` and is the only mod
  allowed to override client behaviour.

## License

MIT License - See [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.
