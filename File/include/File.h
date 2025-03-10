//--------------------------------------------------------------

//--------------------------------------------------------------

#ifndef FILE_H
#define FILE_H

// Make the assumption of c-char strings, not UNICODE
namespace Azul
{

	class File
	{
	public:

		// Constants for the library
		static const uint32_t MAJOR_VERSION = 2;
		static const uint32_t MINOR_VERSION = 1;

		typedef void* Handle;

		enum class Mode : uint32_t
		{
			READ,
			WRITE,
			READ_WRITE
		};

		enum class Position : uint32_t
		{
			BEGIN,
			CURRENT,
			END
		};

		enum class Error : uint32_t
		{
			SUCCESS,
			OPEN_FAIL,
			CLOSE_FAIL,
			WRITE_FAIL,
			READ_FAIL,
			SEEK_FAIL,
			TELL_FAIL,
			FLUSH_FAIL,
			UNDEFINED
		};

	public:
		static File::Error Open(File::Handle &fh, const char* const fileName, File::Mode mode) noexcept;
		static File::Error Close(File::Handle &fh) noexcept;
		static File::Error Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept;
		static File::Error Read(File::Handle fh, void* const _buffer, const DWORD _size) noexcept;
		static File::Error Seek(File::Handle fh, File::Position location, int offset) noexcept;
		static File::Error Tell(File::Handle fh, DWORD& offset) noexcept;
		static File::Error Flush(File::Handle fh) noexcept;
		static bool IsHandleValid(File::Handle fh) noexcept;

	private:
		static DWORD privGetFileDesiredAccess(File::Mode mode) noexcept;
		static DWORD privGetSeek(File::Position location) noexcept;
	};

}

#endif

// --- End of File ---
