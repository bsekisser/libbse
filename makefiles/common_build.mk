#$(info >> deps: $(DEPS))
#$(info >> deps_c: $(DEPS_C))
#$(info >> deps_cpp: $(DEPS_CPP))
#$(info >> dir: $(DIR))
#$(info $(LN) $(LNFLAGS))
#$(info >> obj_dir: $(OBJ_DIR))
#$(info >> objs: $(OBJS))
#$(info >> objs_c: $(OBJS_C))
#$(info >> objs_cpp: $(OBJS_CPP))
#$(info >> src_dir: $(SRC_DIR))
#$(info >> srcs_c: $(SRCS_C))
#$(info >> srcs_cpp: $(SRCS_CPP))
#$(info >> target_arch: $(TARGET_ARCH))
#$(info >> target_marc: $(TARGET_MACH))
#$(info >> vpath: $(VPATH))

$(OBJS_C): $(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJS_CPP): $(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	@[ -d $@ ] || mkdir -p $@

$(DUMP_MACHINE): $(BUILD_DIR)
	@[ -L build/$(DUMP_MACHINE) ] || $(LN) $(LNFLAGS) -t $< $(OBJ_DIR)

.PHONY: $(OBJ_DIR)
$(OBJ_DIR):
	@[ -d $@ ] || mkdir -p $@


-include $(DEPS)
-include $(DEPS_CPP)
