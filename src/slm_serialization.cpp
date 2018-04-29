#include "slm.h"

#include <memory>

namespace SLManager
{
	s_serialization CSerialization::ConvertToByte(CData &Data)
	{
		int iLenKey = 0,
			iLenBuffer = 0,
			iLenMaxBuffer = 0,
			iSizeofPos = 0;


		char *byteBuffer = NULL;
		const char *szKey = NULL;

		e_types eType = ET_NONE;

		s_serialization ssByteBuffer;

		for (CData::iterator it = Data.begin(); it != Data.end(); it++)
		{
			iLenBuffer = 0;

			szKey = ((*it).m_szKey).c_str();
			iLenKey = (strlen(szKey));

			iLenBuffer = sizeof(int); // [len key]
			iLenBuffer += iLenKey; // [key]

			eType = (*it).m_Value.GetType();

			iLenBuffer += sizeof(eType); // [type]

			switch (eType)
			{
				case ET_INT:
				{
					iLenBuffer += sizeof(int); // [int value]
					break;
				}
				case ET_DOUBLE:
				{
					iLenBuffer += sizeof(double); // [double value]
					break;
				}
				case ET_STRING:
				{
					iLenBuffer += sizeof(int); // [len value]

					string Value = (*it).m_Value;
					const char *szValue = Value.c_str();

					int iLenValue = strlen(szValue);

					iLenBuffer += iLenValue; // [string value]
				}
			}

			if (byteBuffer == NULL)
			{
				byteBuffer = new char[iLenBuffer];
			}
			else
			{
				char *byteTemp = new char[iLenMaxBuffer + iLenBuffer];

				memcpy(byteTemp, byteBuffer, iLenMaxBuffer);

				delete byteBuffer;

				byteBuffer = byteTemp;
			}

			iLenMaxBuffer += iLenBuffer;

			if (byteBuffer)
			{
				memcpy(byteBuffer + iSizeofPos, &iLenKey, sizeof(iLenKey));
				iSizeofPos += sizeof(iLenKey);

				memcpy(byteBuffer + iSizeofPos, szKey, iLenKey);
				iSizeofPos += iLenKey;

				memcpy(byteBuffer + iSizeofPos, &eType, sizeof(eType));
				iSizeofPos += sizeof(eType);

				switch (eType)
				{
					case ET_INT:
					{
						int iValue = (*it).m_Value;

						memcpy(&byteBuffer[iSizeofPos], &iValue, sizeof(iValue));
						iSizeofPos += sizeof(iValue);

						break;
					}
					case ET_DOUBLE:
					{
						double dValue = (*it).m_Value;

						memcpy(&byteBuffer[iSizeofPos], &dValue, sizeof(dValue));
						iSizeofPos += sizeof(dValue);

						break;
					}
					case ET_STRING:
					{
						string Value = (*it).m_Value;
						const char *szValue = Value.c_str();

						int iLenValue = strlen(szValue);

						memcpy(&byteBuffer[iSizeofPos], &iLenValue, sizeof(iLenValue));
						iSizeofPos += sizeof(int);

						memcpy(&byteBuffer[iSizeofPos], szValue, iLenValue);
						iSizeofPos += iLenValue;
					}
				}
			}
		}

		ssByteBuffer.iLenBuffer = iLenMaxBuffer;
		ssByteBuffer.byteBuffer = std::auto_ptr<char>(byteBuffer);

		return ssByteBuffer;
	}

	CData CSerialization::ConvertToData(const string &szFileName)
	{
		FILE *fp = fopen(szFileName.c_str(), "rb");

		CData DataBuffer;

		if(fp != NULL)
		{
			fseek(fp, 0, SEEK_SET);

			int iLenKey = 0;
			char *szKey = 0;
			e_types eType = ET_NONE;

			int iValue = 0;
			double dValue = 0;
			char *szValue = 0;

			CVariant Value;

			while(!feof(fp))
			{
				iLenKey = 0;
				fread(&iLenKey, sizeof(iLenKey), 1, fp);

				if(!iLenKey)
				{
					continue;
				}

				szKey = new char(iLenKey);
				fread(szKey, sizeof(char), iLenKey, fp);
				szKey[iLenKey] = '\0';

				fread(&eType, sizeof(eType), 1, fp);

				switch(eType)
				{
					case ET_INT:
					{
						int iValue = 0;
						
						fread(&iValue, sizeof(iValue), 1, fp);

						Value = iValue;

						break;
					}
					case ET_DOUBLE:
					{
						double dValue = 0.0;

						fread(&dValue, sizeof(dValue), 1, fp);

						Value = dValue;

						break;
					}
					case ET_STRING:
					{
						int iLenValue = 0;

						fread(&iLenValue, sizeof(iLenValue), 1, fp);

						if(!iLenValue)
						{
							continue;
						}						

						szValue = new char[iLenValue];
						fread(szValue, sizeof(char), iLenValue, fp);
						szValue[iLenValue] = '\0';

						Value = szValue;
					}
				}

				DataBuffer.Add(szKey, Value);
			}
		}

		return DataBuffer;
	}
}