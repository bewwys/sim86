#include <stdio.h>

#define mask_field_mov_instruction 0x88
#define mask_field_mov_d_reg_dest 0b00000010

#define mask_field_mov_ds 0b00000000
#define mask_field_mov_dd 0b00000010
enum d_type {
    source_reg,
    dest_reg
};
enum d_type d_field_val;

// Single bit w field instruction operation byte/word
#define mask_field_mov_bd 0b00000000
#define mask_field_mov_wd 0b00000001
enum w_type {
    byte,
    wide
};
enum w_type w_field_val;

// Mod field 2 bits
#define mask_field_mov_mod_memory_mode_no_displacement    0b00000000
#define mask_field_mov_mod_memory_mode_8bit_displacement  0b01000000
#define mask_field_mov_mod_memory_mode_16bit_displacement 0b10000000
#define mask_field_mov_mod_register_mode                  0b11000000

enum mod_type {
    memory_mode_no_displacement,
    memory_mode_8bit_displacement,
    memory_mode_16bit_displacement,
    register_mode_no_displacement
};

enum mod_type mod;

// Reg field 3 bits
// To know if we have to deal with a wide register or byte,
// we need to lookup the w field.
#define mask_field_mov_reg_alx  0b00000000
#define mask_field_mov_reg_clx  0b00001000
#define mask_field_mov_reg_dlx  0b00010000
#define mask_field_mov_reg_blx  0b00011000
#define mask_field_mov_reg_ahsp 0b00100000
#define mask_field_mov_reg_chbp 0b00101000
#define mask_field_mov_reg_dhsi 0b00110000
#define mask_field_mov_reg_bhdi 0b00111000
enum registers {
    al, ax,
    cl, cx,
    dl, dx,
    bl, bx,
    ah, sp,
    ch, bp,
    dh, si,
    bh, di
};
enum registers reg_register;

// This meaning of the encoding for this field depends on the 
// and the w bit field.
// mod MOD_11 means register to register
// mod MOD_00, MOD_01, MOD_10 is effective address.
#define mask_field_mov_rm_000 0b00000000
#define mask_field_mov_rm_001 0b00000001
#define mask_field_mov_rm_010 0b00000010
#define mask_field_mov_rm_011 0b00000011
#define mask_field_mov_rm_100 0b00000100
#define mask_field_mov_rm_101 0b00000101
#define mask_field_mov_rm_110 0b00000110
#define mask_field_mov_rm_111 0b00000111
enum registers rm_register;

