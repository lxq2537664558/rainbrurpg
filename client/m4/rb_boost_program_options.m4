AC_DEFUN([RB_CHECK_BOOST_PROGRAM_OPTIONS],[
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([boost/program_options.hpp], [],
    [AC_MSG_ERROR(You need the Boost.Program_options development library.)])
dnl Cannot test for library with AC_CHECK_LIB due to namespace
  AC_CHECK_LIB(boost_program_options, main, [], [
    AC_MSG_ERROR("Error! You need to have Boost.Program_options installed.")
  ])
])
