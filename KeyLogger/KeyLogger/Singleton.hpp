#pragma once
#include <memory>
template <typename T>
class Singleton {
public:
	Singleton() {};
	~Singleton() {};
	static T* get() {
		static std::unique_ptr<T>instance(new T());
		return instance.get();
	}
private:
};