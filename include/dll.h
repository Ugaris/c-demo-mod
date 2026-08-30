/*
 * DLL Export/Import macros for cross-platform compatibility
 */

#ifndef DLL_H
#define DLL_H

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)
#else
#if __GNUC__ >= 4 || defined(__clang__)
#define DLL_EXPORT __attribute__((visibility("default")))
/* 'extern' keeps data declarations from becoming tentative definitions:
 * without it the mod gets its own hidden zeroed copy of every client
 * variable instead of reading the client's. */
#define DLL_IMPORT extern
#else
#define DLL_EXPORT
#define DLL_IMPORT extern
#endif
#endif

#endif /* DLL_H */
