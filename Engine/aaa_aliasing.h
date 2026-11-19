#pragma once
#pragma pack(push, 4)
class aaa_aliasing {
public:
	struct element {
		int a;
	};
	struct pos_float {
		float x, y;
	};
	struct points {
		pos_float p1, p2;
	};
	points Points;
	element Element;
};
#pragma pack(pop)