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
    OGRE_CFLAGS="$OGRE_CFLAGS -I$rb_cross_compil_prefix/include/OGRE"
    dnl A hack for d3dx9.h header
    OGRE_CFLAGS="$OGRE_CFLAGS -I/usr/include/wine/windows/"

    LDFLAGS="$LDFLAGS -lOgreMain$DLL_EXT -lfreeimage$DLL_EXT"
    echo "Adding zzip flags for "mingw32msvc""
    LDFLAGS="$LDFLAGS -lzzip$DLL_EXT $FREETYPE_LIBS"
    echo "Adding libintl flags for "mingw32msvc""
    LDFLAGS="$LDFLAGS -lintl$DLL_EXT"
    AC_SUBST(OGRE_PLUGINDIR, [$rb_cross_compil_prefix/lib/OGRE])
  else
    PKG_CHECK_MODULES(OGRE, [OGRE >= 1.6.0 OGRE < 1.8.0])
    AC_SUBST(OGRE_PLUGINDIR, [$($PKG_CONFIG --variable=plugindir OGRE)])

    # Devil
    AC_CHECK_LIB(jpeg, main, [], [])
  fi
])
