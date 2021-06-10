cc = g++
params = -std=c++11 -lgtest -lgtest_main -lpthread
src = $(shell find . -name "*.cpp")
obj = $(src:%.cpp=%.o)
prom = $(src:%.cpp=%)

# test:testTesting.o 
# 	g++ -o test testTesting.o $(params)
$(prom):$(obj)
	$(cc) -o $@ $< $(params)

%.o:%.cpp
	$(cc) -c $< -o $@ $(params)

clean:
	rm -r $(prom) $(obj)