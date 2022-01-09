NAME:=mk1
VERSION:=1.0

# Dirs
#
# In
BIN_DIR:=bin
BINS:=$(wildcard bin/*.cc)
BIN_PHONIES:=$(notdir $(basename $(BINS)))
# Out
OUT_DIR:=obj/$(VERSION)
OUT_BIN:=$(OUT_DIR)/bin
OUT_LIB:=$(OUT_DIR)/lib
OUT_DIRS:=$(OUT_DIR) $(OUT_BIN) $(OUT_LIB)
BIN_EXECS:=$(addprefix $(OUT_BIN)/,$(BIN_PHONIES))

.PHONY: $(BIN_PHONIES) dirs clean

all: dirs $(BIN_EXECS)

$(OUT_DIRS):
dirs: $(OUT_DIRS)
	mkdir -p $^

$(OUT_BIN)/%: dirs $(BIN_DIR)/%.cc
	g++ -o $@ $(filter-out $<,$^)

$(BIN_PHONIES):
	@$(MAKE) $(OUT_BIN)/$@

clean:
	rm -rf obj
