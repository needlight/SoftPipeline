
#pragma once

#include <vector>
#include <string>

typedef unsigned int uint;
typedef unsigned __int64 uint64;
typedef wchar_t wchar;


namespace SRP
{
	///////////////////////////////////////////////////////////
	// Math
	///////////////////////////////////////////////////////////
	class Point2;
	class Point3;
	class Point4;
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix2;
	class Matrix3;
	class Matrix4;
	
	class Rect2;
	class Rect3;

	///////////////////////////////////////////////////////////
	// Else
	///////////////////////////////////////////////////////////
	class PixelFormat;
	class Resolution;

	class Color
	{
	public:
		float _a, _r, _g, _b;
	};

	///////////////////////////////////////////////////////////
	// States of RenderingPipeline
	///////////////////////////////////////////////////////////


	class LightState
	{
	public:
		Color _ambient;
		Color _diffuse;
		Color _specular;
		Color _emissive;
	};

	class MaterialState
	{
	public:
		Color _ambient;
		Color _diffuse;
		Color _specular;
		Color _emissive;
	};

	class TextureState
	{
	public:
	};

	enum FillMode
	{
		FM_POINT,
		FM_LINE,
		FM_SURFACE,
	};

	class AlphaState;
	class StencilState;
	class ZState;
	class FogState;

	class DrawState
	{
	public:
		FillMode _fill_mode;
		bool _enable_light;
		bool _enable_mtl;
	};

	///////////////////////////////////////////////////////////
	// GDI Lib Wrap
	///////////////////////////////////////////////////////////
	class GDILibWrap
	{
	public:
		void DrawPoint( Point2& point, Color& color );
		void DrawLine( Point2& start, Point2& end, int width, Color& color );
		void DrawRect( Rect2& rect, Color& color );
		void DrawCircle( Point2& pos, float radius, Color& color );
	};

	///////////////////////////////////////////////////////////
	// Rendering Pipeline
	///////////////////////////////////////////////////////////
	class Transformation
	{
	public:
		Matrix4 _world_mtx;
		Matrix4 _view_mtx;
		Matrix4 _projection_mtx;
	};

	class VSInput;
	class VSOutput;

	class VertexShader
	{
	public:
		
	};

	class PSInput;
	class PSOutput;

	class PixelShader
	{
	};

	///////////////////////////////////////////////////////////
	// Resource
	///////////////////////////////////////////////////////////
	enum ResType
	{
		RT_VERTEX_SHADER,
		RT_PIXEL_SHADER,
		RT_TEXTURE,
		RT_SURFACE,
		RT_INDEX_BUFFER,
		RT_VERTEX_BUFFER,
	};

	class ResID
	{
	public:
		ResID& operator=( uint64 );
		uint64 operator( uint64 )();

	public:
		ResType _type;
		int _idx;
	};

	class ResMan
	{
	public:
		ResMan();
		~ResMan();

		ResID CreateVertexShader( const char* name );
		void DestroyVertexShader( ResID id );
	};

	///////////////////////////////////////////////////////////
	// SRPDevice
	///////////////////////////////////////////////////////////
	class SRPDeviceParam
	{
	public:
		SRPDeviceParam();
		SRPDeviceParam();
		~SRPDeviceParam() {}

	public:
		Rect2 _draw_rect;
		PixelFormat _format;
		Resolution _resolution;
		
		// 流处理单元数，可以用作VS计算，也可以用作PS计算，由SRPDevice负责管理派发给谁使用，数值最好等于CPU核心数
		int _stream_processor_cnt;
	};

	class SRPDevice
	{
	public:
		SRPDevice( SRPDeviceParam& param );
		~SRPDevice();

		ResMan& GetResMan();

		void EnableVerterShader( ResID& resid, bool enable );
		void EnablePixelShader( ResID& resid, bool enable );

		void BeginDraw();
		void EndDraw();
		void Clear();
		void Draw();
	};
};