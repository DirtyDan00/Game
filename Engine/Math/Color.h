#pragma once
#include <Windows.h>
#include <iostream>

namespace nc
{
	struct Color
	{
		float r, g, b;
		Color() : r{ 0 }, g{ 0 }, b{ 0 }{}
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b }{}

		float& operator [] (size_t index);
		//const float& operator [] const (size_t index);

		void Set(float r, float g, float b);

		Color operator + (const Color& c) const;
		Color operator - (const Color& c) const;
		Color operator * (const Color& c) const;
		Color operator / (const Color& c) const;

		Color operator + (float s) const;
		Color operator - (float s) const;
		Color operator * (float s) const;
		Color operator / (float s) const;


		Color operator += (const Color& c);
		Color operator -= (const Color& c);
		Color operator *= (const Color& c);
		Color operator /= (const Color& c);

		Color& operator += (float s);
		Color& operator -= (float s);
		Color& operator *= (float s);
		Color& operator /= (float s);

		friend std::istream& operator >> (std::istream& stream, Color& c);

		COLORREF Pack888() const;

		operator COLORREF() const
		{
			BYTE _r = static_cast<BYTE>(r * 255.0f);
			BYTE _g = static_cast<BYTE>(g * 255.0f);
			BYTE _b = static_cast<BYTE>(b * 255.0f);

			return (_r) | (_g << 8) | (_b << 16);

		}

		static const Color white;
		static const Color red;
		static const Color blue;
		static const Color green;


	};

	
}