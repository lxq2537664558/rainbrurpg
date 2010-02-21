dnl
dnl Modifications :
dnl - 29 dec 2008 : Using $DLL_EXT for more macros
dnl - 03 dec 2008 : 
dnl         - RB_CHECK_FREETYPE macro now check freetype-config presence
dnl         - RB_CHECK_LIBFOX macro now check fox-config presence
dnl - 27 oct 2008 : RB_CHECK_FREETYPE macro implementation for client/
dnl - 20 oct 2008 : Better handling of cross-compil through the
dnl                 RB_HANDLE_CROSS_COMPIL macro.
dnl

dnl From Jim Meyering
dnl Define HAVE_STRUCT_UTIMBUF if `struct utimbuf' is declared --
dnl usually in <utime.h>.
dnl Some systems have utime.h but don't declare the struct anywhere.

AC_DEFUN([jm_CHECK_TYPE_STRUCT_UTIMBUF],
[
  AC_CHECK_HEADERS(utime.h)
  AC_REQUIRE([AC_HEADER_TIME])
  AC_CACHE_CHECK([for struct utimbuf], fu_cv_sys_struct_utimbuf,
    [AC_TRY_COMPILE(
      [
#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#ifdef HAVE_UTIME_H
# include <utime.h>
#endif
      ],
      [static struct utimbuf x; x.actime = x.modtime;],
      fu_cv_sys_struct_utimbuf=yes,
      fu_cv_sys_struct_utimbuf=no)
    ])

  if test $fu_cv_sys_struct_utimbuf = yes; then
    AC_DEFINE_UNQUOTED(HAVE_STRUCT_UTIMBUF, 1,
[Define if struct utimbuf is declared -- usually in <utime.h>.
   Some systems have utime.h but don't declare the struct anywhere. ])
  fi
])

dnl Defines installation directory in config.h
dnl
dnl The prefix var is set to the prefix configure parameter 
dnl './configure --prefix=???'
dnl If this parameter is not used, $prefix is set to NONE
dnl
dnl We then use the ASSUMED_INSTALL_PEFIX
AC_DEFUN([RB_INSTALL_DIR],
[

  ASSUMED_INSTALL_PEFIX=/usr/local
  GET_INSTALL_PREFIX=$prefix
  if test $prefix = NONE; then
    GET_INSTALL_PREFIX=$ASSUMED_INSTALL_PEFIX
    echo "#############################################################"
    echo "  Warning :"
    echo "  Install prefix is NONE, assuming " $GET_INSTALL_PREFIX
    echo "#############################################################"
  else
    echo "Found install prefix set to " $GET_INSTALL_PREFIX
  fi

  dnl Using the UNQUOTED definition to get shell expansion for
  dnl GET_INSTALL_PREFIX variable
  AC_DEFINE_UNQUOTED([USER_INSTALL_PREFIX], "${GET_INSTALL_PREFIX}", 
  [
  The directory installation prefix.

  This value is needed to locate the datafiles.
  ])

])

dnl Tests the OgreMain lib and headers
dnl
dnl This function is used to test the header Ogre.h and
dnl the OgreMain library. It is used by configure.in
dnl
dnl Warning : This macro need to be called after RB_CHECK_FREETYPE
dnl           because it uses FREETYPE_LIBS value
dnl
AC_DEFUN([RB_CHECK_OGREMAIN],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding OGRE flags for "mingw32msvc""
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/OGRE"
    LDFLAGS="$LDFLAGS -lOgreMain$DLL_EXT -lfreeimage$DLL_EXT"
    echo "Adding zzip flags for "mingw32msvc""
    LDFLAGS="$LDFLAGS -lzzip$DLL_EXT $FREETYPE_LIBS"
    echo "Adding libintl flags for "mingw32msvc""
    LDFLAGS="$LDFLAGS -lintl$DLL_EXT"
    AC_SUBST(OGRE_PLUGINDIR, [$rb_cross_compil_prefix/lib/OGRE])
  else
    PKG_CHECK_MODULES(OGRE, [OGRE >= 1.4.0])
    AC_SUBST(OGRE_PLUGINDIR, [$($PKG_CONFIG --variable=plugindir OGRE)])

    # Devil
    AC_CHECK_LIB(jpeg, main, [], [])
  fi
])

dnl Checks for libOIS and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBOIS],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding OIS flags for "mingw32msvc""
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/OIS"
    LDFLAGS="$LDFLAGS -lOIS$DLL_EXT"
  else
    PKG_CHECK_MODULES(OIS, [OIS >= 0.1])	
  fi
])

dnl Checks for the FOX-toolkit and one of its header
dnl
dnl It set the FOX_CONFIG var to the fox-config tool executable
dnl or exit with an error if no found.
dnl
dnl Then, it set the FOX_CFLAGS and FOX_LIBS to fox-config returned value
dnl
dnl param: $1 The version number that must at least be installed. Examples:
dnl        1.6 or 1.8 (wothout quotes or revision number).
dnl
dnl
AC_DEFUN([RB_CHECK_LIBFOX],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding FOX flags for "mingw32msvc""
    FOX_CFLAGS="-I$rb_cross_compil_prefix/include/FOX-1.6"
    FOX_LIBS="-lFOX-1.6$DLL_EXT"
  else
    dnl Get the correct executable
    AC_PATH_TOOL(FOX_CONFIG, fox-config, 'NOT_FOUND')

    if test $FOX_CONFIG = 'NOT_FOUND'
    then
      echo "Error! You need the Fox-Toolkit installed. Cannot find the fox-config tool."
      exit -1
    fi


    dnl check for version
    echo -n "checking if Fox version is at least v$1... "
    FOX_VERSION=`$FOX_CONFIG --version`
    if test "${FOX_VERSION:0:3}" == "$1"
    then 
      echo "yes"
    else
      echo "no"
      echo -n "Error! You need at least Fox-Toolkit v$1. "
      echo "The version I found is $FOX_VERSION."
      exit -1
    fi

    dnl Getting compiler flags
    FOX_CFLAGS=`$FOX_CONFIG --cflags`
    FOX_LIBS=`$FOX_CONFIG --libs`
  fi

  AC_SUBST(FOX_CFLAGS)
  AC_SUBST(FOX_LIBS)
])

dnl Checks for the Curl lib and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBCURL],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding CURL flags for "mingw32msvc""
    libcurl_CFLAGS="-I$rb_cross_compil_prefix/include/curl"
    libcurl_LIBS="-lcurl$DLL_EXT"
  else
    PKG_CHECK_MODULES(libcurl, [libcurl >= 7.15])	
  fi  
])

dnl Checks for the SLang lib and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBSLANG],
[
  AC_CHECK_LIB(slang, main, [], [
    echo "Error! You need to have SLang installed."
    exit -1
  ])
  AC_CHECK_HEADER([slang.h], [], [
    echo "Error! Cannot find the SLang headers."
    exit -1
  ])

])

dnl Checks for the PagingLandScapeManager2 Ogre plugin
dnl
dnl We don't need to check headers as it is a dlopened library but 
dnl it is not a lib* called file so we use AC_CHECK_FILE, first in /usr/lib
dnl then, if not found, in /usr/local/lib
dnl
dnl If PLSM2 is not found, it does not exit, it complains about the error
dnl but does not exit.
dnl
AC_DEFUN([RB_CHECK_PLSM2],
[
dnl  AC_CHECK_FILE(/usr/lib/OGRE/Plugin_PagingLandScape2.so, [], [
dnl    AC_CHECK_FILE(/usr/local/lib/OGRE/Plugin_PagingLandScape2.so, [], [
dnl      echo "Error! You need to have the PagingLandScape2 Ogre plugin."
dnl      exit -1
dnl    ])
dnl  ])
])

dnl Define the server Option 
dnl
dnl Provides the --enable-server option of the configure script
dnl By default, the server is disabled
dnl
AC_DEFUN([RB_OPTION_SERVER],
[
  AC_ARG_ENABLE(server, AC_HELP_STRING([--enable-server],
    [Build the RainbruRPG server. It is recommended if you want to
       run your own public server or if you want local play
       (default=no)]),
    [build_server=$enableval], 
    [build_server=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-server])

  case $build_server in
    yes)
      server=true
      AC_DEFINE([BUILD_SERVER], [], [Defines if the server is built])
      AC_DEFINE(BUILD_SERVER)
      AC_MSG_RESULT(yes)
      ;;
    *)
      server=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_SERVER_FLAGS], [test x$server = xtrue])
  AC_DEFINE([BUILD_LIB_DESIGN], [], [Is the design library built ?])
  AM_CONDITIONAL([BUILD_LIB_DESIGN], [test x$server = xtrue])
])

dnl Define the editor Option 
dnl
dnl Provides the --enable-editor option of the configure script
dnl By default, the editor is disabled
dnl
AC_DEFUN([RB_OPTION_EDITOR],
[
  AC_ARG_ENABLE(editor, AC_HELP_STRING([--enable-editor],
    [Build the RainbruRPG editor. It is recommended if you want to
       creates your own maps or edit an existing one
       (default=no)]),
    [build_editor=$enableval], 
    [build_editor=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-editor])

  case $build_editor in
    yes)
      editor=true
      AC_DEFINE([BUILD_EDITOR], [], [Defines if the editor is built])
      AC_DEFINE(BUILD_EDITOR)
      AC_MSG_RESULT(yes)
      ;;
    *)
      editor=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_EDITOR_FLAGS], [test x$editor = xtrue])
  AM_CONDITIONAL([BUILD_LIB_DESIGN], [test x$editor = xtrue])
])

dnl Checks for the boost_filesystem lib ad headers
dnl
dnl
AC_DEFUN([RB_CHECK_BOOST_FS],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding boost_filesystem flags for "mingw32msvc""
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/"
    LDFLAGS="$LDFLAGS -lboost_filesystem-1_34_1$DLL_EXT"
  else
    AC_CHECK_LIB(boost_filesystem, main, [], [
      echo "Error! You need to have Boost-filesystem installed."
      exit -1
    ])
    AC_CHECK_HEADER([boost/filesystem/path.hpp], [], [
      echo "Error! Cannot find the Boost-filesystem headers."
      exit -1
    ])
  fi
])

dnl Define the tools Option 
dnl
dnl Provides the --enable-editor option of the configure script
dnl By default, the editor is disabled
dnl
AC_DEFUN([RB_OPTION_TOOLS],
[
  AC_ARG_ENABLE(tools, AC_HELP_STRING([--enable-tools],
    [Build the RainbruRPG tools. It is recommended only for package
	maintainers and curious users
       (default=no)]),
    [build_tools=$enableval], 
    [build_tools=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-tools])

  case $build_tools in
    yes)
      tools=true
      AC_MSG_RESULT(yes)
      ;;
    *)
      tools=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_TOOLS_FLAGS], [test x$tools = xtrue])
])

dnl Checks for the Qt4 lib ad headers (QtCore and QtGui needed)
dnl
dnl
AC_DEFUN([RB_CHECK_QT4],
[
  AC_CHECK_LIB(QtCore, main, [], [
    echo "Error! You need to have Qt4 (Core) installed."
    exit -1
  ])
  AC_CHECK_LIB(QtGui, main, [], [
    echo "Error! You need to have Qt4 (Gui) installed."
    exit -1
  ])
  AC_CHECK_LIB(QtNetwork, main, [], [
    echo "Error! You need to have Qt4 (Network) installed."
    exit -1
  ])
  AC_CHECK_LIB(Qt3Support, main, [], [
    echo "Error! You need to have Qt4 (Qt3Support) installed."
    exit -1
  ])

dnl  AC_CHECK_HEADER([qt4/Qt/qevent.h], [], [
dnl    echo "Error! Cannot find Qt4 headers."
dnl    exit -1
dnl  ])

])

dnl Checks for the Qt4 lib ad headers (QtCore and QtGui needed)
dnl
dnl
AC_DEFUN([RB_CHECK_ENET],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding enet flags for "mingw32msvc""
dnl Do not include directly enet/ cause it define a time.h file that
dnl seems to conflict with a system header file
dnl    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/enet/"
    LDFLAGS="$LDFLAGS -lenet$DLL_EXT"
  else
    AC_CHECK_LIB(enet, main, [], [
      echo "Error! You need to have libenet-dev installed."
    exit -1
    ])

    AC_CHECK_HEADER([enet/enet.h], [], [
      echo "Error! Cannot find libenet headers."
      exit -1
    ])
  fi
])

dnl Defines the tests Option 
dnl
dnl Provides the --enable-test option of the configure script
dnl By default, the unit tests is disabled
dnl
AC_DEFUN([RB_OPTION_TESTS],
[
  AC_ARG_ENABLE(tests, AC_HELP_STRING([--enable-tests],
    [Build the RainbruRPG unit tests. It is recommended only for package
	maintainers and curious users
       (default=no)]),
    [build_tests=$enableval], 
    [build_tests=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-tests])

  case $build_tests in
    yes)
      tests=true
      AC_MSG_RESULT(yes)
      ;;
    *)
      tests=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_TESTS_FLAGS], [test x$tests = xtrue])
])

dnl Tests the glib library and headers
dnl
AC_DEFUN([RB_CHECK_GLIB],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding glib-2.0 flags for mingw32msvc"
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/glib-2.0/"
    LDFLAGS="$LDFLAGS -lglib-2.0$DLL_EXT"
  else
    PKG_CHECK_MODULES(GLIB, [glib-2.0 >= 2.0.0])
  fi
])

dnl Tests the libsig++ library and headers
dnl
AC_DEFUN([RB_CHECK_LIBSIG],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding sigc++ flags for mingw32msvc"
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/sigc++-2.0/"
    LDFLAGS="$LDFLAGS -lsigc-2.0$DLL_EXT"
  else
    PKG_CHECK_MODULES(SIGC, [sigc++-2.0 >= 2.0.0])
  fi
])

dnl Tests the libgd library and headers
dnl
AC_DEFUN([RB_CHECK_LIBGD],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding libgd flags for mingw32msvc"
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/sigc++-2.0/"
    LDFLAGS="$LDFLAGS -lgd$DLL_EXT"
  else
    AC_CHECK_LIB(gd, main, [], [
      echo "Error! You need to have libgd installed."
      exit -1
    ])
    AC_CHECK_HEADER([gd.h], [], [
       echo "Error! Cannot find the libgd headers."
       exit -1
     ])
  fi
])

dnl Tests the libgnet library and headers
dnl
AC_DEFUN([RB_CHECK_LIBGNET],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding libgnet-2.0 flags for mingw32msvc"
    CFLAGS="$CFLAGS -I$rb_cross_compil_prefix/include/gnet/"
    LDFLAGS="$LDFLAGS -lgnet-2.0$DLL_EXT"
  else
    PKG_CHECK_MODULES(GNET, [gnet-2.0 >= 2.0.0])
  fi

])


dnl Test the usability of the boost::thread library
dnl
AC_DEFUN([RB_CHECK_BOOST_THREAD],
[
  if test $rb_cross_compil_host == "win32"
  then	
    echo "Adding boost_thread flags for "mingw32msvc""
    CFLAGS="$CFLAGS"
    LDFLAGS="$LDFLAGS -lboost_thread-1_34_1$DLL_EXT"
  else
    AC_CHECK_LIB(boost_thread, main, [], [
      echo "Error! You need to have boost::thread installed."
      exit -1
    ])
    AC_CHECK_HEADER([boost/thread.hpp], [], [
       echo "Error! Cannot find the boost::thread headers."
       exit -1
    ])
  fi
])

dnl Test the usability of the magic library
dnl
AC_DEFUN([RB_CHECK_MAGIC],
[
  AC_CHECK_LIB(magic, main, [], [
    echo "Error! You need to have libmagic installed."
    exit -1
  ])
  AC_CHECK_HEADER([magic.h], [], [
     echo "Error! Cannot find the libmagic headers."
     exit -1
   ])
])

dnl The following RB_CHECK_DEFINED function is based on a macro 
dnl taken from the web page : 
dnl http://gnu.univ-paris.com/software/ac-archive/ax_check_define.html
dnl
dnl Many thanks to the original author

AC_DEFUN([RB_CHECK_DEFINED],[
AS_VAR_PUSHDEF([ac_var],[ac_cv_defined_$1])dnl
AC_CACHE_CHECK([for $1 defined], ac_var,
AC_TRY_COMPILE(,[
  #ifdef $1
  int ok;
  #else
  choke me
  #endif
],AS_VAR_SET(ac_var, yes),AS_VAR_SET(ac_var, no)))
AS_IF([test AS_VAR_GET(ac_var) != "no"], [$2], [$3])dnl
AS_VAR_POPDEF([ac_var])dnl
])

dnl RB_CONDITIONAL_LINKING
AC_DEFUN([RB_CONDITIONAL_LINKING_LIB_MAGIC],
[
  # cheking libMagic if we build the server
  RB_CHECK_DEFINED([BUILD_SERVER], [
    echo "Server will be built, checking for libmagic, qt"
    RB_CHECK_MAGIC
    RB_CHECK_QT4
  ], [  

    echo "Server will NOT be built"

    # cheking libMagic if we build the editor
    RB_CHECK_DEFINED([BUILD_EDITOR], [
      echo "Editor will be built, checking for libmagic, qt"
      RB_CHECK_MAGIC
      RB_CHECK_QT4
      AC_DEFINE(BUILD_LIB_DESIGN)
    ], [  
      echo "Editor will NOT be built"
    ])

  ])
])

dnl Defines the DEBUG option
dnl
dnl Provides the --enable-debug to enable local administration site
dnl and information logging
dnl
AC_DEFUN([RB_OPTION_DEBUG],
[
  AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug],
    [Build the package with local admin-site authentification and
       informative logging informations. Should be for developpers only.
       (default=no)]),
    [build_debug=$enableval], 
    [build_debug=no])

  AC_MSG_CHECKING([if we should define DEBUG])

  case $build_debug in
    yes)
      AC_MSG_RESULT(yes)
      AC_DEFINE([RAINBRU_RPG_DEBUG], [], [Activate local website 
                 administration and intensive informative logging 
                 informations])
      ;;
    *)
      AC_MSG_RESULT(no)
      ;;
  esac
#  AM_CONDITIONAL([RB_OPTION_ALL_FLAGS], [test x$all = xtrue])
#  AM_CONDITIONAL([BUILD_LIB_DESIGN], [test x$all = xtrue])
])

dnl Define the scrollpane test option
dnl
dnl Provides the --enable-scrollp-test option of the configure script
dnl
AC_DEFUN([RB_OPTION_SCROLLPANE_TEST],
[
  AC_ARG_ENABLE(scrollp-test, AC_HELP_STRING([--enable-scrollp-test],
    [Build a scrollpane test window in the main menu game state. It is only
    a developper option, used during scrollpane implementation.
       (default=no)]),
    [scrollp_test=$enableval], 
    [scrollp_test=no])

  AC_MSG_CHECKING([if we should build scrollpane test window])

  case $scrollp_test in
    yes)
      scrollpane_test=true
      AC_DEFINE([RB_SCROLLPANE_TEST], [], [Defines if the scrollpane 
      test window is built])
      AC_DEFINE(RB_SCROLLPANE_TEST)
      AC_MSG_RESULT(yes)
      ;;
    *)
      scrollpane_test=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_SCROLLPANE_TEST], [test x$scrollpane_test = xtrue])
])

dnl Define the MultiColumnList test option
dnl
dnl Provides the --enable-mcl-test option of the configure script
dnl
AC_DEFUN([RB_OPTION_MCL_TEST],
[
  AC_ARG_ENABLE(mcl-test, AC_HELP_STRING([--enable-mcl-test],
    [Build a MultiColumnList test window in the main menu game state. It is only
    a developper option, used during MultiColumnList implementation.
       (default=no)]),
    [mcl_test=$enableval], 
    [mcl_test=no])

  AC_MSG_CHECKING([if we should build MultiColumnList test window])

  case $mcl_test in
    yes)
      _mcl_test=true
      AC_DEFINE([RB_MULTICOLUMNLIST_TEST], [], [Defines if the  MultiColumnList
      test window is built])
      AC_DEFINE(RB_MULTICOLUMNLIST_TEST)
      AC_MSG_RESULT(yes)
      ;;
    *)
      _mcl_test=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_MULTICOLUMNLIST_TEST], [test x$_mcl_test = xtrue])
])

dnl Define an option used to disable the std headers deprecated warning
dnl due to Ogre
dnl
dnl Please see maincore/ogreimport.h for further informations
dnl
AC_DEFUN([RB_OPTION_OGRE_DEPREC_WARN],
[
  AC_ARG_ENABLE(Wno-stddep-ogre, AC_HELP_STRING([--enable-Wno-stddep-ogre],
    [Disables deprecated warnings of std headers due to Ogre includes.
       (default=no)]),
    [ogre_no_deprec=$enableval], 
    [ogre_no_deprec=no])

  AC_MSG_CHECKING([if we should disable std deprecated warnings due to Ogre])

  case $ogre_no_deprec in
    yes)
      _ogre_no_deprec=true
      AC_DEFINE([RB_DISABLE_OGRE_DEPREC_WARN], [], [Defines if we must disable
      the deprecated warnings due to Ogre inclusion of std headers])
      AC_DEFINE(RB_DISABLE_OGRE_DEPREC_WARN)
      AC_MSG_RESULT(yes)
      ;;
    *)
      _ogre_no_deprec=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_DISABLE_OGRE_DEPREC_WARN], [test x$_ogre_no_deprec = xtrue])
])

dnl Define the tools Option 
dnl
dnl Provides the --enable-editor option of the configure script
dnl By default, the editor is disabled
dnl
AC_DEFUN([RB_OPTION_EXAMPLES],
[
  AC_ARG_ENABLE(tools, AC_HELP_STRING([--enable-examples],
    [Build the RainbruRPG examples. It is recommended only for package
	maintainers and curious users
       (default=no)]),
    [build_examples=$enableval], 
    [build_examples=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-examples])

  case $build_examples in
    yes)
      examples=true
      AC_MSG_RESULT(yes)
      ;;
    *)
      examples=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_EXAMPLES_FLAGS], [test x$examples = xtrue])
])

dnl Define the terminalApi Option 
dnl
dnl Provides the --enable-terminal-api option of the configure script
dnl By default, the lib is disabled
dnl
AC_DEFUN([RB_OPTION_TAPI],
[
  AC_ARG_ENABLE(terminal-api, AC_HELP_STRING([--enable-terminal-api],
    [Build the TerminalApi library. It is a deprecated library, only
    build it if you are curious.
       (default=no)]),
    [build_tapi=$enableval], 
    [build_tapi=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-terminalApi])

  case $build_tapi in
    yes)
      RB_CHECK_LIBSLANG
      terminal_api=true
      AC_DEFINE([BUILD_TAPI], [], [Defines if the TerminalApi libary is built])
      AC_DEFINE(BUILD_TAPI)
      AC_MSG_RESULT(yes)
      ;;
    *)
      terminal_api=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_TAPI_FLAGS], [test x$terminal_api = xtrue])
])

dnl
dnl Handle the cross-compilation
dnl
dnl It set the rb_cross_compil_host variable to win32 if cross-compilation
dnl to win32 is detected. It also set the rb_cross_compil_prefix prefix
dnl
dnl param: $1 The prefix for cross-compilation used with CFLAGS and LDFLAGS
dnl        if cross-compilation is detected. Set it to '/usr/cross' by
dnl        example if headers are in /usr/cross/include and libs are in
dnl        /usr/cross/lib
dnl
dnl        $2 The suffix added to all library flags when cross-compiling
dnl        changing lname to lname.dll if suffix is '.dll' by example. 
dnl        You need to add the dot of the extension.
dnl
dnl Warning : using '.dll' as extension causes many undefined reference
dnl           when linking the executable. The undefined reference seems
dnl           to come from the stdc++ library (string and containers).
dnl
AC_DEFUN([RB_HANDLE_CROSS_COMPIL],
[
  echo -n "checking for cross-compilation..."

  if test $host_os ==  "mingw32msvc"
  then
    echo "win32. Prefix is $1"
    rb_cross_compil_host=win32
    rb_cross_compil_prefix=$1
    LDFLAGS="$LDFLAGS -lstdc++ -L/usr/cross/lib"
    DLL_EXT="$2"
  else  
    echo "no"
    rb_cross_compil_host=no
    DLL_EXT=""
  fi
  AC_SUBST(DLL_EXT)
  AC_SUBST(rb_cross_compil_host)
])

AC_DEFUN([RB_CONDITIONAL_LINKING_CPPUNIT],
[

  AC_MSG_CHECKING([if we should search for CppUnit])

  case $build_tests in
    yes)
      tests=true
      AC_MSG_RESULT(yes)
      RB_CHECK_CPPUNIT
      ;;
    *)
      tests=false
      AC_MSG_RESULT(no)
      ;;
  esac
])

AC_DEFUN([RB_CHECK_CPPUNIT],[
  PKG_CHECK_MODULES(CPPUNIT, [cppunit >= 1.12.0])
])
