UNAME_S := $(shell uname -s)

CC = gcc
FLAGS = -Werror -Wextra -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(UNAME_S),Darwin)
	TST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck 
	TST_FLAG := -I/opt/homebrew/opt/check/include 
else
	TST_LIBS = $(shell pkg-config --libs check) 
	TST_FLAG = 
endif

DIR_FUNC_C = .
DIR_TEST_C = ./tests

DIR_FUNC_OBJ = obj_func
DIR_FUNC_GCOV_OBJ = obj_func_gcov
DIR_TEST_OBJ = obj_test

FILES_FUNC_C := $(wildcard $(DIR_FUNC_C)/s21_*.c)
FILES_FUNC_H := $(wildcard $(DIR_FUNC_C)/s21_*.h)
FILES_TEST_C := $(wildcard $(DIR_TEST_C)/*.c)
FILES_TEST_H := $(wildcard $(DIR_TEST_C)/*.h)

FILES_FUNC_OBJ := $(patsubst $(DIR_FUNC_C)/%.c, $(DIR_FUNC_OBJ)/%.o, $(FILES_FUNC_C))
FILES_FUNC_GCOV_OBJ := $(patsubst $(DIR_FUNC_C)/%.c, $(DIR_FUNC_GCOV_OBJ)/%.o, $(FILES_FUNC_C))
FILES_TEST_OBJ := $(patsubst $(DIR_TEST_C)/%.c, $(DIR_TEST_OBJ)/%.o, $(FILES_TEST_C))

DOCKER_IMAGE = my_project_valgrind

all: makedirs s21_matrix.a gcov_report

s21_matrix.a: makedirs $(FILES_FUNC_OBJ)
	ar rcs $@ $(FILES_FUNC_OBJ)

runTest : test
	./s21_test

test : makedirs $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ)
	$(CC)  $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ) -o s21_test $(TST_LIBS)

$(DIR_FUNC_OBJ)/%.o: $(DIR_FUNC_C)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_TEST_OBJ)/%.o: $(DIR_TEST_C)/%.c
	$(CC) $(FLAGS) -c $< -o $@  $(TST_FLAG)

gcov_report: makedirs $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ)
	$(CC) $(GCOV_FLAGS) $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ) -o s21_gcov_test $(TST_LIBS)
	./s21_gcov_test
	lcov -t "test_res" -o test_res.info -c -d .
	genhtml -o report test_res.info
	rm $(DIR_FUNC_GCOV_OBJ)/*gcda $(DIR_FUNC_GCOV_OBJ)/*gcno
	open report/index.html

$(DIR_FUNC_GCOV_OBJ)/%.o: $(DIR_FUNC_C)/%.c
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

makedirs:
	mkdir -p obj_func_gcov obj_func obj_test report

clang:
	clang-format -n *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src

clean:
	-rm s21_test s21_gcov_test *.a
	-rm *.exe
	-rm -r obj_func obj_func_gcov obj_test report
	-rm test-* $(DIR_FUNC_GCOV_OBJ)/*.o
	-rm valgrind_log.txt

valgrind:
	docker build -t $(DOCKER_IMAGE) .
	docker run --rm -it -v $(PROJECT_DIR):$(CONTAINER_PROJECT_DIR) $(DOCKER_IMAGE) /bin/sh -c "make -C /project test"
	docker run --rm -it my_project_valgrind valgrind ./s21_test > valgrind_log.txt
