#pragma once

#include <string>
#include <cstdint>

struct Texture
{
	Texture() {}
	~Texture()
	{
		free(ptr);
		ptr = nullptr;
	}

	uint8_t* ptr = nullptr;
	uint32_t height = 0;		// pixel count
	uint32_t width = 0;			// pixel count
	uint32_t size = 0;			// byte size
	std::string name;

	// Copy constructor and operators are deleted for design reasons.
	// We generally do not want any duplicates of a single asset in memory.
	// So any object that wants texture's data should reference to the once imported instance of it.
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

	Texture& operator=(Texture&& other) noexcept
	{
		if (this == &other) return *this;
		
		this->ptr = other.ptr;
		this->height = other.height;
		this->width = other.width;
		this->size = other.size;
		this->name = std::move(other.name);

		other.ptr = nullptr;
		other.height = 0;
		other.width = 0;
		other.size = 0;

		return *this;
	}
};