# setup

export TOP_DIR = $(PWD)

# recipies


.PHONY:all
all: $(addprefix all-, $(TARGETs))

.PHONY: all-%
all-%:
	$(MAKE) -f git/makefiles/common_build.mk all TARGET=$*


.PHONY: clean
clean: $(addprefix clean-, $(TARGETs))

.PHONY: clean-%
clean-%:
	$(MAKE) -f git/makefiles/common_clean.mk clean TARGET=$*


.PHONY: clean_all
clean_all: $(addprefix clean_all-, $(TARGETs))

.PHONY: clean_all-%
clean_all-%:
	$(MAKE) -f git/makefiles/common_clean.mk clean_all TARGET=$*


lib%:
	$(MAKE) -f git/makefiles/common_build.mk $@ TARGET=$@


.PHONY: mostlyclean
mostlyclean: $(addprefix mostlyclean-, $(TARGETs))

.PHONY: mostlyclean-%
mostlyclean-%:
	$(MAKE) -f git/makefiles/common_clean.mk mostlyclean TARGET=$*


%.exe:
	$(MAKE) -f git/makefiles/build_exe.mk all TARGET=$@
