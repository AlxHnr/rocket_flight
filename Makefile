P_NAME  = rocket_flight
OBJECTS = main.o particle.o render_gfx.o

# flags
CFLAGS  = -Wall -O2 `sdl-config --cflags` -I.
LDFLAGS = -lm `sdl-config --libs` -lSDL_gfx

# main application
$(P_NAME)/$(P_NAME): $(OBJECTS:%.o=obj/%.o)
	mkdir -p $(P_NAME)
	$(CC) $(LDFLAGS) $(OBJECTS:%.o=obj/%.o) -o $(P_NAME)/$(P_NAME)

# compile objects
obj/%.o: %.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $<
	mv *.o obj

# run application
run: $(P_NAME)/$(P_NAME)
	cd $(P_NAME) && ./$(P_NAME)

# additional stuff

clean:
	- rm -rf $(P_NAME)/$(P_NAME) obj
