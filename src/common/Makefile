# Make a Minuetz variant

BUILD=../build/$(ROOT)
PROG=$(BUILD)/minuetz.tap
TEST=$(BUILD)/ay-test.tap
RTEST=$(BUILD)/ay-reg-test.tap

../$(RELEASES)/minuetz-$(ROOT).zip: $(PROG) $(TEST) $(RTEST) Makefile
	@mkdir -p ../$(RELEASES)
	@rm -f ../$(RELEASES)/minuetz-$(ROOT).zip
	@zip -j ../$(RELEASES)/minuetz-$(ROOT).zip $(PROG) $(TEST) $(RTEST) >/dev/null
	@mkdir -p ../$(RELEASES)/minuetz-$(ROOT)-files
	@cp $(PROG) ../$(RELEASES)/minuetz-$(ROOT)-files
	@cp $(TEST) ../$(RELEASES)/minuetz-$(ROOT)-files
	@cp $(RTEST) ../$(RELEASES)/minuetz-$(ROOT)-files

$(PROG): $(BUILD)/minuetz-basic.tap $(BUILD)/minuetz-assembly.bin Makefile
	@mkdir -p $(BUILD)
	@cp $(BUILD)/minuetz-basic.tap minuetz-ml.tap
	@cp $(BUILD)/minuetz-assembly.bin minuetz-ml
	@bin2tap -append -a 28930 -o minuetz-ml.tap minuetz-ml
	@cp minuetz-ml.tap $(BUILD)/minuetz.tap
	@rm minuetz-ml minuetz-ml.tap

#
# build the minuetz-basic .tap file
#
$(BUILD)/minuetz-basic.tap: $(BUILD)/minuetz-basic.txt Makefile
	@mkdir -p $(BUILD)
	@zmakebas -a 1 -n minuetz -o $(BUILD)/minuetz-basic.tap $(BUILD)/minuetz-basic.txt

#
# adjust the minuetz-basic .txt file
#
$(BUILD)/minuetz-basic.txt: minuetz-basic.txt Makefile
	@mkdir -p $(BUILD)
	@cat minuetz-basic.txt | \
	    sed -e 's/!!RA!!/$(RA)/g' | \
		sed -e 's/!!RV!!/$(RV)/g' | \
		sed -e 's/!!RR!!/$(RR)/g' > \
			$(BUILD)/minuetz-basic.txt

#
# build the test .tap file
#
$(TEST): $(BUILD)/ay-test-basic.txt Makefile
	@mkdir -p $(BUILD)
	@zmakebas -a 1 -n ay-test -o $(BUILD)/ay-test.tap $(BUILD)/ay-test-basic.txt

#
# adjust the test .txt file
#
$(BUILD)/ay-test-basic.txt: ay-test-basic.txt Makefile
	@mkdir -p $(BUILD)
	@cat ay-test-basic.txt | \
	    sed -e 's/!!RA!!/$(RA)/g' | \
		sed -e 's/!!RV!!/$(RV)/g' | \
		sed -e 's/!!RR!!/$(RR)/g' > \
		    $(BUILD)/ay-test-basic.txt

#
# build the reg-test .tap file
#
$(RTEST): $(BUILD)/ay-reg-test-basic.txt Makefile
	@mkdir -p $(BUILD)
	@zmakebas -a 1 -n ay-test -o $(BUILD)/ay-reg-test.tap $(BUILD)/ay-reg-test-basic.txt

#
# adjust the reg-test .txt file
#
$(BUILD)/ay-reg-test-basic.txt: ay-reg-test-basic.txt Makefile
	@mkdir -p $(BUILD)
	@cat ay-reg-test-basic.txt | \
	    sed -e 's/!!RA!!/$(RA)/g' | \
		sed -e 's/!!RV!!/$(RV)/g' | \
		sed -e 's/!!RR!!/$(RR)/g' > \
		    $(BUILD)/ay-reg-test-basic.txt

$(BUILD)/minuetz-assembly.bin: minuetz-assembly.src $(BUILD)/bartab.src Makefile
	@mkdir -p $(BUILD)
	@spasm -f raw -v errors,undef -Dregaddr=$(RA) -Dregout=$(RV) -I $(BUILD) \
	    -o $(BUILD)/minuetz-assembly.bin -L minuetz-assembly.src
	@echo "NOTETABLE (104 BYTES)" >$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 104 $(BUILD)/minuetz-assembly.bin 0x9b4 0x7ab6 >>$(BUILD)/check-$(ROOT).txt
	@echo "DICETABLES (176 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 176 $(BUILD)/minuetz-assembly.bin +0xa1c 0x7b1e >>$(BUILD)/check-$(ROOT).txt
	@echo "DRAWDICEDATA1 (252 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 252 $(BUILD)/minuetz-assembly.bin +0xacc 0x7bce >>$(BUILD)/check-$(ROOT).txt
	@echo "DRAWDICEDATA2 (12 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 12 $(BUILD)/minuetz-assembly.bin +0xbc8 0x7cca >>$(BUILD)/check-$(ROOT).txt
	@echo "DRAWDICEDATA3 (40 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 40 $(BUILD)/minuetz-assembly.bin +0xbd4 0x7cd6 >>$(BUILD)/check-$(ROOT).txt
	@echo "DICEMAIN (102 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 102 $(BUILD)/minuetz-assembly.bin +0xbfc 0x7cfe >>$(BUILD)/check-$(ROOT).txt
	@echo "DRAWDICE (29 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 29 $(BUILD)/minuetz-assembly.bin +0xc62 0x7d64 >>$(BUILD)/check-$(ROOT).txt
	@echo "PRTDOTS (30 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 30 $(BUILD)/minuetz-assembly.bin +0xc7f 0x7d81 >>$(BUILD)/check-$(ROOT).txt
	@echo "NATTABLE (51 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 51 $(BUILD)/minuetz-assembly.bin +0xcdf 0x7de1 >>$(BUILD)/check-$(ROOT).txt
	@echo "NOTESORT (74 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 74 $(BUILD)/minuetz-assembly.bin +0xd12 0x7e14 >>$(BUILD)/check-$(ROOT).txt
	@echo "PLAYMAIN (77 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 77 $(BUILD)/minuetz-assembly.bin +0xd5c 0x7e5e >>$(BUILD)/check-$(ROOT).txt
	@echo "PLAYSLOT (38 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 38 $(BUILD)/minuetz-assembly.bin +0xda9 0x7eab >>$(BUILD)/check-$(ROOT).txt
	@echo "OUT (22 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 22 $(BUILD)/minuetz-assembly.bin +0xdcf 0x7ed1 >>$(BUILD)/check-$(ROOT).txt
	@echo "MUSICBOX (25 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 25 $(BUILD)/minuetz-assembly.bin +0xde5 0x7ee7 >>$(BUILD)/check-$(ROOT).txt
	@echo "PART (23 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 23 $(BUILD)/minuetz-assembly.bin +0xdfe 0x7f00 >>$(BUILD)/check-$(ROOT).txt
	@echo "BEEPOUT (36 BYTES)" >>$(BUILD)/check-$(ROOT).txt
	@od --traditional -Ad -tu1 -v -w6 -N 36 $(BUILD)/minuetz-assembly.bin +0xe15 0x7f17 >>$(BUILD)/check-$(ROOT).txt



$(BUILD)/bartab: bartab.c Makefile
	@mkdir -p $(BUILD)
	@gcc -o $(BUILD)/bartab bartab.c

$(BUILD)/bartab.src: $(BUILD)/bartab Makefile
	@mkdir -p $(BUILD)
	@$(BUILD)/bartab >$(BUILD)/bartab.src
