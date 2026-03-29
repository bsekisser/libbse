include git/makefiles/common_setup.mk


.PHONY: clean
clean: clean-build-dir
	[ ! -e $(TARGET) ] || rm $(TARGET)

clean_all: clean-build-dir
	[ ! -e $(TARGET) ] || rm $(TARGET)

.PHONY: clean-build-subdir
clean-build-dir: clean-obj-dir
	[ ! -d $(BUILD_DIR) ] || rm -r $(BUILD_DIR)

.PHONY: clean-obj-dir
clean-obj-dir:
	[ ! -d $(OBJ_DIR_ROOT) ] || rm -r $(OBJ_DIR_ROOT)

.PHONY: mostlyclean
mostlyclean:
	-rm $(DEPS) $(OBJS)