int main(void) {
    char current_instruction_type;
    short instruction_00 = 0x89D9;
    char instruction_high = 0x89;
    
    char mov_rm_to_or_from_reg_pattern = 0x88;
    
    if ((instruction_high & mov_rm_to_or_from_reg_pattern) == mov_rm_to_or_from_reg_pattern) {
        printf("The instruction is a mov register/memory to/from register\n");
        // printf("mov ");
        if (((char)(instruction_00) & mask_field_mov_mod_memory_mode_no_displacement) == mask_field_mov_mod_memory_mode_no_displacement) {
            mod = memory_mode_no_displacement;
        }
        if (((char)(instruction_00) & mask_field_mov_mod_memory_mode_8bit_displacement) == mask_field_mov_mod_memory_mode_8bit_displacement) {
            mod = memory_mode_8bit_displacement;
        }
        if (((char)(instruction_00) & mask_field_mov_mod_memory_mode_16bit_displacement) == mask_field_mov_mod_memory_mode_16bit_displacement) {
            mod = memory_mode_16bit_displacement;
        }
        if (((char)(instruction_00) & mask_field_mov_mod_register_mode) == mask_field_mov_mod_register_mode) {
            mod = register_mode_no_displacement;
        }

        if (((instruction_high) & mask_field_mov_bd) == mask_field_mov_bd) {
            w_field_val = byte;
        }
        if (((instruction_high) & mask_field_mov_wd) == mask_field_mov_wd) {
            w_field_val = wide;
        }

        if (((instruction_high) & mask_field_mov_ds) == mask_field_mov_ds) {
            d_field_val = source_reg;
        }
        if (((instruction_high) & mask_field_mov_dd) == mask_field_mov_dd) {
            d_field_val = dest_reg;
        }

        if (((char)(instruction_00) & mask_field_mov_reg_alx) == mask_field_mov_reg_alx) {
            // TODO(): Do we need an enum if not set
            if (w_field_val == byte) {
                reg_register = al;
            }
            if (w_field_val == wide) {
                reg_register = ax;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_clx) == mask_field_mov_reg_clx) {
            if (w_field_val == byte) {
                reg_register = cl;
            }
            if (w_field_val == wide) {
                reg_register = cx;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_dlx) == mask_field_mov_reg_dlx) {
            if (w_field_val == byte) {
                reg_register = dl;
            }
            if (w_field_val == wide) {
                reg_register = dx;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_blx) == mask_field_mov_reg_blx) {
            if (w_field_val == byte) {
                reg_register = bl;
            }
            if (w_field_val == wide) {
                reg_register = bx;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_ahsp) == mask_field_mov_reg_ahsp) {
            if (w_field_val == byte) {
                reg_register = ah;
            }
            if (w_field_val == wide) {
                reg_register = sp;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_chbp) == mask_field_mov_reg_chbp) {
            if (w_field_val == byte) {
                reg_register = ch;
            }
            if (w_field_val == wide) {
                reg_register = bp;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_dhsi) == mask_field_mov_reg_dhsi) {
            if (w_field_val == byte) {
                reg_register = dh;
            }
            if (w_field_val == wide) {
                reg_register = si;
            }
        }
        if (((char)(instruction_00) & mask_field_mov_reg_bhdi) == mask_field_mov_reg_bhdi) {
            if (w_field_val == byte) {
                reg_register = bh;
            }
            if (w_field_val == wide) {
                reg_register = di;
            }
        }




        if (((char)(instruction_00) & mask_field_mov_rm_000) == mask_field_mov_rm_000) {
            // TODO(): Do we need an enum if not set
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = al;
                }
                if (w_field_val == wide) {
                    rm_register = ax;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_001) == mask_field_mov_rm_001) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = cl;
                }
                if (w_field_val == wide) {
                    rm_register = cx;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_010) == mask_field_mov_rm_010) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = dl;
                }
                if (w_field_val == wide) {
                    rm_register = dx;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_011) == mask_field_mov_rm_011) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = bl;
                }
                if (w_field_val == wide) {
                    rm_register = bx;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_100) == mask_field_mov_rm_100) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = ah;
                }
                if (w_field_val == wide) {
                    rm_register = sp;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_101) == mask_field_mov_rm_101) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = ch;
                }
                if (w_field_val == wide) {
                    rm_register = bp;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_110) == mask_field_mov_rm_110) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = dh;
                }
                if (w_field_val == wide) {
                    rm_register = si;
                }
            }
        }
        if (((char)(instruction_00) & mask_field_mov_rm_111) == mask_field_mov_rm_111) {
            if (mod == memory_mode_no_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_8bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == memory_mode_16bit_displacement) {
                printf("R/M not yet implemented\n");
            }
            if (mod == register_mode_no_displacement) {
                if (w_field_val == byte) {
                    rm_register = bh;
                }
                if (w_field_val == wide) {
                    rm_register = di;
                }
            }
        }

        char *instruction = "mov";
        char *dest;
        char *source;
        char *registers_table[16] = {"al", "ax", "cl", "cx", "dl", "dx", "bl", "bx", "ah", "sp", "ch", "bp", "dh", "si", "bh", "di"};

        if (mod == register_mode_no_displacement) {
            // TODO(): Good time to check for parsing errors.
            if (d_field_val == source_reg) {
                source = registers_table[reg_register];
                dest = registers_table[rm_register];
            }
            if (d_field_val == dest_reg) {
                source = registers_table[rm_register];
                dest = registers_table[reg_register];
            }
        }
        printf("%s %s, %s", instruction, dest, source);
    }
    else {
        printf("System fault. Unkown instruction.\n");
    }
    return (0);
}