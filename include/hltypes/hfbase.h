/// @file
/// @version 2.6
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Provides a base for high level file handling.

#ifndef HLTYPES_FILE_BASE_H
#define HLTYPES_FILE_BASE_H

#include <stdint.h>
#include <stdio.h>

#include "hsbase.h"
#include "hstring.h"

#include "hltypesExport.h"

namespace hltypes
{
	class Stream;

	/// @brief Used for information about files.
	struct hltypesExport FileInfo
	{
		/// @brief File size.
		int64_t size;
		/// @brief The time the file was created.
		int64_t creation_time;
		/// @brief The time the file was last accessed.
		int64_t access_time;
		/// @brief The time the file was last modified.
		int64_t modification_time;

		/// @brief Constructor.
		FileInfo();
		/// @brief Destructor.
		~FileInfo();

	};
	
	template <class T> class Array;
	/// @brief Provides a base for high level file handling.
	/// @note When writing, \\r may be used, but \\r will be removed during read.
	class hltypesExport FileBase : public StreamBase
	{
	public:
		/// @brief Defines file access modes.
		/// @note Windows text read/write modes are not used because they do not work properly in multiplatform environments.
		enum AccessMode
		{
			/// @brief Read-only file mode. ("rb")
			READ,
			/// @brief Write-only file mode. ("wb")
			WRITE,
			/// @brief Write and append file mode. ("ab")
			APPEND,
			/// @brief Read and write file mode. ("r+b")
			READ_WRITE,
			/// @brief Read, write and create file mode. ("w+b")
			READ_WRITE_CREATE,
			/// @brief Read and append file mode. ("a+b")
			READ_APPEND
		};
		
		/// @brief Constructor with filename.
		/// @param[in] filename Name of the file (may include path).
		FileBase(const String& filename);
		/// @brief Basic constructor.
		FileBase();
		/// @brief Destructor.
		~FileBase();

		/// @brief Sets the number of repeated attempts to access a file.
		/// @param[in] value New value.
		static inline void setRepeats(int value) { repeats = value; }
		/// @brief Sets the timeout in miliseconds between repeated attempts to access a file.
		/// @param[in] value New value.
		static inline void setTimeout(float value) { timeout = value; }

		/// @brief Gets the extension of the filename.
		/// @param[in] filename The path.
		/// @return Extension of the filename.
		static String extension_of(const String& path);
		/// @brief Gets the filename with the extension (with the prepended directory path).
		/// @param[in] filename The path.
		/// @return Filename with the extension (with the prepended directory path).
		static String no_extension(const String& path);

	protected:
		/// @brief Current filename.
		String filename;
		/// @brief OS file handle.
		void* cfile;

		/// @brief Gets special descriptor.
		/// @return Special descriptor.
		String _descriptor();

		/// @brief Opens an OS file.
		/// @param[in] filename Name of the file (may include path).
		/// @param[in] access_mode File access mode.
		/// @param[in] repeats Number of repeated attempts to access a file.
		/// @param[in] timeout Timeout in miliseconds between repeated attempts to access a file.
		/// @note If this instance is already working with an opened file handle, that file handle will be closed.
		void _fopen(const String& filename, AccessMode access_mode, int repeats, float timeout);
		/// @brief Closes file.
		void _fclose();
		/// @brief Reads data from the file.
		/// @param[in] src Destination data buffer.
		/// @param[in] count Number of elements to read.
		/// @return Number of bytes read.
		int _fread(void* buffer, int count);
		/// @brief Writes data to the file.
		/// @param[in] src Source data buffer.
		/// @param[in] count Number of elements contained in buffer.
		/// @return Number of bytes written.
		int _fwrite(const void* buffer, int count);
		/// @brief Checks if file is open.
		/// @return True if file is open.
		bool _fis_open();
		/// @brief Gets current position in file.
		/// @return Current position in file.
		int64_t _fposition();
		/// @brief Seeks to position in file.
		/// @param[in] offset Seeking offset in bytes.
		/// @param[in] seek_mode Seeking mode.
		/// @return True if successful.
		bool _fseek(int64_t offset, SeekMode seek_mode = CURRENT);

		/// @brief Checks if a file exists.
		/// @param[in] filename Name of the file.
		/// @param[in] case_sensitive Whether to check case sensitive files if file was not found.
		/// @return True if file exists.
		/// @note Disabling case_sensitive is somewhat costly if the given file is not found at first.
		static bool _fexists(const String& filename, bool case_sensitive = true);

		/// @brief Defines the number of repeated attempts to access a file.
		static int repeats;
		/// @brief Defines the timeout in miliseconds between repeated attempts to access a file.
		static float timeout;

	};

}

/// @brief Alias for simpler code.
typedef hltypes::FileBase hfbase;
/// @brief Alias for simpler code.
typedef hltypes::FileInfo hfinfo;

#endif

