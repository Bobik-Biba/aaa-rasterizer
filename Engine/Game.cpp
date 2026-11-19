/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <new>
#include "targets.h"
#include "aaa_aliasing.h"
#include "xinput.h"
#include <algorithm>
#include <format>
#pragma comment(lib, "xinput.lib")

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	objs_sizes = (int*)(raw_memory);
	objs_size_1 = &objs_sizes[0];
	objs_size_2 = &objs_sizes[1];//кирпич
	objs_size_3 = &objs_sizes[2];//кирпич
	objs_size_4 = &objs_sizes[3];//кирпич
	*objs_size_1 = sizeof(targets);
	target_1 = new (raw_memory + 16) targets();
	target_2 = new (raw_memory + 16 + *objs_size_1) targets();//кирпич
	target_3 = new (raw_memory + 16 + *objs_size_1 * 2) targets();//кирпич
	target_4 = new (raw_memory + 16 + *objs_size_1 * 3) targets();//кирпич
	pad = (XINPUT_STATE*)(raw_memory + 16 + *objs_size_1 * 4);
	safety_values = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE));
	max_resolutions = (int*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12);
	max_resolutions_f = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8);
	square = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8);
	count_st = (int*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4);
	width = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8);
	height = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4);
	aaa_aliasing_ = new (raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4) aaa_aliasing();
	fx = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing));
	fx_int = (int*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing) + 12);
	normals = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing) + 12 + 4);
	counter_int = (int*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing) + 12 + 4 + 8);
	returns = (float*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing) + 12 + 4 + 8+8);
	bools=(bool*)(raw_memory + 16 + *objs_size_1 * 4 + sizeof(XINPUT_STATE) + 12 + 8 + 8 + 4 + 8 + 4 + 4 + sizeof(aaa_aliasing) + 12 + 4 + 8 + 8+2);

	msq_max = &safety_values[0];
	msq_x = &safety_values[1];
	msq_y = &safety_values[2];
	target_1->pos.x = 200.435f;
	target_1->pos.y = 200.234f;

	target_1->sizes.width = 200.0f;
	target_1->sizes.height = 190.0f;

	target_1->Points.p1.x = target_1->pos.x - target_1->sizes.width * 0.5f;
	target_1->Points.p1.y = target_1->pos.y - target_1->sizes.height * 0.5f;

	target_1->Points.p2.x = target_1->pos.x - target_1->sizes.width * 0.5f;
	target_1->Points.p2.y = target_1->pos.y + target_1->sizes.height * 0.5f;

	target_1->Points.p3.x = target_1->pos.x + target_1->sizes.width * 0.5f;
	target_1->Points.p3.y = target_1->pos.y + target_1->sizes.height * 0.5f;

	target_1->Points.p4.x = target_1->pos.x + target_1->sizes.width * 0.5f;
	target_1->Points.p4.y = target_1->pos.y - target_1->sizes.height * 0.5f;

	target_2->Points.p4.x = 50.0f;
	target_2->Points.p4.y = 50.0f;
	target_2->Points.p1.x = 200.0f;
	target_2->Points.p1.y = 100.0f;

	target_2->Points.p2.x = 200.0f;
	target_2->Points.p2.y = 10.0f;
	target_2->Points.p3.x = 600.0f;
	target_2->Points.p3.y = 60.0f;

	max_resolutions_f_x = &max_resolutions_f[0];
	max_resolutions_f_y = &max_resolutions_f[1];
	max_resolution_h = &max_resolutions[0];
	*max_resolution_h = Graphics::ScreenHeight - 1;
	*max_resolutions_f_y = float(*max_resolution_h);
	max_resolution_w = &max_resolutions[1];
	*max_resolution_w = Graphics::ScreenWidth - 1;
	*max_resolutions_f_x = float(*max_resolution_w);

	*square = 0.0f;
	*height = 0.0f;
	*width = 0.0f;

	fx_k = &fx[0];
	fx_b = &fx[1];
	fx_k_1 = &fx[2];

	count_st_1 = &count_st[0];
	count_st_2 = &count_st[1];
	normal_x = &normals[0];
	normal_y = &normals[1];
	counter_int_width = &counter_int[0];
	counter_int_height = &counter_int[1];
	return1=&returns[0];
	return2=&returns[1];

	bools1 = &bools[0];
	bools2 = &bools[1];
}
__forceinline static void ZeroError(
	float& pos, 
	float& speed, 
	int& max_resolution, 
	float& size) {
	pos += speed;
	if (pos < size* 0.5f) {
		pos = size* 0.5f;
	}
	else if (pos > max_resolution-size*0.5f) {
		pos = max_resolution-size*0.5f;
	}
}
__forceinline void Game::aaa_seam(
	float& __restrict x1,
	float& __restrict y1,
	float& __restrict x2,
	float& __restrict y2,
	float& __restrict k,
	float& __restrict b,
	int& __restrict count_st,
	int& __restrict count_st2,
	int& __restrict fx_int,
	int& __restrict counter_width,
	int& __restrict counter_height,
	float& __restrict k_1,
	float& __restrict return1,
	float& __restrict return2
) {
	count_st2 = (y2 <= y1) ? 1 : -1;
	count_st = (x2 <= x1) ? 1 : -1;
	if ((x2 == x1) && (y2 == y1)) {
		gfx.PutPixel(x2, y2, 255, 255, 255);
	}
	else if (x2 == x1) {
		fx_int = _mm_cvtss_si32(_mm_set_ss(x1));
		count_st2 = (y2 <= y1) ? 1 : (-1);
		for (counter_width = _mm_cvtss_si32(_mm_set_ss(y2)); counter_width >= _mm_cvtss_si32(_mm_set_ss(y1)); counter_width += count_st2) {
			gfx.PutPixel(fx_int, count_st, 255, 255, 255);
		}
	}
	else if (y1 == y2) {
		fx_int = _mm_cvtss_si32(_mm_set_ss(y1));
		count_st = (x2 <= x1) ? 1 : (-1);
		for (counter_width = _mm_cvtss_si32(_mm_set_ss(x2)); counter_width >= _mm_cvtss_si32(_mm_set_ss(x1)); counter_width += count_st) {
			gfx.PutPixel(counter_width, fx_int, 255, 255, 255);
		}
	}
	else {
		return2 = (y2 - y1) / (x2 - x1);
		k_1 = 1.0f / return2;
		b = y2 - return2 * x2;
		k = return2;
		return1 = 0.5f;
		*(uint32_t*)&return1 = 0x3F000000u | (*(uint32_t*)&return2 & 0x80000000u);
		*(uint32_t*)&return2 &= 0x7FFFFFFF;
		if (
			return2>=1.0f
			) {
			counter_height = _mm_cvtss_si32(_mm_set_ss(y2));
			for (counter_height; counter_height != _mm_cvtss_si32(_mm_set_ss(y1)); counter_height += count_st2) {
				for (counter_width = int((float(counter_height) -return1 - b) * k_1); counter_width != int((float(counter_height) + return1 - b) * k_1) + count_st; counter_width += count_st) {
					gfx.PutPixel(counter_width, counter_height, 255, 255, 255);
				};
			};
		}
		else {
			counter_width = _mm_cvtss_si32(_mm_set_ss(x2));
			for (counter_width; counter_width != _mm_cvtss_si32(_mm_set_ss(x1)); counter_width += count_st) {
				for (counter_height = int((float(counter_width) -return1) * k + b); counter_height != int((float(counter_width) + return1) * k + b) + count_st2; counter_height += count_st2) {
					gfx.PutPixel(counter_width, counter_height, 255, 255, 255);
				};
			};
		};
	};
};
__forceinline void Game::aaa_aliasing_fx(
	float& __restrict x1, 
	float& __restrict y1, 
	float& __restrict x2, 
	float& __restrict y2, 
	float& __restrict k, 
	float& __restrict b, 
	int& __restrict count_st, 
	int& __restrict count_st2, 
	int& __restrict fx_int,
	float& __restrict normal_x, 
	float& __restrict normal_y, 
	float& __restrict width, 
	float& __restrict height, 
	int& __restrict counter_width, 
	int& __restrict counter_height, 
	float& __restrict k_1,
	float& __restrict square,
	float& __restrict return1,
	float& __restrict return2
) {
	if (x2 == x1) {
		count_st = (y2 >= y1) ? 1 : -1;
		width = x1-(float(_mm_cvtss_si32(_mm_set_ss(x1))) + 0.5f*float(count_st));
		*(uint32_t*)&width &= 0x7FFFFFFF;
		fx_int = _mm_cvtss_si32(_mm_set_ss(width*255.0f));
		counter_height = _mm_cvtss_si32(_mm_set_ss(x2));
		for (counter_width = _mm_cvtss_si32(_mm_set_ss(y1)); counter_width != _mm_cvtss_si32(_mm_set_ss(y2)); counter_width += count_st) {
			gfx.PutPixel(counter_height, counter_width, fx_int, fx_int, fx_int);
		}
	}
	else if (y1 == y2) {
		count_st = (x2 >= x1) ? 1 : -1;
		width = y1 - (float(_mm_cvtss_si32(_mm_set_ss(y1))) + 0.5f * float(count_st));
		*(uint32_t*)&width &= 0x7FFFFFFF;
		fx_int = _mm_cvtss_si32(_mm_set_ss(width * 255.0f));
		counter_height = _mm_cvtss_si32(_mm_set_ss(y2));
		for (counter_width = _mm_cvtss_si32(_mm_set_ss(x1)); counter_width != _mm_cvtss_si32(_mm_set_ss(x2)); counter_width += count_st) {
			gfx.PutPixel(counter_width, counter_height, fx_int, fx_int, fx_int);
		}
	}
	else {
		return2 = (y2 - y1) / (x2 - x1);
		k_1 = 1.0f / return2;
		b = y2 - return2 * x2;
		k = return2;
		*(uint32_t*)&return2 &= 0x7FFFFFFF;
		count_st = (y2 >= y1) ? 1 : -1;
		count_st2 = (x2 >= x1) ? 1 : -1;
		if (
			return2 <1.0f
		){
			for (counter_height = _mm_cvtss_si32(_mm_set_ss(y1))+count_st; counter_height != _mm_cvtss_si32(_mm_set_ss(y2)) - count_st; counter_height += count_st) {
				counter_width = _mm_cvtss_si32(_mm_set_ss((float(counter_height) -float(count_st)*0.5f - b) * k_1))+count_st2;
				width = float(counter_height) + float(count_st) * 0.5f;
				for (counter_width; counter_width != _mm_cvtss_si32(_mm_set_ss((float(counter_height) + float(count_st) * 0.5f - b) * k_1)); counter_width += count_st2) {
					normal_y = (float(counter_width) * k + b) - width;
					*(uint32_t*)&normal_y &= 0x7FFFFFFF;
					normal_y = normal_y * 255.0f;
					fx_int = int(normal_y)+1;
					gfx.PutPixel(counter_width, counter_height, fx_int, fx_int, fx_int);
				}
				width = (float(counter_height) - float(count_st) * 0.5f - b) * k_1;
				counter_width = _mm_cvtss_si32(_mm_set_ss(width));
				if (width != float(counter_width) + 0.5f * float(count_st2)) {
					normal_x = (float(counter_width) + 0.5f * float(count_st2));
					normal_y = (normal_x * k + b) - (float(counter_height) - float(count_st) * 0.5f);
					normal_x = normal_x - width;
					*(uint32_t*)&normal_y &= 0x7FFFFFFF;
					*(uint32_t*)&normal_x &= 0x7FFFFFFF;
					square = (1.0f - (normal_x * normal_y) * 0.5f) * 255.0f;
					fx_int = int(square)+1;
					gfx.PutPixel(counter_width, counter_height, fx_int, fx_int, fx_int);
					if (wnd.kbd.KeyIsPressed(VK_INSERT)) {
						gfx.PutPixel(counter_width, counter_height, 255, 0, 0);
					}
				}
				width = (float(counter_height) + float(count_st) * 0.5f - b) * k_1;
				counter_width = _mm_cvtss_si32(_mm_set_ss(width));
				if (width != float(counter_width) - 0.5f * float(count_st2)) {
					normal_x = (float(counter_width) - 0.5f * float(count_st2));
					normal_y = (normal_x * k + b) - (float(counter_height) + float(count_st) * 0.5f);
					normal_x = normal_x - width;
					*(uint32_t*)&normal_y &= 0x7FFFFFFF;
					*(uint32_t*)&normal_x &= 0x7FFFFFFF;
					square = ((normal_y * normal_x) * 0.5f) * 255.0f;
					fx_int = int(square)+1;
					gfx.PutPixel(counter_width, counter_height, fx_int, fx_int, fx_int);
					if (wnd.kbd.KeyIsPressed(VK_INSERT)) {
						gfx.PutPixel(counter_width, counter_height, 0, 0, 255);
					}
				}
			}
		}
		/*else {














		}*/
	};
};

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	//aaa_seam(target_1->Points.p3.x, target_1->Points.p3.y, target_1->Points.p1.x, target_1->Points.p1.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *counter_int_width, *counter_int_height, *fx_k_1, *return2, *return1);
	//aaa_aliasing_fx(target_1->Points.p2.x, target_1->Points.p2.y, target_1->Points.p1.x, target_1->Points.p1.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *return1);
	//aaa_aliasing_fx(target_1->Points.p2.x, target_1->Points.p2.y, target_1->Points.p3.x, target_1->Points.p3.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *return1);
	//gfx.PutPixel(int(target_1->Points.p3.x), int(target_1->Points.p3.y), 255, 255, 255);
	//gfx.PutPixel(int(target_1->Points.p1.x)+1, int(target_1->Points.p1.y)+1, 255, 255, 255);
	//aaa_seam(target_1->Points.p1.x, target_1->Points.p1.y, target_1->Points.p3.x, target_1->Points.p3.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *counter_int_width, *counter_int_height, *fx_k_1, *return2, *return1);
	//aaa_seam(target_1->Points.p1.x, target_1->Points.p1.y, target_1->Points.p4.x, target_1->Points.p4.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *counter_int_width, *counter_int_height, *fx_k_1, *return2, *return1);
	//aaa_seam(target_1->Points.p2.x, target_1->Points.p2.y, target_1->Points.p4.x, target_1->Points.p4.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *counter_int_width, *counter_int_height, *fx_k_1, *return2, *return1);
	//aaa_seam(target_1->Points.p4.x, target_1->Points.p4.y, target_1->Points.p2.x, target_1->Points.p2.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *counter_int_width, *counter_int_height, *fx_k_1, *return2, *return1);
	*fx_k_1 = (target_1->Points.p4.y - target_1->Points.p2.y) / (target_1->Points.p4.x - target_1->Points.p2.x);
	*fx_b = target_1->Points.p2.y - *fx_k_1 * target_1->Points.p2.x;
	*count_st_1 = 1;
	*count_st_2 = 1;
	for (*counter_int_width = int(target_1->Points.p2.x) + 1, *count_st_1 = 1; *counter_int_width < int(target_1->Points.p4.x); *counter_int_width += *count_st_1) {
		for (*counter_int_height = int(*counter_int_width * *fx_k_1 + *fx_b) + 1, *count_st_2 = 1; *counter_int_height <= int(target_1->Points.p4.y); *counter_int_height += *count_st_2) {
			gfx.PutPixel(*counter_int_width, *counter_int_height, 255, 255, 255);
		}
	}
	aaa_aliasing_fx(target_1->Points.p2.x, target_1->Points.p2.y, target_1->Points.p4.x, target_1->Points.p4.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *square, *return1, *return2);
	aaa_aliasing_fx(target_1->Points.p2.x, target_1->Points.p2.y, target_1->Points.p1.x, target_1->Points.p1.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *square, *return1, *return2);
	aaa_aliasing_fx(target_1->Points.p4.x, target_1->Points.p4.y, target_1->Points.p1.x, target_1->Points.p1.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *square, *return1, *return2);
	aaa_aliasing_fx(target_2->Points.p3.x, target_2->Points.p3.y, target_2->Points.p2.x, target_2->Points.p2.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *square, *return1, *return2);
	//aaa_aliasing_fx(target_2->Points.p3.x, target_2->Points.p3.y, target_2->Points.p2.x, target_2->Points.p2.y, *fx_k, *fx_b, *count_st_1, *count_st_2, *fx_int, *normal_x, *normal_y, *width, *height, *counter_int_width, *counter_int_height, *fx_k_1, *square, *return1, *return2);
}

