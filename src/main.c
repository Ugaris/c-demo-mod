/*
 * Ugaris Native Demo Mod
 *
 * A simple demonstration of native mod development for the Ugaris Client.
 * This mod shows basic API usage: commands, rendering, and game data access.
 *
 * Commands:
 *   #hello     - Display a greeting message
 *   #stats     - Show current HP/Mana/Gold
 *   #overlay   - Toggle a simple HUD overlay
 */

#include <stdio.h>
#include <string.h>
#include "amod/amod.h"

/* Mod state */
static int show_overlay = 0;
static int overlay_opacity = 70;  /* demonstrates an AMOD_OPT_SLIDER */
static int frame_count = 0;

/* ========================================================================
 * LIFECYCLE CALLBACKS
 * ======================================================================== */

DLL_EXPORT char *amod_version(void)
{
    return "Native Demo Mod 1.0.0";
}

DLL_EXPORT void amod_init(void)
{
    note("Native Demo Mod initializing...");
}

DLL_EXPORT void amod_exit(void)
{
    note("Native Demo Mod shutting down.");
}

DLL_EXPORT void amod_gamestart(void)
{
    note("Native Demo Mod: Game started! Welcome, %s", username);
    addline("Native Demo Mod loaded. Type #hello for commands.");
}

DLL_EXPORT void amod_tick(void)
{
    /* Called 24 times per second */
}

DLL_EXPORT void amod_frame(void)
{
    frame_count++;

    if (!show_overlay) {
        return;
    }

    /* Draw a simple overlay panel */
    int x = dotx(DOT_TL) + 10;
    int y = doty(DOT_TL) + 10;
    int w = 180;
    int h = 80;

    /* Panel background */
    render_rect(x, y, x + w, y + h, IRGB(4, 4, 6));

    /* Panel border */
    render_line(x, y, x + w, y, IRGB(12, 12, 16));
    render_line(x, y + h, x + w, y + h, IRGB(12, 12, 16));
    render_line(x, y, x, y + h, IRGB(12, 12, 16));
    render_line(x + w, y, x + w, y + h, IRGB(12, 12, 16));

    /* Title */
    render_text(x + 4, y + 4, whitecolor, 0, "Native Demo Mod");

    /* Stats display */
    char buf[128];
    int text_y = y + 20;

    snprintf(buf, sizeof(buf), "HP: %d / %d", hp, value[0][V_HP]);
    render_text(x + 4, text_y, healthcolor, 0, buf);
    text_y += 14;

    snprintf(buf, sizeof(buf), "Mana: %d / %d", mana, value[0][V_MANA]);
    render_text(x + 4, text_y, manacolor, 0, buf);
    text_y += 14;

    snprintf(buf, sizeof(buf), "Gold: %d", gold);
    render_text(x + 4, text_y, IRGB(31, 31, 0), 0, buf);
    text_y += 14;

    snprintf(buf, sizeof(buf), "Frame: %d", frame_count);
    render_text(x + 4, text_y, textcolor, 0, buf);
}

DLL_EXPORT void amod_mouse_move(int x, int y)
{
    (void)x;
    (void)y;
}

/* ========================================================================
 * INPUT CALLBACKS
 * ======================================================================== */

DLL_EXPORT int amod_mouse_click(int x, int y, int what)
{
    (void)x;
    (void)y;
    (void)what;
    return 0; /* Don't consume */
}

DLL_EXPORT int amod_keydown(SDL_Keycode key)
{
    (void)key;
    return 0; /* Don't consume */
}

DLL_EXPORT int amod_keyup(SDL_Keycode key)
{
    (void)key;
    return 0;
}

/* ---- Settings in Options > Mods -----------------------------------------
 * Export these three and the client draws your settings under your mod's name
 * in the Mods tab: a heading, a checkbox, a slider. It calls amod_option_get()
 * each frame it draws them, so return your live values; it never saves them
 * for you, so persist anything you care about under client_config_dir(). */
DLL_EXPORT int amod_options_count(void)
{
    return 3;
}

DLL_EXPORT int amod_option_get(int index, struct amod_option *out)
{
    memset(out, 0, sizeof(*out));
    switch (index) {
    case 0:
        out->type = AMOD_OPT_HEADER;
        snprintf(out->label, sizeof(out->label), "Demo");
        return 1;
    case 1:
        out->type = AMOD_OPT_TOGGLE;
        out->value = show_overlay;
        snprintf(out->label, sizeof(out->label), "Show overlay");
        return 1;
    case 2:
        out->type = AMOD_OPT_SLIDER;
        out->value = overlay_opacity;
        out->min_val = 0;
        out->max_val = 100;
        snprintf(out->label, sizeof(out->label), "Opacity");
        return 1;
    }
    return 0;
}

DLL_EXPORT void amod_option_set(int index, int value)
{
    if (index == 1) show_overlay = value;
    else if (index == 2) overlay_opacity = value;
}

DLL_EXPORT int amod_client_cmd(const char *buf)
{
    if (strcmp(buf, "#hello") == 0) {
        addline("=== Native Demo Mod Commands ===");
        addline("#hello   - Show this help");
        addline("#stats   - Display current stats");
        addline("#overlay - Toggle HUD overlay");
        return 1;
    }

    if (strcmp(buf, "#stats") == 0) {
        int level = exp2level(experience);
        addline("=== Player Stats ===");
        addline("Level: %d  Experience: %d", level, experience);
        addline("HP: %d/%d  Mana: %d/%d", hp, value[0][V_HP], mana, value[0][V_MANA]);
        addline("STR: %d  AGI: %d  INT: %d  WIS: %d",
                value[0][V_STR], value[0][V_AGI], value[0][V_INT], value[0][V_WIS]);
        addline("Gold: %d", gold);
        return 1;
    }

    if (strcmp(buf, "#overlay") == 0) {
        show_overlay = !show_overlay;
        addline("Overlay: %s", show_overlay ? "ON" : "OFF");
        return 1;
    }

    return 0; /* Not our command */
}
