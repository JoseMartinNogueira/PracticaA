all: genTex genDicc dicc ent cd hsh bloom

genTex: genTex.cpp
	g++ -o genTex genTex.cpp 

genDicc: genDicc.cpp
	g++ -o genDicc genDicc.cpp

dicc: diccionario.txt
	./genDicc > diccionario.txt

ent: entrada.txt
	./genTex > entrada.txt

cd: cercaDicotomica.cpp
	g++ -o cercaDicotomica cercaDicotomica.cpp

hsh: hashAlgorithm.cpp
	g++ -o hashAlgorithm hashAlgorithm.cpp

bloom: bloomFilter.cpp	
	g++ -o bloomFilter bloomFilter.cpp

rm: -rf *.o all