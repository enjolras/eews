TEMPLATE = subdirs 
CONFIG += warn_on \
          qt \
          thread \
 debug_and_release \
 ordered
SUBDIRS += libs \
  src \
  plugins

