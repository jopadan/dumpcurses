#ifndef _PRINT_HEX_H
#define _PRINT_HEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <ncurses.h>

uint8_t u64_get_u8(uint64_t addr, uint8_t i, int endian);
uint16_t u64_get_u16(uint64_t addr, uint8_t i, int endian);
uint32_t u64_get_u32(uint64_t addr, uint8_t i, int endian);

bool print_hex_addr(uint64_t addr, int mode, int tuple_len);
bool print_hex_data(uint8_t* buf, size_t len, int line_len, int tuple_len);

#endif
