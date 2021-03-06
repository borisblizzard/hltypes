/// @file
/// @version 4.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifndef _MSC_VER // required for memcpy on non-MSVC compilers
#include <string.h>
#include <stdlib.h>
#endif

#include "hfile.h"
#include "hlog.h"
#include "hltypesUtil.h"
#include "hstream.h"

namespace hltypes
{
	Stream::Stream(int initialCapacity) :
		StreamBase(),
		stream(NULL),
		streamSize((int64_t)0),
		streamPosition((int64_t)0),
		capacity((int64_t)hmax(MIN_HSTREAM_CAPACITY, initialCapacity))
	{
		// using malloc because realloc is used later
		this->stream = (unsigned char*)malloc((int)this->capacity);
	}

	Stream::Stream(unsigned char* initialData, int initialDataSize) :
		StreamBase(),
		stream(NULL),
		streamSize((int64_t)initialDataSize),
		streamPosition((int64_t)0),
		capacity((int64_t)initialDataSize)
	{
		// using malloc because realloc is used later
		if (initialDataSize > 0)
		{
			this->stream = (unsigned char*)malloc((int)this->capacity);
			if (this->stream != NULL)
			{
				memcpy(this->stream, initialData, initialDataSize);
			}
			else
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		else
		{
			this->capacity = MIN_HSTREAM_CAPACITY;
			this->stream = (unsigned char*)malloc(MIN_HSTREAM_CAPACITY);
			if (this->stream == NULL)
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		this->_updateDataSize();
	}

	Stream::Stream(unsigned char* initialData, int initialDataSize, int initialCapacity) :
		StreamBase(),
		stream(NULL),
		streamSize((int64_t)initialDataSize),
		streamPosition((int64_t)0),
		capacity((int64_t)hmax(initialCapacity, initialDataSize))
	{
		// using malloc because realloc is used later
		if (initialDataSize > 0)
		{
			this->stream = (unsigned char*)malloc((int)this->capacity);
			if (this->stream != NULL)
			{
				memcpy(this->stream, initialData, initialDataSize);
			}
			else
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		else
		{
			this->capacity = MIN_HSTREAM_CAPACITY;
			this->stream = (unsigned char*)malloc(MIN_HSTREAM_CAPACITY);
			if (this->stream == NULL)
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		this->_updateDataSize();
	}

	Stream::Stream(const Stream& other) :
		StreamBase(),
		stream(NULL),
		streamSize(other.streamSize),
		streamPosition(other.streamPosition),
		capacity(other.capacity)
	{
		// must not used assignment operator here due to internally uninitialized class
		// using malloc because realloc is used later
		if (this->streamSize > (int64_t)0)
		{
			this->stream = (unsigned char*)malloc((int)this->capacity);
			if (this->stream != NULL)
			{
				memcpy(this->stream, (unsigned char*)other, (int)this->streamSize);
			}
			else
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		else
		{
			this->capacity = MIN_HSTREAM_CAPACITY;
			this->stream = (unsigned char*)malloc(MIN_HSTREAM_CAPACITY);
			if (this->stream == NULL)
			{
				hlog::errorf(logTag, "Could not allocate %d bytes of memory for hstream!", this->capacity);
			}
		}
		this->_updateDataSize();
	}

	Stream::~Stream()
	{
		if (this->stream != NULL)
		{
			free(this->stream);
			this->stream = NULL;
		}
	}
	
	void Stream::clear(int newCapacity)
	{
		this->streamSize = 0;
		this->streamPosition = 0;
		this->setCapacity(newCapacity);
		this->_updateDataSize();
	}
	
	bool Stream::setCapacity(int newCapacity)
	{
		newCapacity = hmax(MIN_HSTREAM_CAPACITY, newCapacity); // not allowing less than MIN_HSTREAM_CAPACITY bytes
		if (this->capacity != newCapacity)
		{
			unsigned char* newStream = (unsigned char*)realloc(this->stream, newCapacity);
			if (newStream == NULL) // could not reallocate enough memory
			{
				return false;
			}
			this->stream = newStream;
			this->capacity = newCapacity;
			if (this->streamSize > this->capacity)
			{
				this->streamSize = this->capacity;
				this->_updateDataSize();
			}
		}
		return true;
	}

	int Stream::writeRaw(void* buffer, int count)
	{
		return StreamBase::writeRaw(buffer, count);
	}

	int Stream::writeRaw(StreamBase& stream, int count)
	{
		this->_validate();
		int result = 0;
		if (count > 0)
		{
			this->_tryIncreaseCapacity(count);
			if (count > 0)
			{
				result = stream.readRaw(&this->stream[(int)this->streamPosition], count);
				if (result > 0)
				{
					stream.seek(-result);
					this->streamPosition += result;
					if (this->streamSize < this->streamPosition)
					{
						this->streamSize = this->streamPosition;
						this->_updateDataSize();
					}
				}
			}
		}
		return result;
	}

	int Stream::writeRaw(StreamBase& stream)
	{
		return StreamBase::writeRaw(stream);
	}

	int Stream::writeRaw(Stream& stream, int count)
	{
		return StreamBase::writeRaw(stream, count);
	}

	int Stream::writeRaw(Stream& stream)
	{
		return StreamBase::writeRaw(stream);
	}

	int Stream::prepareManualWriteRaw(int count)
	{
		this->_validate();
		int result = 0;
		if (count > 0)
		{
			this->_tryIncreaseCapacity(count);
			if (count > 0)
			{
				result = count;
				if (this->streamSize < this->streamPosition + count)
				{
					this->streamSize = this->streamPosition + count;
					this->_updateDataSize();
				}
			}
		}
		return result;
	}

	int Stream::fill(unsigned char value, int count)
	{
		this->_validate();
		int result = 0;
		if (count > 0)
		{
			this->_tryIncreaseCapacity(count);
			if (count > 0)
			{
				memset(&this->stream[(int)this->streamPosition], value, count);
				result = count;
				this->streamPosition += count;
				if (this->streamSize < this->streamPosition)
				{
					this->streamSize = this->streamPosition;
					this->_updateDataSize();
				}
			}
		}
		return result;
	}

	bool Stream::truncate(int64_t targetSize)
	{
		this->_validate();
		if (targetSize >= this->size())
		{
			return false;
		}
		this->streamSize = hmax(targetSize, (int64_t)0);
		this->streamPosition = hmin(this->streamPosition, this->streamSize);
		this->_updateDataSize();
		return true;
	}

	const unsigned char& Stream::operator[](int index) const
	{
		if (index < 0)
		{
			index = (int)((int64_t)index + this->streamSize);
		}
		return this->stream[index];
	}

	Stream& Stream::operator=(const Stream& other)
	{
		int64_t otherDataSize = other.dataSize;
		this->streamSize = other.streamSize;
		this->streamPosition = other.streamPosition;
		this->setCapacity((int)other.capacity);
		// using malloc because realloc is used later
		if (otherDataSize > 0)
		{
			if (this->capacity >= otherDataSize)
			{
				memcpy(this->stream, (unsigned char*)other.stream, (int)otherDataSize);
			}
			else
			{
				hlog::errorf(logTag, "Failed cloning stream, capacity < otherDataSize. This is either a realloc failure, or a thread race condition.");
			}
		}
		this->_updateDataSize();
		return (*this);
	}

	Stream::operator char*() const
	{
		return (char*)&this->stream[0];
	}

	Stream::operator const char*() const
	{
		return (const char*)&this->stream[0];
	}

	Stream::operator unsigned char*() const
	{
		return &this->stream[0];
	}

	Stream::operator const unsigned char*() const
	{
		return &this->stream[0];
	}

	void Stream::_updateDataSize()
	{
		this->dataSize = this->streamSize;
	}
	
	int Stream::_read(void* buffer, int count)
	{
		int readSize = (int)hclamp((int64_t)count, (int64_t)0, this->streamSize - this->streamPosition);
		if (readSize > 0)
		{
			memcpy(buffer, &this->stream[this->streamPosition], readSize);
			this->streamPosition += readSize;
		}
		return readSize;
	}

	int Stream::_write(const void* buffer, int count)
	{
		int result = 0;
		if (count > 0)
		{
			this->_tryIncreaseCapacity(count);
			if (count > 0)
			{
				memcpy(&this->stream[(int)this->streamPosition], buffer, count);
				result = count;
				this->streamPosition += result;
				this->streamSize = hmax(this->streamSize, this->streamPosition);
			}
		}
		return result;
	}
	
	bool Stream::_isOpen() const
	{
		return (this->stream != NULL);
	}
	
	int64_t Stream::_position() const
	{
		return this->streamPosition;
	}
	
	bool Stream::_seek(int64_t offset, SeekMode seekMode)
	{
		if (seekMode == SeekMode::Current)
		{
			this->streamPosition = hclamp(this->streamPosition + offset, (int64_t)0, this->streamSize);
		}
		else if (seekMode == SeekMode::Start)
		{
			this->streamPosition = hclamp(offset, (int64_t)0, this->streamSize);
		}
		else if (seekMode == SeekMode::End)
		{
			this->streamPosition = hclamp(this->streamSize + offset, (int64_t)0, this->streamSize);
		}
		return true;
	}
	
	bool Stream::_tryIncreaseCapacity(int& write_size)
	{
		if (write_size > this->capacity - this->streamPosition && !this->setCapacity(hpotCeil((int)(write_size + this->streamPosition))))
		{
			// could not reallocate enough memory, reduce write_size
			write_size = (int)hmax(this->capacity - this->streamPosition, (int64_t)0);
			return false;
		}
		return true;
	}

}
