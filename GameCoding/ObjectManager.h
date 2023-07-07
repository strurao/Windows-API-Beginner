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

	// ���۷����� �޴� ����? ���� ���� ����� �Ƴ��� ���ؼ�!
	const vector<Object*>& GetObjects() { return _objects; }

	template<typename T>
	T* CreateObject()
	{
		// type trait 
		// ������ Ÿ�ӿ� T Ÿ�� ��ü�� object Ÿ������ �ٲٰ�ʹٸ�?
		// static_assert(std::is_convertible<T*, Object*>);

		T* object = new T();
		object->Init();

		return object;
	}

private:
	vector<Object*> _objects;
};

