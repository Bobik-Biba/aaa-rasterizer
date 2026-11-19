/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "targets.h"
#include "aaa_aliasing.h"
#include <xinput.h>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	~Game();
private:
	void ComposeFrame();
	void UpdateModel();
	__forceinline void aaa_seam(float& __restrict x1, float& __restrict y1, float& __restrict x2, float& __restrict y2, float& __restrict k, float& __restrict b, int& __restrict count_st, int& __restrict count_st2, int& __restrict fx_int, int& __restrict counter_width, int& __restrict counter_height, float& __restrict k_1, float& __restrict return1, float& __restrict return2);
	__forceinline void aaa_aliasing_fx( float& __restrict x1, float& __restrict y1, float& __restrict x2, float& __restrict y2, float& __restrict k_orig, float& __restrict b, int& __restrict count_st, int& __restrict count_st2, int& __restrict fx_int, float& __restrict normal_x, float& __restrict normal_y, float& __restrict width, float& __restrict height, int& __restrict counter_width, int& __restrict counter_height, float& __restrict k_1, float& __restrict square, float& __restrict return1,float& __restrict return2);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	char* raw_memory = new char[2048];
	int* objs_sizes = nullptr;
	int* objs_size_1 = nullptr;
	int* objs_size_2 = nullptr;
	int* objs_size_3 = nullptr;
	int* objs_size_4 = nullptr;

	XINPUT_STATE* pad;

	targets* target_1 = nullptr;
	targets* target_2 = nullptr;
	targets* target_3 = nullptr;
	targets* target_4 = nullptr;
	aaa_aliasing* aaa_aliasing_ = nullptr;


	float* safety_values = nullptr;
	float* msq_max = nullptr;
	float* msq_x = nullptr;
	float* msq_y = nullptr;

	int* max_resolution_w = nullptr;
	int* max_resolution_h = nullptr;
	int* max_resolutions = nullptr;

	float* max_resolutions_f = nullptr;
	float* max_resolutions_f_x = nullptr;
	float* max_resolutions_f_y = nullptr;
	float* square = nullptr;
	float* width = nullptr;
	float* height = nullptr;

	float* fx = nullptr;

	float* fx_k = nullptr;
	float* fx_b = nullptr;
	float* fx_k_1 = nullptr;

	int* count_st = nullptr;
	int* count_st_1 = nullptr;
	int* count_st_2 = nullptr;
	int* fx_int = nullptr;

	float* normals = nullptr;
	float* normal_x = nullptr;
	float* normal_y = nullptr;

	int* counter_int = nullptr;
	int* counter_int_width = nullptr;
	int* counter_int_height = nullptr;
	
	float* returns = nullptr;
	float* return1 = nullptr;
	float* return2 = nullptr;

	bool* bools = nullptr;
	bool* bools1 = nullptr;
	bool* bools2 = nullptr;

	/********************************/
	/*  User Variables              */
	/********************************/
/*******************************************************************************
* ШПАРГАЛКА ПО РАЗМЕРАМ ТИПОВ ДАННЫХ В C++ (x64 Windows)                       *
*******************************************************************************/
/*                                                                            */
/* bool           = 1 байт  (8 бит). Хранит true/false.                       */
/* char           = 1 байт  (8 бит). Хранит символы или числа от -128 до 127. */
/*                                                                            */
/* short          = 2 байта (16 бит). Числа от -32 768 до 32 767.             */
/* unsigned short = 2 байта.       Числа от 0 до 65 535.                      */
/*                                                                            */
/* int            = 4 байта (32 бит). От -2 млрд до +2 млрд (Родной тип CPU). */
/* unsigned int   = 4 байта.       От 0 до 4.2 млрд.                          */
/* long           = 4 байта (32 бит). В Windows равен обычному int.           */
/*                                                                            */
/* long long      = 8 байт  (64 бит). Огромные числа (до 9 квинтиллионов).    */
/*                                                                            */
/* --- ТИПЫ С ПЛАВАЮЩЕЙ ТОЧКОЙ (ДРОБИ) ---                                    */
/* float          = 4 байта (32 бит). Одиночная точность (7 знаков после ,).  */
/* double         = 8 байт  (64 бит). Двойная точность (15 знаков после ,).   */
/*                                                                            */
/* --- УКАЗАТЕЛИ ---                                                          */
/* Любой указатель (*a, *keys, char*, void*) на 64-битной системе             */
/* ВСЕГДА весит ровно 8 байт (64 бита), потому что адрес памяти               */
/* в x64 архитектуре физически не помещается в меньший объём.                 */
/* sizeof(тип данных или массив) возвращает его размер в байтах               */
/******************************************************************************/
};