CC = gcc
FLAGS = -lglfw -lGL -lX11 -lpthread -ldl -lGLEW 
TARGET = app
FILES = app.c shader.c

$(TARGET): $(FILES)
			$(CC) $(FILES) -o $(TARGET) $(FLAGS)


