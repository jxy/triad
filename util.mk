CONFIGS := $(patsubst $(rootdir)/Makefile.%,%,$(wildcard $(rootdir)/Makefile.*))
TARGET ?= $(shell hostname)
$(info Available configurations: $(CONFIGS))
$(info Set target: $(TARGET))
$(foreach T,$(CONFIGS),$(if $(findstring $(T),$(TARGET)),$(eval include $(rootdir)/Makefile.$(T))))
$(if $(CONFIG),$(info Target ID: $(CONFIG)),$(error No CONFIG found; please set a proper TARGET))

RUN := _runner_(){ echo "$$@"; $(SETUP); "$$@"; }; _runner_
