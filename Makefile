.PHONY: all ptracer tests check clean TAGS

all: ptracer

ptracer:
	$(MAKE) -C src

tests check:
	$(MAKE) -C tests run

coverage:
	$(MAKE) -C tests coverage

TAGS:
	ctags -eR

clean:
	$(MAKE) -C tests clean
	$(MAKE) -C src clean
	find -name "*~" -delete
	$(RM) TAGS
