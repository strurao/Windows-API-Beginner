#pragma once

class Object;

class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	~ObjectManager();

	void Add(Object* object);
	void Remove(Object* object);
	void Clear();

	// 레퍼런스로 받는 이유? 벡터 복사 비용을 아끼기 위해서!
	const vector<Object*>& GetObjects() { return _objects; }

	template<typename T>
	T* CreateObject()
	{
		// type trait 
		// 컴파일 타임에 T 타입 객체를 object 타입으로 바꾸고싶다면?
		// static_assert(std::is_convertible<T*, Object*>);

		T* object = new T();
		object->Init();

		return object;
	}

private:
	vector<Object*> _objects;
};

