bin_PROGRAMS = editordemundos

editordemundos_SOURCES = editordemundos.cc	main_window_glade.cc 	main_window.cc \
				editor.cpp nuevo_nivel.cpp tabla.cpp cuadro.cpp cordenada.cpp insertar_imag.cpp \
	icono.cpp

noinst_HEADERS = main_window_glade.hh 	main_window.hh editor.h \
				definiciones_editor.h nuevo_nivel.h tabla.h cuadro.h cordenada.h insertar_imag.h icono.h

AM_CXXFLAGS = @CXXFLAGS@ @GTKMM_CFLAGS@ 

editordemundos_LDADD = @LIBS@ @GTKMM_LIBS@ 
