CC = gcc
CFLAGS = -O2

SRC_DIR := src
INC_DIR := $(SRC_DIR)/include
OBJ_DIR := obj
OUT_DIR := out
UTIL_OBJ := linalg_util.o

linalg_util: $(INC_DIR)/linalg_util.h $(INC_DIR)/linalg_util.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(INC_DIR)/$@.c -o $(OBJ_DIR)/$(UTIL_OBJ)

hello: $(SRC_DIR)/hello.c
	$(CC) $(CFLAGS) $< -o $(OUT_DIR)/$@

hilbert_multiply: $(SRC_DIR)/hilbert_multiply.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ_DIR)/$(UTIL_OBJ) $(OBJ_DIR)/$@.o -o $(OUT_DIR)/$@

trapezoid_rule: $(SRC_DIR)/trapezoid_rule.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ_DIR)/$(UTIL_OBJ) $(OBJ_DIR)/$@.o -lm -o $(OUT_DIR)/$@

trapezoid_mc: $(SRC_DIR)/trapezoid_mc.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ_DIR)/$(UTIL_OBJ) $(OBJ_DIR)/$@.o -lm -o $(OUT_DIR)/$@

jacobi: $(SRC_DIR)/jacobi.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(OBJ_DIR)/$@.o
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ_DIR)/$(UTIL_OBJ) $(OBJ_DIR)/$@.o -lm -o $(OUT_DIR)/$@

all: linalg_util hello hilbert_multiply trapezoid_rule trapezoid_mc jacobi

.PHONY: clean
clean:
	rm -r $(OBJ_DIR)/*.o
	rm -r $(OUT_DIR)/*
