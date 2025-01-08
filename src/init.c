// src/init.c
#include <R.h>
#include <Rinternals.h>

// Example initialization function
void R_init_rgdal(DllInfo *info) {
    // Initialization code here
    Rprintf("rgdal package initialized.\n");
}
