PROJECT=oriT1
LS_LIBS=file utils records
LS_EXES=create insert list
INSTALL_PATH?=/usr/local


CFLAGS=-Wno-discarded-qualifiers -g -I./include -L./build/lib -O3
LINK_LIBS=$(foreach f, $(LS_LIBS), -l${PROJECT}_${f})
CC=gcc
BUNDLE_AR=ar rcs


all: libs exes

build/%.o: src/%.c
	${CC} -o $@ -c $< ${CFLAGS}

build/lib/lib${PROJECT}_%.a: build/%.o
	${BUNDLE_AR} $@ $<

libs: $(foreach f, $(LS_LIBS), build/lib/lib${PROJECT}_${f}.a)

build/bin/${PROJECT}.%: src/%.c libs
	${CC} -o $@ $< ${LINK_LIBS} ${CFLAGS}

exes: $(foreach f, $(LS_EXES), build/bin/${PROJECT}.${f})

.PHONY: clean install

install:
	mkdir -p ${INSTALL_PATH}/{bin,include,lib}
	cp -r include/${PROJECT} ${INSTALL_PATH}/include/${PROJECT}
	$(foreach f, $(LS_LIBS), cp -r build/lib/lib${f}.a ${INSTALL_PATH}/lib/;)
	$(foreach f, $(LS_EXES), cp -r build/bin/${f} ${INSTALL_PATH}/bin/;)

clean:
	$(foreach f, $(LS_LIBS), rm build/lib/lib${PROJECT}_${f}.a;)
	$(foreach f, $(LS_EXES), rm build/bin/${f}.cgi;)