ACLOCAL_AMFLAGS= -I m4 --install
SUBDIRS= shaders textures

EXTRA_DIST = SphereAsset.h Camera.h GameWorld.h GameManager.h GameAsset.h LoadShader.h Light.h

bin_PROGRAMS = assignment 
assignment_SOURCES = main.cpp SphereAsset.cpp Camera.cpp GameWorld.cpp GameManager.cpp LoadShader.cpp Light.cpp

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++0x
AM_CPPFLAGS += $(gl_CPPFLAGS) $(glew_CPPFLAGS) $(sdl2_CPPFLAGS) $(BOOST_CPPFLAGS)
LIBS+= $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_LIBS)
# No .pc file so library path needs to be hardcoded
assignment_LDFLAGS= -lSOIL
