noinst_PROGRAMS = olefuzzer

AM_CXXFLAGS = \
	-I$(top_srcdir)/inc \
	-I$(top_srcdir)/src/lib \
	$(DEBUG_CXXFLAGS)

noinst_LTLIBRARIES = libcommonfuzzer.la

libcommonfuzzer_la_SOURCES = \
	commonfuzzer.cpp \
	commonfuzzer.h

olefuzzer_LDADD = \
	$(top_builddir)/src/lib/librevenge-stream-@RVNG_MAJOR_VERSION@.@RVNG_MINOR_VERSION@.la \
	libcommonfuzzer.la \
	-lFuzzingEngine

olefuzzer_SOURCES = \
	olefuzzer.cpp
