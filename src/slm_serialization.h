#ifndef _SLM_SERIALIZATION_H_
#define _SLM_SERIALIZATION_H_

namespace SLManager
{
	struct s_serialization
	{
		int iLenBuffer;
		std::auto_ptr<char> byteBuffer;
	};

	class CSerialization
	{
	public:
		s_serialization ConvertToByte(CData &Data);
		CData ConvertToData(const string &szFileName);
	};
}

#endif // _SLM_SERIALIZATION_H_