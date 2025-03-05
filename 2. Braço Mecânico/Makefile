# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -g

# Bibliotecas necessárias
LIBS = -ldl -lglfw -lGL

# Nome do executável
TARGET = braco_mec

# Arquivo fonte
SRC = braco_mec.cpp

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)
