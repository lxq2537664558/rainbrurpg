AC_DEFUN([RB_CHECK_BOOST_SPIRIT],[
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([boost/spirit.hpp], [],
    [AC_MSG_ERROR(You need the Boost.Spirit development library.)])
  dnl Do not use AC_CHECK_LIB, it is a header lib only
])
