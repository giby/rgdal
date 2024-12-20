# dnl Process this file with autoconf to produce a configure script.
define([pkgversion], esyscmd([sh -c "grep Version: DESCRIPTION | cut -d' ' -f2 | tr -d '\n'"]))dnl
AC_INIT([rgdal],[pkgversion],[Roger.Bivand@nhh.no])
AC_CONFIG_SRCDIR(src/gdal-bindings.cpp)

# find R home and set correct compiler + flags
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([cannot determine R_HOME. Make sure you use R CMD INSTALL!])
fi
AC_MSG_NOTICE([R_HOME: ${R_HOME}])
RBIN="${R_HOME}/bin/R"

# pick all flags for testing from R
: ${CC=`"${RBIN}" CMD config CC`}
: ${CXX=`"${RBIN}" CMD config CXX`}
: ${CFLAGS=`"${RBIN}" CMD config CFLAGS`}
: ${CPPFLAGS=`"${RBIN}" CMD config CPPFLAGS`}
: ${CXXFLAGS=`"${RBIN}" CMD config CXXFLAGS`}
: ${LDFLAGS=`"${RBIN}" CMD config LDFLAGS`}

AC_MSG_NOTICE([CC: ${CC}])
AC_MSG_NOTICE([CXX: ${CXX}])
AC_MSG_NOTICE([CFLAGS: ${CFLAGS}])
AC_MSG_NOTICE([CPPFLAGS: ${CPPFLAGS}])
AC_MSG_NOTICE([CXXFLAGS: ${CXXFLAGS}])
AC_MSG_NOTICE([LDFLAGS: ${LDFLAGS}])

AC_ARG_ENABLE([loadflags], 
    [AS_HELP_STRING([--enable-loadflags=yes/no],[use value of R CMD config LDFLAGS for configure, default yes])], 
    [loadflags=${enableval}], 
    [loadflags="yes"])

if test "${loadflags}" = "no" ; then
    LDFLAGS=""
    AC_MSG_NOTICE(value of R CMD config LDFLAGS not used for configure)
fi
AC_MSG_NOTICE([LDFLAGS: ${LDFLAGS}])

CXX17=`"${RBIN}" CMD config CXX17`
CXX17STD=`"${RBIN}" CMD config CXX17STD`

AC_MSG_NOTICE([CXX17 is: ${CXX17}, CXX17STD is: ${CXX17STD}])

CXX="${CXX17} ${CXX17STD}"

AC_MSG_NOTICE([CXX is: ${CXX}])

if test -n "${CXX17}"; then
  HAVE_CXX17=1
else
  HAVE_CXX17=0
fi

if test [${HAVE_CXX17} = 1] ; then
  AC_MSG_NOTICE([C++17 support available])
else
  AC_MSG_NOTICE([C++17 support not available])
fi

AC_MSG_NOTICE([${PACKAGE_NAME}: ${PACKAGE_VERSION}])

AC_CHECK_FILE([/usr/bin/svnversion],
 [SVN_VERSION=`svnversion -n '.'`],
 [SVN_VERSION=""])

if test "${SVN_VERSION}" != "exported" && test -n "${SVN_VERSION}" && test "${SVN_VERSION}" != "Unversioned directory"; then
  echo "${SVN_VERSION}" > inst/SVN_VERSION
else
  SVN_VERSION=`cat inst/SVN_VERSION | tr -d '\n'`
fi
AC_MSG_NOTICE([svn revision: ${SVN_VERSION}])

# Set the default path to gdal-config and allow override via --with-gdal-config
GDAL_CONFIG="gdal-config"

AC_ARG_WITH([gdal-config],
    AS_HELP_STRING([--with-gdal-config=GDAL_CONFIG],[the location of gdal-config]),
           [GDAL_CONFIG=$withval])

if test -n "$GDAL_CONFIG" ; then
    AC_MSG_NOTICE([Using specified gdal-config: $GDAL_CONFIG])
else
    AC_PATH_PROG([GDAL_CONFIG], [gdal-config], [no])
fi

if test "$GDAL_CONFIG" = "no" ; then
  AC_MSG_ERROR([gdal-config not found or not executable. Please install GDAL or make sure gdal-config is in your PATH.])
else
  AC_MSG_NOTICE([gdal-config found: ${GDAL_CONFIG}])
fi

AC_MSG_CHECKING([gdal-config usability])
if $GDAL_CONFIG --version > /dev/null 2>&1; then
  GDAL_CPPFLAGS=`${GDAL_CONFIG} --cflags`
  GDAL_LIBS=`${GDAL_CONFIG} --libs`
  GDAL_VERSION=`${GDAL_CONFIG} --version`
  GDAL_DEP_LIBS=`${GDAL_CONFIG} --dep-libs`
  GDAL_DATADIR=`${GDAL_CONFIG} --datadir`
  gdalok=yes
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([gdal-config is not usable. Please ensure GDAL is correctly installed.])
fi

