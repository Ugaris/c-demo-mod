/*
 * Astonia mod structures and constants
 * Simplified version for external mod development
 */

#ifndef AMOD_STRUCTS_H
#define AMOD_STRUCTS_H

#include <stdint.h>

/* Utility macros */
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/* Core constants */
#define V_MAX         200
#define DIST          ((unsigned int)25)
#define MAPDX         (DIST * 2 + 1)
#define MAPDY         (DIST * 2 + 1)
#define MAXMN         (MAPDX * MAPDY)
#define INVENTORYSIZE 110
#define CONTAINERSIZE (INVENTORYSIZE)
#define MAXCHARS      2048
#define MAXEF         64

/* Render alignment flags */
#define RENDER_ALIGN_OFFSET 0
#define RENDER_ALIGN_CENTER 1
#define RENDER_ALIGN_NORMAL 2

/* Text rendering flags */
#define RENDER_TEXT_LEFT    0
#define RENDER_TEXT_RIGHT   2
#define RENDER_TEXT_SHADED  4
#define RENDER_TEXT_LARGE   0
#define RENDER_TEXT_SMALL   8
#define RENDER_TEXT_FRAMED  16
#define RENDER_TEXT_BIG     32
#define RENDER_TEXT_NOCACHE 64

/* Color macros (RGB 5-5-5 format) */
#define IGET_R(c)     ((((unsigned short int)(c)) >> 10) & 0x1F)
#define IGET_G(c)     ((((unsigned short int)(c)) >> 5) & 0x1F)
#define IGET_B(c)     ((((unsigned short int)(c)) >> 0) & 0x1F)
#define IRGB(r, g, b) (((r) << 10) | ((g) << 5) | ((b) << 0))

/* Screen anchor points (DOT_*) */
#define DOT_TL  0   /* Top left */
#define DOT_BR  1   /* Bottom right */
#define DOT_WEA 2   /* Worn equipment */
#define DOT_INV 3   /* Inventory */
#define DOT_CON 4   /* Container */
#define DOT_TXT 9   /* Chat window */
#define DOT_SKL 12  /* Skill list */
#define DOT_GLD 13  /* Gold */
#define DOT_MCT 16  /* Map center */
#define DOT_TOP 17  /* Equipment bar top left */
#define DOT_BOT 18  /* Bottom window top left */
#define DOT_HLP 23  /* Help top left */
#define MAX_DOT 32

/* Stat indices (V_*) */
#define V_HP        0
#define V_ENDURANCE 1
#define V_MANA      2
#define V_WIS       3
#define V_INT       4
#define V_AGI       5
#define V_STR       6
#define V_ARMOR     7
#define V_WEAPON    8
#define V_LIGHT     9
#define V_SPEED     10

/* Mouse button events */
#define SDL_MOUM_LUP   1
#define SDL_MOUM_LDOWN 2
#define SDL_MOUM_RUP   3
#define SDL_MOUM_RDOWN 4
#define SDL_MOUM_MUP   5
#define SDL_MOUM_MDOWN 6
#define SDL_MOUM_WHEEL 7

/* Quest constants */
#define MAXSHRINE 256
#define MAXQUEST  100

/* Server mod commands */
#define SV_MOD1 58
#define SV_MOD2 59
#define SV_MOD3 60
#define SV_MOD4 61
#define SV_MOD5 62

/* Render effect structure */
typedef struct ddfx {
    unsigned int sprite;
    signed char sink;
    unsigned char scale;
    char cr, cg, cb;
    char clight, sat;
    unsigned short c1, c2, c3, shine;
    char light;
    char freeze;
    char ml, ll, rl, ul, dl;
    char align;
    short int clipsx, clipex;
    short int clipsy, clipey;
    unsigned char alpha;
} RenderFX;

/* Map tile structure */
struct map {
    unsigned short int gsprite;
    unsigned short int gsprite2;
    unsigned short int fsprite;
    unsigned short int fsprite2;
    unsigned int isprite;
    unsigned short ic1, ic2, ic3;
    unsigned int flags;
    unsigned int csprite;
    unsigned int cn;
    unsigned char cflags;
    unsigned char action;
    unsigned char duration;
    unsigned char step;
    unsigned char dir;
    unsigned char health;
    unsigned char mana;
    unsigned char shield;
    unsigned int ef[4];
    unsigned char sink;
    int value;
    int mmf;
    char rlight;
    /* Additional fields omitted for brevity */
};

/* Player structure */
struct player {
    char name[80];
    int csprite;
    short level;
    unsigned short c1, c2, c3;
    unsigned char clan;
    unsigned char pk_status;
};

/* Quest structure */
struct quest {
    unsigned char done : 6;
    unsigned char flags : 2;
};

#endif /* AMOD_STRUCTS_H */
