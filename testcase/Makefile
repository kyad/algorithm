.PHONY: all
all: a.out

a.out: a.cc
	g++ -I ${HOME}/ac-library $< -Wall

.PHONY: clean
clean:
	rm -f a.out

.PHONY: gen-test
gen-test:
	rm test/random-*
	oj g/i 'python gen.py'
	oj g/o -c ./ac.out