AC_MSG_NOTICE([GDAL: ${GDAL_VERSION}])

# Automatically determine the best proj.pc
PROJ_PC_PATHS=("/opt/local/lib/proj9/lib/pkgconfig" "/opt/local/lib/proj8/lib/pkgconfig" "/opt/local/lib/proj5/lib/pkgconfig" "/usr/local/lib-old/pkgconfig")

for path in "${PROJ_PC_PATHS[@]}"; do
  if test -f "$path/proj.pc"; then
    export PKG_CONFIG_PATH=$path
    AC_MSG_NOTICE([Using proj.pc from: $path])
    break
  fi
done

# Check if proj.pc was set and usable
if test -z "$PKG_CONFIG_PATH"; then
  AC_MSG_ERROR([proj.pc not found in any known locations. Please install PROJ or set PKG_CONFIG_PATH manually.])
fi

# Check PROJ configuration
AC_MSG_CHECKING([pkg-config proj exists])
if pkg-config proj --exists; then
  AC_MSG_NOTICE([pkg-config proj exists, will use it])
  PROJ_CPPFLAGS=$(pkg-config proj --cflags)
  PROJ_LIBS=$(pkg-config proj --libs)
else
  AC_MSG_NOTICE([pkg-config proj not available])
  PROJ_CPPFLAGS="-I/opt/local/include"
  PROJ_LIBS="-lproj"
fi

AC_MSG_NOTICE([PROJ CPP flags: ${PROJ_CPPFLAGS}])
AC_MSG_NOTICE([PROJ LIBS: ${PROJ_LIBS}])

# Continue with the rest of the script...
# PROJ checking and other configurations continue here as in your original script
  echo "  set PKG_CONFIG_PATH to the directory containing proj.pc"
  proj_config_ok=no
fi

PROJ_VERSION=""
PROJ6=""

if test "${proj_config_ok}" = yes; then
  PROJ_VERSION=`${PROJ_CONFIG} --modversion`
  AC_MSG_NOTICE([PROJ version: ${PROJ_VERSION}])

  PROJ_VERSION_DOT=`echo ${PROJ_VERSION} | tr -d "."`
  PROJV1=`echo "${PROJ_VERSION}" | cut -c 1`

  if test "${PROJV1}" -ge 6; then
    PKG_CPPFLAGS="-DPROJ_H_API"
    PROJ6="yes"
  else
    AC_MSG_NOTICE([PROJ version < 6.0.0])
    PKG_CPPFLAGS=""
    PROJ6="no"
  fi

else
  AC_MSG_NOTICE([PROJ version not determined using pkg-config proj])
fi


AC_ARG_WITH([proj-include],
    AS_HELP_STRING([--with-proj-include=DIR],[location of proj header files]),
    [proj_include_path=$withval])
if test [ -n "$proj_include_path" ] ; then
   proj_include_path="-I${proj_include_path}"
   AC_SUBST([PKG_CPPFLAGS],["${PKG_CPPFLAGS} ${proj_include_path} ${INPKG_CPPFLAGS}"])
  if test "${proj_config_ok}" = yes; then
    AC_MSG_NOTICE([--with-proj-include= overrides pkg-config proj --cflags])
  fi
else
  if test "${proj_config_ok}" = yes; then
    PROJ_INCLUDE_PATH=`${PROJ_CONFIG} --cflags`
    proj_include_path=${PROJ_INCLUDE_PATH}
    AC_SUBST([PKG_CPPFLAGS],["${PKG_CPPFLAGS} ${PROJ_INCLUDE_PATH} ${INPKG_CPPFLAGS}"])
  fi
fi

# honor PKG_xx overrides
CPPFLAGS="${INCPPFLAGS} ${PKG_CPPFLAGS}"
AC_MSG_NOTICE([PROJ CPP flags: ${PKG_CPPFLAGS}])
PKG_LIBS=""
PROJ_LIB_PATH=""
          
# ditto for a library path
AC_ARG_WITH([proj-lib],
    AS_HELP_STRING([--with-proj-lib=LIB_PATH],[the location of proj libraries]),
               [proj_lib_path=$withval])
if test [ -n "$proj_lib_path" ] ; then
    AC_SUBST([PKG_LIBS], ["-L${proj_lib_path} ${INPKG_LIBS}"])
  if test "${proj_config_ok}" = yes; then
    AC_MSG_NOTICE([--with-proj-lib= overrides pkg-config proj --libs])
  fi
