AC_DEFUN([RB_CHECK_RBUIC],[
  AC_ARG_VAR([TOOL_RBUIC], [Define the path to the ruby UI compiler])
  AC_PATH_PROG(TOOL_RBUIC, rbuic4, [no])
  case $TOOL_RBUIC in
    no)
      dnl Nothing
      rbuic4_was_found=false
      ;;    
    *)   
      AC_DEFINE([HAVE_RBUIC], [], [Defines if the ruby UI compiler was found])
      AC_DEFINE(HAVE_RBUIC)
      rbuic4_was_found=true
      ;;
  esac  
  AM_CONDITIONAL(RBUIC_FOUND, test x$rbuic4_was_found = xtrue)
])
