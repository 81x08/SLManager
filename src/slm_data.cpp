#include "slm.h"

namespace SLManager
{
	CVariant CData::Add(const string &szKey, const CVariant &Value)
	{
		if (IsKey(szKey))
		{
			auto it = find_if(m_Data.begin(), m_Data.end(), [&szKey] (const s_container &Container)
			{
				return szKey == Container.m_szKey;
			});

			(*it).m_Value = Value;

			return (*it).m_Value;
		}
		else
		{
			s_container Container(szKey, Value);

			m_Data.push_back(Container);
		}

		return m_Data.back().m_Value;
	}

	CVariant CData::Get(const string& szKey) const
	{
		if (IsKey(szKey))
		{
			for (vector<s_container>::const_iterator it = m_Data.begin(); it != m_Data.end(); it++)
			{
				if (szKey == (*it).m_szKey)
				{
					return (*it).m_Value;
				}
			}
		}

		return CVariant();
	}

	const int CData::Length() const
	{
		return m_Data.size();
	}

	const bool CData::IsKey(const string &szKey) const
	{
		return any_of(m_Data.begin(), m_Data.end(), [&szKey] (const s_container &Container)
		{
			return szKey == Container.m_szKey;
		});
	}

	const bool CData::Remove(const string& szKey)
	{
		if (IsKey(szKey))
		{
			auto it = remove_if(m_Data.begin(), m_Data.end(), [&szKey] (const s_container &Container)
			{
				return szKey == Container.m_szKey;
			});

			m_Data.erase(it, m_Data.end());

			return true;
		}

		return false;
	}

	void CData::Clear()
	{
		m_Data.clear();
	}
}