#pragma once

#include <Eigen/Dense>

// temp file containing some functions
namespace RenderingDEMO
{
	class Math
	{
	public:
		inline static Eigen::Matrix4f GetLookAtMatrix(const Eigen::Vector3f& eyePos, const Eigen::Vector3f& focusPos, const Eigen::Vector3f& upDir)
		{
			Eigen::Matrix4f mat = Eigen::Matrix4f::Identity();

			Eigen::Vector3f up = upDir.normalized();
			Eigen::Vector3f f = (focusPos - eyePos).normalized();
			Eigen::Vector3f s = f.cross(up).normalized();
			Eigen::Vector3f u = s.cross(f).normalized();

			mat(0, 0) = s.x();
			mat(0, 1) = s.y();
			mat(0, 2) = s.z();
			mat(1, 0) = u.x();
			mat(1, 1) = u.y();
			mat(1, 2) = u.z();
			mat(2, 0) = -f.x();
			mat(2, 1) = -f.y();
			mat(2, 2) = -f.z();
			mat(0, 3) = -s.dot(eyePos);
			mat(1, 3) = -u.dot(eyePos);
			mat(2, 3) = f.dot(eyePos);

			return mat;
		}

		inline static Eigen::Matrix4f GetPerspectiveFovMatrix(float fovy, float aspect, float znear, float zfar)
		{
			Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();
			Eigen::Array<float, 1, 1> halfFovy(fovy * 0.5 * 0.0174533f);

			float t = halfFovy.tan()(0, 0);
			float f = zfar / znear - zfar;

			mat(0, 0) = 1.0f / (aspect * t);
			mat(1, 1) = 1.0f / t;
			mat(2, 2) = f;
			mat(3, 2) = -1.0f;
			mat(2, 3) = f * znear;

			return mat;
		}

		inline static Eigen::Matrix4f GetOrthographicMatrix(float width, float height, float znear, float zfar)
		{
			Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();
			float f = 1.0f / (znear - zfar);

			mat(0, 0) = 2.0f / width;
			mat(1, 1) = 2.0f / height;
			mat(2, 2) = f;
			mat(2, 3) = f * znear;
			mat(3, 3) = 1.0f;

			return mat;
		};
	};
}