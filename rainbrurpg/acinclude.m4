#serial 3

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
  AC_DEFINE([USER_INSTALL_PREFIX], [], 
[
The directory installation prefix.

This value is needed to locate the datafiles.
])

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
  AC_DEFINE_UNQUOTED(USER_INSTALL_PREFIX, "$GET_INSTALL_PREFIX")
])

dnl Tests the OgreMain lib and headers
dnl
dnl This function is used to test the header Ogre.h and
dnl the OgreMain library. 
dnl It is used by configure.in
AC_DEFUN([RB_CHECK_OGREMAIN],
[
  PKG_CHECK_MODULES(OGRE, [OGRE >= 1.4.0])
  AC_SUBST(OGRE_PLUGINDIR, [$($PKG_CONFIG --variable=plugindir OGRE)])

  PKG_CHECK_MODULES(CEGUI, [CEGUI >= 0.5.0])
#  AC_SUBST(CEGUI_OGRE_CFLAGS, [$($PKG_CONFIG --cflags CEGUI-OGRE)])
#  AC_SUBST(CEGUI_OGRE_LIBS, [$($PKG_CONFIG --libs CEGUI-OGRE)])

  # Devil
  AC_CHECK_LIB(jpeg, main, [], [])

])

dnl Checks for libOIS and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBOIS],
[
  PKG_CHECK_MODULES(OIS, [OIS >= 0.1])	
])

dnl Checks for the FOX-toolkit and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBFOX],
[
  AC_CHECK_LIB(FOX-1.6, main, [], [
    echo "Error! You need to have FOX-Toolkit 1.6 installed."
    exit -1
  ])
  AC_CHECK_HEADER([fox-1.6/fxver.h], [], [
    echo "Error! Cannot find the FOX-Toolkit 1.6 headers."
    exit -1
  ])
])

dnl Checks for the Curl lib and one of its header
dnl
dnl
AC_DEFUN([RB_CHECK_LIBCURL],
[
dnl  AC_CHECK_LIB(curl, main, [], [
dnl    echo "Error! You need to have libcurl installed."
dnl    exit -1
dnl  ])
dnl  AC_CHECK_HEADER([curl/curl.h], [], [
dnl    echo "Error! Cannot find the libcurl headers."
dnl    exit -1
dnl  ])
  PKG_CHECK_MODULES(libcurl, [libcurl >= 7.17])	


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
  AC_CHECK_LIB(boost_filesystem, main, [], [
    echo "Error! You need to have Boost-filesystem installed."
    exit -1
  ])
  AC_CHECK_HEADER([boost/filesystem/path.hpp], [], [
    echo "Error! Cannot find the Boost-filesystem headers."
    exit -1
  ])

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

dnl Define the all Option 
dnl
dnl Provides the --enable-all to enable all the 'enable like'
dnl ./configure script options
dnl
AC_DEFUN([RB_OPTION_ALL],
[
  AC_ARG_ENABLE(all, AC_HELP_STRING([--enable-all],
    [Build the whole package. It is a convenience option that build
	the client, the server, the editor and the tools.
       (default=no)]),
    [build_all=$enableval], 
    [build_all=no])

  AC_MSG_CHECKING([if we should build RainbruRPG-all])

  case $build_all in
    yes)
      all=true
      AC_MSG_RESULT(yes)
      AC_DEFINE(BUILD_SERVER)
      AC_DEFINE(BUILD_EDITOR)
      ;;
    *)
      all=false
      AC_MSG_RESULT(no)
      ;;
  esac
  AM_CONDITIONAL([RB_OPTION_ALL_FLAGS], [test x$all = xtrue])
  AM_CONDITIONAL([BUILD_LIB_DESIGN], [test x$all = xtrue])
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

  AC_CHECK_LIB(enet, main, [], [
    echo "Error! You need to have libenet-dev installed."
    exit -1
  ])

  AC_CHECK_HEADER([enet/enet.h], [], [
    echo "Error! Cannot find libenet headers."
    exit -1
  ])

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
  AC_CHECK_LIB(glib-2.0, main, [], [
    echo "Error! You need to have glib-2.0 installed."
    exit -1
  ])
dnl  AC_CHECK_HEADER([glib-2.0/glib.h], [], [
dnl     echo "Error! Cannot find the glib-2.0 headers."
dnl     exit -1
dnl   ])
])

dnl Tests the libsig++ library and headers
dnl
AC_DEFUN([RB_CHECK_LIBSIG],
[
  AC_CHECK_LIB(sigc-2.0, main, [], [
    echo "Error! You need to have sigc++-2.0 installed."
    exit -1
  ])
])

dnl Tests the libgd library and headers
dnl
AC_DEFUN([RB_CHECK_LIBGD],
[
  AC_CHECK_LIB(gd, main, [], [
    echo "Error! You need to have libgd installed."
    exit -1
  ])
  AC_CHECK_HEADER([gd.h], [], [
     echo "Error! Cannot find the libgd headers."
     exit -1
   ])
])

dnl Tests the libgd library and headers
dnl
AC_DEFUN([RB_CHECK_LIBGNET],
[
  AC_CHECK_LIB(gnet-2.0, main, [], [
    echo "Error! You need to have GNet installed."
    exit -1
  ])
dnl  AC_CHECK_HEADER([gnet-2.0/tcp.h], [], [
dnl     echo "Error! Cannot find the GNet headers."
dnl     exit -1
dnl   ])
])


dnl Test the usability of the boost::thread library
dnl
AC_DEFUN([RB_CHECK_BOOST_THREAD],
[
  AC_CHECK_LIB(boost_thread, main, [], [
    echo "Error! You need to have boost::thread installed."
    exit -1
  ])
  AC_CHECK_HEADER([boost/thread.hpp], [], [
     echo "Error! Cannot find the boost::thread headers."
     exit -1
   ])
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

dnl RB_CONDITIONNAL_LINKING
AC_DEFUN([RB_CONDITIONNAL_LINKING_LIB_MAGIC],
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
