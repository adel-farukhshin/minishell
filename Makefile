project					:= minishell

inc_dir					:= ./inc
src_dir					:= ./src
sources					:= $(wildcard ${src_dir}/*.c)
test_dir				:= ./test
support_dir				:= ./support
unit_test_dir			:= ${test_dir}/unit
unit_tests				:= $(wildcard ${unit_test_dir}/*.cpp)
integration_test_dir	:= ${test_dir}/integration
integration_tests		:= $(wildcard ${integration_test_dir}/*.bats)

build_dir				:= ./build
obj_dir					:= ${build_dir}/obj
bin_dir					:= ${build_dir}/bin
unit_test_build_dir		:= ${build_dir}/test/unit
integration_build_dir	:= ${build_dir}/test/integration
executable				:= ${bin_dir}/${project}
build_dirs				:= ${obj_dir} ${bin_dir} ${unit_test_build_dir} ${integration_build_dir}
objects					:= $(subst .c,.o,$(subst ${src_dir},${obj_dir},${sources}))
libft 					:= ./libft

dirs					:= ${inc_dir} ${src_dir} ${support_dir} ${test_dir} \
							${unit_test_dir} ${integration_test_dir} ${build_dirs}

all_unit_tests			:= ${unit_test_build_dir}/all_tests

CC						:= gcc 
CFLAGS					:= -I${inc_dir} -g -Wall -Wextra -Werror  -O0 

.PHONY: all  clean fclean re 
.PHONY: run test utest integration-test debug leak-check

all: ${executable}

setup:
	mkdir -p ${dirs}
	git clone https://github.com/google/googletest.git ${support_dir}/gtest

run: ${executable}
	@${^}

${executable}: ${objects} | ${bin_dir}
	make -C ${libft}
	${CC} ${CFLAGS} -o ${@} ${^} -L./libft -lft -lreadline

${obj_dir}/%.o: ${src_dir}/%.c | ${obj_dir}
	${CC} ${CFLAGS} -c -o ${@} ${<}

${build_dirs}:
	mkdir -p ${@}

clean:
	make clean -C ./libft
	rm -f ${objects}

fclean: clean
	make clean -C ./libft
	rm -f ${executable}
	rm -rf ${unit_test_build_dir}

re: fclean all

unit-test: | ${unit_test_build_dir}
	bash support/test/unit/make.sh
	# cmake -S support/test/unit/ -B ${unit_test_build_dir}

# Build tests
# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(gtest_dir)/include -isystem $(gmock_dir)/include
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

test_objects	:= $(subst .cpp,_test.o,$(subst ${unit_test_dir},${unit_test_build_dir},${unit_tests}))
test_names		:= ${patsubst %.cpp,%,$(subst ${unit_test_dir},${src_dir},${unit_tests})}
test_c_objects	:= ${foreach name,${test_names},${wildcard ${name}*.c}}
test_objects	+= ${subst .c,.o,${subst ${src_dir},${obj_dir},${test_c_objects}}}

utest: utest-build
	${all_unit_tests}

utest-build: ${test_objects} ${unit_test_build_dir}/gmock_main.a
	${CXX} -o ${all_unit_tests} ${^}

${unit_test_build_dir}/%_test.o: ${unit_test_dir}/%.cpp | ${unit_test_build_dir}
	${CXX} -c -I${inc_dir} $(CPPFLAGS) $(CXXFLAGS) -o ${@} ${<}

utest-clean:
	rm -f ${unit_test_build_dir}/*

# Builds gmock.a and gmock_main.a.

gtest_dir = ./support/gtest/googletest
gmock_dir = ./support/gtest/googlemock

GTEST_HEADERS = $(gtest_dir)/include/gtest/*.h \
                $(gtest_dir)/include/gtest/internal/*.h
GMOCK_HEADERS = $(gmock_dir)/include/gmock/*.h \
                $(gmock_dir)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)
GTEST_SRCS_ = $(gtest_dir)/src/*.cc $(gtest_dir)/src/*.h $(GTEST_HEADERS)
GMOCK_SRCS_ = $(gmock_dir)/src/*.cc $(GMOCK_HEADERS)

gmock.a				:= ${unit_test_build_dir}/gmock.a
gmock_main.a		:= ${unit_test_build_dir}/gmock_main.a

gmock_dep			:= ${addprefix ${unit_test_build_dir}/,gmock-all.o gtest-all.o}
gmock_main_dep		:= ${addprefix ${unit_test_build_dir}/,gmock-all.o gtest-all.o gmock_main.o}

${gmock.a}: ${gmock_dep}
	$(AR) $(ARFLAGS) $@ $^

${gmock_main.a}: ${gmock_main_dep}
	$(AR) $(ARFLAGS) $@ $^

${unit_test_build_dir}/gmock-all.o: $(GMOCK_SRCS_)
	$(CXX) -c $(CPPFLAGS) -I$(gtest_dir) -I$(gmock_dir) $(CXXFLAGS) \
            $(gmock_dir)/src/gmock-all.cc -o ${@}

${unit_test_build_dir}/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) -c $(CPPFLAGS) -I$(gtest_dir) -I$(gmock_dir) $(CXXFLAGS) \
            $(gtest_dir)/src/gtest-all.cc -o ${@}

${unit_test_build_dir}/gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) -c $(CPPFLAGS) -I$(gtest_dir) -I$(gmock_dir) $(CXXFLAGS) \
            $(gmock_dir)/src/gmock_main.cc -o ${@}
