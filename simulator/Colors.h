/**
 * @file Colors.h
 * @author gon1332
 * @anchor https://stackoverflow.com/questions/1780599/what-is-the-meaning-of-posix
 * 
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 * 
 * @brief Header file providing constants for coloured output in the std output
 */


// Header guard
#ifndef COLORS_H
#define COLORS_H

// Necessary includes
#include <stdlib.h>

// Define square character
#define SQR  "\u25A0"

// Define forground colour codes
#define RST  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// Define constant colour functions
#define FBLK(x) KBLK x RST
#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

// End header guard
#endif 