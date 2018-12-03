/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/12/03 19:18:24 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*
 * [1] live NO_PLAYER on 4 bytes (10 cycles) -> NO_PLAYER is alive | 
 * [2] ld X (scalar or index) on 4/2 bytes, REG (5 cycles) -> load X into REG
 * [3] st X (REG1 || IND, address) on 1/2 bytes, REG -> stores the value of X into REG
 * [4] add X (REG), Y (REG), Z (REG) -> add X and Y values and stores it into Z
 * [5] sub X (REG), Y (REG), Z (REG) -> sub X and Y values and stores it into Z
 * [6] and X (REG, IND, DIR), Y (REG, IND, DIR), Z (REG) ->  X & Y value and stores it into Z
 * [7] or X (REG, IND, DIR), Y (REG, IND, DIR), Z (REG) ->  X | Y value and stores it into Z
 * [8] xor X (REG, IND, DIR), Y (REG, IND, DIR), Z (REG) ->  X ^ Y value and stores it into Z
 *		[9] zjmp X (index on 2 bytes), jumps to the index if carry == 1
 * [10] ldi X (index), Y (index), REG, add X and Y values uses the result as an address, reads a value of REG_SIZE and  stores it into REG
 * [11] sti REG, X (index), Y (index), add X and Y use this value as an address to store REG value
 * [12] fork X (index), create a new process which inherits state of his father except for his PC which will be at PC + (X % IDX_MOD)
 * [13] lld X (scalar or index) on 4/2 bytes, REG (5 cycles) -> long load X into REG (same as ld without % IDX_MOD)
 * [14] lldi X (index), Y (index), REG, add X and Y values and stores it into REG (no modulo to addresses)
 * [15] lfork X (index), create a new process which inherits state of his father except for his PC which will be at PC + X
 * [16] aff REG -> REG value that is interpreted % 256 and should be output on STDOUT
*/

/*
 *
 * MOD CARRY
 * [2] ld 0
 * [4] add 0
 * [5] sub 0
 * [6] and 0
 * [7] or 0
 * [8] xor 0
 * [13] lld 0
 * [14] lldi 1
 *
 * DONT MOD CARRY
 * [10] ldi 1
 *
 * NEEDS CARRY TO BE 1
 * [9] zjmp 1
 *
 * */
