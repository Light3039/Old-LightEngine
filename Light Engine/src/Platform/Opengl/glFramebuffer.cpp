#include "ltpch.h"
#include "glFramebuffer.h"


#include "Renderer/GraphicsContext.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"

#include <glad/glad.h>

namespace Light {

	glFramebuffer::glFramebuffer(const std::string& vertex, const std::string& fragment)
	{
		m_Shader = Shader::Create(vertex, fragment);

		// create framebuffer and color texture
		glCreateFramebuffers(1, &m_FrameBufferID);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorTextureID);

		// bind framebuffer and color texture
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		             GraphicsContext::GetConfigurations().resolution.width,
		             GraphicsContext::GetConfigurations().resolution.height,
		             NULL, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);

		// check
		LT_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
		               "glFramebuffer::glFramebuffer: framebuffer status is not complete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	glFramebuffer::~glFramebuffer()
	{
		glDeleteTextures(1, &m_ColorTextureID);
		glDeleteFramebuffers(1, &m_FrameBufferID);
	}

	void glFramebuffer::BindAsTarget()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void glFramebuffer::BindAsResource()
	{
		m_Shader->Bind();
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
	}

	void glFramebuffer::Resize(unsigned int width, unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, NULL, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

}