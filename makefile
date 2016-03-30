FILES :=            \
    Collatz.cpp     \
    Collatz.h       \
    Collatz.log     \
    html            \
    RunCollatz.cpp  \
    RunCollatz.in   \
    RunCollatz.out  \
    TestCollatz.cpp \
    TestCollatz.out

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall -DTEST
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

RunCollatz: Collatz.h Collatz.cpp RunCollatz.cpp
	$(CXX) $(CXXFLAGS) $(GPROFFLAGS) Collatz.cpp RunCollatz.cpp -o RunCollatz

html: Doxyfile Collatz.h Collatz.cpp RunCollatz.cpp TestCollatz.cpp
	doxygen Doxyfile

Collatz.log:
	git log > Collatz.log

Doxyfile:
	doxygen -g

RunCollatz.tmp: RunCollatz
	./RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.tmp RunCollatz.out
	$(GPROF) ./RunCollatz

TestCollatz: Collatz.h Collatz.cpp TestCollatz.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Collatz.cpp TestCollatz.cpp -o TestCollatz $(LDFLAGS)

TestCollatz.tmp: TestCollatz
	$(VALGRIND) ./TestCollatz                                       >  TestCollatz.tmp 2>&1
	$(GCOV) -b Collatz.cpp     | grep -A 5 "File 'Collatz.cpp'"     >> TestCollatz.tmp
	$(GCOV) -b TestCollatz.cpp | grep -A 5 "File 'TestCollatz.cpp'" >> TestCollatz.tmp
	cat TestCollatz.tmp

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCollatz
	rm -f RunCollatz.tmp
	rm -f TestCollatz
	rm -f TestCollatz.tmp

config:
	git config -l

log: Collatz.log

scrub:
	make clean
	rm -f  Collatz.log
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCollatz.tmp TestCollatz.tmp
