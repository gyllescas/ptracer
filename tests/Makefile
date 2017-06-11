.PHONY: all clean run coverage

TESTS := parse_args trace

RUNTESTS := $(TESTS:%=run-%)
CLEANTESTS := $(TESTS:%=clean-%)
COVTESTS := $(TESTS:%=cov-%)

.PHONY: $(TESTS)
.PHONY: $(RUNTESTS)
.PHONY: $(CLEANTESTS)
.PHONY: $(COVTESTS)

all: $(TESTS)

$(TESTS):
	$(MAKE) -C $@

$(RUNTESTS):
	$(MAKE) -C $(@:run-%=%) run

run: $(RUNTESTS)

$(COVTESTS):
	$(MAKE) -C $(@:cov-%=%) coverage

coverage: $(COVTESTS)

$(CLEANTESTS):
	$(MAKE) -C $(@:clean-%=%) clean

clean: $(CLEANTESTS)
