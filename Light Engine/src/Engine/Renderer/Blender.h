#pragma once

#include "Core/Core.h"

namespace Light {

	// ZERO              = D3D11_BLEND_ZERO           = GL_ZERO
	// ONE               = D3D11_BLEND_ONE            = GL_ONE
	// SRC_COLOR         = D3D11_BLEND_SRC_COLOR      = GL_SRC_COLOR
	// SRC_COLOR_INVERSE = D3D11_BLEND_INV_SRC_COLOR  = GL_ONE_MINUS_SRC_COLOR
	// SRC_ALPHA         = D3D11_BLEND_SRC_ALPHA      = GL_SRC_ALPHA
	// SRC_ALPHA_INVERSE = D3D11_BLEND_INV_SRC_ALPHA  = GL_ONE_MINUS_SRC_ALPHA
	// DST_COLOR         = D3D11_BLEND_DEST_COLOR     = GL_DST_COLOR
	// DST_COLOR_INVERSE = D3D11_BLEND_INV_DEST_COLOR = GL_ONE_MINUS_DST_COLOR
	// DST_ALPHA         = D3D11_BLEND_DEST_ALPHA     = GL_DST_ALPHA
	// DST_ALPHA_INVERSE = D3D11_BLEND_INV_DEST_ALPHA = GL_ONE_MINUS_DST_ALPHA

	enum class BlendFactor
	{
		ZERO = 0,
		ONE,

		SRC_COLOR,
		SRC_COLOR_INVERSE,
		SRC_ALPHA,
		SRC_ALPHA_INVERSE,

		DST_COLOR,
		DST_COLOR_INVERSE,
		DST_ALPHA,
		DST_ALPHA_INVERSE,
	};

	class Blender
	{
	private:
		static std::unique_ptr<Blender> s_Context;
	protected:
		static BlendFactor s_SrcFactor;
		static BlendFactor s_DstFactor;

		static bool b_Enabled;
	public:
		virtual ~Blender() = default;

		static inline void Enable () { b_Enabled = true ; s_Context->EnableImpl();  }
		static inline void Disable() { b_Enabled = false; s_Context->DisableImpl(); }

		static inline void SetSrcFactor(BlendFactor factor) { s_SrcFactor = factor; s_Context->SetSrcFactorImpl(factor); }
		static inline void SetDstFactor(BlendFactor factor) { s_DstFactor = factor; s_Context->SetDstFactorImpl(factor); }

		static void ShowDebugWindow();

		static inline bool IsEnabled() { return b_Enabled; }

		virtual void EnableImpl() = 0;
		virtual void DisableImpl() = 0;

		virtual void SetSrcFactorImpl(BlendFactor factor) = 0;
		virtual void SetDstFactorImpl(BlendFactor factor) = 0;
	private:
		friend class GraphicsContext;
		static void Init();

		static const char* FactorToString(BlendFactor factor);
	};

}