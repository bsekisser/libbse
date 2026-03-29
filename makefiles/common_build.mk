include git/makefiles/common_setup.mk


all: $(TARGET)


%.exe: %.c
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.exe: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.exe: $(OBJ_TARGET_EXE)
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@


lib%.a: $(OBJ_DIR)/lib%.a
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@


lib%.so: CFLAGS += -fPIC
lib%.so: LDFLAGS += -shared

lib%.so: $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

lib%.so: $(OBJ_TARGET_LIB_SO)
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@


$(BUILD_DIR):
	mkdir -p $@

$(BUILD_SUBDIR): $(BUILD_DIR)
	$(LN) $(LNFLAGS) $(OBJ_DIR) $@


$(OBJ_DIR): $(BUILD_SUBDIR)
	mkdir -p $@


$(OBJS_C): $(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJS_CPP): $(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<


$(OBJ_TARGET_EXE): $(OBJS) | $(OBJ_DIR)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(OBJ_TARGET_LIB_A): $(OBJ_TARGET_LIB_A)($(OBJS)) | $(OBJ_DIR)

$(OBJ_TARGET_LIB_SO): $(OBJS) | $(OBJ_DIR)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@


$(TARGET_EXE): $(OBJ_TARGET_EXE) | $(OBJ_DIR)
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@

$(TARGET_LIB_A): $(OBJ_TARGET_LIB_A) | $(OBJ_DIR)
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@

$(TARGET_LIB_SO): $(OBJ_TARGET_LIB_SO) | $(OBJ_DIR)
	[ -L $@ ] || $(LN) $(LNFLAGS) $< $@


-include $(DEPS)
-include $(OBJ_DIR)/*.d
