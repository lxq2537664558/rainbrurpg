AC_DEFUN([RB_CHECK_BOOST_GRAPH],[
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([boost/graph/adjacency_list.hpp], [],
    [AC_MSG_ERROR(You need the Boost.Graph development library.)])
  dnl Do not use AC_CHECK_LIB, it is a header lib only
])
