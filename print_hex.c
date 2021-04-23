#include "print_hex.h"

uint8_t u64_get_u8(uint64_t addr, uint8_t i, int endian)
{
	return (addr >> (i * 8));
}

uint16_t u64_get_u16(uint64_t addr, uint8_t i, int endian)
{
	return (addr >> (i * 16));
}

uint32_t u64_get_u32(uint64_t addr, uint8_t i, int endian)
{
	return (addr >> (i * 32));
}

bool print_hex_addr(uint64_t addr, int addr_len, int tuple_len)
{
	bool mask32 = (addr_len == 32) && (sizeof(uintptr_t) <= 4);

	switch(tuple_len) {
		case 2 << 0:

			printw("| %02X %02X | %02X %02X |",
			mask32 ? 0 : u64_get_u8(addr, 7, 0),
			mask32 ? 0 : u64_get_u8(addr, 6, 0),
			mask32 ? 0 : u64_get_u8(addr, 5, 0),
			mask32 ? 0 : u64_get_u8(addr, 4, 0));
			
			printw(" %02X %02X | %02X %02X |",
			u64_get_u8(addr, 3, 0),
			u64_get_u8(addr, 2, 0),
			u64_get_u8(addr, 1, 0),
			u64_get_u8(addr, 0, 0));
			break;
		case 2 << 1:
			printw("| %04X %04X |",
			mask32 ? 0 : u64_get_u16(addr, 3, 0),
			mask32 ? 0 : u64_get_u16(addr, 2, 0));

			printw(" %04X %04X |",
			u64_get_u16(addr, 1, 0),
			u64_get_u16(addr, 0, 0));
			break;
		case 2 << 2:
			printw("| %08tX |",
			mask32 ? 0 : u64_get_u32(addr, 1, 0));

			printw(" %08tX |",
			(uintptr_t)u64_get_u32(addr, 0, 0));
			break;
		default:
			printw("| %08tX",
			mask32 ? 0 : u64_get_u32(addr, 1, 0));

        		attrset(COLOR_PAIR(addr % 8));
			printw("%08tX |",
			(uintptr_t)u64_get_u32(addr, 0, 0));
			break;
	}

	return true;
}

bool print_hex_data(uint8_t* buf, size_t len, int line_len, int tuple_len)
{
	int addr_len = tuple_len ? tuple_len / 2: ( UINT64_MAX - (uint64_t)buf + (uint64_t)len) > UINT32_MAX ? 8 : 4;
	bool separator = true;
	/* for every line */
	for(uint64_t i = 0; i < len; i+=line_len)
	{
		/* print the address offset i */
        	attrset(A_BOLD | COLOR_PAIR(5));
		printw("\t\t|");
		if(addr_len == 8)
		{
			printw(" %08X ", i >> 32);
			if(separator)
				printw("|");
			printw(" %08X", i);
		}
		else
			printw(" %08X", i);

		printw(" | \t");

		/* print the hexadeximal interpret of buf */
		for(int j = 0; j < line_len; j++)
		{
			if (j == 8)
				printw(" ");

        		attrset(A_BOLD | COLOR_PAIR(buf[i + j] % 8));
			printw("%02X ", buf[i + j]);
		}

		printw("\t|");

		/* print the ascii interpret of buf */
		for(int j = 0; j < line_len; j++)
		{
			uint8_t c = buf[i+j];
        		attrset(A_BOLD | COLOR_PAIR(c % 8));
			if (c < ' ' || c > '~')
				c = '.';
			printw("%c", c);
		}

		printw("|\n");

		refresh();
	}

	return true;
}
