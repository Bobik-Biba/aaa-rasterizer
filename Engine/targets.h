#pragma once
#pragma pack(push, 4)
class targets {
	public:
		struct pos_float {
			float x, y;
		};
		struct size {
			float width, height;
		};
		struct points {
			pos_float p1, p2, p3, p4;
		};
		struct aaa {
			int x, y;
		};
		pos_float pos;
		pos_float f_vector;
		points Points;
		size sizes;
		aaa size;
};
#pragma pack(pop)