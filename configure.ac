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

# Add argument to specify the location of proj.pc
AC_ARG_WITH([proj-pc],
    AS_HELP_STRING([--with-proj-pc=DIR],[location of proj.pc]),
           [PROJ_PC_DIR=$withval])

if test -n "$PROJ_PC_DIR" ; then
    export PKG_CONFIG_PATH=$PROJ_PC_DIR
    AC_MSG_NOTICE([Using proj.pc from: $PROJ_PC_DIR])
else
    # Fallback to automatic detection
    PROJ_PC_PATHS=("/opt/local/lib/proj9/lib/pkgconfig" "/opt/local/lib/proj8/lib/pkgconfig" "/opt/local/lib/proj5/lib/pkgconfig" "/usr/local/lib-old/pkgconfig")
    for path in "${PROJ_PC_PATHS[@]}"; do
      if test -f "$path/proj.pc"; then
        export PKG_CONFIG_PATH=$path
        AC_MSG_NOTICE([Using proj.pc from: $path])
        break
      fi
    done
fi

# Check if proj.pc was set and usable
if test -z "$PKG_CONFIG_PATH"; then
  AC_MSG_ERROR([proj.pc not found in any known locations. Please install PROJ or set PKG_CONFIG_PATH manually.])
fi

# Check PROJ configuration
AC_MSG_CHECKING([pkg-config proj exists])
if pkg-config proj --exists; then
  AC_MSG_NOTICE([pkg-config proj exists, will use it])
  PROJ_CPPFLAGS=$(pkg-config --cflags proj)
  PROJ_LIBS=$(pkg-config --libs proj)
else
  AC_MSG_NOTICE([pkg-config proj not available])
  PROJ_CPPFLAGS="-I/opt/local/include"
  PROJ_LIBS="-lproj"
fi

AC_MSG_NOTICE([PROJ CPP flags: ${PROJ_CPPFLAGS}])
AC_MSG_NOTICE([PROJ LIBS: ${PROJ_LIBS}])

# Check PROJ header API
AC_MSG_CHECKING([PROJ header API])
if echo "#include <proj.h>" | ${CC} -E - ${PROJ_CPPFLAGS} > /dev/null 2>&1; then
  AC_MSG_NOTICE([Using proj.h])
  PROJ_API="proj.h"
  PROJ6="yes"
elif echo "#include <proj_api.h>" | ${CC} -E - ${PROJ_CPPFLAGS} > /dev/null 2>&1; then
  AC_MSG_NOTICE([Using proj_api.h])
  PROJ_API="proj_api.h"
  PROJ6="no"
else
  AC_MSG_ERROR([Neither proj.h nor proj_api.h found in include path])
fi

# Check PROJ version
if test "${PROJ6}" = "yes"; then
  PROJ_VERSION_H=$(echo "#include <proj.h>" | ${CC} -E - ${PROJ_CPPFLAGS} - | grep -o 'PROJ_VERSION [0-9.]*' | cut -d' ' -f2)
else
  PROJ_VERSION_H=$(echo "#include <proj_api.h>" | ${CC} -E - ${PROJ_CPPFLAGS} - | grep -o 'PJ_VERSION [0-9]*' | cut -d' ' -f2)
fi

if test -z "${PROJ_VERSION_H}"; then
  AC_MSG_ERROR([Failed to determine PROJ version from headers])
else
  AC_MSG_NOTICE([Determined PROJ version from headers: ${PROJ_VERSION_H}])
fi

# Additional checks for compatibility between GDAL and PROJ versions
GDAL_MAJOR=$(echo ${GDAL_VERSION} | cut -d'.' -f1)
GDAL_MINOR=$(echo ${GDAL_VERSION} | cut -d'.' -f2)
PROJ_VERSION_DOT=$(echo ${PROJ_VERSION_H} | tr -d '.')

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

if test "${PROJ6}" = "yes" && test "${PROJ_API}" = "proj_api.h"; then
  PROJ_CPPFLAGS="${PROJ_CPPFLAGS} -DACCEPT_USE_OF_DEPRECATED_PROJ_API_H"
fi

AC_MSG_CHECKING([PROJ version >= 4.8.0])
if test ${PROJ_VERSION_DOT} -lt 480 ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([upgrade PROJ to 4.8.0 or later])
else
  AC_MSG_RESULT(yes)
fi

AC_MSG_CHECKING([projects.h presence and usability])
if echo "#include <projects.h>" | ${CC} -E - ${PROJ_CPPFLAGS} > /dev/null 2>&1; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([projects.h not found in standard or given locations.])
fi

AC_ARG_WITH([proj-share],
    AS_HELP_STRING([--with-proj-share=SHARE_PATH],[the location of proj metadata files]),
               [proj_share_path=$withval])
if test [ -n "$proj_share_path" ] ; then
    AC_MSG_NOTICE([PROJ_LIB: ${proj_share_path}])
fi

# Finalize configuration
AC_SUBST([PKG_CPPFLAGS], ["${PROJ_CPPFLAGS} ${GDAL_CPPFLAGS}"])
AC_SUBST([PKG_LIBS], ["${PROJ_LIBS} ${GDAL_LIBS} ${GDAL_DEP_LIBS}"])
AC_MSG_NOTICE([Package CPP flags: ${PKG_CPPFLAGS}])
AC_MSG_NOTICE([Package LIBS: ${PKG_LIBS}])

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT
