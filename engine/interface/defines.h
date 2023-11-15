#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifndef DLL_USE
#ifdef LIBRARY
#define DLL_USE DLL_EXPORT
#else
#define DLL_USE DLL_IMPORT
#endif
#endif
