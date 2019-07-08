TEMPLATE = subdirs
SUBDIRS += kleiner-brauhelfer-core \
           kleiner-brauhelfer

kleiner-brauhelfer-core.subdir = kleiner-brauhelfer-core
kleiner-brauhelfer.subdir = kleiner-brauhelfer
kleiner-brauhelfer.depends = kleiner-brauhelfer-core
TRANSLATIONS += kleiner-brauhelfer/languages/kb2_de.ts  kleiner-brauhelfer/languages/kb2_en.ts