else
  if test ${proj_config_ok} = "yes"; then
    PROJ_LIB_PATH=`${PROJ_CONFIG} --libs`
    AC_SUBST([PKG_LIBS], ["${PROJ_LIB_PATH} ${INPKG_LIBS}"])
  else
    AC_SUBST([PKG_LIBS], ["${INPKG_LIBS} -lproj"])
  fi
fi

LIBS="${PKG_LIBS} ${LIBS}"
AC_MSG_NOTICE([PROJ LIBS: ${PKG_LIBS}])


AC_ARG_WITH([proj_api],
    [  --with-proj_api[=ARG]        legacy proj_api.h while still available, or current proj.h (ARG="proj_api.h", "proj.h"(default))],,)

AC_MSG_CHECKING([PROJ header API:])

if test -z "$with_proj_api" ; then
  PROJ_API=""
  if test "${PROJ6}" = "yes" ; then
    PROJ_API="proj.h"
  fi
  if test "${PROJ6}" = "no" ; then
    PROJ_API="proj_api.h"
  fi
else
  PROJ_API="$with_proj_api"
fi

api_string_ok="no"
if test -z "${PROJ_API}" ; then
  api_string_ok="yes"
fi
if test "${PROJ_API}" = "proj.h" ; then
  api_string_ok="yes"
fi
if test "${PROJ_API}" = "proj_api.h" ; then
  api_string_ok="yes"
fi

if test ${api_string_ok} = "no" ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([PROJ API string ${PROJ_API} not recognized.])
else
  AC_MSG_RESULT(yes)
fi

if test -z ${PROJ_API} ; then
  AC_MSG_NOTICE([API to be used as yet undetermined, searching ...])
  PROJ_VERSION_H=""
  LIBS="${INLIBS} ${PKG_LIBS}"
# proj.h case
[cat > proj_conf_test_proj.c <<_EOCONF
#include <stdio.h>
#include <stdlib.h>
#include <proj.h>

int main(void) {
    printf("%d.%d.%d\n", PROJ_VERSION_MAJOR, PROJ_VERSION_MINOR, PROJ_VERSION_PATCH);
    exit(0);
}
_EOCONF]

  if test `${CC} ${CFLAGS} ${PKGCPPFLAGS} -o proj_conf_test_proj proj_conf_test_proj.c ${PKG_LIBS} 2> /dev/null; echo $?` = 0 ; then
    PROJ_API="proj.h"
    PROJ6="yes"
    PROJ_VERSION_H=`./proj_conf_test_proj`
    PROJ_VERSION_DOT=`echo ${PROJ_VERSION_H} | tr -d "."`
rm -f proj_conf_test_proj.c proj_conf_test_proj
  else
