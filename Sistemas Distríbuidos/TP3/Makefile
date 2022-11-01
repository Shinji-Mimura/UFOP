COMPILER = javac -Xlint
BINARIES = $(EXEC_PROG)

SOURCES := $(shell find -name '*.java')

OBJECTS = $(SOURCES:.java=.class)

%.class: %.java
	$(COMPILER) -d . -classpath . $<

all: $(OBJECTS)
	@echo Build Completed

broker:
	java appl.Broker

client:
	java appl.OneAppl

.PHONY : clean
clean:
	find . -type f -name '*.class' -delete
