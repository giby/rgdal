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
