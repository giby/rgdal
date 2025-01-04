// gdal-bindings.cpp

#include <Rinternals.h>

// Undefine the conflicting length macro
#undef length

#include <cpl_string.h>
#include <vector>
#include <locale>
#include <ogr_api.h>
#include <ogr_srs_api.h>
#include <ogr_geometry.h>
#include <ogrsf_frmts.h>

// Redefine length for R code
#define length Rf_length

// Rest of your existing code...

void someFunction() {
    // Declare variables
    int i; 
    char **papszCreateOptions = NULL;
    SEXP sOpts = R_NilValue;

    // Your existing code...
    for (i = 0; i < length(sOpts); i++) {
        papszCreateOptions = CSLAddString(papszCreateOptions, CHAR(STRING_ELT(sOpts, i)));
    }
    
    // More existing code...
}

// Additional functions and definitions...

void anotherFunction() {
    // Declare variables
    int i;
    char **papszOpenOptions = NULL;
    SEXP sOpts = R_NilValue;

    // Your existing code...
    for (i = 0; i < length(sOpts); i++) {
        papszOpenOptions = CSLAddString(papszOpenOptions, CHAR(STRING_ELT(sOpts, i)));
    }
    
    // More existing code...
}

void yetAnotherFunction() {
    // Declare variables
    int i;
    char **papszAllowedDrivers = NULL;
    SEXP allowedDr = R_NilValue;

    // Your existing code...
    for (i = 0; i < length(allowedDr); i++) {
        papszAllowedDrivers = CSLAddString(papszAllowedDrivers, CHAR(STRING_ELT(allowedDr, i)));
    }
    
    // More existing code...
}

void anotherFunctionAgain() {
    // Declare variables
    int i;
    char **papszCreateOptions = NULL;
    SEXP sxpOpts = R_NilValue;

    // Your existing code...
    for (i = 0; i < length(sxpOpts); i++) {
        papszCreateOptions = CSLAddString(papszCreateOptions, CHAR(STRING_ELT(sxpOpts, i)));
    }
    
    // More existing code...
}

void yetAnotherFunctionAgain() {
    // Declare variables
    int i;
    SEXP sxpNames = R_NilValue;

    // Your existing code...
    for (i = 0; i < length(sxpNames); ++i) {
        // Your processing code
    }
    
    // More existing code...
}
