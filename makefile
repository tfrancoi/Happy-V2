


export CC=g++
export CFLAGS=-W -Wall -g
export LDFLAGS=
SRC_DIR=src
export EXEC=main

all: $(EXEC)
 
$(EXEC):
	@(cd $(SRC_DIR) && $(MAKE))

.PHONY: clean mrproper $(EXEC)

clean:
	@(cd $(SRC_DIR) && $(MAKE) $@)

mrproper: clean
	@(cd $(SRC_DIR) && $(MAKE) $@)
			
