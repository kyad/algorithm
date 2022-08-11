.PHONY: all
all: debug

debug: debug.cc
	$(CXX) -o $@ $<

.PHONY: clean
clean:
	rm -rf debug

.PHONY: test
test: debug
	./debug | diff - test/debug.out
