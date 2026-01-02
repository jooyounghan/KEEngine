#pragma once
#include "IBuffer.h"

namespace ke
{
	DECLARE_ENUM_CLASS(EOpenMode, uint8,
		ReadOnly,
		WriteOnly,
		ReadWrite
	);

	class FileCore
	{
	public:
		FileCore(const char* path, EOpenMode openMode);
		~FileCore();

	protected:
		FILE*		_fp = nullptr;
		uint64		_fileSize = 0;
		errno_t		_openStatus = 0;

	private:
		errno_t openFile(const char* path, const char* mode, FILE*& fpOut);
		uint64	getFileSize() const;

	public:
		inline bool		isValid() const { return _fp != nullptr; }
		inline FILE*	getFilePointer() const { return _fp; }
		inline errno_t	getOpenStatus() const { return _openStatus; }
		inline uint64	getSize() const { return _fileSize; }
	};

	class ReadTag {};
	class WriteTag {};

	class BlockRead : public ReadTag
	{
	public:
		explicit BlockRead(FileCore&) {}
	};

	class BlockWrite : public WriteTag
	{
	public:
		explicit BlockWrite(FileCore&) {}
	};

	class AllowRead : public ReadTag
	{
	public:
		explicit AllowRead(FileCore& fileCore);

	protected:
		FileCore*	_fileCore = nullptr;
		size_t		_fileOffset = 0;

	public:
		void read(IBuffer* buffer, size_t size);

	public:
		void setOffset(size_t offset);
		inline size_t getOffset() const { return _fileOffset; }

	private:
		void updateOffset(long ftellResult);
	};

	class AllowWrite : public WriteTag
	{
	public:
		explicit AllowWrite(FileCore& fileCore);

	protected:
		FileCore* _fileCore = nullptr;

	public:
		void write(const IBuffer* buffer, size_t count);
	};

	template<typename ReadPolicy, typename WritePolicy, EOpenMode OpenMode>
	class File
	{
	public:
		explicit File(const char* path)
			: _fileCore(path, OpenMode)
			, _readPolicy(_fileCore)
			, _writePolicy(_fileCore)
		{
		}
		~File() = default;

	protected:
		FileCore	_fileCore;
		ReadPolicy	_readPolicy;
		WritePolicy	_writePolicy;

	public:
		const FileCore&		core() const { return _fileCore; }
		ReadPolicy&			reader() { return _readPolicy; }
		WritePolicy&		writer() { return _writePolicy; }
		const ReadPolicy&	reader() const { return _readPolicy; }
		const WritePolicy&	writer() const { return _writePolicy; }

		STATIC_ASSERT_IS_BASE_OF(ReadTag, ReadPolicy);
		STATIC_ASSERT_IS_BASE_OF(WriteTag, WritePolicy);
	};

	using ReadOnlyFile = File<AllowRead, BlockWrite, EOpenMode::ReadOnly>;
	using WriteOnlyFile = File<BlockRead, AllowWrite, EOpenMode::WriteOnly>;
	using ReadWriteFile = File<AllowRead, AllowWrite, EOpenMode::ReadWrite>;
}