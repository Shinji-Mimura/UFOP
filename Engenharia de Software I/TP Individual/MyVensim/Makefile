ifeq ($(OS),Windows_NT) 
CLEAN = del bin\*.dll bin\*.exe bin\*.out bin\*.o
else
CLEAN = rm -rf bin/*.dll bin/*.exe bin/*.out bin/*.o bin/unit_tests.dll
endif

api:
	g++ -shared ./src/lib/systemImpl.cpp ./src/lib/flowImpl.cpp ./src/lib/modelImpl.cpp -o bin/api.dll -Lbin -fPIC -Wl,-rpath,bin

all_funcional:
	g++ ./test/funcional/main.cpp ./test/funcional/FuncionalTests.cpp -Lbin -lapi -o ./bin/functional_tests -Wl,-rpath,bin

all_unit: 
	g++ ./test/unit/*.cpp  -Lbin -lapi -o bin/unit_tests -Wl,-rpath,bin


run_funcional:
	./bin/functional_tests.exe

run_unit:
	./bin/unit_tests.exe

clean:
	$(CLEAN)
	@echo "clean completed"

