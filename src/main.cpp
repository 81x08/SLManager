#include "slm.h"

using namespace SLManager;

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "\tSave Load Manager:\n"
		 << "\t[1] �������� ������\n"
		 << "\t[2] ����������� �����\n"
		 << "\t[3] �������� ��� ������\n"
		 << "\t[4] ����� �������� �� �����\n"
		 << "\t[5] ������� �������� �� �����\n"
		 << "\t[6] ������� ��� ������\n"
		 << "\t[7] ��������� ������\n"
		 << "\t[8] ��������� �� �����\n"
		 << "\t[0] �����\n"
		 << endl;

	CData Data;

	int iPressKey = 0;

	bool bCloseProgram = false;

	while(!bCloseProgram)
	{
		do
		{
			cout << "\n\t*������� ����� ������: ";
			fflush(stdin);
		} while (scanf("%d", &iPressKey) != 1 || (iPressKey < 0 || iPressKey > 8));

		switch(iPressKey)
		{
			case 0:
			{
				bCloseProgram = true;

				break;
			}
			case 1:
			{
				char szKey[MAX_LEN_KEY];

				cout << "\n\t*������� ��������� ������:";

				do
				{
					cout << "\n\t\t{1 �� 3} - [����]: ";
					fflush(stdin);
				} while (scanf("%s", &szKey) != 1);

				e_types eType = ET_NONE;

				cout << "\n\t\t[1 - int]"
					 << "\n\t\t[2 - double]"
					 << "\n\t\t[3 - string]\n";

				do
				{
					cout << "\t\t{2 �� 3} - [��� ��������]: ";
					fflush(stdin);
				} while (scanf("%d", &eType) != 1 || (eType <= ET_NONE || eType > ET_STRING));

				CVariant Value;

				switch(eType)
				{
					case ET_INT:
					{
						int iValue = 0;

						do
						{
							cout << "\n\t\t{3 �� 3} - [�������� �������]: ";
							fflush(stdin);
						} while (scanf("%i", &iValue) != 1);

						Value = iValue;

						break;
					}
					case ET_DOUBLE:
					{
						double dValue = 0;

						do
						{
							cout << "\n\t\t{3 �� 3} - [������������ �������]: ";
							fflush(stdin);
						} while (scanf("%d", &dValue) != 1);

						Value = dValue;

						break;
					}
					case ET_STRING:
					{
						char szValue[MAX_LEN_VALUE];

						do
						{
							cout << "\n\t\t{3 �� 3} - [��������� �������]: ";
							fflush(stdin);
						} while (scanf("%s", &szValue) != 1);

						Value = szValue;

						break;
					}
				}

				Data.Add(szKey, Value);

				break;
			}
			case 2:
			{
				if (!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";

					break;
				}

				int iLength = Data.Length();

				string szFirstKey, szSecondKey;

				CData::iterator itFirst, itSecond;

				for (int i = 0; i < iLength - 1; i++)
				{
					for (int j = 0; j < iLength - i - 1; j++)
					{
						itFirst = (Data.begin() + j);
						itSecond = (Data.begin() + j + 1);

						szFirstKey = (*itFirst).m_szKey;
						szSecondKey = (*itSecond).m_szKey;

						if(szFirstKey[0] > szSecondKey[0])
						{
							iter_swap(itFirst, itSecond);
						}
					}
				}

				cout << "\t\t[!] ������ ���� �������������� �� ��������!\n";

				break;
			}
			case 3:
			{
				if(!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";
					
					break;
				}

				cout << "\t\t[#] ~ .:����:.\t\t.:��������:.\n";

				int iCount = 0;

				string szKey;
				e_types eType = ET_NONE;
				CVariant Value;

				for(CData::iterator it = Data.begin(); it != Data.end(); it++)
				{
					iCount++;

					szKey = (*it).m_szKey;

					Value = (*it).m_Value;

					eType = Value.GetType();

					switch(eType)
					{
						case ET_INT:
						{
							cout << "\t\t[" << iCount << "] ~ [" << szKey << "]\t\t[" << (int)Value << "]\n";

							break;
						}
						case ET_DOUBLE:
						{
							cout << "\t\t[" << iCount << "] ~ [" << szKey << "]\t\t[" << (double)Value << "]\n";

							break;
						}
						case ET_STRING:
						{
							cout << "\t\t[" << iCount << "] ~ [" << szKey << "]\t\t[" << (string)Value << "]\n";

							break;
						}
					}
				}

				break;
			}
			case 4:
			{
				if (!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";

					break;
				}

				char szKey[MAX_LEN_KEY];

				do
				{
					cout << "\t\t������� �������� �����: ";
					fflush(stdin);
				} while (scanf("%s", szKey) != 1);

				if(Data.IsKey(szKey))
				{
					CVariant Value = Data.Get(szKey);

					e_types eType = Value.GetType();

					switch(eType)
					{
						case ET_INT:
						{
							cout << "\t\t[!] �������� �������� �����: " << (int)Value;

							break;
						}
						case ET_DOUBLE:
						{
							cout << "\t\t[!] ������������ �������� �����: " << (double)Value;

							break;
						}
						case ET_STRING:
						{
							cout << "\t\t[!] ��������� �������� �����: " << (string)Value;

							break;
						}
					}
				}
				else
				{
					cout << "\t\t[X] ������ ����� �� �������!";
				}

				cout << endl;

				break;
			}
			case 5:
			{
				if (!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";

					break;
				}

				char szKey[MAX_LEN_KEY];

				do
				{
					cout << "\t\t������� �������� ���������� �����: ";
					fflush(stdin);
				} while (scanf("%s", szKey) != 1);

				if (Data.IsKey(szKey))
				{
					if(Data.Remove(szKey))
					{
						cout << "\t\t[!] ���� ��� ������� �����!";
					}
					else
					{
						cout << "\t\t[X] �� ������� ������� ����!";
					}
				}
				else
				{
					cout << "\t\t[X] ������ ����� �� �������!";
				}

				cout << endl;

				break;
			}
			case 6:
			{
				if (!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";

					break;
				}

				Data.Clear();

				cout << "\t\t[!] ��� ������ ���� �������!\n";

				break;
			}
			case 7:
			{
				if (!Data.Length())
				{
					cout << "\t\t[X] ������ ������ ����!\n";

					break;
				}

				char szFileName[MAX_LEN_FILENAME];

				do
				{
					cout << "\t\t������� �������� �����: ";
					fflush(stdin);
				} while (scanf("%s", &szFileName) != 1);

				FILE *fp = fopen(szFileName, "wb");

				if(fp)
				{
					CSerialization *Serial = new CSerialization();

					if(Serial)
					{
						s_serialization byteBuffer = Serial->ConvertToByte(Data);

						fwrite(byteBuffer.byteBuffer.get(), 1, byteBuffer.iLenBuffer, fp);

						fclose(fp);

						byteBuffer.byteBuffer.reset();

						delete Serial;

						cout << "\t\t[!] ��� ������ ���� �������� � ����!.\n";
					}
					else
					{
						cout << "\t\t[X] �� ��������� ������ �1.\n";
					}
				}
				else
				{
					cout << "\n\t\t[X] �� ������� ������� ����!.\n";
				}
				
				break;
			}
			case 8:
			{
				char szFileName[MAX_LEN_FILENAME];

				do
				{
					cout << "\t\t������� �������� �����: ";
					fflush(stdin);
				} while (scanf("%s", szFileName) != 1);

				CSerialization *Serial = new CSerialization();

				if(Serial)
				{
					CData LoadData = Serial->ConvertToData(szFileName);

					if (LoadData.Length())
					{
						Data = LoadData;
					}

					delete Serial;

					cout << "\t\t[!] ������ �� ����� ���� ������� ���������!\n";
				}
				else
				{
					cout << "\t\t[X] �� ��������� ������ �2.\n";
				}

				break;
			}
		}
	}

	return 0;
}