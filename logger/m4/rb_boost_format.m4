AC_DEFUN([RB_CHECK_BOOST_FORMAT],[
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([boost/format.hpp], [],
    [AC_MSG_ERROR(You need the Boost.Format development library.)])
  dnl Do not use AC_CHECK_LIB, it is a header lib only
])