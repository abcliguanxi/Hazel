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
		//rotation ��λ��������(0,0,1)����ת m_Rotation
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0,0,1));
		
		/*
			1. �������λ�ú���ת��ʵ����ȷ���۲�ռ��ԭ��ͳ���
			2. ģ�Ͷ�����Ҫת���۲�ռ���--���ת����3-
			3. ������blender�н��õ�ģ��(Cube 8��������"ģ�;ֲ��ռ�"����Ϊvertices_local��
			4. ȷ��ģ�Ͷ���������ռ������꡾��ģ�Ͷ�������Ӿֲ��ռ�任������ռ� �ñ任����ģ�;���(Model_Matrix)ʵ�֡� 
				vertices_world��8��������"����ռ�"���꡿ = Model_Matrix * vertices_local
			5. ȷ��ģ�Ͷ����ڹ۲�ռ������꡾��ģ�Ͷ������������ռ�任���۲�ռ� �ñ任���ɹ۲����(View_Matrix)ʵ�֡�
				��λ�ȡView_Matrix
				5.1 �������������ռ��� Position and Rotation ����õ�transform
				5.2 ������ϵת���Ƕ�	transform ������ռ�ת���۲�ռ�
									transform.inverse ���۲�ռ�ת������ռ� ��ʱ�������ϵ����������ϵ�غ�,�����Զ��(0,0,0)����-Z ����
				5.3 ������ת���Ƕ�   transform.inverse ��ģ�Ͷ������������ռ�ת���۲�ռ䣬�����View_Matrix
				vertices_view��8��������"�۲�ռ�"���꡿ = View_Matrix * Model_Matrix * vertices_local
			6. ȷ��ģ�Ͷ����ڲü��ռ������� ����ģ�Ͷ�������ӹ۲�ռ�任���ü��ռ� �ñ任����ͶӰ����(Projection_Matrix)ʵ�֡�
				vertices_clip��8��������"�ü��ռ�"���꡿ = Projection_Matrix * View_Matrix * Model_Matrix * vertices_local
		*/
		// ����ֻ�Ƕ�����������ã����ֻ���� m_ViewMatrix and m_ProjectionMatrix
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
