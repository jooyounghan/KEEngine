#pragma once
#include <cstdio>
#include "EnumMacro.h"
#include "KEConstant.h"
#include "StaticBuffer.h"
#include "TypeTraits.h"
#include "AssertManager.h"

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
		errno_t		_openStatus = 0;
		uint64		_fileSize = 0;

	private:
		errno_t openFile(const char* path, const char* mode, FILE*& fpOut);
		uint64 getFileSize() const;

	public:
		inline bool isValid() const { return _fp != nullptr; }
		inline FILE* getFilePointer() const { return _fp; }
		inline errno_t getOpenStatus() const { return _openStatus; }
		inline uint64 getSize() const { return _fileSize; }
	};

#define VALIDATE_FILE_CORE() if (_fileCore == nullptr) return

    class ReadTag {};

	class BlockRead : public ReadTag 
	{
	public:
		explicit BlockRead(FileCore&) {}
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
		void readAll(IBuffer* buffer, size_t size);

	public:
		void setOffset(size_t offset);
		inline size_t getOffset() const { return _fileOffset; }

	private:
		void updateOffset(long ftellResult);
	};

	class WriteTag {};

	class BlockWrite : public WriteTag
	{
	public:
		explicit BlockWrite(FileCore&) {}
	};

	template<size_t BufferSize = KEConstant::kFileWriteBufferSize>
	class AllowWrite : public WriteTag
	{
	public:
		explicit AllowWrite(FileCore& fileCore);
		~AllowWrite();

	protected:
		FileCore* _fileCore = nullptr;
		StaticBuffer<BufferSize> _writeBuffer;

	public:
		void write(const void* const input, size_t count);
		void flush();
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
		const FileCore& core() const{ return _fileCore; }
		ReadPolicy& reader() { return _readPolicy; }
		WritePolicy& writer() { return _writePolicy; }
		const ReadPolicy& reader() const { return _readPolicy; }
		const WritePolicy& writer() const { return _writePolicy; }

		static_assert(KETrait::IsBaseOf<ReadTag, ReadPolicy>::value, "ReadPolicy must be derived from ReadTag");
		static_assert(KETrait::IsBaseOf<WriteTag, WritePolicy>::value, "WritePolicy must be derived from WriteTag");
	};

	using ReadOnlyFile = File<AllowRead, BlockWrite, EOpenMode::ReadOnly>;
	template<size_t BufferSize = KEConstant::kFileWriteBufferSize>
	using WriteOnlyFile = File<BlockRead, AllowWrite<BufferSize>, EOpenMode::WriteOnly>;

	template<size_t BufferSize = KEConstant::kFileWriteBufferSize>
	using ReadWriteFile = File<AllowRead, AllowWrite<BufferSize>, EOpenMode::ReadWrite>;
}

#include "File.hpp"