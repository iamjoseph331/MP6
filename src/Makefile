TARGET=csiechat_server csiechat_client
INCLUDE=-I../include
BIN=../bin
FLAG=-g
GCC=g++
#for c++
#GCC=g++
CSIECHAT_SERVER_OBJS=csiechat_server_main.o
CSIECHAT_CLIENT_OBJS=csiechat_client_main.o csiechat_client.o
LIB=-lm -lbsd
.PHONY: clean
all: $(TARGET)
  
%.o: %.cpp
	@echo "making: " $@
	@$(GCC) $< -c $(FLAG) $(INCLUDE)
%.o: %.c
	@echo "making: " $@
	@$(GCC) $< -c $(FLAG) $(INCLUDE)
 
clean:
	rm -rf *.o
	@for bin in $(TARGET); do \
		echo "rm -rf $(BIN)/$$bin"; \
		rm -rf $(BIN)/$$bin; \
	done
csiechat_server: $(CSIECHAT_SERVER_OBJS)
	@echo "making: " $@
	@$(GCC) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(CSIECHAT_SERVER_OBJS) $(LIB)
csiechat_client: $(CSIECHAT_CLIENT_OBJS)
	@echo "making: " $@
	@$(GCC) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(CSIECHAT_CLIENT_OBJS) $(LIB)
