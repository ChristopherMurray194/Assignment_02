AC_INIT([assignmnet], [0.1])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror, foreign subdir-objects])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])

AC_PROG_LIBTOOL
AC_PROG_CXX
AC_LANG(C++)

AC_CHECK_HEADER([glm/glm.hpp], , AC_MSG_ERROR(GLM headers are required.))
AC_CHECK_HEADER([glm/ext.hpp], , AC_MSG_ERROR(GLM EXT header is required.))
AC_CHECK_HEADER([SOIL/SOIL.h], , AC_MSG_ERROR(SOIL header is required.))

# Check for the following libraries on the system
PKG_CHECK_MODULES([gl], [gl])
PKG_CHECK_MODULES([glew], [glew])
PKG_CHECK_MODULES([sdl2], [sdl2])

AC_CONFIG_FILES([
Makefile
shaders/Makefile
textures/Makefile
])

AC_OUTPUT
