/*
 * fondo-nds.c
 * This file is part of Fondo-Nds
 *
 * Copyright (C) 2011 - Félix Arreola Rodríguez
 *
 * Fondo-Nds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Fondo-Nds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fondo-Nds; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <nds.h>

#include "fondo.h"
#include "fondo2.h"

int main () {
	powerOn (POWER_ALL_2D);
	
	lcdMainOnBottom ();
	/* Asignar los bancos de memoria vram */
	vramSetPrimaryBanks (VRAM_A_MAIN_BG, VRAM_B_MAIN_BG, VRAM_C_SUB_BG, VRAM_D_LCD);
	
	/* Activar modos de video */
	videoSetMode (MODE_5_2D | DISPLAY_BG3_ACTIVE);
	videoSetModeSub (MODE_5_2D | DISPLAY_BG3_ACTIVE);
	
	/* Activar el fondo en el motor principal */
	REG_BG3CNT = BG_BMP16_256x256 |
	             BG_BMP_BASE(0) |
	             BG_PRIORITY(3);
	
	REG_BG3PA = 1 << 8;
	REG_BG3PB = 0;
	REG_BG3PC = 0;
	REG_BG3PD = 1 << 8;
	
	REG_BG3X = 0;
	REG_BG3Y = 0;
	
	REG_BG3CNT_SUB = BG_BMP16_256x256 |
	                 BG_BMP_BASE (16) |
	                 BG_PRIORITY (3);
	
	REG_BG3PA_SUB = 1 << 8;
	REG_BG3PB_SUB = 0;
	REG_BG3PC_SUB = 0;
	REG_BG3PD_SUB = 1 << 8;
	
	REG_BG3X_SUB = 0;
	REG_BG3Y_SUB = 0;
	
	DC_FlushRange (fondoBitmap, fondoBitmapLen);
	DC_FlushRange (fondo2Bitmap, fondo2BitmapLen);
	
	/* Empezar la copia de los fondos */
	dmaCopy (fondoBitmap, BG_BMP_RAM (0), fondoBitmapLen);
	dmaCopy (fondo2Bitmap, BG_BMP_RAM_SUB(16), fondo2BitmapLen);
	
	return 0;
}
