#include "hzpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	

	void OrthographicCamera::RecalculateViewMatrix()
	{
		//rotation 单位矩阵沿着(0,0,1)轴旋转 m_Rotation
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0,0,1));
		
		/*
			1. 设置相机位置和旋转其实就是确定观察空间的原点和朝向
			2. 模型顶点需要转到观测空间中--如何转换看3-
			3. 假设在blender中建好的模型(Cube 8个顶点在"模型局部空间"坐标为vertices_local）
			4. 确定模型顶点在世界空间中坐标【将模型顶点坐标从局部空间变换到世界空间 该变换是由模型矩阵(Model_Matrix)实现】 
				vertices_world【8个顶点在"世界空间"坐标】 = Model_Matrix * vertices_local
			5. 确定模型顶点在观测空间中坐标【将模型顶点坐标从世界空间变换到观察空间 该变换是由观察矩阵(View_Matrix)实现】
				如何获取View_Matrix
				5.1 设置相机在世界空间中 Position and Rotation 计算得到transform
				5.2 从坐标系转换角度	transform 将世界空间转到观测空间
									transform.inverse 将观测空间转到世界空间 此时相机坐标系与世界坐标系重合,相机永远在(0,0,0)点往-Z 方向看
				5.3 从坐标转换角度   transform.inverse 将模型顶点坐标从世界空间转到观测空间，这就是View_Matrix
				vertices_view【8个顶点在"观测空间"坐标】 = View_Matrix * Model_Matrix * vertices_local
			6. 确定模型顶点在裁剪空间中坐标 【将模型顶点坐标从观察空间变换到裁剪空间 该变换是由投影矩阵(Projection_Matrix)实现】
				vertices_clip【8个顶点在"裁剪空间"坐标】 = Projection_Matrix * View_Matrix * Model_Matrix * vertices_local
		*/
		// 这里只是对相机进行设置，因此只计算 m_ViewMatrix and m_ProjectionMatrix
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
