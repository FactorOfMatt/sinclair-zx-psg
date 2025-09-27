# Makefile for Minuetz program

export RELEASES=releases

variants = yc he zon wss

allrel=$(addsuffix .zip,$(addprefix $(RELEASES)/minuetz-,$(variants)))

all: $(allrel) Makefile

# Your Computer "Mozart"
$(RELEASES)/minuetz-yc.zip: Makefile common/Makefile
	@RA=221 RV=223 RR=221 ROOT=yc $(MAKE) -C common

# Hobby Electronics "ZX Sound"
$(RELEASES)/minuetz-he.zip: Makefile common/Makefile
	@RA=159 RV=223 RR=191 ROOT=he $(MAKE) -C common

# Bi-Pak ZON-X (X-81?)
$(RELEASES)/minuetz-zon.zip: Makefile common/Makefile
	@RA=223 RV=31 RR=31 ROOT=zon $(MAKE) -C common

# William Stuart - RR (the read port) is a guess
$(RELEASES)/minuetz-wss.zip: Makefile common/Makefile
	@RA=221 RV=223 RR=221 ROOT=wss $(MAKE) -C common

artifacts: $(allrel) Makefile
	@mkdir -p artifacts
	@rm -f artifacts/all-artifacts.zip
	@rm -f build/*/bartab 
	@zip -r artifacts/all-artifacts.zip build/* >/dev/null
	@cp releases/*.zip artifacts

clean:
	@rm -fr build releases/minuetz-*-files

very-clean:
	@rm -fr build releases

extremely-clean:
	@rm -fr build releases artifacts

