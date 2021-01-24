RcAioPRU: RcAioPRU.p
	pasm -V3 -c RcAioPRU.p RcAioPRU_BBBMINI -DBBBMINI
	pasm -V3 -c RcAioPRU.p RcAioPRU_BBBLUE -DBBBLUE
	pasm -V3 -c RcAioPRU.p RcAioPRU_POCKET -DPOCKET
	pasm -V3 -c RcAioPRU.p RcAioPRU_BBAI -DBBAI

debug: RcAioPRU.p
	pasm -V3 -c RcAioPRU.p RcAioPRU_BBBMINI -DBBBMINI -DDEBUG
	pasm -V3 -c RcAioPRU.p RcAioPRU_BBBLUE -DBBBLUE -DDEBUG
	pasm -V3 -c RcAioPRU.p RcAioPRU_POCKET -DPOCKET -DDEBUG
	pasm -V3 -c RcAioPRU.p RCAioPRU_BBAI -DBBAI -DDEBUG

test: RcAioPRUTest.c
	gcc -g -o RcAioPRUTest RcAioPRUTest.c

clean:
	rm RcAioPRU_BBBMINI_bin.h RcAioPRU_BBBLUE_bin.h RcAioPRU_POCKET_bin.h RcAioPRUTest RcAioPRU_BBIA_bin.h
