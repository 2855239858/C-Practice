cc = g++
prom = test
deps = $(shell find ./ -name "*.h")
src = h_cpp_test.cpp ./head/algorithm.cpp
obj = $(src:%.cpp=%.o)

$(prom):$(obj)
	$(cc) -o $(prom) $(obj)

%.o:%.cpp
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
