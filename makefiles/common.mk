#$(info obj_dir: $(OBJ_DIR))


.PHONY: clean
clean:
	-rm -rf $(OBJ_DIR)

.PHONY: clean_all
clean_all: clean clean_libs clean_logs
	-rm -rf $(BUILD_DIR)

.PHONY: clean_exe
clean_exe:
	-rm $(TARGET_EXE)

.PHONY: clean_liba
clean_liba:
	-rm $(TARGET_LIB_A)

.PHONY: clean_libs
clean_libs:
	-rm *.a *.so

.PHONY: clean_libso
clean_libso:
	-rm $(TARGET_LIB_SO)

.PHONY: clean_logs
clean_logs:
	-rm *.debug *.log *.trace
