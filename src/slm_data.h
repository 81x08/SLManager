#ifndef _SLM_DATA_H_
#define _SLM_DATA_H_

#include "slm_adapter.h"

namespace SLManager
{
	class CData
	{
	private:
		struct s_container
		{
			s_container(const string &szKey, const CVariant Value) : m_szKey(szKey), m_Value(Value) {}

			string m_szKey;
			CVariant m_Value;
		};

		vector<s_container> m_Data;

	public:
		#pragma region iterator

		typedef vector<s_container>::iterator iterator;

		iterator begin()
		{
			return m_Data.begin();
		}
			
		iterator end()
		{
			return m_Data.end();
		}

		#pragma endregion

		CAdapter operator[] (const string &szKey) { return CAdapter(this, szKey); }

	public:
		CVariant Add(const string &szKey, const CVariant &Value);
		CVariant Get(const string &szKey) const;
		
		const int Length() const;
		const bool IsKey(const string &szKey) const;
		const bool Remove(const string &szKey);
		void Clear();
	};
}

#endif // _SLM_DATA_H_