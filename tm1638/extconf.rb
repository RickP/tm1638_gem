require 'mkmf'
have_library('bcm2835')
have_library('tm1638')
$CFLAGS += " -std=c99"
create_makefile('tm1638')
