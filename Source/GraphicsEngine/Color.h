#pragma once

struct Color
{
#pragma warning( push )
#pragma warning( disable : 4201 )

	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		struct
		{
			float red;
			float green;
			float blue;
			float alpha;
		};
		float values[4];
	};
#pragma warning( pop )
	//float r;
	//float g;
	//float b;
	//float a;

	static const Color white;
	static const Color clear;
	static const Color black;
}; 


