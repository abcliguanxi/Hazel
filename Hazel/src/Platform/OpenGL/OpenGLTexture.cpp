#include "hzpch.h"

#include <glad/glad.h>
#include "stb_image.h"
#include "OpenGLTexture.h"

namespace Hazel
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);//stbi ͼƬԭ�������Ͻ� opengl ͼƬԭ�������½� ��Ҫ��ֱ��ת
		stbi_uc* data = stbi_load(path.c_str(), &width, &height,&channels,0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//һ�����ǰ�data�ϴ���GPU���Ͳ���Ҫ������CPU���ڴ�����
		glTextureSubImage2D(m_RendererID, 0, 0, 0,m_Width,m_Height,GL_RGB,GL_UNSIGNED_BYTE,data);
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);//0�����۵�����
	}
}


