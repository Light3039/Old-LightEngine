#include "ltpch.h"
#include "GraphicsContext.h"

#include "Blender.h"
#include "RenderCommand.h"
#include "Renderer.h"

#include "Font/FontManager.h"

#include "UserInterface/UserInterface.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "Platform/DirectX/dxGraphicsContext.h"
#endif
#include "Platform/Opengl/glGraphicsContext.h"

#include <imgui.h>

namespace Light {

	std::unique_ptr<GraphicsContext> GraphicsContext::s_Context = nullptr;
	GraphicsAPI GraphicsContext::s_Api = GraphicsAPI::Default;

	void GraphicsContext::CreateContext(GraphicsAPI api, const GraphicsConfigurations& configurations)
	{
		LT_PROFILE_FUNC();

		// don't re-initialize the same graphics api
		if (s_Api == api && api != GraphicsAPI::Default)
		{
			LT_CORE_ERROR("GraphicsContext::CreateContext: re-initializing same graphics api is not allowed, api: {}", api);
			return;
		}

		// if api is 'Default', find the preferred graphics api based on platform
		if (api == GraphicsAPI::Default)
		{
#ifdef LIGHT_PLATFORM_WINDOWS
			s_Api = GraphicsAPI::Directx;
#else
			s_Api = GraphicsAPI::Opengl;
#endif
		}
		else
			s_Api = api;


		// create GraphicsContext
		if (s_Api == GraphicsAPI::Opengl)
			s_Context = std::make_unique<glGraphicsContext>(configurations); // opengl
		LT_DX(else if (s_Api == GraphicsAPI::Directx)
			s_Context = std::make_unique<dxGraphicsContext>(configurations);) // directx
		else
			LT_CORE_ASSERT(false, "GraphicsContext::CreateContext: invalid GraphicsAPI");

		// initialize GraphicsContext dependent classes
		RenderCommand::SetGraphicsContext(s_Context.get());
		Blender::Init();
		Renderer::Init();
		UserInterface::Init();
		FontManager::Init();
	}

	void GraphicsContext::ShowDebugWindow()
	{
		ImGui::BulletText("graphics api: %s", s_Api == GraphicsAPI::Opengl  ? "opengl"  :
		                                      s_Api == GraphicsAPI::Directx ? "directx" : "");

		ImGui::BulletText("resolution: [%d x %d]", m_Configurations.resolution.width, m_Configurations.resolution.height);
		ImGui::BulletText("aspect ratio: %f", m_Configurations.resolution.aspectRatio);
		ImGui::BulletText("v-sync: %s", m_Configurations.vSync ? "on" : "off");
		// #todo: properties...
	}

}