void Game::ComposeFrame()
{
	if (XInputGetState(0, pad) == ERROR_SUCCESS) {
		target_1->f_vector.x = pad->Gamepad.sThumbRX / 4096.0f;
		target_1->f_vector.y = -pad->Gamepad.sThumbRY / 4096.0f;
		*msq_x = float(pad->Gamepad.sThumbRX);
		*msq_y = float(pad->Gamepad.sThumbRY);
		*msq_max = float(*msq_y * *msq_y + *msq_x * *msq_x);
		if (*msq_max > 1073676289.0f) { //1073676289.0f=32767^(2)
			*msq_max = 32767.0f / (sqrt(*msq_max));
			target_1->f_vector.x = target_1->f_vector.x * (*msq_max);
			target_1->f_vector.y = target_1->f_vector.y * (*msq_max);
		}
	}

	target_1->Points.p1.x = target_1->pos.x - target_1->sizes.width * 0.5f;
	target_1->Points.p1.y = target_1->pos.y + target_1->sizes.height * 0.5f;

	target_1->Points.p2.x = target_1->pos.x - target_1->sizes.width * 0.5f;
	target_1->Points.p2.y = target_1->pos.y - target_1->sizes.height * 0.5f;

	target_1->Points.p3.x = target_1->pos.x + target_1->sizes.width * 0.5f;
	target_1->Points.p3.y = target_1->pos.y - target_1->sizes.height * 0.5f;

	target_1->Points.p4.x = target_1->pos.x + target_1->sizes.width * 0.5f;
	target_1->Points.p4.y = target_1->pos.y + target_1->sizes.height * 0.5f;
	if (GetAsyncKeyState(VK_SHIFT)) {
		target_1->sizes.height += pad->Gamepad.bRightTrigger * 0.01f;
		target_1->sizes.height -= pad->Gamepad.bLeftTrigger * 0.01f;
		if (target_1->sizes.height < 1.0f) {
			target_1->sizes.height = 1.0f;
		}
		else if(target_1->sizes.height > Graphics::ScreenHeight-1) {
			target_1->sizes.height = Graphics::ScreenHeight - 1.0f;
		}
	}
	else {
		target_1->sizes.width += pad->Gamepad.bRightTrigger * 0.01f;
		target_1->sizes.width -= pad->Gamepad.bLeftTrigger * 0.01f;
		if (target_1->sizes.width < 1.0f) {
			target_1->sizes.width = 1.0f;
		}
		else if (target_1->sizes.width > Graphics::ScreenWidth-1) {
			target_1->sizes.width = Graphics::ScreenWidth - 1.0f;
		}
	};
	ZeroError(target_1->pos.x, target_1->f_vector.x, *max_resolution_w, target_1->sizes.width);
	ZeroError(target_1->pos.y, target_1->f_vector.y, *max_resolution_h, target_1->sizes.height);
}
Game::~Game() {
	delete[] raw_memory;
}