[cat > proj_conf_test_proj_api.c <<_EOCONF
#include <stdio.h>
#include <stdlib.h>
#include <proj_api.h>

int main(void) {
    printf("%d\n", PJ_VERSION);
    exit(0);
}
_EOCONF]
    if test `${CC} ${CFLAGS} ${PKG_CPPFLAGS} -o proj_conf_test_proj_api proj_conf_test_proj_api.c ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
      PROJ_API="proj_api.h"
      PROJ6="no"
      PROJ_VERSION_H=`./proj_conf_test_proj_api`
      PROJ_VERSION_DOT=`echo ${PROJ_VERSION_H} | tr -d "."`
rm -f proj_conf_test_proj_api.c proj_conf_test_proj_api
    fi
  fi
  if test -z "${PROJ_VERSION_H}"; then
    AC_MSG_ERROR([API to be used not found])
  else
    AC_MSG_NOTICE([Using API: ${PROJ_API}])
  fi
fi

dnl PROJ >= 6 contains C++ code, so AC_CHECK_LIB needs to be
dnl with the C++ runtime (and rgdal is going to use C++).
AC_LANG(C++)

if test "${PROJ_API}" =  "proj.h" ; then

  if test ${PROJ6} = "yes"; then
    projhok=yes
    AC_CHECK_HEADER([proj.h],,projhok=no)
    if test "${projhok}" = no; then
      AC_MSG_ERROR([proj.h not found in given locations.])
    fi
    libprojok=yes
    AC_CHECK_LIB([proj], [proj_context_create],,libprojok=no)
    if test "${libprojok}" = no; then
      AC_MSG_ERROR([proj_context_create not found in libproj.])
    fi
  fi

fi

if test "${PROJ_API}" =  "proj_api.h"; then

LIBS="${INLIBS} ${PKG_LIBS}"
AC_MSG_CHECKING(proj_api.h presence and usability)
[cat > proj_conf_test1.c <<_EOCONF
#include <stdio.h>
#include <stdlib.h>
#include <proj_api.h>

int main(void) {
    printf("%d\n", PJ_VERSION);
    exit(0);
}
_EOCONF]

  if test `${CC} ${CFLAGS} ${PKG_CPPFLAGS} -o proj_conf_test1 proj_conf_test1.c ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
    PROJ_VERSION_H=`./proj_conf_test1`
    AC_MSG_RESULT(yes)
  else
    if test `${CC} ${CFLAGS} ${PKG_CPPFLAGS} -DACCEPT_USE_OF_DEPRECATED_PROJ_API_H -o proj_conf_test1 proj_conf_test1.c ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
      PROJ6="yes"
      PKG_CPPFLAGS="${PKG_CPPFLAGS} -DACCEPT_USE_OF_DEPRECATED_PROJ_API_H"
      PROJ_VERSION_H=`./proj_conf_test1`
      AC_MSG_RESULT(yes)
    else
      AC_MSG_RESULT(no)
      AC_MSG_ERROR([proj_api.h not found in standard or given locations.])
    fi
  fi

rm -f proj_conf_test1.c proj_conf_test1

if test -n "${PROJ_VERSION}" ; then
  AC_MSG_CHECKING([PROJ version agreement])
  PROJ_VERSION_DOT=`echo ${PROJ_VERSION} | tr -d "."`
  if test "${PROJ_VERSION_DOT}$" = "${PROJ_VERSION_H}$"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([proj_api.h and pkg-config give different versions])
  fi
fi

fi

if test -z "${PROJ_VERSION_DOT}"; then
  PROJ_VERSION_DOT=`echo ${PROJ_VERSION_H} | tr -d "."`
fi
NEW_PROJ_WITH_OLD_GDAL="no"
AC_MSG_CHECKING([Using GDAL < 3 with PROJ >= 6])
if test ${GDAL_MAJOR} -lt 3 && test ${PROJ_VERSION_DOT} -ge 600; then
    AC_MSG_RESULT(yes)
    if test ${PROJ_API} = "proj.h"; then
        AC_MSG_ERROR([GDAL >= 3 should be used with PROJ >= 6, use --with-proj_api="proj_api.h" for deprecated API])
    else
        NEW_PROJ_WITH_OLD_GDAL="yes"
        AC_MSG_WARN([GDAL >= 3 should be used with PROJ >= 6])
    fi
  else
    AC_MSG_RESULT(no)
fi

if test "${PROJ6}" = "yes" && test "${PROJ_API}" =  "proj_api.h"; then
    PKG_CPPFLAGS="${PKG_CPPFLAGS} -DACCEPT_USE_OF_DEPRECATED_PROJ_API_H"
fi

AC_MSG_CHECKING([PROJ version >= 4.8.0])
if test ${PROJ_VERSION_DOT} -lt 480 ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([upgrade PROJ to 4.8.0 or later])
else
  AC_MSG_RESULT(yes)
fi

if test ${PROJ_VERSION_DOT} -lt 493; then

if test ${PROJ_VERSION_DOT} = 480 ; then
  ADDED_PKG_INCL_480=`pwd`"/inst/include"
  AC_SUBST([PKG_CPPFLAGS],["${PKG_CPPFLAGS} -I${ADDED_PKG_INCL_480}"])
  proj_include_path="${PKG_CPPFLAGS} -I${ADDED_PKG_INCL_480}"
  CPPFLAGS="${INCPPFLAGS} ${PKG_CPPFLAGS}"
fi

AC_MSG_CHECKING(projects.h presence and usability)
[cat > proj_conf_test1a.c <<_EOCONF
#include <stdio.h>
#include <stdlib.h>
#include <projects.h>

int main(void) {
    exit(0);
}
_EOCONF]

if test `${CC} ${CFLAGS} ${PKG_CPPFLAGS} -o proj_conf_test1a proj_conf_test1a.c ${PKG_LIBS} 2> /dev/null; echo $?` = 0; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  STOP="stop"
fi
rm -f proj_conf_test1a.c proj_conf_test1a

if test "$STOP" = "stop" ; then
    echo "projects.h not found in standard or given locations."
    echo "PROJ 4.8.0 was bundled wrongly, and did not provide"
    echo "the file. A copy is provided in init/include in the source"
    echo "package for the users to place in the same directory"
    echo "as proj_api.h manually."
    exit 1
fi

fi

AC_ARG_WITH([proj-share],
    AS_HELP_STRING([--with-proj-share=SHARE_PATH],[the location of proj metadata files]),
               [proj_share_path=$withval])
if test [ -n "$proj_share_path" ] ; then
    AC_MSG_NOTICE([PROJ_LIB: ${proj_share_path}])
fi

if test ${PROJ6} = "no"; then

[cat > proj_conf_test2.c <<_EOCONF
#include <stdio.h>
#include <stdlib.h>
#include <proj_api.h>
#if PJ_VERSION == 480
FILE *pj
