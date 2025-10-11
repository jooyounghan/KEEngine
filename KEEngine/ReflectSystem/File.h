#pragma once
#include <cstdio>
#include "EnumMacro.h"
#include "KEConstant.h"
#include "StaticBuffer.h"
#include "TypeTraits.h"

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

	public:
		errno_t openFile(const char* path, const char* mode, FILE*& fpOut);

	public:
		inline bool isValid() const { return _fp != nullptr; }
		inline FILE* getFilePointer() const { return _fp; }
		inline errno_t getOpenStatus() const { return _openStatus; }
	};

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
		void*		_data = nullptr;
		size_t		_size = 0;

	public:
		void readAll();
		void read(size_t offset, size_t size);

	protected:
		void freeData();

	public:
		inline const void*	getReadData() const { return _data; }
		inline size_t		getReadSize() const { return _size; }
	};

	class WriteTag {};

	class BlockWrite : public WriteTag
	{
	public:
		explicit BlockWrite(FileCore&) {}
	};

	class AllowWrite : public WriteTag
	{
	public:
		explicit AllowWrite(FileCore& fileCore);
		~AllowWrite();

	protected:
		FileCore* _fileCore = nullptr;
		StaticBuffer<KEConstant::kFileWriteBufferSize> _writeBuffer;

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
		ReadPolicy& reader() { return _readPolicy; }
		WritePolicy& writer() { return _writePolicy; }
		const ReadPolicy& reader() const { return _readPolicy; }
		const WritePolicy& writer() const { return _writePolicy; }

		static_assert(KETrait::IsBaseOf<ReadTag, ReadPolicy>::value, "ReadPolicy must be derived from ReadTag");
		static_assert(KETrait::IsBaseOf<WriteTag, WritePolicy>::value, "WritePolicy must be derived from WriteTag");
	};

	using ReadOnlyFile = File<AllowRead, BlockWrite, EOpenMode::ReadOnly>;
	using WriteOnlyFile = File<BlockRead, AllowWrite, EOpenMode::WriteOnly>;
	using ReadWriteFile = File<AllowRead, AllowWrite, EOpenMode::ReadWrite>;
}