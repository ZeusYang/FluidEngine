#pragma once

#include "Matrix4x4.h"

namespace Engine
{
	//!
	//! \brief Quaternion class defined as q = w + xi + yj + zk.
	//!
	template <typename T>
	class Quaternion
	{
	public:
		static_assert(
			std::is_floating_point<T>::value,
			"Quaternion only can be instantiated with floating point types");

		//! Real part.
		T w;
		//!< Imaginary part (i).
		T x;
		//!< Imaginary part (j).
		T y;
		//!< Imaginary part (k).
		T z;

		// MARK: Constructors

		//! Make an identity quaternion.
		Quaternion();

		//! Constructs a quaternion with given elements.
		Quaternion(T newW, T newX, T newY, T newZ);

		//! Constructs a quaternion with given elements.
		Quaternion(const std::initializer_list<T>& lst);

		//! Constructs a quaternion with given rotation axis and angle.
		Quaternion(const Vector3<T>& axis, T angle);

		//! Constructs a quaternion with from and to vectors.
		Quaternion(const Vector3<T>& from, const Vector3<T>& to);

		//! Constructs a quaternion with three basis vectors.
		Quaternion(
			const Vector3<T>& axis0,
			const Vector3<T>& axis1,
			const Vector3<T>& axis2);

		//! Constructs a quaternion with 3x3 rotational matrix.
		explicit Quaternion(const Matrix3x3<T>& m33);

		//! Copy constructor.
		Quaternion(const Quaternion& other);


		// MARK: Basic setters

		//! Sets the quaternion with other quaternion.
		void set(const Quaternion& other);

		//! Sets the quaternion with given elements.
		void set(T newW, T newX, T newY, T newZ);

		//! Sets the quaternion with given elements.
		void set(const std::initializer_list<T>& lst);

		//! Sets the quaternion with given rotation axis and angle.
		void set(const Vector3<T>& axis, T angle);

		//! Sets the quaternion with from and to vectors.
		void set(const Vector3<T>& from, const Vector3<T>& to);

		//! Sets quaternion with three basis vectors.
		void set(
			const Vector3<T>& rotationBasis0,
			const Vector3<T>& rotationBasis1,
			const Vector3<T>& rotationBasis2);

		//! Sets the quaternion with 3x3 rotational matrix.
		void set(const Matrix3x3<T>& matrix);


		// MARK: Basic getters

		//! Returns quaternion with other base type.
		template <typename U>
		Quaternion<U> castTo() const;

		//! Returns normalized quaternion.
		Quaternion normalized() const;


		// MARK: Binary operator methods - new instance = this instance (+) input

		//! Returns this quaternion * vector.
		Vector3<T> mul(const Vector3<T>& v) const;

		//! Returns this quaternion * other quaternion.
		Quaternion mul(const Quaternion& other) const;

		//! Computes the dot product with other quaternion.
		T dot(const Quaternion<T>& other);


		// MARK: Binary operator methods - new instance = input (+) this instance

		//! Returns other quaternion * this quaternion.
		Quaternion rmul(const Quaternion& other) const;

		// MARK: Augmented operator methods - this instance (+)= input

		//! Returns this quaternion *= other quaternion.
		void imul(const Quaternion& other);


		// MARK: Modifiers

		//! Makes this quaternion identity.
		void setIdentity();

		//! Rotate this quaternion with given angle in radians.
		void rotate(T angleInRadians);

		//! Normalizes the quaternion.
		void normalize();


		// MARK: Complex getters

		//! Returns the rotational axis.
		Vector3<T> axis() const;

		//! Returns the rotational angle.
		T angle() const;

		//! Returns the axis and angle.
		void getAxisAngle(Vector3<T>* axis, T* angle) const;

		//! Returns the inverse quaternion.
		Quaternion inverse() const;

		//! Converts to the 3x3 rotation matrix.
		Matrix3x3<T> matrix3() const;

		//! Converts to the 4x4 rotation matrix.
		Matrix4x4<T> matrix4() const;

		//! Returns L2 norm of this quaternion.
		T l2Norm() const;


		// MARK: Setter operators

		//! Assigns other quaternion.
		Quaternion& operator=(const Quaternion& other);

		//! Returns this quaternion *= other quaternion.
		Quaternion& operator*=(const Quaternion& other);


		// MARK: Getter operators

		//! Returns the reference to the i-th element.
		T& operator[](size_t i);

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const;

		//! Returns true if equal.
		bool operator==(const Quaternion& other) const;

		//! Returns true if not equal.
		bool operator!=(const Quaternion& other) const;


		// MARK: Builders

		//! Returns identity matrix.
		static Quaternion makeIdentity();


	};

