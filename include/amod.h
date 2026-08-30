/*
 * Astonia Mod API Header
 *
 * This header defines the interface between mods and the Ugaris Client.
 * Mods implement the amod_* functions, and call the client-exported functions.
 */

#ifndef AMOD_H
#define AMOD_H

#include "dll.h"
#include "astonia.h"
#include "amod_structs.h"

/* Cross-compiler printf format attribute */
#if defined(__GNUC__) || defined(__clang__)
#define PRINTF_FORMAT(fmt, args) __attribute__((format(printf, fmt, args)))
#else
#define PRINTF_FORMAT(fmt, args)
#endif

/* ========================================================================
 * MOD LIFECYCLE CALLBACKS
 * Implement these functions in your mod
 * ======================================================================== */

/* Called when mod is loaded */
DLL_EXPORT void amod_init(void);

/* Called when mod is unloaded */
DLL_EXPORT void amod_exit(void);

/* Return version string for display */
DLL_EXPORT char *amod_version(void);

/* Called when player enters the game */
DLL_EXPORT void amod_gamestart(void);

/* Called every game tick (24 times per second) */
DLL_EXPORT void amod_tick(void);

/* Called every frame (up to 60+ times per second) */
DLL_EXPORT void amod_frame(void);

/* Called when mouse moves */
DLL_EXPORT void amod_mouse_move(int x, int y);

/* ========================================================================
 * INPUT CALLBACKS
 * Return values:
 *   1  = consume event, prevent client and other mods from processing
 *  -1  = consume for client only, allow other mods to process
 *   0  = don't consume, let client handle normally
 * ======================================================================== */

/* Mouse click handler */
DLL_EXPORT int amod_mouse_click(int x, int y, int what);

/* Key down handler */
DLL_EXPORT int amod_keydown(int key);

/* Key up handler (must handle if keydown was handled) */
DLL_EXPORT int amod_keyup(int key);

/* Chat command handler (commands starting with #) */
DLL_EXPORT int amod_client_cmd(const char *buf);

/* ========================================================================
 * CLIENT-EXPORTED FUNCTIONS
 * Call these functions from your mod
 * ======================================================================== */

/* Logging functions */
DLL_IMPORT int note(const char *format, ...) PRINTF_FORMAT(1, 2);
DLL_IMPORT int warn(const char *format, ...) PRINTF_FORMAT(1, 2);
DLL_IMPORT int fail(const char *format, ...) PRINTF_FORMAT(1, 2);
DLL_IMPORT void addline(const char *format, ...) PRINTF_FORMAT(1, 2);

/* Rendering functions */
DLL_IMPORT void render_rect(int sx, int sy, int ex, int ey, unsigned short int color);
DLL_IMPORT void render_line(int fx, int fy, int tx, int ty, unsigned short col);
DLL_IMPORT void render_pixel(int x, int y, unsigned short col);
DLL_IMPORT int render_text(int sx, int sy, unsigned short int color, int flags, const char *text);
DLL_IMPORT int render_text_length(int flags, const char *text);
DLL_IMPORT void render_sprite(int sprite, int scrx, int scry, int light, int align);

/* GUI position helpers */
DLL_IMPORT int dotx(int didx);
DLL_IMPORT int doty(int didx);
DLL_IMPORT int butx(int bidx);
DLL_IMPORT int buty(int bidx);

/* Utility functions */
DLL_IMPORT int exp2level(int val);
DLL_IMPORT int level2exp(int level);
DLL_IMPORT int mil_rank(int exp);

/* ========================================================================
 * CLIENT-EXPORTED DATA
 * Access game state through these variables
 * ======================================================================== */

/* Player state */
/* Current client types: stats are 16-bit, experience/gold/tick 32-bit */
DLL_IMPORT unsigned short hp;
DLL_IMPORT unsigned short mana;
DLL_IMPORT unsigned short rage;
DLL_IMPORT unsigned short endurance;
DLL_IMPORT unsigned short lifeshield;
DLL_IMPORT unsigned int experience;
DLL_IMPORT unsigned int gold;
DLL_IMPORT unsigned int tick;

/* Stats: value[0][x] = modified, value[1][x] = base */
DLL_IMPORT unsigned short value[2][V_MAX];

/* Inventory */
DLL_IMPORT int item[INVENTORYSIZE];
DLL_IMPORT int item_flags[INVENTORYSIZE];

/* Map data */
DLL_IMPORT int originx;
DLL_IMPORT int originy;
DLL_IMPORT struct map map[MAPDX * MAPDY];

/* Player data */
DLL_IMPORT struct player player[MAXCHARS];
DLL_IMPORT char username[40];

/* Keyboard modifiers */
DLL_IMPORT int vk_shift, vk_control, vk_alt;

/* Colors (pre-defined) */
DLL_IMPORT unsigned short int whitecolor, graycolor, blackcolor;
DLL_IMPORT unsigned short int redcolor, greencolor, bluecolor;
DLL_IMPORT unsigned short int textcolor, healthcolor, manacolor;

#endif /* AMOD_H */
