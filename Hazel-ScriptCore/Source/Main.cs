using System;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;

namespace Hazel
{
	// C# 
	// struct -> stack allocated
	// class  -> heap allocated(+ GC)
	public struct Vector3
	{
		public float X, Y, Z;

		public static Vector3 Zero => new Vector3(0.0f);

		public Vector3(float scalar)
		{
			X = scalar;
			Y = scalar;
			Z = scalar;
		}

		public Vector3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		public static Vector3 operator+(Vector3 a, Vector3 b)
		{
			return new Vector3(a.X + b.X, a.Y + b.Z, a.Z + b.Z);
		}


		public static Vector3 operator* (Vector3 vector, float scalar)
		{
			return new Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
		}

		//public static operator *=(float scalar)
		//{
		//	return new Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar)
		//}
	}

	public static class InternalCalls
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void NativeLog(string text, int parameter);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetTranslation(ulong entityID, out Vector3 translation);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float TransformComponent_SetTranslation(ulong entityID, ref Vector3 translation);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Input_IsKeyDown(KeyCode keycode);
	}

	public class Entity
	{
		protected Entity() { ID = 0; }
		internal Entity(ulong id)
		{
			ID = id;
		}

		public readonly ulong ID;

		public Vector3 Translation
		{
			get
			{
				InternalCalls.TransformComponent_GetTranslation(ID,out Vector3 translation);
				return translation;
			}
			set
			{
				InternalCalls.TransformComponent_SetTranslation(ID,ref value);
			}
		}
	}

}