	//! Computes spherical linear interpolation.
	template <typename T>
	Quaternion<T> slerp(
		const Quaternion<T>& a,
		const Quaternion<T>& b,
		T t);

	//! Returns quaternion q * vector v.
	template <typename T>
	Vector<T, 3> operator*(const Quaternion<T>& q, const Vector<T, 3>& v);

	//! Returns quaternion a times quaternion b.
	template <typename T>
	Quaternion<T> operator*(const Quaternion<T>& a, const Quaternion<T>& b);

	//! Float-type quaternion.
	typedef Quaternion<float> QuaternionF;

	//! Double-type quaternion.
	typedef Quaternion<double> QuaternionD;

	//! ----------------------------------Definition-----------------------------

	// Constructors
	template <typename T>
	inline Quaternion<T>::Quaternion() {
		setIdentity();
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(T newW, T newX, T newY, T newZ) {
		set(newW, newX, newY, newZ);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(const std::initializer_list<T>& lst) {
		set(lst);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(const Vector3<T>& axis, T angle) {
		set(axis, angle);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(const Vector3<T>& from, const Vector3<T>& to) {
		set(from, to);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(
		const Vector3<T>& rotationBasis0,
		const Vector3<T>& rotationBasis1,
		const Vector3<T>& rotationBasis2) {
		set(rotationBasis0, rotationBasis1, rotationBasis2);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(const Matrix3x3<T>& matrix) {
		set(matrix);
	}

	template <typename T>
	inline Quaternion<T>::Quaternion(const Quaternion& other) {
		set(other);
	}


	// Basic setters
	template <typename T>
	inline void Quaternion<T>::set(const Quaternion& other) {
		set(other.w, other.x, other.y, other.z);
	}

	template <typename T>
	inline void Quaternion<T>::set(T newW, T newX, T newY, T newZ) {
		w = newW;
		x = newX;
		y = newY;
		z = newZ;
	}

	template <typename T>
	inline void Quaternion<T>::set(const std::initializer_list<T>& lst) {
		assert(lst.size() == 4);

		auto inputElem = lst.begin();
		w = *inputElem;
		x = *(++inputElem);
		y = *(++inputElem);
		z = *(++inputElem);
	}

	template <typename T>
	inline void Quaternion<T>::set(const Vector3<T>& axis, T angle) {
		static const T eps = std::numeric_limits<T>::epsilon();

		T axisLengthSquared = axis.lengthSquared();

		if (axisLengthSquared < eps) {
			setIdentity();
		}
		else {
			Vector3<T> normalizedAxis = axis.normalized();
			T s = std::sin(angle / 2);

			x = normalizedAxis.x * s;
			y = normalizedAxis.y * s;
			z = normalizedAxis.z * s;
			w = std::cos(angle / 2);
		}
	}

	template <typename T>
	inline void Quaternion<T>::set(const Vector3<T>& from, const Vector3<T>& to) {
		static const T eps = std::numeric_limits<T>::epsilon();

		Vector3<T> axis = from.cross(to);

		T fromLengthSquared = from.lengthSquared();
		T toLengthSquared = to.lengthSquared();

		if (fromLengthSquared < eps ||
			toLengthSquared < eps) {
			setIdentity();
		}
		else {
			T axisLengthSquared = axis.lengthSquared();

			// In case two vectors are exactly the opposite, pick orthogonal vector
			// for axis.
			if (axisLengthSquared < eps) {
				axis = std::get<0>(from.tangential());
			}

			set(from.dot(to), axis.x, axis.y, axis.z);
			w += l2Norm();

			normalize();
		}
	}

	template <typename T>
	inline void Quaternion<T>::set(
		const Vector3<T>& rotationBasis0,
		const Vector3<T>& rotationBasis1,
		const Vector3<T>& rotationBasis2) {
		Matrix3x3<T> matrix3;

		matrix3.setColumn(0, rotationBasis0.normalized());
		matrix3.setColumn(1, rotationBasis1.normalized());
		matrix3.setColumn(2, rotationBasis2.normalized());

		set(matrix3);
	}

	template <typename T>
	inline void Quaternion<T>::set(const Matrix3x3<T>& m) {
		static const T eps = std::numeric_limits<T>::epsilon();
		static const T quater = static_cast<T>(0.25);

		T onePlusTrace = m.trace() + 1;

		if (onePlusTrace > eps) {
			T S = std::sqrt(onePlusTrace) * 2;
			w = quater * S;
			x = (m(2, 1) - m(1, 2)) / S;
			y = (m(0, 2) - m(2, 0)) / S;
			z = (m(1, 0) - m(0, 1)) / S;
		}
		else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2)) {
			T S = std::sqrt(1 + m(0, 0) - m(1, 1) - m(2, 2)) * 2;
			w = (m(2, 1) - m(1, 2)) / S;
			x = quater * S;
			y = (m(0, 1) + m(1, 0)) / S;
			z = (m(0, 2) + m(2, 0)) / S;
		}
		else if (m(1, 1) > m(2, 2)) {
			T S = std::sqrt(1 + m(1, 1) - m(0, 0) - m(2, 2)) * 2;
			w = (m(0, 2) - m(2, 0)) / S;
			x = (m(0, 1) + m(1, 0)) / S;
			y = quater * S;
			z = (m(1, 2) + m(2, 1)) / S;
		}
		else {
			T S = std::sqrt(1 + m(2, 2) - m(0, 0) - m(1, 1)) * 2;
			w = (m(1, 0) - m(0, 1)) / S;
			x = (m(0, 2) + m(2, 0)) / S;
			y = (m(1, 2) + m(2, 1)) / S;
			z = quater * S;
		}
	}


	// Basic getters
	template <typename T>
	template <typename U>
	Quaternion<U> Quaternion<T>::castTo() const {
		return Quaternion<U>(
			static_cast<U>(w),
			static_cast<U>(x),
			static_cast<U>(y),
			static_cast<U>(z));
	}

	//! Returns normalized quaternion.
	template <typename T>
	Quaternion<T> Quaternion<T>::normalized() const {
		Quaternion q(*this);
		q.normalize();
		return q;
	}

	// Binary operator methods - new instance = this instance (+) input
	template <typename T>
	inline Vector3<T> Quaternion<T>::mul(const Vector3<T>& v) const {
		T _2xx = 2 * x * x;
		T _2yy = 2 * y * y;
		T _2zz = 2 * z * z;
		T _2xy = 2 * x * y;
		T _2xz = 2 * x * z;
		T _2xw = 2 * x * w;
		T _2yz = 2 * y * z;
		T _2yw = 2 * y * w;
		T _2zw = 2 * z * w;

		return Vector3<T>(
			(1 - _2yy - _2zz)*v.x + (_2xy - _2zw)*v.y + (_2xz + _2yw)*v.z,
			(_2xy + _2zw)*v.x + (1 - _2zz - _2xx)*v.y + (_2yz - _2xw)*v.z,
			(_2xz - _2yw)*v.x + (_2yz + _2xw)*v.y + (1 - _2yy - _2xx)*v.z);
	}

	template <typename T>
	inline Quaternion<T> Quaternion<T>::mul(const Quaternion& other) const {
		return Quaternion(
			w * other.w - x * other.x - y * other.y - z * other.z,
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w);
	}

	template <typename T>
	inline T Quaternion<T>::dot(const Quaternion<T>& other) {
		return w * other.w + x * other.x + y * other.y + z * other.z;
	}

	// Binary operator methods - new instance = input (+) this instance
	template <typename T>
	inline Quaternion<T> Quaternion<T>::rmul(const Quaternion& other) const {
		return Quaternion(
			other.w * w - other.x * x - other.y * y - other.z * z,
			other.w * x + other.x * w + other.y * z - other.z * y,
			other.w * y - other.x * z + other.y * w + other.z * x,
			other.w * z + other.x * y - other.y * x + other.z * w);
	}


	// Augmented operator methods - this instance (+)= input
	template <typename T>
	inline void Quaternion<T>::imul(const Quaternion& other) {
		*this = mul(other);
	}


	// Modifiers
	template <typename T>
	inline void Quaternion<T>::setIdentity() {
		set(1, 0, 0, 0);
	}

	template <typename T>
	inline void Quaternion<T>::rotate(T angleInRadians) {
		Vector3<T> axis;
		T currentAngle;

		getAxisAngle(&axis, &currentAngle);

		currentAngle += angleInRadians;

		set(axis, currentAngle);
	}

	template <typename T>
	inline void Quaternion<T>::normalize() {
		T norm = l2Norm();

		if (norm > 0) {
			w /= norm;
			x /= norm;
			y /= norm;
			z /= norm;
		}
	}


	// Complex getters
	template <typename T>
	inline Vector3<T> Quaternion<T>::axis() const {
		Vector3<T> result(x, y, z);
		result.normalize();

		if (2 * std::acos(w) < pi<T>()) {
			return result;
		}
		else {
			return -result;
		}
	}

	template <typename T>
	inline T Quaternion<T>::angle() const {
		T result = 2 * std::acos(w);

		if (result < pi<T>()) {
			return result;
		}
		else {
			// Wrap around
			return 2 * pi<T>() - result;
		}
	}

	template <typename T>
	inline void Quaternion<T>::getAxisAngle(Vector3<T>* axis, T* angle) const {
		axis->set(x, y, z);
		axis->normalize();
		*angle = 2 * std::acos(w);

		if (*angle > pi<T>()) {
			// Wrap around
			(*axis) = -(*axis);
			*angle = 2 * pi<T>() - (*angle);
		}
	}

	template <typename T>
	inline Quaternion<T> Quaternion<T>::inverse() const {
		T denom = w * w + x * x + y * y + z * z;
		return Quaternion(w / denom, -x / denom, -y / denom, -z / denom);
	}

	template <typename T>
	inline Matrix3x3<T> Quaternion<T>::matrix3() const {
		T _2xx = 2 * x * x;
		T _2yy = 2 * y * y;
		T _2zz = 2 * z * z;
		T _2xy = 2 * x * y;
		T _2xz = 2 * x * z;
		T _2xw = 2 * x * w;
		T _2yz = 2 * y * z;
		T _2yw = 2 * y * w;
		T _2zw = 2 * z * w;

		Matrix3x3<T> m(
			1 - _2yy - _2zz, _2xy - _2zw, _2xz + _2yw,
			_2xy + _2zw, 1 - _2zz - _2xx, _2yz - _2xw,
			_2xz - _2yw, _2yz + _2xw, 1 - _2yy - _2xx);

		return m;
	}

	template <typename T>
	inline Matrix4x4<T> Quaternion<T>::matrix4() const {
		T _2xx = 2 * x * x;
		T _2yy = 2 * y * y;
		T _2zz = 2 * z * z;
		T _2xy = 2 * x * y;
		T _2xz = 2 * x * z;
		T _2xw = 2 * x * w;
		T _2yz = 2 * y * z;
		T _2yw = 2 * y * w;
		T _2zw = 2 * z * w;

		Matrix4x4<T> m(
			1 - _2yy - _2zz, _2xy - _2zw, _2xz + _2yw, 0,
			_2xy + _2zw, 1 - _2zz - _2xx, _2yz - _2xw, 0,
			_2xz - _2yw, _2yz + _2xw, 1 - _2yy - _2xx, 0,
			0, 0, 0, 1);

		return m;
	}

	template <typename T>
	inline T Quaternion<T>::l2Norm() const {
		return std::sqrt(w * w + x * x + y * y + z * z);
	}

	// Setter operators
	template <typename T>
	inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion& other) {
		set(other);
		return *this;
	}

	template <typename T>
	inline Quaternion<T>& Quaternion<T>::operator*=(const Quaternion& other) {
		imul(other);
		return *this;
	}


	// Getter operators
	template <typename T>
	inline T& Quaternion<T>::operator[](size_t i) {
		return (&w)[i];
	}

	template <typename T>
	inline const T& Quaternion<T>::operator[](size_t i) const {
		return (&w)[i];
	}

	template <typename T>
	bool Quaternion<T>::operator==(const Quaternion& other) const {
		return w == other.w &&
			x == other.x &&
			y == other.y &&
			z == other.z;
	}

	template <typename T>
	bool Quaternion<T>::operator!=(const Quaternion& other) const {
		return w != other.w ||
			x != other.x ||
			y != other.y ||
			z != other.z;
	}

	template <typename T>
	Quaternion<T> Quaternion<T>::makeIdentity() {
		return Quaternion();
	}


	template <typename T>
	inline Quaternion<T> slerp(
		const Quaternion<T>& a,
		const Quaternion<T>& b,
		T t) {
		static const double threshold = 0.01;
		static const T eps = std::numeric_limits<T>::epsilon();

		T cosHalfAngle = dot(a, b);
		T weightA, weightB;

		// For better accuracy, return lerp result when a and b are close enough.
		if (1.0 - std::fabs(cosHalfAngle) < threshold) {
			weightA = 1.0 - t;
			weightB = t;
		}
		else {
			T halfAngle = std::acos(cosHalfAngle);
			T sinHalfAngle = std::sqrt(1 - cosHalfAngle * cosHalfAngle);

			// In case of angle ~ 180, pick middle value.
			// If not, perform slerp.
			if (std::fabs(sinHalfAngle) < eps) {
				weightA = static_cast<T>(0.5);
				weightB = static_cast<T>(0.5);
			}
			else {
				weightA = std::sin((1 - t) * halfAngle) / sinHalfAngle;
				weightB = std::sin(t * halfAngle) / sinHalfAngle;
			}
		}

		return Quaternion<T>(
			weightA * a.w + weightB * b.w,
			weightA * a.x + weightB * b.x,
			weightA * a.y + weightB * b.y,
			weightA * a.z + weightB * b.z);
	}


	// Operator overloadings
	template <typename T>
	inline Vector<T, 3> operator*(const Quaternion<T>& q, const Vector<T, 3>& v) {
		return q.mul(v);
	}

	template <typename T>
	inline Quaternion<T> operator*(const Quaternion<T>& a, const Quaternion<T>& b) {
		return a.mul(b);
	}

}